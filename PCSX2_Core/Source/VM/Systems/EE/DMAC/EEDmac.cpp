#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/PhysicalMMU/PhysicalMMU_t.h"
#include "Common/Tables/EEDmacChannelTable/EEDmacChannelTable.h"
#include "Common/Types/FIFOQueue/FIFOQueue_t.h"

#include "VM/Systems/EE/DMAC/EEDmac.h"

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
using ChannelID_t = EEDmacChannelTable::ChannelID_t;
using Direction_t = EEDmacChannelTable::Direction_t;
using PhysicalMode_t = EEDmacChannelTable::PhysicalMode_t;
using ChainMode_t = EEDmacChannelTable::ChainMode_t;

EEDmac::EEDmac(VM* vmMain) :
	VMSystem_t(vmMain, System_t::EEDmac),
	mChannelIndex(0),
	mChannel(nullptr),
	mDMAtag()
{
	// Set resource pointer variables.
	mDMAC = getResources()->EE->DMAC;
	mEEPhysicalMMU = getResources()->EE->PhysicalMMU;
}

EEDmac::~EEDmac()
{
}

double EEDmac::executeStep(const ClockSource_t & clockSource, const double & ticksAvailable)
{
	// Check if DMA transfers are enabled. If not, DMAC has nothing to do.
	if (mDMAC->CTRL->getFieldValue(EEDmacRegister_CTRL_t::Fields::DMAE) > 0)
	{
		// Check for any pending/started DMA transfers and perform transfer if enabled.
		for (mChannelIndex = 0; mChannelIndex < Constants::EE::DMAC::NUMBER_DMAC_CHANNELS; mChannelIndex++)
		{
			// Set context variables.
			mChannel = &(*mDMAC->CHANNELS[mChannelIndex]); // I give up, for now I need the speed for debugging. Change back later & sort out why this is so slow.

			// Check if channel is enabled for transfer.
			if (mChannel->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::STR) > 0)
			{
				switch (mChannel->getRuntimeLogicalMode())
				{
				case LogicalMode_t::NORMAL:
				{
					executionStep_Normal();
					break;
				}
				case LogicalMode_t::CHAIN:
				{
					executionStep_Chain();       
					break;
				}
				case LogicalMode_t::INTERLEAVED:
				{
					executionStep_Interleaved(); 
					break;
				}
				default:
				{
					throw std::runtime_error("Could not determine DMA transfer logical mode context. Please fix!");
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

u32 EEDmac::transferData() const
{
	// Determine the direction of data flow. If set to BOTH (true for VIF1 and SIF2 channels), get the runtime direction by checking the CHCR.DIR field.
	Direction_t direction = mChannel->getRuntimeDirection();

	// Get the main memory or SPR address we are reading or writing from. 
	// NOTE: The mask of 0x1FFFFFF0 comes from PCSX2, also in my own testing, the PS2 OS sets MADR to illegal addresses, such as 0x3xxxxxxx.
	//       I can only assume that the DMAC hardware corrects this value. The resulting address will also be qword aligned and restricted to the 'system' memory region.
	const bool SPRFlag = (mChannel->MADR->getFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR) != 0);
	const u32 PhysicalAddressOffset = mChannel->MADR->getFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR) & 0x1FFFFFF0;

	// If we are using the from/toSPR channels, then we need to get the SPR address, and take a different code path. 
	// Within the these channels MADR.SPR is always 0 on these channels (have to use the SADR register as the SPR address).
	if (mChannel->getChannelProperties()->ChannelID == ChannelID_t::toSPR || mChannel->getChannelProperties()->ChannelID == ChannelID_t::fromSPR)
	{
		// We are doing a mem->SPR or SPR->mem, use both MADR and SADR registers.
		// NOTE: The mask of 0x3FF0 comes from PCSX2. I have not personally tested this, but assume it is required.
		//       This mask restricts the address to the 16 kB address range and makes the address qword aligned.
		const u32 SPRPhysicalAddressOffset = mChannel->SADR->readWord(RAW) & 0x3FF0;

		if (direction == Direction_t::FROM)
		{
			u128 packet = readDataMemory(SPRPhysicalAddressOffset, true);
			writeDataMemory(PhysicalAddressOffset, false, packet);
		}
		else if (direction == Direction_t::TO)
		{
			u128 packet = readDataMemory(PhysicalAddressOffset, false);
			writeDataMemory(SPRPhysicalAddressOffset, true, packet);
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
		}
		else if (direction == Direction_t::TO)
		{
			// Check if channel is full - need to try again next cycle.
			if (mChannel->mFIFOQueue->isFull())
				return 0;

			u128 packet = readDataMemory(PhysicalAddressOffset, SPRFlag);
			mChannel->mFIFOQueue->writeQword(RAW, packet);
		}

		// Increment the MADR register by a qword, and decrement the QWC register by a qword.
		mChannel->MADR->increment();
		mChannel->QWC->decrement();

		return 1;
	}
}

void EEDmac::setStateSuspended() const
{
	// Emit the interrupt status bit.
	mDMAC->STAT->raiseIRQLine(mChannelIndex);

	// Change CHCR.STR to 0.
	mChannel->CHCR->setFieldValue(EEDmacChannelRegister_CHCR_t::Fields::STR, 0);
}

void EEDmac::setStateFailedTransfer() const
{
	throw std::runtime_error("failed transfer not implemented.");
}

void EEDmac::executionStep_Normal()
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
	u32 dataCount = transferData();
	if (!dataCount)
	{
		return;
	}

	// Check for source stall control conditions, and update D_STADR if required.
	if (isSourceStallControlOn())
	{
		setDMACStallControlSTADR();
	}

	// Check if QWC == 0 (transfer completed), in which case stop transferring and update status.
	if (mChannel->QWC->readWord(RAW) == 0)
	{
		setStateSuspended();
	}
}

void EEDmac::executionStep_Chain()
{
	// Check the QWC register, make sure that size > 0 for a transfer to occur (otherwise read a tag).
	if (mChannel->QWC->readWord(RAW) > 0)
	{
		// Check for drain stall control conditions (including if we are in "refs" tag), and skip cycle if the data is not ready.
		if (mChannel->isChainInDrainStallControlTag() && isDrainStallControlOn() && isDrainStallControlWaiting())
		{
			setDMACStallControlSIS();
			return;
		}

		// Transfer a data unit (128-bits). If no data was transfered, try again next cycle.
		u32 dataCount = transferData();
		if (!dataCount)
		{
			return;
		}

		// Check for source stall control conditions (including if we are in "cnts" tag id), and update D_STADR if required.
		if (mChannel->isChainInSourceStallControlTag() && isSourceStallControlOn())
		{
			setDMACStallControlSTADR();
		}

		// If QWC is now 0, check for suspend conditions.
		if (mChannel->QWC->readWord(RAW) == 0)
		{
			// Check if we need to emit an interrupt due to tag (done after packet transfer has completed).
			if (mChannel->isChainInInterruptTag())
			{
				setStateSuspended();
			}

			// Check if we need to exit based on tag instruction ("end", "ret", etc).
			if (mChannel->isChainInExitTag())
			{
				mChannel->resetChainExitState();
				setStateSuspended();
			}
		}
	}
	else
	{
		// Check if we are in source or dest chain mode, read in a tag, and perform action based on tag id (which will set MADR, QWC, etc).
		switch (mChannel->getChannelProperties()->ChainMode)
		{
		case ChainMode_t::SOURCE:
		{
			// Read in a tag, exit early if we need to wait for data.
			if (!readChainSourceTag())
				return;

			// Execute the tag handler
			(this->*SRC_CHAIN_INSTRUCTION_TABLE[mDMAtag.getID()])();
			break;
		}
		case ChainMode_t::DEST:
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
			throw std::runtime_error("Could not determine chain mode context.");
		}
		}
	}
}

void EEDmac::executionStep_Interleaved()
{
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
}

void EEDmac::handleInterruptCheck() const
{
	auto& COP0 = getResources()->EE->EECore->COP0;
	auto& D_STAT = mDMAC->STAT;

	// Set the interrupt line if there was a condition set, otherwise clear the interrupt line.
	if (D_STAT->isInterrupted())
		COP0->Cause->setIRQLine(2);
	else
		COP0->Cause->clearIRQLine(2);
}

bool EEDmac::isSourceStallControlOn() const
{
	if (mChannel->getRuntimeDirection() == Direction_t::FROM)
	{
		const u32 STS = mDMAC->CTRL->getFieldValue(EEDmacRegister_CTRL_t::Fields::STS);
		if (mChannelIndex == EEDmacChannelTable::getSTSChannelIndex(STS))
		{
			return true;
		}
	}

	return false;
}

bool EEDmac::isDrainStallControlOn() const
{
	if (mChannel->getRuntimeDirection() == Direction_t::TO)
	{
		auto STD = mDMAC->CTRL->getFieldValue(EEDmacRegister_CTRL_t::Fields::STD);
		if (mChannelIndex == EEDmacChannelTable::getSTDChannelIndex(STD))
		{
			return true;
		}
	}

	return false;
}

void EEDmac::setDMACStallControlSTADR() const
{
	u32 MADR = mChannel->MADR->getFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR);
	mDMAC->STADR->setFieldValue(EEDmacRegister_STADR_t::Fields::ADDR, MADR);
}

void EEDmac::setDMACStallControlSIS() const
{
	// SIS is on irq line 10.
	mDMAC->STAT->raiseIRQLine(10);
}

bool EEDmac::isDrainStallControlWaiting() const
{
	if (mChannel->getRuntimeDirection() == Direction_t::TO)
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

u128 EEDmac::readDataMemory(u32 physicalAddress, bool SPRAccess) const
{
	// Read mem[addr] or spr[addr] (128-bits).
	if (SPRAccess)
		return mEEPhysicalMMU->readQword(RAW, Constants::EE::EECore::ScratchpadMemory::PADDRESS_SCRATCHPAD_MEMORY + physicalAddress);
	else
		return mEEPhysicalMMU->readQword(RAW, physicalAddress);
}

void EEDmac::writeDataMemory(u32 physicalAddress, bool SPRAccess, u128 data) const
{
	// Write mem[addr] or spr[addr] (128-bits).
	if (SPRAccess)
		mEEPhysicalMMU->writeQword(RAW, Constants::EE::EECore::ScratchpadMemory::PADDRESS_SCRATCHPAD_MEMORY + physicalAddress, data);
	else
		mEEPhysicalMMU->writeQword(RAW, physicalAddress, data);
}

bool EEDmac::readChainSourceTag()
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

	// Set CHCR.TAG based upon the DMA tag read (bits 16-31).
	mChannel->CHCR->setFieldValue(EEDmacChannelRegister_CHCR_t::Fields::TAG, (data.lo >> 16) & 0xFFFF);

	// Check if we need to transfer the tag.
	if (mChannel->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::TTE))
	{
		// Write the tag to the channel.
		mChannel->mFIFOQueue->writeQword(RAW, data);
	}

	return true;
}

bool EEDmac::readChainDestTag()
{
	// Check first if there is data available.
	if (mChannel->mFIFOQueue->isEmpty())
		return false;

	// Read tag from channel FIFO (always next to transfer data).
	u128 data = mChannel->mFIFOQueue->readQword(RAW);

	// Set mDMAtag based upon the u128 read from the channel.
	mDMAtag.setValue(data.lo);

	// Set CHCR.TAG based upon the DMA tag read (bits 16-31).
	mChannel->CHCR->setFieldValue(EEDmacChannelRegister_CHCR_t::Fields::TAG, (data.lo >> 16) & 0xFFFF);

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

void EEDmac::INSTRUCTION_UNSUPPORTED()
{
	throw std::runtime_error("DMAC chain mode called invalid tag ID");
}

void EEDmac::SRC_CNT()
{
	// Transfers QWC qwords after the tag, and reads the next qword as the next tag.
	mChannel->QWC->writeWord(RAW, mDMAtag.getQWC());

	// Copy TADR + 0x10 into MADR.
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10);
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR));

	// Calculate where the next tag will be.
	u32 nextTagAddr = mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + (mDMAtag.getQWC() + 1) * 0x10;
	mChannel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, nextTagAddr); // SPR flag unchanged within TADR register.
}

void EEDmac::SRC_NEXT()
{
	// Transfers QWC qwords after the tag, and reads the ADDR field as the next tag.
	mChannel->QWC->writeWord(RAW, mDMAtag.getQWC());

	// Copy TADR + 0x10 into MADR.
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10);
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR));

	// Set next tag.
	mChannel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, mDMAtag.getADDR());
	mChannel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, mDMAtag.getSPR());
}

void EEDmac::SRC_REF()
{
	// Transfers QWC qwords from ADDR field, and reads the next qword as the tag.
	mChannel->QWC->writeWord(RAW, mDMAtag.getQWC());

	// Set MADR = tag.ADDR.
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mDMAtag.getADDR());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mDMAtag.getSPR());

	// Set next qword as tag.
	mChannel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10); // SPR flag unchanged within TADR register.
}

void EEDmac::SRC_REFS()
{
	// TODO: add in stall control.

	// Transfers QWC qwords from ADDR field, and reads the next qword as the tag.
	mChannel->QWC->writeWord(RAW, mDMAtag.getQWC());

	// Set MADR = tag.ADDR.
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mDMAtag.getADDR());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mDMAtag.getSPR());

	// Set next qword as tag.
	mChannel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10); // SPR flag unchanged within TADR register.
}

void EEDmac::SRC_REFE()
{
	// Transfers QWC qwords from ADDR, and suspends after packet transfer.
	mChannel->QWC->writeWord(RAW, mDMAtag.getQWC());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mDMAtag.getADDR());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mDMAtag.getSPR());
	mChannel->setChainExitStateTrue();
}

void EEDmac::SRC_CALL()
{
	// Transfers QWC qwords after tag, and pushes the next qword after the tag onto the stack. Sets the next tag to ADDR field.
	mChannel->QWC->writeWord(RAW, mDMAtag.getQWC());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10);
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR));
	mChannel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, mDMAtag.getADDR());
	mChannel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR, mDMAtag.getSPR());

	// Check for stack overflow, else push the stack.
	if (mChannel->isChainStackOverflowed())
		mChannel->setChainExitStateTrue();
	else
		mChannel->pushChainStack();
}

void EEDmac::SRC_RET()
{
	// Transfers QWC qwords after tag, pops next tag from stack. If stack level = 0, transfers QWC qwords after tag and suspends transfer.
	
	// Check for stack underflow, else pop the stack.
	if (mChannel->isChainStackUnderflowed())
		mChannel->setChainExitStateTrue();
	else
		mChannel->popChainStack();

	// In both cases, QWC following the tag is always performed.
	mChannel->QWC->writeWord(RAW, mDMAtag.getQWC());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10);
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR));
}

void EEDmac::SRC_END()
{
	// Transfers QWC qwords after tag, and suspends after packet transfer.
	mChannel->QWC->writeWord(RAW, mDMAtag.getQWC());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10);
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR));
	mChannel->setChainExitStateTrue();
}

void EEDmac::DST_CNT()
{
	// Transfers QWC qwords after the tag to tag.ADDR, and reads the next qword as the next tag.
	mChannel->QWC->writeWord(RAW, mDMAtag.getQWC());

	// Set MADR to tag values.
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mDMAtag.getADDR());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mDMAtag.getSPR());
}

void EEDmac::DST_CNTS()
{
	// TODO: need to copy MADR to STADR during the transfer.
	// Transfers QWC qwords after the tag to tag.ADDR, and reads the next qword as the next tag.
	mChannel->QWC->writeWord(RAW, mDMAtag.getQWC());

	// Set MADR to tag values.
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mDMAtag.getADDR());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mDMAtag.getSPR());
}

void EEDmac::DST_END()
{
	// Transfers QWC qwords after the tag to tag.ADDR, and suspends transfer after completing.
	mChannel->QWC->writeWord(RAW, mDMAtag.getQWC());

	// Set MADR to tag values.
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mDMAtag.getADDR());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mDMAtag.getSPR());
	mChannel->setChainExitStateTrue();
}

bool EEDmac::isInterleaveLimitReached()
{
	// In transfer block?
	if (!mChannel->isInterleaveInSkipMode())
	{
		// Have we reached the TWQC limit?
		if (mChannel->getInterleavedCount() >= mDMAC->SQWC->getFieldValue(EEDmacRegister_SWQC_t::Fields::TQWC))
		{
			return true;
		}
	}
	// In skip block?
	else
	{
		// Have we reached the TWQC limit?
		if (mChannel->getInterleavedCount() >= mDMAC->SQWC->getFieldValue(EEDmacRegister_SWQC_t::Fields::SQWC))
		{
			return true;
		}
	}

	return false;
}