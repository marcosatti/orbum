#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/ByteMMU/ByteMMU_t.h"
#include "Common/Tables/IOPDmacChannelTable.h"
#include "Common/Types/FIFOQueue/FIFOQueue32_t.h"

#include "VM/VM.h"
#include "VM/Systems/IOP/DMAC/IOPDmac_s.h"

#include "Resources/Resources_t.h"
#include "Resources/IOP/IOP_t.h"
#include "Resources/IOP/INTC/IOPIntc_t.h"
#include "Resources/IOP/INTC/Types/IOPIntcRegisters_t.h"
#include "Resources/IOP/DMAC/IOPDmac_t.h"
#include "Resources/IOP/DMAC/Types/IOPDmacChannelRegisters_t.h"
#include "Resources/IOP/DMAC/Types/IOPDmacChannels_t.h"
#include "Resources/IOP/DMAC/Types/IOPDmacRegisters_t.h"

using LogicalMode_t = IOPDmacChannelTable::LogicalMode_t;
using Direction_t = IOPDmacChannelTable::Direction_t;

IOPDmac_s::IOPDmac_s(VM * vm) :
	VMSystem_s(vm, System_t::IOPDmac),
	mChannel(nullptr),
	mDMAtag(0, 0)
{
	// Set resource pointer variables.
	mDMAC = getVM()->getResources()->IOP->DMAC;
	mINTC = getVM()->getResources()->IOP->INTC;
	mIOPByteMMU = getVM()->getResources()->IOP->MMU;
}

int IOPDmac_s::step(const ClockSource_t clockSource, const int ticksAvailable)
{
#if ACCURACY_SKIP_TICKS_ON_NO_WORK
	// Used to skip ticks. If no channel is enabled for transfers, then all of the ticks will be consumed.
	bool workDone = false;
#endif

	// Check if DMA transfers are enabled. If not, DMAC has nothing to do.
	if (mDMAC->GCTRL->readWord(getContext()) > 0)
	{
		// Run through each channel enabled. Note there is no master DMAC enable bit to check - only the individual channels.
		for (auto& channel : mDMAC->CHANNELS)
		{
			// Set channel resource context.
			mChannel = channel.get();

			// Check if channel is enabled for transfer (both from PCR and the CHCR).
			if (isChannelEnabled())
			{
				switch (mChannel->CHCR->getLogicalMode(getContext()))
				{
				case LogicalMode_t::NORMAL_BURST:
				{
					// Normal/burst mode.
#if ACCURACY_SKIP_TICKS_ON_NO_WORK
					workDone |= transferNormalBurst();
#else
					transferNormalBurst();
#endif
					break;
				}
				case LogicalMode_t::NORMAL_SLICE:
				{
					// Normal/slice mode.
#if ACCURACY_SKIP_TICKS_ON_NO_WORK
					workDone |= transferNormalSlice();
#else
					transferNormalSlice();
#endif
					break;
				}
				case LogicalMode_t::LINKEDLIST:
				{
					// Linked list mode.
					throw std::runtime_error("IOP DMAC linked list mode not implemented.");
				}
				case LogicalMode_t::CHAIN:
				{
					// Chain mode (listed as undefined in nocash PSX docs), based of wisi's docs.
#if ACCURACY_SKIP_TICKS_ON_NO_WORK
					workDone |= transferChain();
#else
					transferChain();
#endif
					break;
				}
				default:
				{
					throw std::runtime_error("Could not determine IOP DMAC channel logical mode.");
				}
				}
			}
		}

		// Check for ICR0 or ICR1 interrupt bit status, send interrupt to IOP INTC (IRQ 3) if not masked.
		handleInterruptCheck();
	}
	
	// DMAC has completed 1 cycle.
#if ACCURACY_SKIP_TICKS_ON_NO_WORK
	if (!workDone)
		return ticksAvailable;
	else
		return 1;
#else
	return 1;
#endif
}

bool IOPDmac_s::transferNormalBurst()
{
	// Transfer a data unit (32-bits). If no data was transfered, try again next cycle.
	int count = transferData();
	if (count == 0)
		return false;

	// Check if there is no more data to process (check BS), in which case stop transferring and update status.
	if (mChannel->BCR->isFinished(false))
		setStateSuspended();

	// Transfer successful, done for this cycle.
	return true;
}

bool IOPDmac_s::transferNormalSlice()
{
	// Transfer a data unit (32-bits). If no data was transfered, try again next cycle.
	int count = transferData();
	if (count == 0)
		return false;

	// Check if there is no more data to process (check BS and BA), in which case stop transferring and update status.
	if (mChannel->BCR->isFinished(true))
		setStateSuspended();
	
	// Transfer successful, done for this cycle.
	return true;
}

bool IOPDmac_s::transferChain()
{
	// Check the transfer size, make sure that size > 0 for a transfer to occur (otherwise read a tag). 
	// TODO: Chain mode has its own transfer length counter? Not sure how this is meant to be counted through BCR register. See wisi's docs later..
	if (mChannel->CHCR->mTagTransferLength > 0)
	{
		// Transfer a data unit (32-bits). If no data was transfered, try again next cycle. 
		int count = transferData();
		if (count == 0)
			return false;

		// Decrement the chain mode transfer length (as we are not using BCR).
		mChannel->CHCR->mTagTransferLength -= count;
		
		// If transfer length is now 0, update the tag flags state, and check for suspend conditions.
		if (mChannel->CHCR->mTagTransferLength == 0)
		{
			// Check if we need to emit an interrupt due to tag (done after packet transfer has completed). Dependent on the tag IRQ flag set and the CHCR.TIE bit set.
			// TODO: verify whats meant to happen... suspend or just emit interrupt?
			if (isChannelIRQEnabled() && mChannel->CHCR->mTagIRQ)
				setStateSuspended();

			// Check if we need to exit based on tag flag (set by ERT flag within DMA tag).
			if (mChannel->CHCR->mTagExit)
				setStateSuspended();

			// Reset the tag flag state (done regardless of the above on every finished tag transfer).
			mChannel->CHCR->resetChainState();
		}

		// Transfer successful, done for this cycle.
		return true;
	}
	else
	{
		// Check if we are in source or dest chain mode, read in a tag (to mDMAtag), and perform action based on tag id (which will set MADR, BCR, etc).
		// TODO: Do check based off the CHCR.DIR (direction) set or based on constant properties? Works both ways, but direction is less code.
		switch (mChannel->CHCR->getDirection(getContext()))
		{
		case Direction_t::TO:
		{
			// Read in a tag, exit early if we need to wait for data.
			if (!readChainSourceTag())
				return false;
			
			break;
		}
		case Direction_t::FROM:
		{
			// Read in a tag, exit early if we need to wait for data.
			if (!readChainDestTag())
				return false;
			
			break;
		}
		default:
		{
			throw std::runtime_error("IOP DMAC could not determine chain mode context.");
		}
		}

		// Set the tag flag properties.
		mChannel->CHCR->mTagExit = mDMAtag.getERT() > 0;
		mChannel->CHCR->mTagIRQ = mDMAtag.getIRQ() > 0;

		// Set the tag data transfer address.
		mChannel->MADR->writeWord(getContext(), mDMAtag.getADDR());

		// Chain mode setup was successful, done for this cycle.
		return true;
	}
}

void IOPDmac_s::handleInterruptCheck() const
{
	// Check ICR0 and ICR1 for interrupt status, else clear the master interrupt and INTC bits.
	if (mDMAC->ICR0->isInterruptPending(getContext()) || mDMAC->ICR1->isInterruptPending(getContext()))
		mINTC->STAT->setFieldValue(getContext(), IOPIntcRegister_STAT_t::Fields::DMA, 1);
	else
	{
		mDMAC->ICR0->setFieldValue(getContext(), IOPDmacRegister_ICR0_t::Fields::MasterInterrupt, 0);
		mINTC->STAT->setFieldValue(getContext(), IOPIntcRegister_STAT_t::Fields::DMA, 0);
	}
}

int IOPDmac_s::transferData() const
{
	// Determine the direction of data flow. 
	Direction_t direction = mChannel->CHCR->getDirection(getContext());

	// Get the main memory address.
	const u32 physicalAddress = mChannel->MADR->readWord(getContext());

	// Transfer data to or from the FIFO queue.
	if (direction == Direction_t::FROM)
	{
		// Check if channel does not have data ready (need at least a single u32) - need to try again next cycle.
		if (mChannel->mFIFOQueue->getCurrentSize() < 1)
		{
			//log(Warning, "IOP DMAC tried to read u32 from FIFO queue (channel %s), but it was empty! Trying again next cycle, but there could be a problem somewhere else!", mChannel->getChannelInfo()->mMnemonic);
			return 0;
		}

		u32 packet = mChannel->mFIFOQueue->readWord(getContext());
		writeDataMemory32(physicalAddress, packet);

		//log(Debug, "IOP DMAC Read u32 channel %s, value = 0x%08X -> MemAddr = 0x%08X", mChannel->getChannelInfo()->mMnemonic, packet, physicalAddress);
	}
	else if (direction == Direction_t::TO)
	{
		// Check if channel is full (we need at least a single u32 space) - need to try again next cycle.
		if (mChannel->mFIFOQueue->getCurrentSize() > (mChannel->mFIFOQueue->getMaxSize() - 1))
		{
			//log(Warning, "IOP DMAC tried to write u32 to FIFO queue (channel %s), but it was full! Trying again next cycle, but there could be a problem somewhere else!", mChannel->getChannelInfo()->mMnemonic);
			return 0;
		}

		u32 packet = readDataMemory32(physicalAddress);
		mChannel->mFIFOQueue->writeWord(getContext(), packet);

		//log(Debug, "IOP DMAC Write u32 channel %s, value = 0x%08X <- MemAddr = 0x%08X", mChannel->getChannelInfo()->mMnemonic, packet, physicalAddress);
	}
	else
	{
		throw std::runtime_error("IOP DMAC could not determine direction! Please debug.");
	}

	// Increment or decrement (depending on CHCR.MAS) the MADR register by a word.
	if (mChannel->CHCR->getFieldValue(getContext(), IOPDmacChannelRegister_CHCR_t::Fields::MAS) == 0)
		mChannel->MADR->increment(getContext());
	else
		mChannel->MADR->decrement(getContext());

	// Update number of word units left (BCR).
	mChannel->BCR->decrement();

	return 1;
}

void IOPDmac_s::setStateSuspended() const
{
	// Stop channel.
	mChannel->CHCR->setFieldValue(getContext(), IOPDmacChannelRegister_CHCR_t::Fields::Start, 0);

	// Emit interrupt stat bit (use ICR0 or ICR1 based on channel index).
	if (mChannel->getChannelID() < 7)
		mDMAC->ICR0->setFieldValue(getContext(), IOPDmacRegister_ICR0_t::Fields::CHANNEL_TCI_KEYS[mChannel->getChannelID()], 1);
	else
		mDMAC->ICR1->setFieldValue(getContext(), IOPDmacRegister_ICR1_t::Fields::CHANNEL_TCI_KEYS[mChannel->getChannelID() % 7], 1);
}

bool IOPDmac_s::isChannelEnabled() const
{
	if (mChannel->CHCR->getFieldValue(getContext(), IOPDmacChannelRegister_CHCR_t::Fields::Start) > 0)
	{
		if (mChannel->getChannelID() < 7)
			return (mDMAC->PCR0->getFieldValue(getContext(), IOPDmacRegister_PCR0_t::Fields::CHANNEL_ENABLE_KEYS[mChannel->getChannelID()]) > 0);
		else
			return (mDMAC->PCR1->getFieldValue(getContext(), IOPDmacRegister_PCR1_t::Fields::CHANNEL_ENABLE_KEYS[mChannel->getChannelID() % 7]) > 0);
	}
	else
	{
		return false;
	}
}

bool IOPDmac_s::isChannelIRQEnabled() const
{
	return (mDMAC->ICR1->getFieldValue(getContext(), IOPDmacRegister_ICR1_t::Fields::CHANNEL_IQE_KEYS[mChannel->getChannelID()]) > 0);
}

u32 IOPDmac_s::readDataMemory32(u32 PhysicalAddressOffset) const
{
	return mIOPByteMMU->readWord(getContext(), PhysicalAddressOffset);
}

void IOPDmac_s::writeDataMemory32(u32 PhysicalAddressOffset, u32 data) const
{
	mIOPByteMMU->writeWord(getContext(), PhysicalAddressOffset, data);
}

u128 IOPDmac_s::readDataMemory128(u32 PhysicalAddressOffset) const
{
	return mIOPByteMMU->readQword(getContext(), PhysicalAddressOffset);
}

bool IOPDmac_s::readChainSourceTag()
{
	// Check for space (u128) in the FIFO queue, which depends on if the tag transfer (TTE) option is on (CHCR bit 8 aka "chopping enable" set). See below.
	if (mChannel->CHCR->getFieldValue(getContext(), IOPDmacChannelRegister_CHCR_t::Fields::CE) > 0)
	{
		if (mChannel->mFIFOQueue->getCurrentSize() > (mChannel->mFIFOQueue->getMaxSize() - Constants::NUMBER_WORDS_IN_QWORD))
		{
			//log(Warning, "IOP DMAC tried to write EE tag (u128) to FIFO queue (%s), but it was full! Trying again next cycle, but there could be a problem somewhere else!", mChannel->getChannelInfo()->mMnemonic);
			return false;
		}
	}

	// Get tag memory address (TADR).
	const u32 TADR = mChannel->TADR->readWord(getContext());

	// Read EE tag (128-bits) from TADR.
	const u128 tag = readDataMemory128(TADR);

	// Set mDMAtag based upon the LSB 64-bits of tag.
	mDMAtag = IOPDMAtag_t(tag.UW[0], tag.UW[1]);

	log(Debug, "IOP tag (source chain mode) read on channel %s, TADR = 0x%08X. Tag0 = 0x%08X, Tag1 = 0x%08X, TTE = %d.", 
		mChannel->getInfo()->mMnemonic, TADR, mDMAtag.getTag0(), mDMAtag.getTag1(), mChannel->CHCR->getFieldValue(getContext(), IOPDmacChannelRegister_CHCR_t::Fields::CE));
	mDMAtag.logDebugAllFields();

	// Check if we need to transfer the tag (CHCR bit 8 aka "chopping enable" set).
	if (mChannel->CHCR->getFieldValue(getContext(), IOPDmacChannelRegister_CHCR_t::Fields::CE) > 0)
	{
		// Setup new tag with LSB 64-bits filled with data from MSB 64-bits of tag read from before, then send.
		u128 sendTag = u128(tag.UW[2], tag.UW[3], 0, 0);
		mChannel->mFIFOQueue->writeQword(getContext(), sendTag);
	}

	// Set tag transfer length.
	// The maximum supported length is 1MB - 16 bytes, rounded up to the nearest qword alignment (from PCSX2).
	// TODO: qword alignment is forced for source chain mode, but not dest - does it matter? Probably doesn't need it, when source chain is enforced anyway (ie: will never receive data that isn't qword aligned).
	// TODO: there is also a 'cache mode' part, but not sure where (also from PCSX2). It shouldn't need to be implemented anyway.
	mChannel->CHCR->mTagTransferLength = (mDMAtag.getLength() + 3) & 0xFFFFC;

	// Increment TADR.
	mChannel->TADR->increment(getContext(), 0x10);

	// TODO: look into the tag transfer enable (TTE) option not set (CHCR bit 8 aka "chopping enable" set).
	//       PCSX2 does not implement anything at all, but wisi might know something. SIF0 has this bit set always. For now, left unimplemented.
	if (mChannel->CHCR->getFieldValue(getContext(), IOPDmacChannelRegister_CHCR_t::Fields::CE) == 0)
		throw std::runtime_error("IOP DMAC source chain mode had TTE set to 0 - what is meant to happen?");

	return true;
}

bool IOPDmac_s::readChainDestTag()
{
	// Check first if there is tag data available.
	if (mChannel->mFIFOQueue->getCurrentSize() < Constants::NUMBER_WORDS_IN_QWORD)
	{
		//log(Warning, "IOP DMAC tried to read tag (u128) from FIFO queue (%s), but it was empty! Trying again next cycle, but there could be a problem somewhere else!", mChannel->getChannelInfo()->mMnemonic);
		return false;
	}

	// Read tag (u128) from channel FIFO. Only first 2 u32's are used for the IOP.
	const u128 tag = mChannel->mFIFOQueue->readQword(getContext());

	// Set mDMAtag based upon the first 2 words read from the channel.
	mDMAtag = IOPDMAtag_t(tag.UW[0], tag.UW[1]);
	
	log(Debug, "IOP tag (dest chain mode) read on channel %s. Tag0 = 0x%08X, Tag1 = 0x%08X, TTE = %d.", 
		mChannel->getInfo()->mMnemonic, mDMAtag.getTag0(), mDMAtag.getTag1(), mChannel->CHCR->getFieldValue(getContext(), IOPDmacChannelRegister_CHCR_t::Fields::CE));
	mDMAtag.logDebugAllFields();

	// Set tag transfer length.
	// The maximum supported length is 1MB - 16 bytes.
	// TODO: qword alignment is forced for source chain mode, but not dest - does it matter? Probably doesn't need it, when source chain is enforced anyway (ie: will never receive data that isn't qword aligned).
	// TODO: there is also a 'cache mode' part, but not sure where (also from PCSX2). It shouldn't need to be implemented anyway.
	// TODO: check if "& 0xFFFFC" is needed, or if its just PCSX2 specific.
	mChannel->CHCR->mTagTransferLength = mDMAtag.getLength();

	// TODO: look into the tag transfer enable (TTE) option not set (CHCR bit 8 aka "chopping enable").
	//       PCSX2 does not implement anything at all, but wisi might know something. SIF1 has this bit set always. For now, left unimplemented.
	if (mChannel->CHCR->getFieldValue(getContext(), IOPDmacChannelRegister_CHCR_t::Fields::CE) == 0)
		throw std::runtime_error("IOP DMAC dest chain mode had TTE set to 0 - what is meant to happen?");

	return true;
}
