#include "stdafx.h"

#include "VM/ExecutionCore/Common/EE/DMAC/EEDmac.h"
#include "PS2Constants/PS2Constants.h"
#include "VM/VMMain.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreExceptions_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreException_t.h"
#include "PS2Resources/EE/DMAC/EEDmac_t.h"
#include "PS2Resources/EE/DMAC/Types/EEDmacChannelRegisters_t.h"
#include "PS2Resources/EE/DMAC/Types/EEDmacChannels_t.h"
#include "PS2Resources/EE/DMAC/Types/EEDmacRegisters_t.h"
#include "PS2Resources/EE/DMAC/Types/DMAtag_t.h"
#include "Common/Types/PhysicalMMU/PhysicalMMU_t.h"
#include "Common/Types/FIFOQueue/FIFOQueue_t.h"
#include "Common/Tables/EEDmacChannelTable/EEDmacChannelTable.h"

using ExType = EECoreException_t::ExType;
using ChannelProperties_t = EEDmacChannelTable::ChannelProperties_t;
using ChannelID_t = EEDmacChannelTable::ChannelID_t;
using Direction_t = EEDmacChannelTable::Direction_t;
using PhysicalMode_t = EEDmacChannelTable::PhysicalMode_t;
using ChainMode_t = EEDmacChannelTable::ChainMode_t;

EEDmac::EEDmac(VMMain * vmMain) :
	VMExecutionCoreComponent(vmMain),
	mChannelIndex(0),
	mChannelProperties(nullptr),
	mDMAtag()
{
	// Set resource pointer variables.
	mDMAC = getResources()->EE->DMAC;
	mEEMMU = getResources()->EE->PhysicalMMU;
}

EEDmac::~EEDmac()
{
}

s64 EEDmac::executionStep(const ClockSource_t & clockSource)
{
	// Check if DMA transfers are enabled. If not, DMAC has nothing to do.
	if (!mDMAC->CTRL->getFieldValue(EEDmacRegister_CTRL_t::Fields::DMAE))
		return 1;

	// Check for any pending/started DMA transfers, by checking the Dn_CHCR.STR register of each channel. Perform transfer if enabled.
	for (mChannelIndex = 0; mChannelIndex < PS2Constants::EE::DMAC::NUMBER_DMAC_CHANNELS; mChannelIndex++)
	{
		// Set context variables.
		mChannel = mDMAC->CHANNELS[mChannelIndex];
		mChannelProperties = mChannel->getChannelProperties();

		// Check if channel is enabled for transfer.
		if (mChannel->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::STR))
		{
			switch (mChannel->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::MOD))
			{
			case 0x0: 
				executionStep_Normal();      break;
			case 0x1: 
				executionStep_Chain();       break;
			case 0x2: 
				executionStep_Interleaved(); break;
			default:
				throw std::runtime_error("Could not determine DMA transfer logical mode context. Please fix!");
			}
		}
	}

	// Check for D_STAT interrupt bit status, send interrupt to EE Core (INT1 line) if not masked.
	checkInterruptStatus();

	// DMAC has completed 1 cycle.
	return 1;
}

void EEDmac::executionStep_Normal() const
{
	// Check the QWC register, make sure that size > 0 in order to start transfer.
	if (mChannel->QWC->getFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC) == 0)
	{
		// TODO: implement failed transfer properly? (See page 79 of EE Users Manual).
		throw std::runtime_error("QWC == 0 at start in normal mode, but not implemented.");
	}

	// Check for drain stall control conditions, and skip cycle if the data is not ready (when the next slice is not ready).
	if (isDrainStallControlOn() && isDrainStallControlWaiting())
	{
		// Set the SIS bit.
		mDMAC->STAT->setFieldValue(EEDmacRegister_STAT_t::Fields::SIS, 1);
		return;
	}
	
	// Transfer a single data unit of 128 bits (same for slice and burst). This function also updates the number of units transferred.
	transferDataUnit();

	// Check for source stall control conditions, and update D_STADR if required.
	if (isSourceStallControlOn())
		updateSourceStallControlAddress();

	// Check if QWC == 0 (transfer completed), in which case stop transferring and update status.
	if (mChannel->QWC->getFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC) == 0)
		suspendTransfer();

	// If the physical mode is set to slice, suspend transfer after 8 units are completed.
	checkSliceQuota();
}

void EEDmac::executionStep_Chain()
{
	// Check the QWC register, make sure that size > 0 for a transfer to occur (otherwise read a tag).
	if (mChannel->QWC->getFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC) > 0)
	{
		// Check for drain stall control conditions (if we are in "refs" tag), and skip cycle if the data is not ready (when the next slice is not ready).
		if (((mChannel->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::TAG) >> 12) & 0x7) == 0x4)
		{
			if (isDrainStallControlOn() && isDrainStallControlWaiting())
			{
				// Set the SIS bit.
				mDMAC->STAT->setFieldValue(EEDmacRegister_STAT_t::Fields::SIS, 1);
				return;
			}
		}

		// Transfer a single data unit of 128 bits (same for slice and burst). This function also updates the number of units transferred.
		transferDataUnit();

		// Check for source stall control conditions (if we are in "cnts" tag id), and update D_STADR if required.
		if (((mChannel->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::TAG) >> 12) & 0x7) == 0x0)
		{
			if (isSourceStallControlOn())
				updateSourceStallControlAddress();
		}
		
		// If QWC is now 0, check for suspend conditions.
		if (mChannel->QWC->getFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC) == 0)
		{
			// Check if we need to emit a tag interrupt (done after packet transfer has completed).
			checkDMAtagPacketInterrupt();

			// Check if we need to exit based on tag instruction ("end", "ret", etc).
			checkChainExit();
		}
	}
	else
	{
		// Check if we are in source or dest chain mode. Perform action based on tag id (which will set MADR, QWC, etc).
		// Need to also read in a tag and set CHCR.TAG to bits 16-31. Also transfer the tag if the CHCR.TTE bit is set.
		switch (mChannelProperties->ChainMode)
		{
		case ChainMode_t::SOURCE:
		{
			checkChainSrcFirstRun(); // Some additional processing needed on src chain first run before starting a transfer (set TADR register).
			readChainSrcDMAtag();
			(this->*SRC_CHAIN_INSTRUCTION_TABLE[mDMAtag.getID()])(); 
			break;
		}
		case ChainMode_t::DEST:
		{
			readChainDstDMAtag();
			(this->*DST_CHAIN_INSTRUCTION_TABLE[mDMAtag.getID()])(); 
			break;
		}
		default:
			throw std::runtime_error("Could not determine chain mode context.");
		}
	}

	// Check for the slice channel quota limit.
	checkSliceQuota();
}

void EEDmac::executionStep_Interleaved() const
{
	// Check the QWC register, make sure that size > 0 in order to start transfer.
	if (mChannel->QWC->getFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC) == 0)
	{
		// TODO: implement failed transfer properly? (See page 79 of EE Users Manual).
		throw std::runtime_error("QWC == 0 at start in interleaved mode, but not implemented.");
	}
	
	// Data of size D_SQWC.TQWC is transferred first, then data of size D_SQWC.SQWC is skipped, until Dn_QWC is reached.
	if (!mChannel->mInterleavedInSkipBlock)
		transferDataUnit(); // Transfer data.
	else
		mChannel->MADR->increment(); // Skip data by incrementing the channel MADR.

	// Increment the mInterleavedCountState.
	mChannel->mInterleavedBlockCount += 1;

	// Check the interleaved mode (transferring/skipping), and change mInterleavedSkipState if required, based on mInterleavedCountState.
	checkInterleaveCount();

	// Check if QWC == 0 (transfer completed), in which case stop transferring and update status.
	if (mChannel->QWC->getFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC) == 0)
		suspendTransfer();

	// If the physical mode is set to slice, suspend transfer after 8 units are completed.
	checkSliceQuota();
}

void EEDmac::checkSliceQuota() const
{
	// If the physical mode is set to slice, reset state and suspend transfer after 8 units are completed.
	if ((mChannelProperties->PhysicalMode == PhysicalMode_t::SLICE)
		&& (mChannel->mSliceCountState % 8 == 0))
	{
		mChannel->mSliceCountState = 0;
		suspendTransfer();
	}
}

void EEDmac::suspendTransfer() const
{
	// Emit the interrupt status bit.
	auto& key = EEDmacRegister_STAT_t::Fields::CIS_KEYS[mChannelIndex];
	mDMAC->STAT->setFieldValue(key, 1);

	// Change CHCR.STR to 0.
	mChannel->CHCR->setFieldValue(EEDmacChannelRegister_CHCR_t::Fields::STR, 0);
}

void EEDmac::checkInterruptStatus() const
{
	auto& D_STAT = mDMAC->STAT;
	auto& Exceptions = getResources()->EE->EECore->Exceptions;

	// Check channel interrupt status.
	for (auto i = 0; i < PS2Constants::EE::DMAC::NUMBER_DMAC_CHANNELS; i++)
	{
		auto& cisKey = EEDmacRegister_STAT_t::Fields::CIS_KEYS[i];
		auto& cimKey = EEDmacRegister_STAT_t::Fields::CIM_KEYS[i];

		auto& cisValue = D_STAT->getFieldValue(cisKey);
		auto& cimValue = D_STAT->getFieldValue(cimKey);

		// Set EE Core interrupt if (CIS & CIM) is true.
		if (cisValue & cimValue)
		{
			IntExceptionInfo_t intex = { 1, 0, 0 };
			Exceptions->setException(EECoreException_t(ExType::EX_INTERRUPT, nullptr, &intex, nullptr));
		}
	}

	// Check stall control interrupt status.
	if (D_STAT->getFieldValue(EEDmacRegister_STAT_t::Fields::SIS) & D_STAT->getFieldValue(EEDmacRegister_STAT_t::Fields::SIS))
	{
		IntExceptionInfo_t intex = { 1, 0, 0 };
		Exceptions->setException(EECoreException_t(ExType::EX_INTERRUPT, nullptr, &intex, nullptr));
	}

	// Check MFIFO interrupt status.
	if (D_STAT->getFieldValue(EEDmacRegister_STAT_t::Fields::MEIS) & D_STAT->getFieldValue(EEDmacRegister_STAT_t::Fields::MEIM))
	{
		IntExceptionInfo_t intex = { 1, 0, 0 };
		Exceptions->setException(EECoreException_t(ExType::EX_INTERRUPT, nullptr, &intex, nullptr));
	}

	// Check for BUSERR interrupt status.
	if (D_STAT->getFieldValue(EEDmacRegister_STAT_t::Fields::BEIS))
	{
		IntExceptionInfo_t intex = { 1, 0, 0 };
		Exceptions->setException(EECoreException_t(ExType::EX_INTERRUPT, nullptr, &intex, nullptr));
	}
}

Direction_t EEDmac::getRuntimeDirection() const
{
	Direction_t direction = mChannelProperties->Direction;
	if (direction == Direction_t::BOTH)
		direction = static_cast<Direction_t>(mChannel->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::DIR));

	return direction;
}

bool EEDmac::isSourceStallControlOn() const
{
	if (getRuntimeDirection() == Direction_t::FROM)
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
	if (getRuntimeDirection() == Direction_t::TO)
	{
		auto STD = mDMAC->CTRL->getFieldValue(EEDmacRegister_CTRL_t::Fields::STD);
		if (mChannelIndex == EEDmacChannelTable::getSTDChannelIndex(STD))
		{
			return true;
		}
	}
	
	return false;
}

void EEDmac::updateSourceStallControlAddress() const
{
	mDMAC->STADR->setFieldValue(EEDmacRegister_STADR_t::Fields::ADDR, mChannel->MADR->getFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR));
}

bool EEDmac::isDrainStallControlWaiting() const
{
	if (getRuntimeDirection() == Direction_t::TO)
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

void EEDmac::transferDataUnit() const
{
	// Determine the direction of data flow. If set to BOTH (true for VIF1 and SIF2 channels), get the runtime direction by checking the CHCR.DIR field.
	Direction_t direction = getRuntimeDirection();

	// Get the main memory or SPR address we are reading or writing from. 
	const u32 PhysicalAddressOffset = mChannel->MADR->getFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR);
	const bool SPRFlag = (mChannel->MADR->getFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR) != 0);

	// If we are using the from/toSPR channels, then we need to get the SPR address, and take a different code path. 
	// Within the these channels MADR.SPR is always 0 on these channels (have to use the SADR register as the SPR address).
	if (mChannelProperties->ChannelID == ChannelID_t::toSPR || mChannelProperties->ChannelID == ChannelID_t::fromSPR)
	{
		// We are doing a mem->SPR or SPR->mem, use both MADR and SADR registers.
		const u32 SPRPhysicalAddressOffset = mChannel->SADR->getFieldValue(EEDmacChannelRegister_SADR_t::Fields::ADDR);

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

		// Increment the SADR address as well as MADR etc (done below).
		mChannel->SADR->increment();
	}
	else 
	{
		// Else transfer data normally.
		if (direction == Direction_t::FROM)
		{
			u128 packet = readDataChannel();
			writeDataMemory(PhysicalAddressOffset, SPRFlag, packet);
		}
		else if (direction == Direction_t::TO)
		{
			u128 packet = readDataMemory(PhysicalAddressOffset, SPRFlag);
			writeDataChannel(packet);
		}
	}

	// Update DataCountState by 1, the MADR register by 0x10 (increment), and decrement the QWC register by 1.
	mChannel->mSliceCountState += 1;
	mChannel->MADR->increment();
	mChannel->QWC->decrement();
}

u128 EEDmac::readDataChannel() const
{
	return mChannel->mFIFOQueue->read();
}

void EEDmac::writeDataChannel(u128 data) const
{
	mChannel->mFIFOQueue->write(data);
}

u128 EEDmac::readDataMemory(u32 physicalAddress, bool SPRAccess) const
{
	// Read mem[addr] or spr[addr] (128-bits).
	if (SPRAccess)
		return mEEMMU->readQwordU(PS2Constants::EE::EECore::ScratchpadMemory::PADDRESS_SCRATCHPAD_MEMORY + physicalAddress);
	else
		return mEEMMU->readQwordU(physicalAddress);
}

void EEDmac::writeDataMemory(u32 physicalAddress, bool SPRAccess, u128 data) const
{
	// Write mem[addr] or spr[addr] (128-bits).
	if (SPRAccess)
		mEEMMU->writeQwordU(PS2Constants::EE::EECore::ScratchpadMemory::PADDRESS_SCRATCHPAD_MEMORY + physicalAddress, data);
	else
		mEEMMU->writeQwordU(physicalAddress, data);
}

void EEDmac::readChainSrcDMAtag()
{
	// Read tag from TADR.
	// Get the main memory or SPR address we are reading or writing from.
	u128 data;
	const u32 TADR = mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR);
	const bool SPRFlag = (mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR) != 0);
	data = readDataMemory(TADR, SPRFlag);

	// Set mDMAtag based upon the u128 read from memory.
	mDMAtag.setValue(data.lo);

	// Set CHCR.TAG based upon the DMA tag read (bits 16-31).
	mChannel->CHCR->setFieldValue(EEDmacChannelRegister_CHCR_t::Fields::TAG, (data.lo >> 16) & 0xFFFF);

	// Check if we need to transfer the tag.
	if (mChannel->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::TTE))
	{
		// Write the tag to the channel.
		writeDataChannel(data);

		// Update DataCountState by 1 (counts towards slice channel quota).
		mChannel->mSliceCountState += 1;
	}
}

void EEDmac::readChainDstDMAtag()
{
	// Read tag from channel FIFO (always next to transfer data).
	u128 data = readDataChannel();

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

		// Update DataCountState by 1 (counts towards slice channel quota).
		mChannel->mSliceCountState += 1;
	}
}

void EEDmac::checkChainSrcFirstRun() const
{
	if (mChannel->mChainSrcFirstRun)
	{
		// Set TADR to (MADR + (QWC * 0x10)) as the next tag address on first run.
		auto ADDR = mChannel->MADR->getFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR);
		auto SPRFlag = mChannel->MADR->getFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR);
		auto QWC = mChannel->QWC->getFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC);
		mChannel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, ADDR + (QWC * 0x10));
		mChannel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR, SPRFlag);

		mChannel->mChainSrcFirstRun = false;
	}
}

void EEDmac::checkDMAtagPacketInterrupt() const
{
	if (mChannel->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::TIE) != 0 
		&& (mChannel->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::TAG) & 0x8000) != 0)
	{
		suspendTransfer();
	}
}

void EEDmac::checkChainExit() const
{
	if (mChannel->mChainExitState)
	{
		// Reset chain state variables.
		mChannel->mChainSrcFirstRun = true;
		mChannel->mChainExitState = false;
		mChannel->mChainStackLevelState = 0;

		suspendTransfer();
	}
}

void EEDmac::INSTRUCTION_UNSUPPORTED()
{
	throw std::runtime_error("DMAC chain mode called invalid tag ID");
}

void EEDmac::SRC_CNT()
{
	// Transfers QWC qwords after the tag, and reads the next qword as the next tag.
	mChannel->QWC->setFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC, mDMAtag.getQWC());

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
	mChannel->QWC->setFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC, mDMAtag.getQWC());

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
	mChannel->QWC->setFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC, mDMAtag.getQWC());

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
	mChannel->QWC->setFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC, mDMAtag.getQWC());

	// Set MADR = tag.ADDR.
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mDMAtag.getADDR());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mDMAtag.getSPR());

	// Set next qword as tag.
	mChannel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10); // SPR flag unchanged within TADR register.
}

void EEDmac::SRC_REFE()
{
	// Transfers QWC qwords from ADDR, and suspends after packet transfer.
	mChannel->QWC->setFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC, mDMAtag.getQWC());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mDMAtag.getADDR());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mDMAtag.getSPR());
	mChannel->mChainExitState = true;
}

void EEDmac::SRC_CALL()
{
	// Transfers QWC qwords after tag, and pushes the next qword after the tag onto the stack. Sets the next tag to ADDR field.
	mChannel->QWC->setFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC, mDMAtag.getQWC());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10);
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR));
	mChannel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, mDMAtag.getADDR());
	mChannel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR, mDMAtag.getSPR());

	// Set stack to after tag.
	u32 & stackIdx = mChannel->mChainStackLevelState;

	if (stackIdx >= 2)
	{
		// Check for stack overflow.
		mChannel->mChainExitState = true;
	}
	else
	{
		// Push onto the stack.
		mChannel->ASR[stackIdx]->setFieldValue(EEDmacChannelRegister_ASR_t::Fields::ADDR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10);
		mChannel->ASR[stackIdx]->setFieldValue(EEDmacChannelRegister_ASR_t::Fields::SPR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR));
		stackIdx += 1;
	}
}

void EEDmac::SRC_RET()
{
	// Transfers QWC qwords after tag, pops next tag from stack. If stack level = 0, transfers QWC qwords after tag and suspends transfer.
	u32 & stackIdx = mChannel->mChainStackLevelState;
	if (stackIdx > 0)
	{
		// Pop the stack.
		mChannel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, mChannel->ASR[stackIdx]->getFieldValue(EEDmacChannelRegister_ASR_t::Fields::ADDR));
		mChannel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, mChannel->ASR[stackIdx]->getFieldValue(EEDmacChannelRegister_ASR_t::Fields::SPR));
		stackIdx -= 1;
	}
	else
	{
		// Check for stack underflow.
		mChannel->mChainExitState = true;
	}

	// In both cases, QWC following the tag is always performed.
	mChannel->QWC->setFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC, mDMAtag.getQWC());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10);
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR));
}

void EEDmac::SRC_END()
{
	// Transfers QWC qwords after tag, and suspends after packet transfer.
	mChannel->QWC->setFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC, mDMAtag.getQWC());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10);
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR));
	mChannel->mChainExitState = true;
}

void EEDmac::DST_CNT()
{
	// Transfers QWC qwords after the tag to tag.ADDR, and reads the next qword as the next tag.
	mChannel->QWC->setFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC, mDMAtag.getQWC());

	// Set MADR to tag values.
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mDMAtag.getADDR());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mDMAtag.getSPR());
}

void EEDmac::DST_CNTS()
{
	// TODO: need to copy MADR to STADR during the transfer.
	// Transfers QWC qwords after the tag to tag.ADDR, and reads the next qword as the next tag.
	mChannel->QWC->setFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC, mDMAtag.getQWC());

	// Set MADR to tag values.
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mDMAtag.getADDR());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mDMAtag.getSPR());
}

void EEDmac::DST_END()
{
	// Transfers QWC qwords after the tag to tag.ADDR, and suspends transfer after completing.
	mChannel->QWC->setFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC, mDMAtag.getQWC());

	// Set MADR to tag values.
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mDMAtag.getADDR());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mDMAtag.getSPR());
	mChannel->mChainExitState = true;
}

void EEDmac::checkInterleaveCount() const
{
	// Are we in a transfer or skip block?
	if (!mChannel->mInterleavedInSkipBlock)
	{
		// Have we reached the TWQC limit?
		if (mChannel->mInterleavedBlockCount >= mDMAC->SQWC->getFieldValue(EEDmacRegister_SWQC_t::Fields::TQWC))
		{
			// Change to skip mode and reset the count.
			mChannel->mInterleavedInSkipBlock = !mChannel->mInterleavedInSkipBlock;
			mChannel->mInterleavedBlockCount = 0;
		}
	}
	else
	{
		// Have we reached the SQWC limit?
		if (mChannel->mInterleavedBlockCount >= mDMAC->SQWC->getFieldValue(EEDmacRegister_SWQC_t::Fields::SQWC))
		{
			// Change to skip mode and reset the count.
			mChannel->mInterleavedInSkipBlock = !mChannel->mInterleavedInSkipBlock;
			mChannel->mInterleavedBlockCount = 0;
		}
	}
}
