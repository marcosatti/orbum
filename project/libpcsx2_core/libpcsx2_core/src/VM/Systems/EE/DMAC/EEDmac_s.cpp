#include "Common/Global/Globals.h"
#include "Common/Types/ByteMMU/ByteMMU_t.h"
#include "Common/Tables/EEDmacChannelTable.h"
#include "Common/Types/FIFOQueue/FIFOQueue_t.h"

#include "VM/VM.h"
#include "VM/Systems/EE/DMAC/EEDmac_s.h"

#include "Resources/Resources_t.h"
#include "Resources/EE/EE_t.h"
#include "Resources/EE/EECore/EECore_t.h"
#include "Resources/EE/EECore/Types/EECoreCOP0_t.h"
#include "Resources/EE/EECore/Types/EECoreCOP0Registers_t.h"
#include "Resources/EE/DMAC/EEDmac_t.h"
#include "Resources/EE/DMAC/Types/EEDmacChannelRegisters_t.h"
#include "Resources/EE/DMAC/Types/EEDmacChannels_t.h"
#include "Resources/EE/DMAC/Types/EEDmacRegisters_t.h"
#include "Resources/EE/DMAC/Types/EEDMAtag_t.h"

using LogicalMode_t = EEDmacChannelTable::LogicalMode_t;
using Direction_t = EEDmacChannelTable::Direction_t;
using PhysicalMode_t = EEDmacChannelTable::PhysicalMode_t;

EEDmac_s::EEDmac_s(VM * vm) :
	VMSystem_t(vm, Context_t::EEDmac),
	mChannel(nullptr),
	mDMAtag(0, 0)
{
	// Set resource pointer variables.
	mDMAC = getVM()->getResources()->EE->DMAC;
	mEEByteMMU = getVM()->getResources()->EE->MMU;
}

void EEDmac_s::initialise()
{
	// Reset channels.
	for (auto& channel : mDMAC->CHANNELS)
	{
		if (channel->CHCR != nullptr) channel->CHCR->initialise();
		if (channel->MADR != nullptr) channel->MADR->initialise();
		if (channel->QWC != nullptr) channel->QWC->initialise();
		if (channel->TADR != nullptr) channel->TADR->initialise();
		if (channel->ASR0 != nullptr) channel->ASR0->initialise();
		if (channel->ASR1 != nullptr) channel->ASR1->initialise();
		if (channel->SADR != nullptr) channel->SADR->initialise();
		if (channel->FIFOQueue != nullptr) channel->FIFOQueue->initialise();
	}

	// Reset DMAC.
	mDMAC->CTRL->initialise();
	mDMAC->STAT->initialise();
	mDMAC->PCR->initialise();
	mDMAC->SQWC->initialise();
	mDMAC->RBSR->initialise();
	mDMAC->RBOR->initialise();
	mDMAC->STADR->initialise();
	mDMAC->ENABLER->initialise();
	mDMAC->ENABLEW->initialise();
}

int EEDmac_s::step(const ClockSource_t clockSource, const int ticksAvailable)
{
#if ACCURACY_SKIP_TICKS_ON_NO_WORK
	// Used to skip ticks. If no channel is enabled for transfers, then all of the ticks will be consumed.
	bool workDone = false;
#endif

	// Check if DMA transfers are enabled. If not, DMAC has nothing to do.
	if (mDMAC->CTRL->getFieldValue(getContext(), EEDmacRegister_CTRL_t::Fields::DMAE) > 0)
	{
		// Check for any pending/started DMA transfers and perform transfer if enabled.
		for (auto& channel : mDMAC->CHANNELS)
		{
			// Set channel resource context.
			mChannel = channel.get();

			// Check if channel is enabled for transfer.
			if (mChannel->CHCR->getFieldValue(getContext(), EEDmacChannelRegister_CHCR_t::Fields::STR) > 0)
			{
				switch (mChannel->CHCR->getLogicalMode(getContext()))
				{
				case LogicalMode_t::NORMAL:
				{
#if ACCURACY_SKIP_TICKS_ON_NO_WORK
					workDone |= transferNormal();
#else
					transferNormal();
#endif
					break;
				}
				case LogicalMode_t::CHAIN:
				{
#if ACCURACY_SKIP_TICKS_ON_NO_WORK
					workDone |= transferChain();
#else
					transferChain();
#endif   
					break;
				}
				case LogicalMode_t::INTERLEAVED:
				{
#if ACCURACY_SKIP_TICKS_ON_NO_WORK
					workDone |= transferInterleaved();
#else
					transferInterleaved();
#endif
					break;
				}
				default:
				{
					throw std::runtime_error("Could not determine EE DMAC channel logical mode.");
				}
				}
			}
		}

		// Check for D_STAT interrupt bit status, send interrupt to EE Core (INT1 line) if not masked.
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

int EEDmac_s::transferData() const
{
	// Determine the runtime direction of data flow by checking the CHCR.DIR field.
	Direction_t direction = mChannel->CHCR->getDirection(getContext());

	// Get the main memory or SPR address we are reading or writing from. 
	// NOTE: The mask of 0x1FFFFFF0 comes from PCSX2, also in my own testing, the PS2 OS sets MADR to illegal addresses, such as 0x3xxxxxxx. This is to do with cache modes, but they are left un-implemented.
	const bool SPRFlag = (mChannel->MADR->getFieldValue(getContext(), EEDmacChannelRegister_MADR_t::Fields::SPR) != 0);
	const u32 PhysicalAddressOffset = mChannel->MADR->getFieldValue(getContext(), EEDmacChannelRegister_MADR_t::Fields::ADDR) & 0x1FFFFFF0;

	// If we are using the from/toSPR channels (channel ID's 8 or 9), then we need to get the SPR address, and take a different code path. 
	// Within the these channels MADR.SPR is always 0 on these channels (have to use the SADR register as the SPR address).
	if (mChannel->getChannelID() == 8 || mChannel->getChannelID() == 9)
	{
		// We are doing a mem->SPR or SPR->mem, use both MADR and SADR registers.
		// NOTE: The mask of 0x3FF0 comes from PCSX2. I have not personally tested this, but assume it is required.
		//       This mask restricts the address to the 16 kB address range and makes the address qword aligned.
		const u32 SPRPhysicalAddressOffset = mChannel->SADR->readWord(getContext()) & 0x3FF0;

		if (direction == Direction_t::FROM)
		{
			u128 packet = readQwordMemory(SPRPhysicalAddressOffset, true);
			writeQwordMemory(PhysicalAddressOffset, false, packet);

#if DEBUG_LOG_EE_DMAC_XFERS
			log(Debug, "EE DMAC Read u128 channel %s, SPRAddr = 0x%08llX, w0 = 0x%08X, w1 = 0x%08X, w2 = 0x%08X, w3 = 0x%08X -> MemAddr = 0x%08X", 
				mChannel->getInfo()->mMnemonic, SPRPhysicalAddressOffset, packet.UW[0], packet.UW[1], packet.UW[2], packet.UW[3], PhysicalAddressOffset);
#endif
		}
		else if (direction == Direction_t::TO)
		{
			u128 packet = readQwordMemory(PhysicalAddressOffset, false);
			writeQwordMemory(SPRPhysicalAddressOffset, true, packet);
			
#if DEBUG_LOG_EE_DMAC_XFERS
			log(Debug, "EE DMAC Write u128 channel %s, SPRAddr = 0x%08llX, w0 = 0x%08X, w1 = 0x%08X, w2 = 0x%08X, w3 = 0x%08X <- MemAddr = 0x%08X",
				mChannel->getInfo()->mMnemonic, SPRPhysicalAddressOffset, packet.UW[0], packet.UW[1], packet.UW[2], packet.UW[3], PhysicalAddressOffset);
#endif
		}
		else
		{
			throw std::runtime_error("EE DMAC could not determine transfer direction (SPR)! Please debug.");
		}

		// Increment the MADR & SADR register by a qword, and decrement the QWC register by a qword.
		mChannel->MADR->increment(getContext());
		mChannel->SADR->increment(getContext());
		mChannel->QWC->decrement(getContext());

		return 1;
	}
	else
	{
		// Else transfer data normally.
		if (direction == Direction_t::FROM)
		{
			// Check if channel does not have data ready (at least 1 qword) - need to try again next cycle.
			if (mChannel->FIFOQueue->getCurrentSize() < Constants::NUMBER_BYTES_IN_QWORD)
				return 0;

			u128 packet = mChannel->FIFOQueue->readQword(getContext());
			writeQwordMemory(PhysicalAddressOffset, SPRFlag, packet);

#if DEBUG_LOG_EE_DMAC_XFERS
			log(Debug, "EE DMAC Read u128 channel %s, w0 = 0x%08X, w1 = 0x%08X, w2 = 0x%08X, w3 = 0x%08X -> MemAddr = 0x%08X", 
				mChannel->getInfo()->mMnemonic, packet.UW[0], packet.UW[1], packet.UW[2], packet.UW[3], PhysicalAddressOffset);
#endif
		}
		else if (direction == Direction_t::TO)
		{
			// Check if channel is full (we need at least 1 qword space) - need to try again next cycle.
			if (mChannel->FIFOQueue->getCurrentSize() > (mChannel->FIFOQueue->getMaxSize() - Constants::NUMBER_BYTES_IN_QWORD))
				return 0;

			u128 packet = readQwordMemory(PhysicalAddressOffset, SPRFlag);
			mChannel->FIFOQueue->writeQword(getContext(), packet);

#if DEBUG_LOG_EE_DMAC_XFERS
			log(Debug, "EE DMAC Write u128 channel %s, w0 = 0x%08X, w1 = 0x%08X, w2 = 0x%08X, w3 = 0x%08X <- MemAddr = 0x%08X",
				mChannel->getInfo()->mMnemonic, packet.UW[0], packet.UW[1], packet.UW[2], packet.UW[3], PhysicalAddressOffset);
#endif
		}
		else
		{
			throw std::runtime_error("EE DMAC could not determine transfer direction! Please debug.");
		}

		// Increment the MADR register by a qword, and decrement the QWC register by a qword.
		mChannel->MADR->increment(getContext());
		mChannel->QWC->decrement(getContext());

		return 1;
	}
}

void EEDmac_s::setStateSuspended() const
{
	// Emit the interrupt status bit.
	mDMAC->STAT->setFieldValue(getContext(), EEDmacRegister_STAT_t::Fields::CHANNEL_CIS_KEYS[mChannel->getChannelID()], 1);

	// Change CHCR.STR to 0.
	mChannel->CHCR->setFieldValue(getContext(), EEDmacChannelRegister_CHCR_t::Fields::STR, 0);
}

void EEDmac_s::setStateFailedTransfer() const
{
	throw std::runtime_error("failed transfer not implemented.");
}

bool EEDmac_s::transferNormal()
{
	// Check the QWC register, make sure that size > 0 in order to start transfer.
	if (mChannel->QWC->readWord(getContext()) == 0)
	{
		setStateFailedTransfer();
		return false;
	}

	// Check for drain stall control conditions, and skip cycle if the data is not ready (when the next slice is not ready).
	if (isDrainStallControlOn() && isDrainStallControlWaiting())
	{
		setDMACStallControlSIS();
		return false;
	}

	// Transfer a data unit (128-bits). If no data was transfered, try again next cycle.
	int count = transferData();
	if (count == 0)
		return false;

	// Check for source stall control conditions, and update D_STADR if required.
	if (isSourceStallControlOn())
		setDMACStallControlSTADR();

	// Check if QWC == 0 (transfer completed), in which case stop transferring and update status.
	if (mChannel->QWC->readWord(getContext()) == 0)
		setStateSuspended();

	// Transfer successful, done for this cycle.
	return true;
}

bool EEDmac_s::transferChain()
{
	// Check the QWC register, make sure that size > 0 for a transfer to occur (otherwise read a tag).
	if (mChannel->QWC->readWord(getContext()) > 0)
	{
		// Check for drain stall control conditions (including if we are in "refs" tag), and skip cycle if the data is not ready.
		if (isDrainStallControlOn() && isDrainStallControlWaiting() && mChannel->CHCR->mTagStallControl)
		{
			setDMACStallControlSIS();
			return false;
		}

		// Transfer a data unit (128-bits). If no data was transfered, try again next cycle.
		int count = transferData();
		if (count == 0)
			return false;

		// Check for source stall control conditions (including if we are in "cnts" tag id), and update D_STADR if required.
		if (isSourceStallControlOn() && mChannel->CHCR->mTagStallControl)
			setDMACStallControlSTADR();

		// If QWC is now 0, update the tag flags state, and check for suspend conditions.
		if (mChannel->QWC->readWord(getContext()) == 0)
		{
			// Check if we need to emit an interrupt due to tag (done after chain transfer has completed). Dependent on the tag IRQ flag set and the CHCR.TIE bit set.
			if (mChannel->CHCR->getFieldValue(getContext(), EEDmacChannelRegister_CHCR_t::Fields::TIE) > 0 && mChannel->CHCR->mTagIRQ)
				setStateSuspended();

			// Check if we need to exit based on tag flag (set by "end", "ret", etc).
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
		// Check if we are in source or dest chain mode, read in a tag (to mDMAtag), and perform action based on tag id (which will set MADR, QWC, etc).
		// TODO: Do check based off the CHCR.DIR (direction) set or based on constant properties listed on pg 42 of EE Users Manual? Works both ways, but direction is less code.
		switch (mChannel->CHCR->getDirection(getContext())) 
		{
		case Direction_t::TO:
		{
			// Read in a tag, exit early if we need to wait for data.
			if (!readChainSourceTag())
				return false;

			// Execute the tag handler
			(this->*SRC_CHAIN_INSTRUCTION_TABLE[mDMAtag.getID()])();
			break;
		}
		case Direction_t::FROM:
		{
			// Read in a tag, exit early if we need to wait for data.
			if (!readChainDestTag())
				return false;

			// Execute the tag handler
			(this->*DST_CHAIN_INSTRUCTION_TABLE[mDMAtag.getID()])();
			break;
		}
		default:
		{
			throw std::runtime_error("EE DMAC could not determine chain mode context.");
		}
		}

		// Set the IRQ flag if the DMAtag.IRQ bit is set.
		mChannel->CHCR->mTagIRQ = (mDMAtag.getIRQ() > 0);

		// Set CHCR.TAG based upon the DMA tag read (bits 16-31).
		mChannel->CHCR->setFieldValue(getContext(), EEDmacChannelRegister_CHCR_t::Fields::TAG, mDMAtag.getTAG());

		// Transfer successful, done for this cycle.
		return true;
	}
}

bool EEDmac_s::transferInterleaved()
{
	throw std::runtime_error("EE DMAC interleave mode not fully implemented (fix me up).");

	/*
	// Check the QWC register, make sure that size > 0 in order to start transfer.
	if (mChannel->QWC->readWord(getContext()) == 0)
	{
		setStateFailedTransfer();
		return;
	}

	// Data of size D_SQWC.TQWC is transferred first, then data of size D_SQWC.SQWC is skipped, until Dn_QWC is reached.
	if (!mChannel->isInterleaveInSkipMode())
	{
		// Transfer a data unit (128-bits). If no data was transfered, try again next cycle.
		u32 dataCount = transferData();
		if (!dataCount)
		{
			return;
		}
	}
	else
	{
		// Skip data by incrementing the channel MADR.
		mChannel->MADR->increment();
	}
		
	// Increment the interleaved count.
	mChannel->incrementInterleaveCount();

	// Check the interleaved mode (transferring/skipping), and change mInterleavedSkipState if required, based on mInterleavedCountState.
	if (isInterleaveLimitReached())
	{
		mChannel->toggleInterleaveMode();
	}

	// Check if QWC == 0 (transfer completed), in which case stop transferring and update status.
	if (mChannel->QWC->readWord(getContext()) == 0)
	{
		setStateSuspended();
	}
	*/
}

void EEDmac_s::handleInterruptCheck() const
{
	auto& COP0 = getVM()->getResources()->EE->EECore->COP0;
	auto& D_STAT = mDMAC->STAT;

	// Set the interrupt line if there was a condition set, otherwise clear the interrupt line.
	if (D_STAT->isInterruptPending(getContext()))
		COP0->Cause->setIRQLine(getContext(), 3);
	else
		COP0->Cause->clearIRQLine(getContext(), 3);
}

bool EEDmac_s::isSourceStallControlOn() const
{
	if (mChannel->CHCR->getDirection(getContext()) == Direction_t::FROM)
	{
		const u32 STS = mDMAC->CTRL->getFieldValue(getContext(), EEDmacRegister_CTRL_t::Fields::STS);
		if (mChannel->getChannelID() == EEDmacChannelTable::getSTSChannelIndex(STS))
		{
			return true;
		}
	}

	return false;
}

bool EEDmac_s::isDrainStallControlOn() const
{
	if (mChannel->CHCR->getDirection(getContext()) == Direction_t::TO)
	{
		auto STD = mDMAC->CTRL->getFieldValue(getContext(), EEDmacRegister_CTRL_t::Fields::STD);
		if (mChannel->getChannelID() == EEDmacChannelTable::getSTDChannelIndex(STD))
		{
			return true;
		}
	}

	return false;
}

void EEDmac_s::setDMACStallControlSTADR() const
{
	u32 MADR = mChannel->MADR->getFieldValue(getContext(), EEDmacChannelRegister_MADR_t::Fields::ADDR);
	mDMAC->STADR->setFieldValue(getContext(), EEDmacRegister_STADR_t::Fields::ADDR, MADR);
}

void EEDmac_s::setDMACStallControlSIS() const
{
	// Set the STAT.SIS bit.
	mDMAC->STAT->setFieldValue(getContext(), EEDmacRegister_STAT_t::Fields::SIS, 1);
}

bool EEDmac_s::isDrainStallControlWaiting() const
{
	if (mChannel->CHCR->getDirection(getContext()) == Direction_t::TO)
	{
		const u32 MADR = mChannel->MADR->getFieldValue(getContext(), EEDmacChannelRegister_MADR_t::Fields::ADDR);
		const u32 STADR = mDMAC->STADR->getFieldValue(getContext(), EEDmacRegister_STADR_t::Fields::ADDR);

		if ((MADR + 8) > STADR)
		{
			return true;
		}
	}

	return false;
}

u128 EEDmac_s::readQwordMemory(const u32 bytePhysicalAddress, const bool SPRAccess) const
{
	// Read mem[addr] or spr[addr] (128-bits). SPR is at offset 0x70000000.
	if (SPRAccess)
		return mEEByteMMU->readQword(getContext(), 0x70000000 + bytePhysicalAddress);
	else
		return mEEByteMMU->readQword(getContext(), bytePhysicalAddress);
}

void EEDmac_s::writeQwordMemory(const u32 bytePhysicalAddress, const bool SPRAccess, const u128 data) const
{
	// Write mem[addr] or spr[addr] (128-bits). SPR is at offset 0x70000000.
	if (SPRAccess)
		mEEByteMMU->writeQword(getContext(), 0x70000000 + bytePhysicalAddress, data);
	else
		mEEByteMMU->writeQword(getContext(), bytePhysicalAddress, data);
}

bool EEDmac_s::readChainSourceTag()
{
	// Check first if we need to transfer the tag - return false if the channel queue is full.
	if (mChannel->CHCR->getFieldValue(getContext(), EEDmacChannelRegister_CHCR_t::Fields::TTE) > 0)
	{
		if (mChannel->FIFOQueue->getCurrentSize() > (mChannel->FIFOQueue->getMaxSize() - Constants::NUMBER_BYTES_IN_QWORD))
			return false;
	}

	// Get tag memory address (TADR).
	const u32 TADR = mChannel->TADR->getFieldValue(getContext(), EEDmacChannelRegister_TADR_t::Fields::ADDR);
	const bool SPRFlag = (mChannel->TADR->getFieldValue(getContext(), EEDmacChannelRegister_TADR_t::Fields::SPR) != 0);

	// Read EE tag (128-bits) from TADR.
	const u128 tag = readQwordMemory(TADR, SPRFlag);

	// Set mDMAtag based upon the LSB 64-bits of tag.
	mDMAtag = EEDMAtag_t(tag.UW[0], tag.UW[1]);
	
#if DEBUG_LOG_EE_DMAC_TAGS
	log(Debug, "EE tag (source chain mode) read on channel %s, TADR = 0x%08X. Tag0 = 0x%08X, Tag1 = 0x%08X, TTE = %d.",
		mChannel->getInfo()->mMnemonic, mChannel->TADR->readWord(getContext()), mDMAtag.getTag0(), mDMAtag.getTag1(), mChannel->CHCR->getFieldValue(getContext(), EEDmacChannelRegister_CHCR_t::Fields::TTE));
	mDMAtag.logDebugAllFields();
#endif
	
	// Check if we need to transfer the tag.
	if (mChannel->CHCR->getFieldValue(getContext(), EEDmacChannelRegister_CHCR_t::Fields::TTE) > 0)
	{
		// Setup new tag with LSB 64-bits filled with data from MSB 64-bits of tag read from before, then send.
		u128 sendTag = u128(tag.UW[2], tag.UW[3], 0, 0);
		mChannel->FIFOQueue->writeQword(getContext(), sendTag);
	}

	return true;
}

bool EEDmac_s::readChainDestTag()
{
	// Check first if there is data available.
	if (mChannel->FIFOQueue->getCurrentSize() < Constants::NUMBER_BYTES_IN_QWORD)
		return false;

	// Read tag from channel FIFO.
	const u128 tag = mChannel->FIFOQueue->readQword(getContext());

	// Set mDMAtag based upon the first 2 words read from the channel.
	mDMAtag = EEDMAtag_t(tag.UW[0], tag.UW[1]);

#if DEBUG_LOG_EE_DMAC_TAGS
	log(Debug, "EE tag (dest chain mode) read on channel %s. Tag0 = 0x%08X, Tag1 = 0x%08X, TTE = %d.", 
		mChannel->getInfo()->mMnemonic, mDMAtag.getTag0(), mDMAtag.getTag1(), mChannel->CHCR->getFieldValue(getContext(), EEDmacChannelRegister_CHCR_t::Fields::TTE));
	mDMAtag.logDebugAllFields();
#endif
	
	// Check if we need to transfer the tag.
	if (mChannel->CHCR->getFieldValue(getContext(), EEDmacChannelRegister_CHCR_t::Fields::TTE) > 0)
	{
		throw std::runtime_error("EE DMAC dest chain mode TTE set but not implemented.");
	}
	
	return true;
}
