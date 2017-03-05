#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/PhysicalMMU/PhysicalMMU_t.h"
#include "Common/Tables/IOPDmacChannelTable/IOPDmacChannelTable.h"
#include "Common/Types/FIFOQueue/FIFOQueue_t.h"

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

using ChannelProperties_t = IOPDmacChannelTable::ChannelProperties_t;
using LogicalMode_t = IOPDmacChannelTable::LogicalMode_t;
using Direction_t = IOPDmacChannelTable::Direction_t;

IOPDmac_s::IOPDmac_s(VM * vm) :
	VMSystem_s(vm, System_t::IOPDmac),
	mChannel(nullptr),
	mDMAtag()
{
	// Set resource pointer variables.
	mDMAC = getVM()->getResources()->IOP->DMAC;
	mINTC = getVM()->getResources()->IOP->INTC;
	mIOPPhysicalMMU = getVM()->getResources()->IOP->PhysicalMMU;
}

IOPDmac_s::~IOPDmac_s()
{
}

int IOPDmac_s::step(const ClockSource_t clockSource, const int ticksAvailable)
{
	// Check if DMA transfers are enabled. If not, DMAC has nothing to do.
	if (mDMAC->GCTRL->readWord(RAW) > 0)
	{
		// Run through each channel enabled. Note there is no master DMAC enable bit to check - only the individual channels.
		for (auto& channel : mDMAC->CHANNELS)
		{
			// Set channel resource context.
			mChannel = channel.get();

			// Check if channel is enabled for transfer (both from PCR and the CHCR).
			if (isChannelEnabled())
			{
				switch (mChannel->CHCR->getLogicalMode())
				{
				case LogicalMode_t::NORMAL_BURST:
				{
					// Normal/burst mode.
					transferNormalBurst();
					break;
				}
				case LogicalMode_t::NORMAL_SLICE:
				{
					// Normal/slice mode.
					transferNormalSlice();
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
					transferChain();
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
	
	return 1;
}

void IOPDmac_s::transferNormalBurst()
{
	// Transfer a data unit (32-bits). If no data was transfered, try again next cycle.
	if (!transferData())
		return;

	// Check if there is no more data to process (check BS), in which case stop transferring and update status.
	if (mChannel->BCR->isFinished(false))
		setStateSuspended();
}

void IOPDmac_s::transferNormalSlice()
{
	// Transfer a data unit (32-bits). If no data was transfered, try again next cycle.
	if (!transferData())
		return;

	// Check if there is no more data to process (check BS and BA), in which case stop transferring and update status.
	if (mChannel->BCR->isFinished(true))
		setStateSuspended();
}

void IOPDmac_s::transferChain()
{
	// Check the transfer size, make sure that size > 0 for a transfer to occur (otherwise read a tag). 
	// TODO: Chain mode has its own transfer length counter? Not sure how this is meant to be counted through BCR register. See wisi's docs later..
	if (mChannel->CHCR->mTagTransferLength > 0)
	{
		// Transfer a data unit (32-bits). If no data was transfered, try again next cycle. 
		int count = transferData();
		if (!count)
			return;

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
	}
	else
	{
		// Check if we are in source or dest chain mode, read in a tag (to mDMAtag), and perform action based on tag id (which will set MADR, BCR, etc).
		// TODO: Do check based off the CHCR.DIR (direction) set or based on constant properties? Works both ways, but direction is less code.
		switch (mChannel->CHCR->getDirection())
		{
		case Direction_t::TO:
		{
			// Read in a tag, exit early if we need to wait for data.
			if (!readChainSourceTag())
				return;
			
			break;
		}
		case Direction_t::FROM:
		{
			// Read in a tag, exit early if we need to wait for data.
			if (!readChainDestTag())
				return;
			
			break;
		}
		default:
		{
			throw std::runtime_error("IOP DMAC could not determine chain mode context.");
		}
		}

		// Set the IRQ flag if the DMAtag.IRQ bit is set.
		mChannel->CHCR->mTagIRQ = (mDMAtag.getIRQ() > 0);
	}
}

void IOPDmac_s::handleInterruptCheck() const
{
	// Check ICR0 and ICR1 for interrupt status, else clear the master interrupt and INTC bits.
	if (mDMAC->ICR0->isInterruptPending() || mDMAC->ICR1->isInterruptPending())
		mINTC->STAT->setFieldValue(IOPIntcRegister_STAT_t::Fields::DMA, 1);
	else
	{
		mDMAC->ICR0->setFieldValue(IOPDmacRegister_ICR0_t::Fields::MasterInterrupt, 0);
		mINTC->STAT->setFieldValue(IOPIntcRegister_STAT_t::Fields::DMA, 0);
	}
}

int IOPDmac_s::transferData() const
{
	// Determine the direction of data flow. 
	Direction_t direction = mChannel->CHCR->getDirection();

	// Get the main memory address.
	const u32 physicalAddress = mChannel->MADR->readWord(RAW);

	// Transfer data to or from the FIFO queue.
	if (direction == Direction_t::FROM)
	{
		// Check if channel does not have data ready - need to try again next cycle.
		if (mChannel->mFIFOQueue->isEmpty())
			return 0;

		u32 packet = mChannel->mFIFOQueue->readWord(RAW);
		writeDataMemory(physicalAddress, packet);

		log(Debug, "IOP DMAC Read u32 channel %s, value = 0x%08X -> MemAddr = 0x%08X", mChannel->getChannelProperties()->Mnemonic, packet, physicalAddress);
	}
	else if (direction == Direction_t::TO)
	{
		// Check if channel is full - need to try again next cycle.
		if (mChannel->mFIFOQueue->isFull())
			return 0;

		u32 packet = readDataMemory(physicalAddress);
		mChannel->mFIFOQueue->writeWord(RAW, packet);

		log(Debug, "IOP DMAC Write u32 channel %s, value = 0x%08X <- MemAddr = 0x%08X", mChannel->getChannelProperties()->Mnemonic, packet, physicalAddress);
	}
	else
	{
		throw std::runtime_error("IOP DMAC could not determine direction! Please debug.");
	}

	// Increment or decrement (depending on CHCR.MAS) the MADR register by a word.
	if (mChannel->CHCR->getFieldValue(IOPDmacChannelRegister_CHCR_t::Fields::MAS) == 0)
		mChannel->MADR->increment();
	else
		mChannel->MADR->decrement();

	// Update number of word units left (BCR).
	mChannel->BCR->decrement();

	return 1;
}

void IOPDmac_s::setStateSuspended() const
{
	// Stop channel.
	mChannel->CHCR->setFieldValue(IOPDmacChannelRegister_CHCR_t::Fields::Start, 0);

	// Emit interrupt stat bit (use ICR0 or ICR1 based on channel index).
	if (mChannel->getChannelID() < 7)
		mDMAC->ICR0->setFieldValue(IOPDmacRegister_ICR0_t::Fields::CHANNEL_TCI_KEYS[mChannel->getChannelID()], 1);
	else
		mDMAC->ICR1->setFieldValue(IOPDmacRegister_ICR1_t::Fields::CHANNEL_TCI_KEYS[mChannel->getChannelID() % 7], 1);
}

bool IOPDmac_s::isChannelEnabled() const
{
	if (mChannel->CHCR->getFieldValue(IOPDmacChannelRegister_CHCR_t::Fields::Start) > 0)
	{
		if (mChannel->getChannelID() < 7)
			return (mDMAC->PCR0->getFieldValue(IOPDmacRegister_PCR0_t::Fields::CHANNEL_ENABLE_KEYS[mChannel->getChannelID()]) > 0);
		else
			return (mDMAC->PCR1->getFieldValue(IOPDmacRegister_PCR1_t::Fields::CHANNEL_ENABLE_KEYS[mChannel->getChannelID() % 7]) > 0);
	}
	else
	{
		return false;
	}
}

bool IOPDmac_s::isChannelIRQEnabled() const
{
	return (mDMAC->ICR1->getFieldValue(IOPDmacRegister_ICR1_t::Fields::CHANNEL_IQE_KEYS[mChannel->getChannelID()]) > 0);
}

u32 IOPDmac_s::readDataMemory(u32 PhysicalAddressOffset) const
{
	return mIOPPhysicalMMU->readWord(RAW, PhysicalAddressOffset);
}

void IOPDmac_s::writeDataMemory(u32 PhysicalAddressOffset, u32 data) const
{
	mIOPPhysicalMMU->writeWord(RAW, PhysicalAddressOffset, data);
}

bool IOPDmac_s::readChainSourceTag()
{
	// Check for the EE tag transfer option (CHCR bit 8 aka "chopping enable" set), and return early if there is no space in the FIFO available.
	if (mChannel->CHCR->getFieldValue(IOPDmacChannelRegister_CHCR_t::Fields::CE) > 0)
	{
		if (mChannel->mFIFOQueue->isFull())
			return false;
	}

	// Read tag (2 x 32-bits) from TADR, and increment.
	const u32 TADR = mChannel->TADR->readWord(RAW);
	const u32 tag0 = readDataMemory(TADR);
	const u32 tag1 = readDataMemory(TADR + 0x4);
	mChannel->TADR->increment(0x8);

	// Set mDMAtag based upon the first 2 words read from the channel.
	mDMAtag.setValue(tag0, tag1);

	log(Debug, "IOP tag (source chain mode) read on channel %s. Tag0 = 0x%08X, Tag1= 0x%08X, XFER_EE_TAG = %d.", mChannel->getChannelProperties()->Mnemonic, tag0, tag1, mChannel->CHCR->getFieldValue(IOPDmacChannelRegister_CHCR_t::Fields::CE));
	mDMAtag.logDebugAllFields();

	// Set the tag transfer properties.
	mChannel->CHCR->mTagExit = mDMAtag.getERT() > 0;
	mChannel->CHCR->mTagIRQ = mDMAtag.getIRQ() > 0;
	mChannel->MADR->writeWord(RAW, mDMAtag.getADDR());

	// Set the transfer length.
	// The maximum supported length is 1MB - 16 bytes, rounded up to the nearest qword alignment (from PCSX2).
	// TODO: there is also a 'cache mode' part, but not sure where (also from PCSX2).
	mChannel->CHCR->mTagTransferLength = (mDMAtag.getLength() + 3) & 0xFFFFC;

	// Check for the EE tag transfer option (CHCR bit 8 aka "chopping enable" set).
	if (mChannel->CHCR->getFieldValue(IOPDmacChannelRegister_CHCR_t::Fields::CE) > 0)
	{
		// Read EE chain tag (LSB 64-bits) from TADR and increment
		const u32 tag2 = readDataMemory(TADR + 0x8);
		const u32 tag3 = readDataMemory(TADR + 0xC);
		mChannel->TADR->increment(0x8);

		// Pack tag words into a u128 for sending. The MSB 64-bits are filled with 0's. Then write to the channel FIFO.
		u128 EEtag = u128(tag2, tag3, 0, 0);
		mChannel->mFIFOQueue->writeQword(RAW, EEtag);
	}

	return true;
}

bool IOPDmac_s::readChainDestTag()
{
	// Check first if there is data available.
	if (mChannel->mFIFOQueue->isEmpty())
		return false;

	// Read tag (2 x 32-bits) from channel FIFO.
	const u32 tag0 = mChannel->mFIFOQueue->readWord(RAW);
	const u32 tag1 = mChannel->mFIFOQueue->readWord(RAW);

	// Set mDMAtag based upon the first 2 words read from the channel.
	mDMAtag.setValue(tag0, tag1);
	
	log(Debug, "IOP tag (dest chain mode) read on channel %s. Tag0 = 0x%08X, Tag1 = 0x%08X, XFER_EE_TAG = %d.", mChannel->getChannelProperties()->Mnemonic, tag0, tag1, mChannel->CHCR->getFieldValue(IOPDmacChannelRegister_CHCR_t::Fields::CE));
	mDMAtag.logDebugAllFields();

	// Set the tag transfer properties.
	mChannel->CHCR->mTagExit = mDMAtag.getERT() > 0;
	mChannel->CHCR->mTagIRQ = mDMAtag.getIRQ() > 0;
	mChannel->MADR->writeWord(RAW, mDMAtag.getADDR());

	// Set the transfer length.
	// The maximum supported length is 1MB - 16 bytes (from PCSX2). TODO: no qword alignment? Might not matter for the IOP side.
	// TODO: there is also a 'cache mode' part, but not sure where (also from PCSX2).
	mChannel->CHCR->mTagTransferLength = (mDMAtag.getLength() + 3) & 0xFFFFC;

	// Check for the EE tag transfer option (CHCR bit 8 aka "chopping enable" set).
	// TODO: implement properly... I think wisi's docs meant this was only for source chain mode? Not sure. PCSX2 doesn't do this at all.
	if (mChannel->CHCR->getFieldValue(IOPDmacChannelRegister_CHCR_t::Fields::CE) > 0)
	{
		// Read EE chain tag (LSB 64-bits) from channel FIFO. This is important or else the FIFO order will get messed up.
		const u32 tag2 = mChannel->mFIFOQueue->readWord(RAW);
		const u32 tag3 = mChannel->mFIFOQueue->readWord(RAW);

		// Check first that the tag size is above 0 - dont bother doing anything (first 16 bits).
		if ((tag2 & 0xFFFF) > 0)
		{
			// Pack tag words into a u128 for sending. The MSB 64-bits are filled with 0's.
			u128 EEtag = u128(tag2, tag3, 0, 0);
			throw std::runtime_error("IOP DMAC had chain mode (dest) with CHCR.8 set - send tag to EE not implemented.");
		}
		else
		{
			log(Warning, "IOP DMAC dest chain mode EE tag had size of zero - not sending.");
		}
	}

	return true;
}
