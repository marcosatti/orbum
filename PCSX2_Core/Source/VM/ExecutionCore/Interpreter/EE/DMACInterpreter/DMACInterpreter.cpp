#include "stdafx.h"

#include "VM/ExecutionCore/Interpreter/EE/DMACInterpreter/DMACInterpreter.h"
#include "Common/PS2Constants/PS2Constants.h"
#include "VM/VMMain.h"
#include "VM/VMMMUHandler/VMMMUHandler.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/EE/EECore/EECore_t.h"
#include "Common/PS2Resources/EE/EECore/Exceptions/Exceptions_t.h"
#include "Common/PS2Resources/EE/EECore/Exceptions/Types/EECoreException_t.h"
#include "Common/PS2Resources/EE/DMAC/DMAC_t.h"
#include "Common/PS2Resources/EE/Types/EE_Registers_t.h"
#include "Common/PS2Resources/EE/DMAC/Types/DMAtag_t.h"

using ExType = EECoreException_t::ExType;

DMACInterpreter::DMACInterpreter(VMMain * vmMain) :
	VMExecutionCoreComponent(vmMain), 
	mChannelID(0), 
	mDMAtag(0, 0)
{
}

DMACInterpreter::~DMACInterpreter()
{
}

void DMACInterpreter::executionStep()
{
	auto& EE = getVM()->getResources()->EE;
	auto& DMAChannelRegisters = EE->DMAChannelRegisters;

	// Check if DMA transfers are enabled.
	if (!EE->EE_REGISTER_D_CTRL->getFieldValue(EERegisterDmacCtrl_t::Fields::DMAE))
		return;

	// Check for any pending/started DMA transfers, by checking the Dn_CHCR.STR register of each channel. Perform transfer if enabled.
	for (mChannelID = 0; mChannelID < PS2Constants::EE::DMAC::NUMBER_DMA_CHANNELS; mChannelID++)
	{
		if (DMAChannelRegisters[mChannelID].CHCR->getFieldValue(EERegisterDmacChcr_t::Fields::STR))
		{
			switch (DMAChannelRegisters[mChannelID].CHCR->getFieldValue(EERegisterDmacChcr_t::Fields::MOD))
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
}

void DMACInterpreter::executionStep_Normal() const
{
	auto& EE = getVM()->getResources()->EE;
	auto& channelRegisters = EE->DMAChannelRegisters[mChannelID];
	auto& channelProperties = ChannelProperties[mChannelID];

	// Check the QWC register, make sure that size > 0 in order to start transfer.
	if (channelRegisters.QWC->getFieldValue(EERegisterDmacQwc_t::Fields::QWC) == 0)
	{
		// TODO: implement failed transfer properly? (See page 79 of EE Users Manual).
		throw std::runtime_error("QWC == 0 at start in normal mode, but not implemented.");
	}
	
	// Transfer a single data unit of 128 bits (same for slice and burst). This function also updates the number of units transferred.
	transferDataUnit();

	// Check if QWC == 0 (transfer completed), in which case stop transferring and update status.
	if (channelRegisters.QWC->getFieldValue(EERegisterDmacQwc_t::Fields::QWC) == 0)
		suspendTransfer();

	// If the physical mode is set to slice, suspend transfer after 8 units are completed.
	if ((channelProperties.PhysicalMode == PhysicalMode_t::SLICE) && (EE->DMAC->SliceCountState[mChannelID] % 8 == 0))
		suspendTransfer();
}

void DMACInterpreter::executionStep_Chain()
{
	auto& EE = getVM()->getResources()->EE;
	auto& channelRegisters = EE->DMAChannelRegisters[mChannelID];
	auto& channelProperties = ChannelProperties[mChannelID];

	// Check the QWC register, make sure that size > 0 for a transfer to occur (otherwise read a tag).
	if (channelRegisters.QWC->getFieldValue(EERegisterDmacQwc_t::Fields::QWC) > 0)
	{
		// Transfer a single data unit of 128 bits (same for slice and burst). This function also updates the number of units transferred.
		transferDataUnit();

		// If QWC is now 0, we need to check for tag interrupts or end the DMA transfer (if the tag ID was "end" etc.).
		if (channelRegisters.QWC->getFieldValue(EERegisterDmacQwc_t::Fields::QWC) == 0)
		{
			// Check if we need to emit a tag interrupt.
			checkDMAtagPacketInterrupt();

			// Check if we need to exit based on tag instruction ("end", "ret", etc).
			checkChainExit();
		}
	}
	else
	{
		// Read in a tag and set CHCH.TAG field (to bits 16-31 of the DMAtag read).
		mDMAtag = readDMAtag();
		channelRegisters.CHCR->setFieldValue(EERegisterDmacChcr_t::Fields::TAG, (mDMAtag.getDMADataUnit().mDataUnit[0] >> 16) & 0xFFFF);

		// Check if we need to transfer the tag.
		if (channelRegisters.CHCR->getFieldValue(EERegisterDmacChcr_t::Fields::TTE))
			transferDMAtag();

		// Check if we are in source or dest chain mode. Perform action based on tag id (which will set MADR, QWC, etc).
		switch (channelProperties.ChainMode)
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

void DMACInterpreter::executionStep_Interleaved()
{
	// TODO: implement.
	throw std::runtime_error("DMA interleaved mode not implemented.");
}

void DMACInterpreter::checkSliceQuota() const
{
	auto& EE = getVM()->getResources()->EE;
	auto& channelProperties = ChannelProperties[mChannelID];

	// If the physical mode is set to slice, suspend transfer after 8 units are completed.
	if ((channelProperties.PhysicalMode == PhysicalMode_t::SLICE)
		&& (EE->DMAC->SliceCountState[mChannelID] % 8 == 0))
	{
		suspendTransfer();
	}
}

void DMACInterpreter::suspendTransfer() const
{
	auto& EE = getVM()->getResources()->EE;
	auto& D_STAT = getVM()->getResources()->EE->EE_REGISTER_D_STAT;
	auto& channelRegisters = getVM()->getResources()->EE->DMAChannelRegisters[mChannelID];

	// Emit the interrupt status bit.
	auto& key = EERegisterDmacStat_t::Fields::CIS_KEYS[mChannelID];
	D_STAT->setFieldValue(key, 1);

	// Change CHCR.STR to 0.
	channelRegisters.CHCR->setFieldValue(EERegisterDmacChcr_t::Fields::STR, 0);
}

void DMACInterpreter::checkInterruptStatus() const
{
	auto& D_STAT = getVM()->getResources()->EE->EE_REGISTER_D_STAT;
	auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;

	for (auto i = 0; i < PS2Constants::EE::DMAC::NUMBER_DMA_CHANNELS; i++)
	{
		auto& cis_key = EERegisterDmacStat_t::Fields::CIS_KEYS[i];
		auto& cim_key = EERegisterDmacStat_t::Fields::CIM_KEYS[i];

		auto& cisValue = D_STAT->getFieldValue(cis_key);
		auto& cimValue = D_STAT->getFieldValue(cim_key);

		// Set EE Core interrupt if (CIS & CIM) is true.
		if (cisValue & cimValue)
		{
			IntExceptionInfo_t intex = { 1, 0, 0 };
			Exceptions->setException(EECoreException_t(ExType::EX_INTERRUPT, nullptr, &intex, nullptr));
		}
	}
}

void DMACInterpreter::transferDataUnit() const
{
	auto& EE = getVM()->getResources()->EE;
	auto& channelRegisters = EE->DMAChannelRegisters[mChannelID];
	auto& channelProperties = ChannelProperties[mChannelID];

	// Determine the direction of data flow. If set to BOTH (true for VIF1 and SIF2 channels), get the runtime direction by checking the CHCR.DIR field.
	Direction_t direction = channelProperties.Direction;
	if (direction == Direction_t::BOTH)
		direction = static_cast<Direction_t>(channelRegisters.CHCR->getFieldValue(EERegisterDmacChcr_t::Fields::DIR));

	// Get the main memory or SPR address we are reading or writing from. 
	const u32 PhysicalAddressOffset = channelRegisters.MADR->getFieldValue(EERegisterDmacMadr_t::Fields::ADDR);
	const bool SPRFlag = (channelRegisters.MADR->getFieldValue(EERegisterDmacMadr_t::Fields::SPR) != 0);

	// If we are using the from/toSPR channels, then we need to get the SPR address, and take a different code path. 
	// Within the these channels MADR.SPR is always 0 on these channels (but also have to use the SADR register).
	// Else transfer data normally. Also check if we are accessing the SPR instead of main memory.
	if (channelProperties.ChannelID == ChannelID_t::toSPR || channelProperties.ChannelID == ChannelID_t::fromSPR)
	{
		const u32 SPRPhysicalAddressOffset = channelRegisters.SADR->getFieldValue(EERegisterDmacSadr_t::Fields::ADDR);

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
	EE->DMAC->SliceCountState[mChannelID] += 1;
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

DMAtag_t DMACInterpreter::readDMAtag() const
{
	auto& channelRegisters = getVM()->getResources()->EE->DMAChannelRegisters[mChannelID];

	// Get the main memory or SPR address we are reading or writing from.
	const u32 TADR = channelRegisters.TADR->getFieldValue(EERegisterDmacMadr_t::Fields::ADDR);
	const bool SPRFlag = (channelRegisters.TADR->getFieldValue(EERegisterDmacMadr_t::Fields::SPR) != 0);

	// Return a DMAtag_t based upon a DMADataUnit_t read from memory.
	return DMAtag_t(readDataMemory(TADR, SPRFlag));
}

void DMACInterpreter::transferDMAtag() const
{
	auto& EE = getVM()->getResources()->EE;
	auto& channelRegisters = EE->DMAChannelRegisters[mChannelID];

	// Write the tag to the channel.
	writeDataChannel(mDMAtag.getDMADataUnit());

	// Update DataCountState by 1 (counts towards slice channel quota).
	EE->DMAC->SliceCountState[mChannelID] += 1;
}

void DMACInterpreter::checkDMAtagPacketInterrupt() const
{
	auto& EE = getVM()->getResources()->EE;
	auto& channelRegisters = EE->DMAChannelRegisters[mChannelID];

	if (channelRegisters.CHCR->getFieldValue(EERegisterDmacChcr_t::Fields::TIE) != 0 
		&& (channelRegisters.CHCR->getFieldValue(EERegisterDmacChcr_t::Fields::TAG) & 0x8000) != 0)
	{
		suspendTransfer();
	}
}

void DMACInterpreter::checkChainExit() const
{
	auto& EE = getVM()->getResources()->EE;

	if (EE->DMAC->ChainExitState[mChannelID])
	{
		// Reset chain state variables.
		EE->DMAC->ChainExitState[mChannelID] = false;
		EE->DMAC->ChainStackLevelState[mChannelID] = 0;

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
	auto& EE = getVM()->getResources()->EE;
	auto& channelRegisters = EE->DMAChannelRegisters[mChannelID];

	channelRegisters.QWC->setFieldValue(EERegisterDmacQwc_t::Fields::QWC, mDMAtag.QWC);
	channelRegisters.MADR->setFieldValue(EERegisterDmacMadr_t::Fields::ADDR, mDMAtag.ADDR);
	channelRegisters.MADR->setFieldValue(EERegisterDmacMadr_t::Fields::SPR, mDMAtag.SPR);
	EE->DMAC->ChainExitState[mChannelID] = true;
}

void DMACInterpreter::CNT()
{
	// Transfers QWC qwords after the tag, and reads the next qword as the next tag.
	auto& EE = getVM()->getResources()->EE;
	auto& channelRegisters = EE->DMAChannelRegisters[mChannelID];

	channelRegisters.QWC->setFieldValue(EERegisterDmacQwc_t::Fields::QWC, mDMAtag.QWC);

	// Copy TADR + 0x10 into MADR.
	channelRegisters.MADR->setFieldValue(EERegisterDmacMadr_t::Fields::ADDR, channelRegisters.TADR->getFieldValue(EERegisterDmacTadr_t::Fields::ADDR) + 0x10);
	channelRegisters.MADR->setFieldValue(EERegisterDmacMadr_t::Fields::SPR, channelRegisters.TADR->getFieldValue(EERegisterDmacTadr_t::Fields::SPR));

	// Calculate where the next tag will be.
	u32 nextTagAddr = channelRegisters.TADR->getFieldValue(EERegisterDmacTadr_t::Fields::ADDR) + (mDMAtag.QWC + 1) * 0x10;
	channelRegisters.TADR->setFieldValue(EERegisterDmacTadr_t::Fields::ADDR, nextTagAddr); // SPR flag unchanged within TADR register.
}

void DMACInterpreter::NEXT()
{
	// Transfers QWC qwords after the tag, and reads the ADDR field as the next tag.
	auto& EE = getVM()->getResources()->EE;
	auto& channelRegisters = EE->DMAChannelRegisters[mChannelID];

	channelRegisters.QWC->setFieldValue(EERegisterDmacQwc_t::Fields::QWC, mDMAtag.QWC);

	// Copy TADR + 0x10 into MADR.
	channelRegisters.MADR->setFieldValue(EERegisterDmacMadr_t::Fields::ADDR, channelRegisters.TADR->getFieldValue(EERegisterDmacTadr_t::Fields::ADDR) + 0x10);
	channelRegisters.MADR->setFieldValue(EERegisterDmacMadr_t::Fields::SPR, channelRegisters.TADR->getFieldValue(EERegisterDmacTadr_t::Fields::SPR));

	// Set next tag.
	channelRegisters.TADR->setFieldValue(EERegisterDmacTadr_t::Fields::ADDR, mDMAtag.ADDR);
	channelRegisters.TADR->setFieldValue(EERegisterDmacTadr_t::Fields::ADDR, mDMAtag.SPR); 
}

void DMACInterpreter::REF()
{
	// Transfers QWC qwords from ADDR field, and reads the next qword as the tag.
	auto& EE = getVM()->getResources()->EE;
	auto& channelRegisters = EE->DMAChannelRegisters[mChannelID];

	channelRegisters.QWC->setFieldValue(EERegisterDmacQwc_t::Fields::QWC, mDMAtag.QWC);

	// Set MADR = tag.ADDR.
	channelRegisters.MADR->setFieldValue(EERegisterDmacMadr_t::Fields::ADDR, mDMAtag.ADDR);
	channelRegisters.MADR->setFieldValue(EERegisterDmacMadr_t::Fields::SPR, mDMAtag.SPR);

	// Set next qword as tag.
	channelRegisters.TADR->setFieldValue(EERegisterDmacTadr_t::Fields::ADDR, channelRegisters.TADR->getFieldValue(EERegisterDmacTadr_t::Fields::ADDR) + 0x10); // SPR flag unchanged within TADR register.
}

void DMACInterpreter::REFS()
{
	// TODO: add in stall control.

	// Transfers QWC qwords from ADDR field, and reads the next qword as the tag.
	auto& EE = getVM()->getResources()->EE;
	auto& channelRegisters = EE->DMAChannelRegisters[mChannelID];

	channelRegisters.QWC->setFieldValue(EERegisterDmacQwc_t::Fields::QWC, mDMAtag.QWC);

	// Set MADR = tag.ADDR.
	channelRegisters.MADR->setFieldValue(EERegisterDmacMadr_t::Fields::ADDR, mDMAtag.ADDR);
	channelRegisters.MADR->setFieldValue(EERegisterDmacMadr_t::Fields::SPR, mDMAtag.SPR);

	// Set next qword as tag.
	channelRegisters.TADR->setFieldValue(EERegisterDmacTadr_t::Fields::ADDR, channelRegisters.TADR->getFieldValue(EERegisterDmacTadr_t::Fields::ADDR) + 0x10); // SPR flag unchanged within TADR register.
}

void DMACInterpreter::CALL()
{
	// Transfers QWC qwords after tag, and pushes the next qword after the tag onto the stack. Sets the next tag to ADDR field.
	auto& EE = getVM()->getResources()->EE;
	auto& channelRegisters = EE->DMAChannelRegisters[mChannelID];

	channelRegisters.QWC->setFieldValue(EERegisterDmacQwc_t::Fields::QWC, mDMAtag.QWC);
	channelRegisters.MADR->setFieldValue(EERegisterDmacMadr_t::Fields::ADDR, channelRegisters.TADR->getFieldValue(EERegisterDmacTadr_t::Fields::ADDR) + 0x10);
	channelRegisters.MADR->setFieldValue(EERegisterDmacMadr_t::Fields::SPR, channelRegisters.TADR->getFieldValue(EERegisterDmacTadr_t::Fields::SPR));
	channelRegisters.TADR->setFieldValue(EERegisterDmacTadr_t::Fields::ADDR, mDMAtag.ADDR);
	channelRegisters.TADR->setFieldValue(EERegisterDmacTadr_t::Fields::SPR, mDMAtag.SPR);

	// Set stack to after tag.
	u8 & stackIdx = EE->DMAC->ChainStackLevelState[mChannelID];
	channelRegisters.ASR[stackIdx]->setFieldValue(EERegisterDmacAsr_t::Fields::ADDR, channelRegisters.TADR->getFieldValue(EERegisterDmacTadr_t::Fields::ADDR) + 0x10);
	channelRegisters.ASR[stackIdx]->setFieldValue(EERegisterDmacAsr_t::Fields::SPR, channelRegisters.TADR->getFieldValue(EERegisterDmacTadr_t::Fields::SPR));
	stackIdx += 1;
}

void DMACInterpreter::RET()
{
	// Transfers QWC qwords after tag, pops next tag from stack. If stack level = 0, transfers QWC qwords after tag and suspends transfer.
	auto& EE = getVM()->getResources()->EE;
	auto& channelRegisters = EE->DMAChannelRegisters[mChannelID];

	u8 & stackIdx = EE->DMAC->ChainStackLevelState[mChannelID];
	if (stackIdx > 0)
	{
		channelRegisters.TADR->setFieldValue(EERegisterDmacTadr_t::Fields::ADDR, channelRegisters.ASR[stackIdx]->getFieldValue(EERegisterDmacAsr_t::Fields::ADDR));
		channelRegisters.TADR->setFieldValue(EERegisterDmacTadr_t::Fields::ADDR, channelRegisters.ASR[stackIdx]->getFieldValue(EERegisterDmacAsr_t::Fields::SPR));
		stackIdx -= 1;
	}
	else
	{
		EE->DMAC->ChainExitState[mChannelID] = true;
	}

	// In both cases, QWC following the tag is always performed.
	channelRegisters.QWC->setFieldValue(EERegisterDmacQwc_t::Fields::QWC, mDMAtag.QWC);
	channelRegisters.MADR->setFieldValue(EERegisterDmacMadr_t::Fields::ADDR, channelRegisters.TADR->getFieldValue(EERegisterDmacTadr_t::Fields::ADDR) + 0x10);
	channelRegisters.MADR->setFieldValue(EERegisterDmacMadr_t::Fields::SPR, channelRegisters.TADR->getFieldValue(EERegisterDmacTadr_t::Fields::SPR));
}

void DMACInterpreter::END()
{
	// Transfers QWC qwords after tag, and suspends after packet transfer.
	auto& EE = getVM()->getResources()->EE;
	auto& channelRegisters = EE->DMAChannelRegisters[mChannelID];

	channelRegisters.QWC->setFieldValue(EERegisterDmacQwc_t::Fields::QWC, mDMAtag.QWC);
	channelRegisters.MADR->setFieldValue(EERegisterDmacMadr_t::Fields::ADDR, channelRegisters.TADR->getFieldValue(EERegisterDmacTadr_t::Fields::ADDR) + 0x10);
	channelRegisters.MADR->setFieldValue(EERegisterDmacMadr_t::Fields::SPR, channelRegisters.TADR->getFieldValue(EERegisterDmacTadr_t::Fields::SPR));
	EE->DMAC->ChainExitState[mChannelID] = true;
}

void DMACInterpreter::CNTS()
{
	// TODO: need to copy MADR to STADR during the transfer.
	// Transfers QWC qwords after the tag, and reads the next qword as the next tag.
	auto& EE = getVM()->getResources()->EE;
	auto& channelRegisters = EE->DMAChannelRegisters[mChannelID];

	channelRegisters.QWC->setFieldValue(EERegisterDmacQwc_t::Fields::QWC, mDMAtag.QWC);

	// Copy TADR + 0x10 into MADR.
	channelRegisters.MADR->setFieldValue(EERegisterDmacMadr_t::Fields::ADDR, channelRegisters.TADR->getFieldValue(EERegisterDmacTadr_t::Fields::ADDR) + 0x10);
	channelRegisters.MADR->setFieldValue(EERegisterDmacMadr_t::Fields::SPR, channelRegisters.TADR->getFieldValue(EERegisterDmacTadr_t::Fields::SPR));

	// Calculate where the next tag will be.
	u32 nextTagAddr = channelRegisters.TADR->getFieldValue(EERegisterDmacTadr_t::Fields::ADDR) + (mDMAtag.QWC + 1) * 0x10;
	channelRegisters.TADR->setFieldValue(EERegisterDmacTadr_t::Fields::ADDR, nextTagAddr); // SPR flag unchanged within TADR register.
}
