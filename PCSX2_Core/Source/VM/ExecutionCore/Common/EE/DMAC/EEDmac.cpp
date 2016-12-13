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
}

EEDmac::~EEDmac()
{
}

s64 EEDmac::executionStep(const ClockSource_t & clockSource)
{
	auto& DMAC = getResources()->EE->DMAC;
	auto& Channels = DMAC->CHANNELS;

	// Check if DMA transfers are enabled.
	if (!DMAC->CTRL->getFieldValue(EEDmacRegister_CTRL_t::Fields::DMAE))
		return 1;

	// Check for any pending/started DMA transfers, by checking the Dn_CHCR.STR register of each channel. Perform transfer if enabled.
	for (mChannelIndex = 0; mChannelIndex < PS2Constants::EE::DMAC::NUMBER_DMAC_CHANNELS; mChannelIndex++)
	{
		if (Channels[mChannelIndex]->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::STR))
		{
			mChannelProperties = Channels[mChannelIndex]->getChannelProperties();
			switch (Channels[mChannelIndex]->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::MOD))
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
	auto& DMAC = getResources()->EE->DMAC;
	auto& Channel = DMAC->CHANNELS[mChannelIndex];

	// Check the QWC register, make sure that size > 0 in order to start transfer.
	if (Channel->QWC->getFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC) == 0)
	{
		// TODO: implement failed transfer properly? (See page 79 of EE Users Manual).
		throw std::runtime_error("QWC == 0 at start in normal mode, but not implemented.");
	}

	// Check for drain stall control conditions, and skip cycle if the data is not ready (when the next slice is not ready).
	if (isDrainStallControlOn() && isDrainStallControlWaiting())
		return;
	
	// Transfer a single data unit of 128 bits (same for slice and burst). This function also updates the number of units transferred.
	transferDataUnit();

	// Check for source stall control conditions, and update D_STADR if required.
	if (isSourceStallControlOn())
		updateSourceStallControlAddress();

	// Check if QWC == 0 (transfer completed), in which case stop transferring and update status.
	if (Channel->QWC->getFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC) == 0)
		suspendTransfer();

	// If the physical mode is set to slice, suspend transfer after 8 units are completed.
	checkSliceQuota();
}

void EEDmac::executionStep_Chain()
{
	auto& DMAC = getResources()->EE->DMAC;
	auto& Channel = DMAC->CHANNELS[mChannelIndex];

	// Check the QWC register, make sure that size > 0 for a transfer to occur (otherwise read a tag).
	if (Channel->QWC->getFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC) > 0)
	{
		// Check for drain stall control conditions (if we are in "refs" tag), and skip cycle if the data is not ready (when the next slice is not ready).
		if (((Channel->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::TAG) >> 12) & 0x7) == 0x4)
		{
			if (isDrainStallControlOn() && isDrainStallControlWaiting())
				return;
		}

		// Transfer a single data unit of 128 bits (same for slice and burst). This function also updates the number of units transferred.
		transferDataUnit();

		// Check for source stall control conditions (if we are in "cnts" tag), and update D_STADR if required.
		if (((Channel->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::TAG) >> 12) & 0x7) == 0x0)
		{
			if (isSourceStallControlOn())
				updateSourceStallControlAddress();
		}
		
		// If QWC is now 0, check for suspend conditions.
		if (Channel->QWC->getFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC) == 0)
		{
			// Check if we need to emit a tag interrupt (done after packet transfer has completed).
			checkDMAtagPacketInterrupt();

			// Check if we need to exit based on tag instruction ("end", "ret", etc).
			checkChainExit();
		}
	}
	else
	{
		// Read in a tag and set CHCR.TAG to bits 16-31. Also transfer the tag if the CHCR.TTE bit is set.
		readDMAtag();

		// Check if we are in source or dest chain mode. Perform action based on tag id (which will set MADR, QWC, etc).
		switch (mChannelProperties->ChainMode)
		{
		case ChainMode_t::SOURCE:
			(this->*SRC_CHAIN_INSTRUCTION_TABLE[mDMAtag.getID()])(); break;
		case ChainMode_t::DEST:
			(this->*DST_CHAIN_INSTRUCTION_TABLE[mDMAtag.getID()])(); break;
		default:
			throw std::runtime_error("Could not determine chain mode context.");
		}
	}

	// Check for the slice channel quota limit.
	checkSliceQuota();
}

void EEDmac::executionStep_Interleaved() const
{
	auto& DMAC = getResources()->EE->DMAC;
	auto& Channel = DMAC->CHANNELS[mChannelIndex];

	// Check the QWC register, make sure that size > 0 in order to start transfer.
	if (Channel->QWC->getFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC) == 0)
	{
		// TODO: implement failed transfer properly? (See page 79 of EE Users Manual).
		throw std::runtime_error("QWC == 0 at start in interleaved mode, but not implemented.");
	}
	
	// Data of size D_SQWC.TQWC is transferred first, then data of size D_SQWC.SQWC is skipped, until Dn_QWC is reached.
	if (!Channel->mInterleavedSkipState)
	{
		// Transfer data.
		transferDataUnit();
	}
	else
	{
		// Skip data by incrementing the channel MADR.
		Channel->MADR->increment();
	}

	// Increment the mInterleavedCountState.
	Channel->mInterleavedCountState += 1;

	// Check the interleaved mode (transferring/skipping), and change mInterleavedSkipState if required, based on mInterleavedCountState.
	checkInterleaveCount();

	// Check if QWC == 0 (transfer completed), in which case stop transferring and update status.
	if (Channel->QWC->getFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC) == 0)
		suspendTransfer();

	// If the physical mode is set to slice, suspend transfer after 8 units are completed.
	checkSliceQuota();
}

void EEDmac::checkSliceQuota() const
{
	auto& DMAC = getResources()->EE->DMAC;
	auto& Channel = DMAC->CHANNELS[mChannelIndex];

	// If the physical mode is set to slice, suspend transfer after 8 units are completed.
	if ((mChannelProperties->PhysicalMode == PhysicalMode_t::SLICE)
		&& (Channel->mSliceCountState % 8 == 0))
	{
		suspendTransfer();
	}
}

void EEDmac::suspendTransfer() const
{
	auto& DMAC = getResources()->EE->DMAC;
	auto& Channel = DMAC->CHANNELS[mChannelIndex];

	// Emit the interrupt status bit.
	auto& key = EEDmacRegister_STAT_t::Fields::CIS_KEYS[mChannelIndex];
	DMAC->STAT->setFieldValue(key, 1);

	// Change CHCR.STR to 0.
	Channel->CHCR->setFieldValue(EEDmacChannelRegister_CHCR_t::Fields::STR, 0);
}

void EEDmac::checkInterruptStatus() const
{
	auto& D_STAT = getResources()->EE->DMAC->STAT;
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
	auto& DMAC = getResources()->EE->DMAC;
	auto& Channel = DMAC->CHANNELS[mChannelIndex];

	Direction_t direction = mChannelProperties->Direction;
	if (direction == Direction_t::BOTH)
		direction = static_cast<Direction_t>(Channel->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::DIR));

	return direction;
}

bool EEDmac::isSourceStallControlOn() const
{
	auto& DMAC = getResources()->EE->DMAC;

	if (getRuntimeDirection() == Direction_t::FROM)
	{
		const u32 STS = DMAC->CTRL->getFieldValue(EEDmacRegister_CTRL_t::Fields::STS);
		if (mChannelIndex == EEDmacChannelTable::getSTSChannelIndex(STS))
		{
			return true;
		}
	}

	return false;
}

bool EEDmac::isDrainStallControlOn() const
{
	auto& DMAC = getResources()->EE->DMAC;

	if (getRuntimeDirection() == Direction_t::TO)
	{
		const u32 STD = DMAC->CTRL->getFieldValue(EEDmacRegister_CTRL_t::Fields::STD);
		if (mChannelIndex == EEDmacChannelTable::getSTDChannelIndex(STD))
		{
			return true;
		}
	}
	
	return false;
}

void EEDmac::updateSourceStallControlAddress() const
{
	auto& DMAC = getResources()->EE->DMAC;
	auto& Channel = DMAC->CHANNELS[mChannelIndex];

	const u32 MADR = Channel->MADR->getFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR);
	DMAC->STADR->setFieldValue(EEDmacRegister_STADR_t::Fields::ADDR, MADR);
}

bool EEDmac::isDrainStallControlWaiting() const
{
	auto& DMAC = getResources()->EE->DMAC;
	auto& Channel = DMAC->CHANNELS[mChannelIndex];

	const u32 MADR = Channel->MADR->getFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR);
	const u32 STADR = DMAC->STADR->getFieldValue(EEDmacRegister_STADR_t::Fields::ADDR);

	if ((MADR + 8) > STADR)
	{
		DMAC->STAT->setFieldValue(EEDmacRegister_STAT_t::Fields::SIS, 1);
		return true;
	}

	return false;
}

void EEDmac::transferDataUnit() const
{
	auto& DMAC = getResources()->EE->DMAC;
	auto& Channel = DMAC->CHANNELS[mChannelIndex];

	// Determine the direction of data flow. If set to BOTH (true for VIF1 and SIF2 channels), get the runtime direction by checking the CHCR.DIR field.
	Direction_t direction = getRuntimeDirection();

	// Get the main memory or SPR address we are reading or writing from. 
	const u32 PhysicalAddressOffset = Channel->MADR->getFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR);
	const bool SPRFlag = (Channel->MADR->getFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR) != 0);

	// If we are using the from/toSPR channels, then we need to get the SPR address, and take a different code path. 
	// Within the these channels MADR.SPR is always 0 on these channels (have to use the SADR register as the SPR address).
	if (mChannelProperties->ChannelID == ChannelID_t::toSPR || mChannelProperties->ChannelID == ChannelID_t::fromSPR)
	{
		// We are doing a mem->SPR or SPR->mem, use both MADR and SADR registers.
		const u32 SPRPhysicalAddressOffset = Channel->SADR->getFieldValue(EEDmacChannelRegister_SADR_t::Fields::ADDR);

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
		Channel->SADR->increment();
	}
	else {
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
	Channel->mSliceCountState += 1;
	Channel->MADR->increment();
	Channel->QWC->decrement();
}

u128 EEDmac::readDataChannel() const
{
	// TODO: implement.
	throw std::runtime_error("DMA channel read qword not implemented.");
}

void EEDmac::writeDataChannel(u128 data) const
{
	// TODO: implement.
	throw std::runtime_error("DMA channel write qword not implemented.");
}

u128 EEDmac::readDataMemory(u32 PhysicalAddressOffset, bool SPRAccess) const
{
	auto& EEMMU = getResources()->EE->PhysicalMMU;

	if (SPRAccess)
	{
		// Read spr[tadr] (lower 64 bits) and spr[tadr + 8] (upper 64 bits).
		u64 lower = EEMMU->readDwordU(PS2Constants::EE::EECore::ScratchpadMemory::PADDRESS_SCRATCHPAD_MEMORY + PhysicalAddressOffset);
		u64 upper = EEMMU->readDwordU(PS2Constants::EE::EECore::ScratchpadMemory::PADDRESS_SCRATCHPAD_MEMORY + PhysicalAddressOffset + 8);
		return u128(lower, upper);
	}
	else
	{
		// Read mem[tadr] (lower 64 bits) and mem[tadr + 8] (upper 64 bits).
		u64 lower = EEMMU->readDwordU(PhysicalAddressOffset);
		u64 upper = EEMMU->readDwordU(PhysicalAddressOffset + 8);
		return u128(lower, upper);
	}
}

void EEDmac::writeDataMemory(u32 PhysicalAddressOffset, bool SPRAccess, u128 data) const
{
	auto& EEMMU = getResources()->EE->PhysicalMMU;

	if (SPRAccess)
	{
		// Write spr[address] (lower 64 bits) and spr[address + 8] (upper 64 bits).
		EEMMU->writeDwordU(PS2Constants::EE::EECore::ScratchpadMemory::PADDRESS_SCRATCHPAD_MEMORY + PhysicalAddressOffset, data.lo);
		EEMMU->writeDwordU(PS2Constants::EE::EECore::ScratchpadMemory::PADDRESS_SCRATCHPAD_MEMORY + PhysicalAddressOffset + 8, data.hi);
	}
	else
	{
		// Write mem[address] (lower 64 bits) and mem[address + 8] (upper 64 bits).
		EEMMU->writeDwordU(PhysicalAddressOffset, data.lo);
		EEMMU->writeDwordU(PhysicalAddressOffset + 8, data.hi);
	}
}

void EEDmac::readDMAtag()
{
	auto& DMAC = getResources()->EE->DMAC;
	auto& Channel = DMAC->CHANNELS[mChannelIndex];

	// Get the main memory or SPR address we are reading or writing from.
	const u32 TADR = Channel->TADR->getFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR);
	const bool SPRFlag = (Channel->TADR->getFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR) != 0);

	// Set mDMAtag based upon the u128 read from memory.
	u128 data = readDataMemory(TADR, SPRFlag);
	mDMAtag.setValue(data.lo);

	// Set CHCR.TAG based upon the DMA tag read (bits 16-31).
	Channel->CHCR->setFieldValue(EEDmacChannelRegister_CHCR_t::Fields::TAG, (data.lo >> 16) & 0xFFFF);

	// Check if we need to transfer the tag.
	if (Channel->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::TTE))
	{
		// Write the tag to the channel.
		writeDataChannel(data);

		// Update DataCountState by 1 (counts towards slice channel quota).
		Channel->mSliceCountState += 1;
	}
}

void EEDmac::checkDMAtagPacketInterrupt() const
{
	auto& DMAC = getResources()->EE->DMAC;
	auto& Channel = DMAC->CHANNELS[mChannelIndex];

	if (Channel->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::TIE) != 0 
		&& (Channel->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::TAG) & 0x8000) != 0)
	{
		suspendTransfer();
	}
}

void EEDmac::checkChainExit() const
{
	auto& DMAC = getResources()->EE->DMAC;
	auto& Channel = DMAC->CHANNELS[mChannelIndex];

	if (Channel->mChainExitState)
	{
		// Reset chain state variables.
		Channel->mChainExitState = false;
		Channel->mChainStackLevelState = 0;

		suspendTransfer();
	}
}

void EEDmac::INSTRUCTION_UNSUPPORTED()
{
	throw std::runtime_error("DMAC chain mode called invalid tag ID");
}

void EEDmac::REFE()
{
	// Transfers QWC qwords from ADDR, and suspends after packet transfer.
	auto& DMAC = getResources()->EE->DMAC;
	auto& Channel = DMAC->CHANNELS[mChannelIndex];

	Channel->QWC->setFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC, mDMAtag.getQWC());
	Channel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mDMAtag.getADDR());
	Channel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mDMAtag.getSPR());
	Channel->mChainExitState = true;
}

void EEDmac::CNT()
{
	// Transfers QWC qwords after the tag, and reads the next qword as the next tag.
	auto& DMAC = getResources()->EE->DMAC;
	auto& Channel = DMAC->CHANNELS[mChannelIndex];

	Channel->QWC->setFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC, mDMAtag.getQWC());

	// Copy TADR + 0x10 into MADR.
	Channel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, Channel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10);
	Channel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, Channel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR));

	// Calculate where the next tag will be.
	u32 nextTagAddr = Channel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + (mDMAtag.getQWC() + 1) * 0x10;
	Channel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, nextTagAddr); // SPR flag unchanged within TADR register.
}

void EEDmac::NEXT()
{
	// Transfers QWC qwords after the tag, and reads the ADDR field as the next tag.
	auto& DMAC = getResources()->EE->DMAC;
	auto& Channel = DMAC->CHANNELS[mChannelIndex];

	Channel->QWC->setFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC, mDMAtag.getQWC());

	// Copy TADR + 0x10 into MADR.
	Channel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, Channel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10);
	Channel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, Channel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR));

	// Set next tag.
	Channel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, mDMAtag.getADDR());
	Channel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, mDMAtag.getSPR()); 
}

void EEDmac::REF()
{
	// Transfers QWC qwords from ADDR field, and reads the next qword as the tag.
	auto& DMAC = getResources()->EE->DMAC;
	auto& Channel = DMAC->CHANNELS[mChannelIndex];

	Channel->QWC->setFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC, mDMAtag.getQWC());

	// Set MADR = tag.ADDR.
	Channel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mDMAtag.getADDR());
	Channel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mDMAtag.getSPR());

	// Set next qword as tag.
	Channel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, Channel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10); // SPR flag unchanged within TADR register.
}

void EEDmac::REFS()
{
	// TODO: add in stall control.

	// Transfers QWC qwords from ADDR field, and reads the next qword as the tag.
	auto& DMAC = getResources()->EE->DMAC;
	auto& Channel = DMAC->CHANNELS[mChannelIndex];

	Channel->QWC->setFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC, mDMAtag.getQWC());

	// Set MADR = tag.ADDR.
	Channel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mDMAtag.getADDR());
	Channel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mDMAtag.getSPR());

	// Set next qword as tag.
	Channel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, Channel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10); // SPR flag unchanged within TADR register.
}

void EEDmac::CALL()
{
	// Transfers QWC qwords after tag, and pushes the next qword after the tag onto the stack. Sets the next tag to ADDR field.
	auto& DMAC = getResources()->EE->DMAC;
	auto& Channel = DMAC->CHANNELS[mChannelIndex];

	Channel->QWC->setFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC, mDMAtag.getQWC());
	Channel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, Channel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10);
	Channel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, Channel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR));
	Channel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, mDMAtag.getADDR());
	Channel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR, mDMAtag.getSPR());

	// Set stack to after tag.
	u8 & stackIdx = Channel->mChainStackLevelState;

	if (stackIdx >= 2)
	{
		// Check for stack overflow.
		Channel->mChainExitState = true;
	}
	else 
	{
		// Push onto the stack.
		Channel->ASR[stackIdx]->setFieldValue(EEDmacChannelRegister_ASR_t::Fields::ADDR, Channel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10);
		Channel->ASR[stackIdx]->setFieldValue(EEDmacChannelRegister_ASR_t::Fields::SPR, Channel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR));
		stackIdx += 1;
	}
}

void EEDmac::RET()
{
	// Transfers QWC qwords after tag, pops next tag from stack. If stack level = 0, transfers QWC qwords after tag and suspends transfer.
	auto& DMAC = getResources()->EE->DMAC;
	auto& Channel = DMAC->CHANNELS[mChannelIndex];

	u8 & stackIdx = Channel->mChainStackLevelState;	
	if (stackIdx > 0)
	{
		// Pop the stack.
		Channel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, Channel->ASR[stackIdx]->getFieldValue(EEDmacChannelRegister_ASR_t::Fields::ADDR));
		Channel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, Channel->ASR[stackIdx]->getFieldValue(EEDmacChannelRegister_ASR_t::Fields::SPR));
		stackIdx -= 1;
	}
	else
	{
		// Check for stack underflow.
		Channel->mChainExitState = true;
	}

	// In both cases, QWC following the tag is always performed.
	Channel->QWC->setFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC, mDMAtag.getQWC());
	Channel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, Channel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10);
	Channel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, Channel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR));
}

void EEDmac::END()
{
	// Transfers QWC qwords after tag, and suspends after packet transfer.
	auto& DMAC = getResources()->EE->DMAC;
	auto& Channel = DMAC->CHANNELS[mChannelIndex];

	Channel->QWC->setFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC, mDMAtag.getQWC());
	Channel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, Channel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10);
	Channel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, Channel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR));
	Channel->mChainExitState = true;
}

void EEDmac::CNTS()
{
	// TODO: need to copy MADR to STADR during the transfer.
	// Transfers QWC qwords after the tag, and reads the next qword as the next tag.
	auto& DMAC = getResources()->EE->DMAC;
	auto& Channel = DMAC->CHANNELS[mChannelIndex];

	Channel->QWC->setFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC, mDMAtag.getQWC());

	// Copy TADR + 0x10 into MADR.
	Channel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, Channel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10);
	Channel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, Channel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR));

	// Calculate where the next tag will be.
	u32 nextTagAddr = Channel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + (mDMAtag.getQWC() + 1) * 0x10;
	Channel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, nextTagAddr); // SPR flag unchanged within TADR register.
}

void EEDmac::checkInterleaveCount() const
{
	auto& DMAC = getResources()->EE->DMAC;
	auto& Channel = DMAC->CHANNELS[mChannelIndex];;

	// Are we in a transfer or skip block?
	if (!Channel->mInterleavedSkipState)
	{
		// Have we reached the TWQC limit?
		if (Channel->mInterleavedCountState >= DMAC->SQWC->getFieldValue(EEDmacRegister_SWQC_t::Fields::TQWC))
		{
			// Change to skip mode and reset the count.
			Channel->mInterleavedSkipState = !Channel->mInterleavedSkipState;
			Channel->mInterleavedCountState = 0;
		}
	}
	else
	{
		// Have we reached the SQWC limit?
		if (Channel->mInterleavedCountState >= DMAC->SQWC->getFieldValue(EEDmacRegister_SWQC_t::Fields::SQWC))
		{
			// Change to skip mode and reset the count.
			Channel->mInterleavedSkipState = !Channel->mInterleavedSkipState;
			Channel->mInterleavedCountState = 0;
		}
	}
}
