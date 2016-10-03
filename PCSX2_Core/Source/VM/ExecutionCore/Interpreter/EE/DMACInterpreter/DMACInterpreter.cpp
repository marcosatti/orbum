#include "stdafx.h"

#include "VM/ExecutionCore/Interpreter/EE/DMACInterpreter/DMACInterpreter.h"
#include "Common/PS2Constants/PS2Constants.h"
#include "VM/VMMain.h"
#include "VM/VMMMUHandler/VMMMUHandler.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/EE/DMAC/DMAC_t.h"
#include "Common/PS2Resources/EE/Types/EE_Registers_t.h"
#include "Common/PS2Resources/EE/DMAC/Types/DMAtag_t.h"

DMACInterpreter::DMACInterpreter(VMMain * vmMain) :
	VMExecutionCoreComponent(vmMain)
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

	// Check for any pending/started DMA transfers, by checking the Dn_CHCR.STR register of each channel.
	for (auto i = 0; i < PS2Constants::EE::DMAC::NUMBER_DMA_CHANNELS; i++)
	{
		if (DMAChannelRegisters[i].CHCR->getFieldValue(EERegisterDmacChcr_t::Fields::STR))
		{
		 	// Branch to the appropriate DMA transfer mode (Normal, Src/Dest Chain or Interleaved)
			switch (DMAChannelRegisters[i].CHCR->getFieldValue(EERegisterDmacChcr_t::Fields::MOD))
			{
			case 0x0:
			{
				// Normal logical mode step.
				executionStep_Normal(i);
				break;
			}
			case 0x1:
			{
				// Chain logical mode step.
				executionStep_Chain(i);
				break;
			}
			case 0x2:
			{
				// Chain logical mode step.
				executionStep_Interleaved(i);
				break;
			}
			default:
			{
				throw std::runtime_error("Could not determine DMA transfer logical mode context. Please fix!");
			}
			}
		}
	}
}

void DMACInterpreter::executionStep_Normal(u32 channelID)
{
	auto& EE = getVM()->getResources()->EE;
	auto& channelRegisters = EE->DMAChannelRegisters[channelID];

	// Get the channel properties.
	auto& channelProperties = ChannelProperties[channelID];

	// Check the QWC register, make sure that size > 0 in order to start transfer.
	if (channelRegisters.QWC->getFieldValue(EERegisterDmacQwc_t::Fields::QWC) == 0)
	{
		// TODO: implement failed transfer properly? (See page 79 of EE Users Manual).
		throw std::runtime_error("QWC == 0 at start, but not implemented.");
	}
	
	// Transfer a single packet (same for slice and burst). This function also updates the number of packets transferred.
	transferDataUnit(channelID);

	// Check if QWC == 0 (transfer completed), in which case stop transferring and update status.
	if (channelRegisters.QWC->getFieldValue(EERegisterDmacQwc_t::Fields::QWC) == 0)
	{
		channelRegisters.CHCR->setFieldValue(EERegisterDmacChcr_t::Fields::STR, 0);
		// INTC.CHx = 1?
	}

	// If the physical mode is set to slice (all channels but to/fromSPR), we need to determine if we should stop transferring 
	//  data after every 8 qwords (a slice), and await the EE core to say continue (set CHCR.STR to 1 again). // TODO: Check!!!
	// If we are in burst mode, don't need to do anything.
	if (channelProperties.PhysicalMode == PhysicalMode_t::SLICE)
	{
		if (EE->DMAC->DataCountState[channelID] % 8 == 0)
		{
			// We have reached a slice limit, suspend transfer.
			channelRegisters.CHCR->setFieldValue(EERegisterDmacChcr_t::Fields::STR, 0);
			// INTC.CHx = 1?
		}
	}
}

void DMACInterpreter::executionStep_Chain(u32 channelID)
{
	auto& EE = getVM()->getResources()->EE;
	auto& channelRegisters = EE->DMAChannelRegisters[channelID];

	// Get the channel properties.
	auto& channelProperties = ChannelProperties[channelID];

	// Check the QWC register, make sure that size > 0 for a transfer to occur (otherwise read a tag).
	if (channelRegisters.QWC->getFieldValue(EERegisterDmacQwc_t::Fields::QWC) > 0)
	{
		
	}
	else
	{
		// Check if we are in source or dest chain mode.
		switch (channelProperties.ChainMode)
		{
		case ChainMode_t::SOURCE:
		{
			// Read in a tag.
			DMAtag_t tag = readDMAtag(channelID);

			// Check if we need to transfer the tag.
			if (channelRegisters.CHCR->getFieldValue(EERegisterDmacChcr_t::Fields::TTE))
				transferDMAtag(channelID, tag);

			// Check if we need to interrupt before continuing.
			// if(CHCR.TIE and TAG.IRQ) interrupt.

			// Perform action based on tag id (which will set MADR and QWC).
			// SrcChainHandler[id](channelID);

			

		}
		case ChainMode_t::DEST:
		{

		}
		default:
		{
			throw std::runtime_error("Could not determine chain mode context.");
		}
		}
	}
}

void DMACInterpreter::executionStep_Interleaved(u32 channelID)
{
	// TODO: implement.
	throw std::runtime_error("DMA interleaved mode not implemented.");
}

void DMACInterpreter::transferDataUnit(u32 channelID)
{
	auto& EE = getVM()->getResources()->EE;
	auto& channelRegisters = EE->DMAChannelRegisters[channelID];

	// Get the channel properties.
	auto& channelProperties = ChannelProperties[channelID];

	// Determine the direction of data flow. If set to BOTH (true for VIF1 and SIF2 channels), get the runtime direction by checking the CHCR.DIR field.
	Direction_t direction = channelProperties.Direction;
	if (direction == Direction_t::BOTH)
		direction = static_cast<Direction_t>(channelRegisters.CHCR->getFieldValue(EERegisterDmacChcr_t::Fields::DIR));

	// Get the main memory or SPR address we are reading or writing from (see SPR flag below). 
	const u32 MemPhysicalAddressOffset = channelRegisters.MADR->getFieldValue(EERegisterDmacMadr_t::Fields::ADDR);

	// If we are using the from/toSPR channels, then we need to get the SPR address, and take a different code path. 
	// Within the these channels MADR.SPR is always 0 on these channels (but have/use the SADR register).
	if (channelProperties.ChannelID == ChannelID_t::toSPR || channelProperties.ChannelID == ChannelID_t::fromSPR)
	{
		const u32 SPRPhysicalAddressOffset = channelRegisters.SADR->getFieldValue(EERegisterDmacSadr_t::Fields::ADDR);

		if (direction == Direction_t::FROM)
		{
			// Read from the SPR to memory.
			DMADataUnit_t packet = readDataMemory(SPRPhysicalAddressOffset, true);
			writeDataMemory(MemPhysicalAddressOffset, false, packet);
		}
		else if (direction == Direction_t::TO)
		{
			// Write from memory to SPR.
			DMADataUnit_t packet = readDataMemory(MemPhysicalAddressOffset, false);
			writeDataMemory(SPRPhysicalAddressOffset, true, packet);
		}

		// Increment the SADR address
		channelRegisters.SADR->increment();
	}
	// Else transfer data normally. Also check if we are accessing the SPR instead of main memory.
	else {
		const bool SPRFlag = (channelRegisters.MADR->getFieldValue(EERegisterDmacMadr_t::Fields::SPR) != 0);
		if (direction == Direction_t::FROM)
		{
			// Read from the channel to memory.
			DMADataUnit_t packet = readDataChannel(channelProperties.ChannelID);
			writeDataMemory(MemPhysicalAddressOffset, SPRFlag, packet);
		}
		else if (direction == Direction_t::TO)
		{
			// Write from memory to the channel.
			DMADataUnit_t packet = readDataMemory(MemPhysicalAddressOffset, SPRFlag);
			writeDataChannel(channelProperties.ChannelID, packet);
		}
	}

	// Update DataCountState by 1, the MADR register by 0x10 (increment), and decrement the QWC register by 1.
	EE->DMAC->DataCountState[channelID] += 1;
	channelRegisters.MADR->increment();
	channelRegisters.QWC->decrement();
}

DMAtag_t DMACInterpreter::readDMAtag(u32 channelID) const
{
	auto& channelRegisters = getVM()->getResources()->EE->DMAChannelRegisters[channelID];

	// Get the main memory or SPR address we are reading or writing from.
	const u32 TADR = channelRegisters.TADR->getFieldValue(EERegisterDmacMadr_t::Fields::ADDR);
	const bool SPRFlag = (channelRegisters.TADR->getFieldValue(EERegisterDmacMadr_t::Fields::SPR) != 0);

	return DMAtag_t(readDataMemory(TADR, SPRFlag));
}

void DMACInterpreter::transferDMAtag(u32 channelID, const DMAtag_t & tag)
{
	auto& EE = getVM()->getResources()->EE;
	auto& channelRegisters = EE->DMAChannelRegisters[channelID];

	// Write the tag to the channel.
	writeDataChannel(ChannelProperties[channelID].ChannelID, tag.getDMADataUnit());

	// Update DataCountState by 1 (counts towards slice channel quota).
	EE->DMAC->DataCountState[channelID] += 1;
}

DMADataUnit_t DMACInterpreter::readDataChannel(ChannelID_t channel)
{
	// TODO: implement.
	throw std::runtime_error("DMA channel read qword not implemented.");
}

void DMACInterpreter::writeDataChannel(ChannelID_t channel, DMADataUnit_t data)
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
