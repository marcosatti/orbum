#include "stdafx.h"

#include "VM/ExecutionCore/Interpreter/EE/DMACInterpreter/DMACInterpreter.h"
#include "Common/PS2Constants/PS2Constants.h"
#include "VM/VMMain.h"
#include "VM/VMMMUHandler/VMMMUHandler.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/EE/EECore/EECore_t.h"
#include "Common/PS2Resources/EE/EECore/EECoreExceptions/EECoreExceptions_t.h"
#include "Common/PS2Resources/EE/EECore/EECoreExceptions/Types/EECoreException_t.h"
#include "Common/PS2Resources/EE/DMAC/DMAC_t.h"
#include "Common/PS2Resources/EE/DMAC/Types/DMAC_Registers_t.h"
#include "Common/PS2Resources/EE/DMAC/Types/DMAtag_t.h"
#include "Common/Tables/EEDmacTable/EEDmacTable.h"

using ExType = EECoreException_t::ExType;
using ChannelProperties_t = EEDmacTable::ChannelProperties_t;
using ChannelID_t = EEDmacTable::ChannelID_t;
using Direction_t = EEDmacTable::Direction_t;
using PhysicalMode_t = EEDmacTable::PhysicalMode_t;
using ChainMode_t = EEDmacTable::ChainMode_t;

DMACInterpreter::DMACInterpreter(VMMain * vmMain) :
	VMExecutionCoreComponent(vmMain),
	mClockSources{ ClockSource_t::BUSCLK },
	mChannelIndex(0),
	mChannelProperties(nullptr),
	mDMAtag(0, 0)
{
}

DMACInterpreter::~DMACInterpreter()
{
}

const std::vector<ClockSource_t>& DMACInterpreter::getClockSources()
{
	return mClockSources;
}

s64 DMACInterpreter::executionStep(const ClockSource_t & clockSource)
{
	auto& DMAC = getVM()->getResources()->EE->DMAC;
	auto& DMAChannelRegisters = DMAC->DMAChannelRegisters;

	// Check if DMA transfers are enabled.
	if (!DMAC->DMAC_REGISTER_D_CTRL->getFieldValue(DmacRegisterCtrl_t::Fields::DMAE))
		return 1;

	// Check for any pending/started DMA transfers, by checking the Dn_CHCR.STR register of each channel. Perform transfer if enabled.
	for (mChannelIndex = 0; mChannelIndex < PS2Constants::EE::DMAC::NUMBER_DMA_CHANNELS; mChannelIndex++)
	{
		if (DMAChannelRegisters[mChannelIndex].CHCR->getFieldValue(DmacRegisterChcr_t::Fields::STR))
		{
			mChannelProperties = EEDmacTable::getChannelInfo(mChannelIndex);
			switch (DMAChannelRegisters[mChannelIndex].CHCR->getFieldValue(DmacRegisterChcr_t::Fields::MOD))
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

void DMACInterpreter::executionStep_Normal() const
{
	auto& DMAC = getVM()->getResources()->EE->DMAC;
	auto& channelRegisters = DMAC->DMAChannelRegisters[mChannelIndex];

	// Check the QWC register, make sure that size > 0 in order to start transfer.
	if (channelRegisters.QWC->getFieldValue(DmacRegisterQwc_t::Fields::QWC) == 0)
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
	if (channelRegisters.QWC->getFieldValue(DmacRegisterQwc_t::Fields::QWC) == 0)
		suspendTransfer();

	// If the physical mode is set to slice, suspend transfer after 8 units are completed.
	checkSliceQuota();
}

void DMACInterpreter::executionStep_Chain()
{
	auto& DMAC = getVM()->getResources()->EE->DMAC;
	auto& channelRegisters = DMAC->DMAChannelRegisters[mChannelIndex];

	// Check the QWC register, make sure that size > 0 for a transfer to occur (otherwise read a tag).
	if (channelRegisters.QWC->getFieldValue(DmacRegisterQwc_t::Fields::QWC) > 0)
	{
		// Check for drain stall control conditions (if we are in "refs" tag), and skip cycle if the data is not ready (when the next slice is not ready).
		if (((channelRegisters.CHCR->getFieldValue(DmacRegisterChcr_t::Fields::TAG) >> 12) & 0x7) == 0x4)
		{
			if (isDrainStallControlOn() && isDrainStallControlWaiting())
				return;
		}

		// Transfer a single data unit of 128 bits (same for slice and burst). This function also updates the number of units transferred.
		transferDataUnit();

		// Check for source stall control conditions (if we are in "cnts" tag), and update D_STADR if required.
		if (((channelRegisters.CHCR->getFieldValue(DmacRegisterChcr_t::Fields::TAG) >> 12) & 0x7) == 0x0)
		{
			if (isSourceStallControlOn())
				updateSourceStallControlAddress();
		}
		
		// If QWC is now 0, check for suspend conditions.
		if (channelRegisters.QWC->getFieldValue(DmacRegisterQwc_t::Fields::QWC) == 0)
		{
			// Check if we need to emit a tag interrupt (done after packet transfer has completed).
			checkDMAtagPacketInterrupt();

			// Check if we need to exit based on tag instruction ("end", "ret", etc).
			checkChainExit();
		}
	}
	else
	{
		// Read in a tag and set CHCR.TAG to bits 16-31.
		readDMAtag();

		// Check if we need to transfer the tag.
		if (channelRegisters.CHCR->getFieldValue(DmacRegisterChcr_t::Fields::TTE))
			transferDMAtag();

		// Check if we are in source or dest chain mode. Perform action based on tag id (which will set MADR, QWC, etc).
		switch (mChannelProperties->ChainMode)
		{
		case ChainMode_t::SOURCE:
			(this->*SRC_CHAIN_INSTRUCTION_TABLE[mDMAtag.ID])(); break;
		case ChainMode_t::DEST:
			(this->*DST_CHAIN_INSTRUCTION_TABLE[mDMAtag.ID])(); break;
		default:
			throw std::runtime_error("Could not determine chain mode context.");
		}
	}

	// Check for the slice channel quota limit.
	checkSliceQuota();
}

void DMACInterpreter::executionStep_Interleaved() const
{
	auto& DMAC = getVM()->getResources()->EE->DMAC;
	auto& channelRegisters = DMAC->DMAChannelRegisters[mChannelIndex];

	// Check the QWC register, make sure that size > 0 in order to start transfer.
	if (channelRegisters.QWC->getFieldValue(DmacRegisterQwc_t::Fields::QWC) == 0)
	{
		// TODO: implement failed transfer properly? (See page 79 of EE Users Manual).
		throw std::runtime_error("QWC == 0 at start in interleaved mode, but not implemented.");
	}
	
	// Data of size D_SQWC.TQWC is transferred first, then data of size D_SQWC.SQWC is skipped, until Dn_QWC is reached.
	if (!DMAC->InterleavedSkipState[mChannelIndex])
	{
		// Transfer data.
		transferDataUnit();
	}
	else
	{
		// Skip data by incrementing the channel MADR.
		channelRegisters.MADR->increment();
	}

	// Increment the InterleavedCountState.
	DMAC->InterleavedCountState[mChannelIndex] += 1;

	// Check the interleaved mode (transferring/skipping), and change InterleavedSkipState if required, based on InterleavedCountState.
	checkInterleaveCount();

	// Check if QWC == 0 (transfer completed), in which case stop transferring and update status.
	if (channelRegisters.QWC->getFieldValue(DmacRegisterQwc_t::Fields::QWC) == 0)
		suspendTransfer();

	// If the physical mode is set to slice, suspend transfer after 8 units are completed.
	checkSliceQuota();
}

void DMACInterpreter::checkSliceQuota() const
{
	auto& DMAC = getVM()->getResources()->EE->DMAC;

	// If the physical mode is set to slice, suspend transfer after 8 units are completed.
	if ((mChannelProperties->PhysicalMode == PhysicalMode_t::SLICE)
		&& (DMAC->SliceCountState[mChannelIndex] % 8 == 0))
	{
		suspendTransfer();
	}
}

void DMACInterpreter::suspendTransfer() const
{
	auto& D_STAT = getVM()->getResources()->EE->DMAC->DMAC_REGISTER_D_STAT;
	auto& channelRegisters = getVM()->getResources()->EE->DMAC->DMAChannelRegisters[mChannelIndex];

	// Emit the interrupt status bit.
	auto& key = DmacRegisterStat_t::Fields::CIS_KEYS[mChannelIndex];
	D_STAT->setFieldValue(key, 1);

	// Change CHCR.STR to 0.
	channelRegisters.CHCR->setFieldValue(DmacRegisterChcr_t::Fields::STR, 0);
}

void DMACInterpreter::checkInterruptStatus() const
{
	auto& D_STAT = getVM()->getResources()->EE->DMAC->DMAC_REGISTER_D_STAT;
	auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;

	// Check channel interrupt status.
	for (auto i = 0; i < PS2Constants::EE::DMAC::NUMBER_DMA_CHANNELS; i++)
	{
		auto& cis_key = DmacRegisterStat_t::Fields::CIS_KEYS[i];
		auto& cim_key = DmacRegisterStat_t::Fields::CIM_KEYS[i];

		auto& cisValue = D_STAT->getFieldValue(cis_key);
		auto& cimValue = D_STAT->getFieldValue(cim_key);

		// Set EE Core interrupt if (CIS & CIM) is true.
		if (cisValue & cimValue)
		{
			IntExceptionInfo_t intex = { 1, 0, 0 };
			Exceptions->setException(EECoreException_t(ExType::EX_INTERRUPT, nullptr, &intex, nullptr));
		}
	}

	// Check stall control interrupt status.
	if (D_STAT->getFieldValue(DmacRegisterStat_t::Fields::SIS) & D_STAT->getFieldValue(DmacRegisterStat_t::Fields::SIS))
	{
		IntExceptionInfo_t intex = { 1, 0, 0 };
		Exceptions->setException(EECoreException_t(ExType::EX_INTERRUPT, nullptr, &intex, nullptr));
	}

	// Check MFIFO interrupt status.
	if (D_STAT->getFieldValue(DmacRegisterStat_t::Fields::MEIS) & D_STAT->getFieldValue(DmacRegisterStat_t::Fields::MEIM))
	{
		IntExceptionInfo_t intex = { 1, 0, 0 };
		Exceptions->setException(EECoreException_t(ExType::EX_INTERRUPT, nullptr, &intex, nullptr));
	}

	// Check for BUSERR interrupt status.
	if (D_STAT->getFieldValue(DmacRegisterStat_t::Fields::BEIS))
	{
		IntExceptionInfo_t intex = { 1, 0, 0 };
		Exceptions->setException(EECoreException_t(ExType::EX_INTERRUPT, nullptr, &intex, nullptr));
	}
}

Direction_t DMACInterpreter::getRuntimeDirection() const
{
	auto& DMAC = getVM()->getResources()->EE->DMAC;
	auto& channelRegisters = DMAC->DMAChannelRegisters[mChannelIndex];

	Direction_t direction = mChannelProperties->Direction;
	if (direction == Direction_t::BOTH)
		direction = static_cast<Direction_t>(channelRegisters.CHCR->getFieldValue(DmacRegisterChcr_t::Fields::DIR));

	return direction;
}

bool DMACInterpreter::isSourceStallControlOn() const
{
	auto& DMAC = getVM()->getResources()->EE->DMAC;

	if (getRuntimeDirection() == Direction_t::FROM)
	{
		const u32 STS = DMAC->DMAC_REGISTER_D_CTRL->getFieldValue(DmacRegisterCtrl_t::Fields::STS);
		if (mChannelIndex == EEDmacTable::getSTSChannelIndex(STS))
		{
			return true;
		}
	}

	return false;
}

bool DMACInterpreter::isDrainStallControlOn() const
{
	auto& DMAC = getVM()->getResources()->EE->DMAC;

	if (getRuntimeDirection() == Direction_t::TO)
	{
		const u32 STD = DMAC->DMAC_REGISTER_D_CTRL->getFieldValue(DmacRegisterCtrl_t::Fields::STD);
		if (mChannelIndex == EEDmacTable::getSTDChannelIndex(STD))
		{
			return true;
		}
	}
	
	return false;
}

void DMACInterpreter::updateSourceStallControlAddress() const
{
	auto& DMAC = getVM()->getResources()->EE->DMAC;
	auto& channelRegisters = DMAC->DMAChannelRegisters[mChannelIndex];

	const u32 MADR = channelRegisters.MADR->getFieldValue(DmacRegisterMadr_t::Fields::ADDR);
	DMAC->DMAC_REGISTER_D_STADR->setFieldValue(DmacRegisterStadr_t::Fields::ADDR, MADR);
}

bool DMACInterpreter::isDrainStallControlWaiting() const
{
	auto& DMAC = getVM()->getResources()->EE->DMAC;
	auto& channelRegisters = DMAC->DMAChannelRegisters[mChannelIndex];

	const u32 MADR = channelRegisters.MADR->getFieldValue(DmacRegisterMadr_t::Fields::ADDR);
	const u32 STADR = DMAC->DMAC_REGISTER_D_STADR->getFieldValue(DmacRegisterStadr_t::Fields::ADDR);

	if ((MADR + 8) > STADR)
	{
		DMAC->DMAC_REGISTER_D_STAT->setFieldValue(DmacRegisterStat_t::Fields::SIS, 1);
		return true;
	}

	return false;
}

void DMACInterpreter::transferDataUnit() const
{
	auto& DMAC = getVM()->getResources()->EE->DMAC;
	auto& channelRegisters = DMAC->DMAChannelRegisters[mChannelIndex];

	// Determine the direction of data flow. If set to BOTH (true for VIF1 and SIF2 channels), get the runtime direction by checking the CHCR.DIR field.
	Direction_t direction = getRuntimeDirection();

	// Get the main memory or SPR address we are reading or writing from. 
	const u32 PhysicalAddressOffset = channelRegisters.MADR->getFieldValue(DmacRegisterMadr_t::Fields::ADDR);
	const bool SPRFlag = (channelRegisters.MADR->getFieldValue(DmacRegisterMadr_t::Fields::SPR) != 0);

	// If we are using the from/toSPR channels, then we need to get the SPR address, and take a different code path. 
	// Within the these channels MADR.SPR is always 0 on these channels (have to use the SADR register as the SPR address).
	if (mChannelProperties->ChannelID == ChannelID_t::toSPR || mChannelProperties->ChannelID == ChannelID_t::fromSPR)
	{
		// We are doing a mem->SPR or SPR->mem, use both MADR and SADR registers.
		const u32 SPRPhysicalAddressOffset = channelRegisters.SADR->getFieldValue(DmacRegisterSadr_t::Fields::ADDR);

		if (direction == Direction_t::FROM)
		{
			DMADataUnit_t packet = readDataMemory(SPRPhysicalAddressOffset, true);
			writeDataMemory(PhysicalAddressOffset, false, packet);
		}
		else if (direction == Direction_t::TO)
		{
			DMADataUnit_t packet = readDataMemory(PhysicalAddressOffset, false);
			writeDataMemory(SPRPhysicalAddressOffset, true, packet);
		}

		// Increment the SADR address as well as MADR etc (done below).
		channelRegisters.SADR->increment();
	}
	else {
		// Else transfer data normally.
		if (direction == Direction_t::FROM)
		{
			DMADataUnit_t packet = readDataChannel();
			writeDataMemory(PhysicalAddressOffset, SPRFlag, packet);
		}
		else if (direction == Direction_t::TO)
		{
			DMADataUnit_t packet = readDataMemory(PhysicalAddressOffset, SPRFlag);
			writeDataChannel(packet);
		}
	}

	// Update DataCountState by 1, the MADR register by 0x10 (increment), and decrement the QWC register by 1.
	DMAC->SliceCountState[mChannelIndex] += 1;
	channelRegisters.MADR->increment();
	channelRegisters.QWC->decrement();
}

DMADataUnit_t DMACInterpreter::readDataChannel() const
{
	// TODO: implement.
	throw std::runtime_error("DMA channel read qword not implemented.");
}

void DMACInterpreter::writeDataChannel(DMADataUnit_t data) const
{
	// TODO: implement.
	throw std::runtime_error("DMA channel write qword not implemented.");
}

DMADataUnit_t DMACInterpreter::readDataMemory(u32 PhysicalAddressOffset, bool SPRAccess) const
{
	auto& VMMMU = getVM()->getMMU();

	if (SPRAccess)
	{
		// Read spr[tadr] (lower 64 bits) and spr[tadr + 8] (upper 64 bits).
		u64 lower = VMMMU->readDwordU(PS2Constants::EE::EECore::ScratchpadMemory::PADDRESS_SCRATCHPAD_MEMORY + PhysicalAddressOffset);
		u64 upper = VMMMU->readDwordU(PS2Constants::EE::EECore::ScratchpadMemory::PADDRESS_SCRATCHPAD_MEMORY + PhysicalAddressOffset + 8);
		return DMADataUnit_t(lower, upper);
	}
	else
	{
		// Read mem[tadr] (lower 64 bits) and mem[tadr + 8] (upper 64 bits).
		u64 lower = VMMMU->readDwordU(PhysicalAddressOffset);
		u64 upper = VMMMU->readDwordU(PhysicalAddressOffset + 8);
		return DMADataUnit_t(lower, upper);
	}
}

void DMACInterpreter::writeDataMemory(u32 PhysicalAddressOffset, bool SPRAccess, DMADataUnit_t data) const
{
	auto& VMMMU = getVM()->getMMU();

	if (SPRAccess)
	{
		// Write spr[address] (lower 64 bits) and spr[address + 8] (upper 64 bits).
		VMMMU->writeDwordU(PS2Constants::EE::EECore::ScratchpadMemory::PADDRESS_SCRATCHPAD_MEMORY + PhysicalAddressOffset, data.mDataUnit[0]);
		VMMMU->writeDwordU(PS2Constants::EE::EECore::ScratchpadMemory::PADDRESS_SCRATCHPAD_MEMORY + PhysicalAddressOffset + 8, data.mDataUnit[1]);
	}
	else
	{
		// Write mem[address] (lower 64 bits) and mem[address + 8] (upper 64 bits).
		VMMMU->writeDwordU(PhysicalAddressOffset, data.mDataUnit[0]);
		VMMMU->writeDwordU(PhysicalAddressOffset + 8, data.mDataUnit[1]);
	}
}

void DMACInterpreter::readDMAtag()
{
	auto& channelRegisters = getVM()->getResources()->EE->DMAC->DMAChannelRegisters[mChannelIndex];

	// Get the main memory or SPR address we are reading or writing from.
	const u32 TADR = channelRegisters.TADR->getFieldValue(DmacRegisterMadr_t::Fields::ADDR);
	const bool SPRFlag = (channelRegisters.TADR->getFieldValue(DmacRegisterMadr_t::Fields::SPR) != 0);

	// Set mDMAtag based upon the DMADataUnit_t read from memory.
	mDMAtag = readDataMemory(TADR, SPRFlag);

	// Set CHCR.TAG based upon the DMA tag read (bits 16-31).
	channelRegisters.CHCR->setFieldValue(DmacRegisterChcr_t::Fields::TAG, (mDMAtag.getDMADataUnit().mDataUnit[0] >> 16) & 0xFFFF);
}

void DMACInterpreter::transferDMAtag() const
{
	auto& DMAC = getVM()->getResources()->EE->DMAC;
	auto& channelRegisters = DMAC->DMAChannelRegisters[mChannelIndex];

	// Write the tag to the channel.
	writeDataChannel(mDMAtag.getDMADataUnit());

	// Update DataCountState by 1 (counts towards slice channel quota).
	DMAC->SliceCountState[mChannelIndex] += 1;
}

void DMACInterpreter::checkDMAtagPacketInterrupt() const
{
	auto& DMAC = getVM()->getResources()->EE->DMAC;
	auto& channelRegisters = DMAC->DMAChannelRegisters[mChannelIndex];

	if (channelRegisters.CHCR->getFieldValue(DmacRegisterChcr_t::Fields::TIE) != 0 
		&& (channelRegisters.CHCR->getFieldValue(DmacRegisterChcr_t::Fields::TAG) & 0x8000) != 0)
	{
		suspendTransfer();
	}
}

void DMACInterpreter::checkChainExit() const
{
	auto& DMAC = getVM()->getResources()->EE->DMAC;

	if (DMAC->ChainExitState[mChannelIndex])
	{
		// Reset chain state variables.
		DMAC->ChainExitState[mChannelIndex] = false;
		DMAC->ChainStackLevelState[mChannelIndex] = 0;

		suspendTransfer();
	}
}

void DMACInterpreter::INSTRUCTION_UNSUPPORTED()
{
	throw std::runtime_error("DMAC chain mode called invalid tag ID");
}

void DMACInterpreter::REFE()
{
	// Transfers QWC qwords from ADDR, and suspends after packet transfer.
	auto& DMAC = getVM()->getResources()->EE->DMAC;
	auto& channelRegisters = DMAC->DMAChannelRegisters[mChannelIndex];

	channelRegisters.QWC->setFieldValue(DmacRegisterQwc_t::Fields::QWC, mDMAtag.QWC);
	channelRegisters.MADR->setFieldValue(DmacRegisterMadr_t::Fields::ADDR, mDMAtag.ADDR);
	channelRegisters.MADR->setFieldValue(DmacRegisterMadr_t::Fields::SPR, mDMAtag.SPR);
	DMAC->ChainExitState[mChannelIndex] = true;
}

void DMACInterpreter::CNT()
{
	// Transfers QWC qwords after the tag, and reads the next qword as the next tag.
	auto& DMAC = getVM()->getResources()->EE->DMAC;
	auto& channelRegisters = DMAC->DMAChannelRegisters[mChannelIndex];

	channelRegisters.QWC->setFieldValue(DmacRegisterQwc_t::Fields::QWC, mDMAtag.QWC);

	// Copy TADR + 0x10 into MADR.
	channelRegisters.MADR->setFieldValue(DmacRegisterMadr_t::Fields::ADDR, channelRegisters.TADR->getFieldValue(DmacRegisterTadr_t::Fields::ADDR) + 0x10);
	channelRegisters.MADR->setFieldValue(DmacRegisterMadr_t::Fields::SPR, channelRegisters.TADR->getFieldValue(DmacRegisterTadr_t::Fields::SPR));

	// Calculate where the next tag will be.
	u32 nextTagAddr = channelRegisters.TADR->getFieldValue(DmacRegisterTadr_t::Fields::ADDR) + (mDMAtag.QWC + 1) * 0x10;
	channelRegisters.TADR->setFieldValue(DmacRegisterTadr_t::Fields::ADDR, nextTagAddr); // SPR flag unchanged within TADR register.
}

void DMACInterpreter::NEXT()
{
	// Transfers QWC qwords after the tag, and reads the ADDR field as the next tag.
	auto& DMAC = getVM()->getResources()->EE->DMAC;
	auto& channelRegisters = DMAC->DMAChannelRegisters[mChannelIndex];

	channelRegisters.QWC->setFieldValue(DmacRegisterQwc_t::Fields::QWC, mDMAtag.QWC);

	// Copy TADR + 0x10 into MADR.
	channelRegisters.MADR->setFieldValue(DmacRegisterMadr_t::Fields::ADDR, channelRegisters.TADR->getFieldValue(DmacRegisterTadr_t::Fields::ADDR) + 0x10);
	channelRegisters.MADR->setFieldValue(DmacRegisterMadr_t::Fields::SPR, channelRegisters.TADR->getFieldValue(DmacRegisterTadr_t::Fields::SPR));

	// Set next tag.
	channelRegisters.TADR->setFieldValue(DmacRegisterTadr_t::Fields::ADDR, mDMAtag.ADDR);
	channelRegisters.TADR->setFieldValue(DmacRegisterTadr_t::Fields::ADDR, mDMAtag.SPR); 
}

void DMACInterpreter::REF()
{
	// Transfers QWC qwords from ADDR field, and reads the next qword as the tag.
	auto& DMAC = getVM()->getResources()->EE->DMAC;
	auto& channelRegisters = DMAC->DMAChannelRegisters[mChannelIndex];

	channelRegisters.QWC->setFieldValue(DmacRegisterQwc_t::Fields::QWC, mDMAtag.QWC);

	// Set MADR = tag.ADDR.
	channelRegisters.MADR->setFieldValue(DmacRegisterMadr_t::Fields::ADDR, mDMAtag.ADDR);
	channelRegisters.MADR->setFieldValue(DmacRegisterMadr_t::Fields::SPR, mDMAtag.SPR);

	// Set next qword as tag.
	channelRegisters.TADR->setFieldValue(DmacRegisterTadr_t::Fields::ADDR, channelRegisters.TADR->getFieldValue(DmacRegisterTadr_t::Fields::ADDR) + 0x10); // SPR flag unchanged within TADR register.
}

void DMACInterpreter::REFS()
{
	// TODO: add in stall control.

	// Transfers QWC qwords from ADDR field, and reads the next qword as the tag.
	auto& DMAC = getVM()->getResources()->EE->DMAC;
	auto& channelRegisters = DMAC->DMAChannelRegisters[mChannelIndex];

	channelRegisters.QWC->setFieldValue(DmacRegisterQwc_t::Fields::QWC, mDMAtag.QWC);

	// Set MADR = tag.ADDR.
	channelRegisters.MADR->setFieldValue(DmacRegisterMadr_t::Fields::ADDR, mDMAtag.ADDR);
	channelRegisters.MADR->setFieldValue(DmacRegisterMadr_t::Fields::SPR, mDMAtag.SPR);

	// Set next qword as tag.
	channelRegisters.TADR->setFieldValue(DmacRegisterTadr_t::Fields::ADDR, channelRegisters.TADR->getFieldValue(DmacRegisterTadr_t::Fields::ADDR) + 0x10); // SPR flag unchanged within TADR register.
}

void DMACInterpreter::CALL()
{
	// Transfers QWC qwords after tag, and pushes the next qword after the tag onto the stack. Sets the next tag to ADDR field.
	auto& DMAC = getVM()->getResources()->EE->DMAC;
	auto& channelRegisters = DMAC->DMAChannelRegisters[mChannelIndex];

	channelRegisters.QWC->setFieldValue(DmacRegisterQwc_t::Fields::QWC, mDMAtag.QWC);
	channelRegisters.MADR->setFieldValue(DmacRegisterMadr_t::Fields::ADDR, channelRegisters.TADR->getFieldValue(DmacRegisterTadr_t::Fields::ADDR) + 0x10);
	channelRegisters.MADR->setFieldValue(DmacRegisterMadr_t::Fields::SPR, channelRegisters.TADR->getFieldValue(DmacRegisterTadr_t::Fields::SPR));
	channelRegisters.TADR->setFieldValue(DmacRegisterTadr_t::Fields::ADDR, mDMAtag.ADDR);
	channelRegisters.TADR->setFieldValue(DmacRegisterTadr_t::Fields::SPR, mDMAtag.SPR);

	// Set stack to after tag.
	u8 & stackIdx = DMAC->ChainStackLevelState[mChannelIndex];

	if (stackIdx >= 2)
	{
		// Check for stack overflow.
		DMAC->ChainExitState[mChannelIndex] = true;
	}
	else 
	{
		// Push onto the stack.
		channelRegisters.ASR[stackIdx]->setFieldValue(DmacRegisterAsr_t::Fields::ADDR, channelRegisters.TADR->getFieldValue(DmacRegisterTadr_t::Fields::ADDR) + 0x10);
		channelRegisters.ASR[stackIdx]->setFieldValue(DmacRegisterAsr_t::Fields::SPR, channelRegisters.TADR->getFieldValue(DmacRegisterTadr_t::Fields::SPR));
		stackIdx += 1;
	}
}

void DMACInterpreter::RET()
{
	// Transfers QWC qwords after tag, pops next tag from stack. If stack level = 0, transfers QWC qwords after tag and suspends transfer.
	auto& DMAC = getVM()->getResources()->EE->DMAC;
	auto& channelRegisters = DMAC->DMAChannelRegisters[mChannelIndex];

	u8 & stackIdx = DMAC->ChainStackLevelState[mChannelIndex];	
	if (stackIdx > 0)
	{
		// Pop the stack.
		channelRegisters.TADR->setFieldValue(DmacRegisterTadr_t::Fields::ADDR, channelRegisters.ASR[stackIdx]->getFieldValue(DmacRegisterAsr_t::Fields::ADDR));
		channelRegisters.TADR->setFieldValue(DmacRegisterTadr_t::Fields::ADDR, channelRegisters.ASR[stackIdx]->getFieldValue(DmacRegisterAsr_t::Fields::SPR));
		stackIdx -= 1;
	}
	else
	{
		// Check for stack underflow.
		DMAC->ChainExitState[mChannelIndex] = true;
	}

	// In both cases, QWC following the tag is always performed.
	channelRegisters.QWC->setFieldValue(DmacRegisterQwc_t::Fields::QWC, mDMAtag.QWC);
	channelRegisters.MADR->setFieldValue(DmacRegisterMadr_t::Fields::ADDR, channelRegisters.TADR->getFieldValue(DmacRegisterTadr_t::Fields::ADDR) + 0x10);
	channelRegisters.MADR->setFieldValue(DmacRegisterMadr_t::Fields::SPR, channelRegisters.TADR->getFieldValue(DmacRegisterTadr_t::Fields::SPR));
}

void DMACInterpreter::END()
{
	// Transfers QWC qwords after tag, and suspends after packet transfer.
	auto& DMAC = getVM()->getResources()->EE->DMAC;
	auto& channelRegisters = DMAC->DMAChannelRegisters[mChannelIndex];

	channelRegisters.QWC->setFieldValue(DmacRegisterQwc_t::Fields::QWC, mDMAtag.QWC);
	channelRegisters.MADR->setFieldValue(DmacRegisterMadr_t::Fields::ADDR, channelRegisters.TADR->getFieldValue(DmacRegisterTadr_t::Fields::ADDR) + 0x10);
	channelRegisters.MADR->setFieldValue(DmacRegisterMadr_t::Fields::SPR, channelRegisters.TADR->getFieldValue(DmacRegisterTadr_t::Fields::SPR));
	DMAC->ChainExitState[mChannelIndex] = true;
}

void DMACInterpreter::CNTS()
{
	// TODO: need to copy MADR to STADR during the transfer.
	// Transfers QWC qwords after the tag, and reads the next qword as the next tag.
	auto& DMAC = getVM()->getResources()->EE->DMAC;
	auto& channelRegisters = DMAC->DMAChannelRegisters[mChannelIndex];

	channelRegisters.QWC->setFieldValue(DmacRegisterQwc_t::Fields::QWC, mDMAtag.QWC);

	// Copy TADR + 0x10 into MADR.
	channelRegisters.MADR->setFieldValue(DmacRegisterMadr_t::Fields::ADDR, channelRegisters.TADR->getFieldValue(DmacRegisterTadr_t::Fields::ADDR) + 0x10);
	channelRegisters.MADR->setFieldValue(DmacRegisterMadr_t::Fields::SPR, channelRegisters.TADR->getFieldValue(DmacRegisterTadr_t::Fields::SPR));

	// Calculate where the next tag will be.
	u32 nextTagAddr = channelRegisters.TADR->getFieldValue(DmacRegisterTadr_t::Fields::ADDR) + (mDMAtag.QWC + 1) * 0x10;
	channelRegisters.TADR->setFieldValue(DmacRegisterTadr_t::Fields::ADDR, nextTagAddr); // SPR flag unchanged within TADR register.
}

void DMACInterpreter::checkInterleaveCount() const
{
	auto& DMAC = getVM()->getResources()->EE->DMAC;

	// Are we in a transfer or skip block?
	if (!DMAC->InterleavedSkipState[mChannelIndex])
	{
		// Have we reached the TWQC limit?
		if (DMAC->InterleavedCountState[mChannelIndex] >= DMAC->DMAC_REGISTER_D_SQWC->getFieldValue(DmacRegisterSqwc_t::Fields::TQWC))
		{
			// Change to skip mode and reset the count.
			DMAC->InterleavedSkipState[mChannelIndex] = !DMAC->InterleavedSkipState[mChannelIndex];
			DMAC->InterleavedCountState[mChannelIndex] = 0;
		}
	}
	else
	{
		// Have we reached the SQWC limit?
		if (DMAC->InterleavedCountState[mChannelIndex] >= DMAC->DMAC_REGISTER_D_SQWC->getFieldValue(DmacRegisterSqwc_t::Fields::SQWC))
		{
			// Change to skip mode and reset the count.
			DMAC->InterleavedSkipState[mChannelIndex] = !DMAC->InterleavedSkipState[mChannelIndex];
			DMAC->InterleavedCountState[mChannelIndex] = 0;
		}
	}
}
