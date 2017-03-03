#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/PhysicalMMU/PhysicalMMU_t.h"
#include "Common/Tables/EEDmacChannelTable/EEDmacChannelTable.h"
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
#include "Resources/EE/DMAC/Types/DMAtag_t.h"

using ChannelProperties_t = EEDmacChannelTable::ChannelProperties_t;
using Direction_t = EEDmacChannelTable::Direction_t;
using PhysicalMode_t = EEDmacChannelTable::PhysicalMode_t;

EEDmac_s::EEDmac_s(VM * vm) :
	VMSystem_s(vm, System_t::EEDmac),
	mChannel(nullptr),
	mDMAtag()
{
	// Set resource pointer variables.
	mDMAC = getVM()->getResources()->EE->DMAC;
	mEEPhysicalMMU = getVM()->getResources()->EE->PhysicalMMU;
}

EEDmac_s::~EEDmac_s()
{
}

int EEDmac_s::step(const ClockSource_t clockSource, const int ticksAvailable)
{
	// Check if DMA transfers are enabled. If not, DMAC has nothing to do.
	if (mDMAC->CTRL->getFieldValue(EEDmacRegister_CTRL_t::Fields::DMAE) > 0)
	{
		// Check for any pending/started DMA transfers and perform transfer if enabled.
		for (auto& channel : mDMAC->CHANNELS)
		{
			// Set channel resource context.
			mChannel = channel.get();

			// Check if channel is enabled for transfer.
			if (mChannel->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::STR) > 0)
			{
				switch (mChannel->CHCR->getLogicalMode())
				{
				case LogicalMode_t::NORMAL:
				{
					transferNormal();
					break;
				}
				case LogicalMode_t::CHAIN:
				{
					transferChain();       
					break;
				}
				case LogicalMode_t::INTERLEAVED:
				{
					transferInterleaved(); 
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
	return 1;
}

u32 EEDmac_s::transferData() const
{
	// Determine the direction of data flow. If set to BOTH (true for VIF1 and SIF2 channels), get the runtime direction by checking the CHCR.DIR field.
	Direction_t direction = mChannel->CHCR->getDirection();

	// Get the main memory or SPR address we are reading or writing from. 
	// NOTE: The mask of 0x1FFFFFF0 comes from PCSX2, also in my own testing, the PS2 OS sets MADR to illegal addresses, such as 0x3xxxxxxx.
	//       I can only assume that the DMAC hardware corrects this value. The resulting address will also be qword aligned and restricted to the 'system' memory region.
	const bool SPRFlag = (mChannel->MADR->getFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR) != 0);
	const u32 PhysicalAddressOffset = mChannel->MADR->getFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR) & 0x1FFFFFF0;

	// If we are using the from/toSPR channels (channel ID's 8 or 9), then we need to get the SPR address, and take a different code path. 
	// Within the these channels MADR.SPR is always 0 on these channels (have to use the SADR register as the SPR address).
	if (mChannel->getChannelID() == 8 || mChannel->getChannelID() == 9)
	{
		// We are doing a mem->SPR or SPR->mem, use both MADR and SADR registers.
		// NOTE: The mask of 0x3FF0 comes from PCSX2. I have not personally tested this, but assume it is required.
		//       This mask restricts the address to the 16 kB address range and makes the address qword aligned.
		const u32 SPRPhysicalAddressOffset = mChannel->SADR->readWord(RAW) & 0x3FF0;

		if (direction == Direction_t::FROM)
		{
			u128 packet = readDataMemory(SPRPhysicalAddressOffset, true);
			writeDataMemory(PhysicalAddressOffset, false, packet);

			log(Debug, "EE DMAC Read u128 channel %s, SPRAddr = 0x%08llX, valueLo = 0x%016llX, valueHi = 0x%016X -> MemAddr = 0x%08X", 
				mChannel->getChannelProperties()->Mnemonic, SPRPhysicalAddressOffset, packet.lo, packet.hi, PhysicalAddressOffset);
		}
		else if (direction == Direction_t::TO)
		{
			u128 packet = readDataMemory(PhysicalAddressOffset, false);
			writeDataMemory(SPRPhysicalAddressOffset, true, packet);

			log(Debug, "EE DMAC Write u128 channel %s, SPRAddr = 0x%08llX, valueLo = 0x%016llX, valueHi = 0x%016X <- MemAddr = 0x%08X",
				mChannel->getChannelProperties()->Mnemonic, SPRPhysicalAddressOffset, packet.lo, packet.hi, PhysicalAddressOffset);
		}
		else
		{
			throw std::runtime_error("EE DMAC could not determine transfer direction (SPR)! Please debug.");
		}

		// Increment the MADR & SADR register by a qword, and decrement the QWC register by a qword.
		mChannel->MADR->increment();
		mChannel->SADR->increment();
		mChannel->QWC->decrement();

		return 1;
	}
	else
	{
		// Else transfer data normally.
		if (direction == Direction_t::FROM)
		{
			// Check if channel does not have data ready - need to try again next cycle.
			if (mChannel->mFIFOQueue->isEmpty())
				return 0;

			u128 packet = mChannel->mFIFOQueue->readQword(RAW);
			writeDataMemory(PhysicalAddressOffset, SPRFlag, packet);

			log(Debug, "EE DMAC Read u128 channel %s, valueLo = 0x%016llX, valueHi = 0x%016llX -> MemAddr = 0x%08X", 
				mChannel->getChannelProperties()->Mnemonic, packet.lo, packet.hi, PhysicalAddressOffset);
		}
		else if (direction == Direction_t::TO)
		{
			// Check if channel is full - need to try again next cycle.
			if (mChannel->mFIFOQueue->isFull())
				return 0;

			u128 packet = readDataMemory(PhysicalAddressOffset, SPRFlag);
			mChannel->mFIFOQueue->writeQword(RAW, packet);

			log(Debug, "EE DMAC Write u128 channel %s, valueLo = 0x%016llX, valueHi = 0x%016llX <- MemAddr = 0x%08X",
				mChannel->getChannelProperties()->Mnemonic, packet.lo, packet.hi, PhysicalAddressOffset);
		}
		else
		{
			throw std::runtime_error("EE DMAC could not determine transfer direction! Please debug.");
		}

		// Increment the MADR register by a qword, and decrement the QWC register by a qword.
		mChannel->MADR->increment();
		mChannel->QWC->decrement();

		return 1;
	}
}

void EEDmac_s::setStateSuspended() const
{
	// Emit the interrupt status bit.
	mDMAC->STAT->setFieldValue(EEDmacRegister_STAT_t::Fields::CHANNEL_IRQ_KEYS[mChannel->getChannelID()], 1);

	// Change CHCR.STR to 0.
	mChannel->CHCR->setFieldValue(EEDmacChannelRegister_CHCR_t::Fields::STR, 0);
}

void EEDmac_s::setStateFailedTransfer() const
{
	throw std::runtime_error("failed transfer not implemented.");
}

void EEDmac_s::transferNormal()
{
	// Check the QWC register, make sure that size > 0 in order to start transfer.
	if (mChannel->QWC->readWord(RAW) == 0)
	{
		setStateFailedTransfer();
		return;
	}

	// Check for drain stall control conditions, and skip cycle if the data is not ready (when the next slice is not ready).
	if (isDrainStallControlOn() && isDrainStallControlWaiting())
	{
		setDMACStallControlSIS();
		return;
	}

	// Transfer a data unit (128-bits). If no data was transfered, try again next cycle.
	if (!transferData())
		return;

	// Check for source stall control conditions, and update D_STADR if required.
	if (isSourceStallControlOn())
		setDMACStallControlSTADR();

	// Check if QWC == 0 (transfer completed), in which case stop transferring and update status.
	if (mChannel->QWC->readWord(RAW) == 0)
		setStateSuspended();
}

void EEDmac_s::transferChain()
{
	// Check the QWC register, make sure that size > 0 for a transfer to occur (otherwise read a tag).
	if (mChannel->QWC->readWord(RAW) > 0)
	{
		// Check for drain stall control conditions (including if we are in "refs" tag), and skip cycle if the data is not ready.
		if (isDrainStallControlOn() && isDrainStallControlWaiting() && mChannel->CHCR->mTagStallControl)
		{
			setDMACStallControlSIS();
			return;
		}

		// Transfer a data unit (128-bits). If no data was transfered, try again next cycle.
		if (!transferData())
			return;

		// Check for source stall control conditions (including if we are in "cnts" tag id), and update D_STADR if required.
		if (isSourceStallControlOn() && mChannel->CHCR->mTagStallControl)
			setDMACStallControlSTADR();

		// If QWC is now 0, update the tag flags state, and check for suspend conditions.
		if (mChannel->QWC->readWord(RAW) == 0)
		{
			// Check if we need to emit an interrupt due to tag (done after packet transfer has completed). Dependent on the tag IRQ flag set and the CHCR.TIE bit set.
			if (mChannel->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::TIE) > 0 && mChannel->CHCR->mTagIRQ)
				setStateSuspended();

			// Check if we need to exit based on tag flag (set by "end", "ret", etc).
			if (mChannel->CHCR->mTagExit)
				setStateSuspended();

			// Reset the tag flag state (done regardless of the above on every finished tag transfer).
			mChannel->CHCR->resetTagFlags();
		}
	}
	else
	{
		// Check if we are in source or dest chain mode, read in a tag (to mDMAtag), and perform action based on tag id (which will set MADR, QWC, etc).
		// TODO: Do check based off the CHCR.DIR (direction) set or based on constant properties listed on pg 42 of EE Users Manual? Works both ways, but direction is less code.
		switch (mChannel->CHCR->getDirection()) 
		{
		case Direction_t::TO:
		{
			// Read in a tag, exit early if we need to wait for data.
			if (!readChainSourceTag())
				return;

			// Execute the tag handler
			(this->*SRC_CHAIN_INSTRUCTION_TABLE[mDMAtag.getID()])();
			break;
		}
		case Direction_t::FROM:
		{
			// Read in a tag, exit early if we need to wait for data.
			if (!readChainDestTag())
				return;

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
		mChannel->CHCR->setFieldValue(EEDmacChannelRegister_CHCR_t::Fields::TAG, (mDMAtag.mTagValue >> 16) & 0xFFFF);
	}
}

void EEDmac_s::transferInterleaved()
{
	throw std::runtime_error("EE DMAC interleave mode not fully implemented (fixup).");

	/*
	// Check the QWC register, make sure that size > 0 in order to start transfer.
	if (mChannel->QWC->readWord(RAW) == 0)
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
	if (mChannel->QWC->readWord(RAW) == 0)
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
	if (D_STAT->isInterruptPending())
		COP0->Cause->setIRQLine(2);
	else
		COP0->Cause->clearIRQLine(2);
}

bool EEDmac_s::isSourceStallControlOn() const
{
	if (mChannel->CHCR->getDirection() == Direction_t::FROM)
	{
		const u32 STS = mDMAC->CTRL->getFieldValue(EEDmacRegister_CTRL_t::Fields::STS);
		if (mChannel->getChannelID() == EEDmacChannelTable::getSTSChannelIndex(STS))
		{
			return true;
		}
	}

	return false;
}

bool EEDmac_s::isDrainStallControlOn() const
{
	if (mChannel->CHCR->getDirection() == Direction_t::TO)
	{
		auto STD = mDMAC->CTRL->getFieldValue(EEDmacRegister_CTRL_t::Fields::STD);
		if (mChannel->getChannelID() == EEDmacChannelTable::getSTDChannelIndex(STD))
		{
			return true;
		}
	}

	return false;
}

void EEDmac_s::setDMACStallControlSTADR() const
{
	u32 MADR = mChannel->MADR->getFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR);
	mDMAC->STADR->setFieldValue(EEDmacRegister_STADR_t::Fields::ADDR, MADR);
}

void EEDmac_s::setDMACStallControlSIS() const
{
	// Set the STAT.SIS bit.
	mDMAC->STAT->setFieldValue(EEDmacRegister_STAT_t::Fields::SIS, 1);
}

bool EEDmac_s::isDrainStallControlWaiting() const
{
	if (mChannel->CHCR->getDirection() == Direction_t::TO)
	{
		const u32 MADR = mChannel->MADR->getFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR);
		const u32 STADR = mDMAC->STADR->getFieldValue(EEDmacRegister_STADR_t::Fields::ADDR);

		if ((MADR + 8) > STADR)
		{
			return true;
		}
	}

	return false;
}

u128 EEDmac_s::readDataMemory(u32 physicalAddress, bool SPRAccess) const
{
	// Read mem[addr] or spr[addr] (128-bits).
	if (SPRAccess)
		return mEEPhysicalMMU->readQword(RAW, Constants::EE::EECore::ScratchpadMemory::PADDRESS_SCRATCHPAD_MEMORY + physicalAddress);
	else
		return mEEPhysicalMMU->readQword(RAW, physicalAddress);
}

void EEDmac_s::writeDataMemory(u32 physicalAddress, bool SPRAccess, u128 data) const
{
	// Write mem[addr] or spr[addr] (128-bits).
	if (SPRAccess)
		mEEPhysicalMMU->writeQword(RAW, Constants::EE::EECore::ScratchpadMemory::PADDRESS_SCRATCHPAD_MEMORY + physicalAddress, data);
	else
		mEEPhysicalMMU->writeQword(RAW, physicalAddress, data);
}

bool EEDmac_s::readChainSourceTag()
{
	// Check first if we need to transfer the tag - return false if the channel queue is full.
	if (mChannel->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::TTE))
	{
		if (mChannel->mFIFOQueue->isFull())
			return false;
	}

	// Read tag from TADR.
	// Get the main memory or SPR address we are reading or writing from.
	u128 data;
	const u32 TADR = mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR);
	const bool SPRFlag = (mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR) != 0);
	data = readDataMemory(TADR, SPRFlag);

	// Set mDMAtag based upon the u128 read from memory (lower 64-bits).
	mDMAtag.setValue(data.lo);
	
	// Check if we need to transfer the tag.
	if (mChannel->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::TTE))
	{
		// Write the tag to the channel.
		mChannel->mFIFOQueue->writeQword(RAW, data);
	}

	return true;
}

bool EEDmac_s::readChainDestTag()
{
	// Check first if there is data available.
	if (mChannel->mFIFOQueue->isEmpty())
		return false;

	// Read tag from channel FIFO (always next to transfer data).
	u128 data = mChannel->mFIFOQueue->readQword(RAW);

	// Set mDMAtag based upon the u128 read from the channel.
	mDMAtag.setValue(data.lo);
	
	// Check if we need to transfer the tag.
	if (mChannel->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::TTE))
	{
		// Write the tag to memory (MADR) and increment.
		const u32 MADR = mChannel->MADR->getFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR);
		const bool SPRFlag = (mChannel->MADR->getFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR) != 0);
		writeDataMemory(MADR, SPRFlag, data);
		mChannel->MADR->increment();
	}
	
	return true;
}
