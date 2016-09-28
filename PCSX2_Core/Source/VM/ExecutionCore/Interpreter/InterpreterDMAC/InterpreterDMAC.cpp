#include "stdafx.h"

#include "VM/ExecutionCore/Interpreter/InterpreterDMAC/InterpreterDMAC.h"
#include "Common/PS2Constants/PS2Constants.h"
#include "VM/VMMain.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/EE/DMAC/DMAC_t.h"
#include "Common/PS2Resources/EE/Types/EE_Registers_t.h"

InterpreterDMAC::InterpreterDMAC(VMMain * vmMain) :
	VMExecutionCoreComponent(vmMain)
{
}

InterpreterDMAC::~InterpreterDMAC()
{
}

void InterpreterDMAC::executionStep()
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

void InterpreterDMAC::executionStep_Normal(u32 channelID)
{
	auto& EE = getVM()->getResources()->EE;
	auto& channelRegisters = EE->DMAChannelRegisters[channelID];

	// Get the channel properties.
	auto& channelProperties = ChannelProperties[channelID];

	// Check the QWC register, make sure that size > 0.
	const u32 QWC = channelRegisters.QWC->getFieldValue(EERegisterDmacQwc_t::Fields::QWC);
	if (QWC == 0)
	{
		// TODO: implement failed transfer properly? (See page 79 of EE Users Manual).
		throw std::runtime_error("QWC == 0, but not implemented.");
	}

	// Check if we have reached the QWC, in which case stop transferring and update status.
	if (EE->DMAC->PacketCountState[channelID] == QWC)
	{
		// TODO: implement.
		throw std::runtime_error("PacketCountState[channelID] == QWC, but not implemented.");
	}
	
	// Transfer a single packet (same for slice and burst). This function also updates the number of packets transferred.
	transferPacket(channelID);

	// If the physical mode is set to slice (all channels but to/fromSPR), we need to determine if we should stop transferring 
	//  data after every 8 qwords (a slice), and await the EE core to say continue (set CHCR.STR to 1 again). 
	// If we are in burst mode, don't need to do anything.
	if (channelProperties.PhysicalMode == PhysicalMode_t::SLICE)
	{
		if (EE->DMAC->PacketCountState[channelID] % 8 == 0)
		{
			// We have reached a slice limit, suspend transfer, update MADR (next packet access address) and QWC (remaining packets) registers.
			// TODO: how do we suspend transfer? Set CHCR.STR = 0 and/or sent interrupt?
			const u32 MADR = channelRegisters.MADR->getFieldValue(EERegisterDmacMadr_t::Fields::ADDR);
			const u32 addressOffset = EE->DMAC->PacketCountState[channelID] * Constants::NUMBER_BYTES_IN_QWORD;

			channelRegisters.MADR->setFieldValue(EERegisterDmacMadr_t::Fields::ADDR, MADR + addressOffset);
			channelRegisters.QWC->setFieldValue(EERegisterDmacQwc_t::Fields::QWC, QWC - 8);
			channelRegisters.CHCR->setFieldValue(EERegisterDmacChcr_t::Fields::STR, 0);
		}
	}

}

void InterpreterDMAC::transferPacket(u32 channelID)
{
	auto& EE = getVM()->getResources()->EE;
	auto& channelRegisters = EE->DMAChannelRegisters[channelID];

	// Get the channel properties.
	auto& channelProperties = ChannelProperties[channelID];

	// Determine the direction of data flow. If set to BOTH (true for VIF1 and SIF2 channels), 
	//  get the runtime direction by checking the CHCR.DIR field.
	Direction_t direction = channelProperties.Direction;
	if (direction == Direction_t::BOTH)
		direction = static_cast<Direction_t>(channelRegisters.CHCR->getFieldValue(EERegisterDmacChcr_t::Fields::DIR));

	// If we are continuing a transfer, we need to calculate an address offset that is applied to the addresses below.
	const u32 addressOffset = EE->DMAC->PacketCountState[channelID] * Constants::NUMBER_BYTES_IN_QWORD;

	// Get the main memory or SPR address we are reading or writing from (see SPR flag below). 
	const u32 MemPhysicalAddressOffset = channelRegisters.MADR->getFieldValue(EERegisterDmacMadr_t::Fields::ADDR) + addressOffset;

	// If we are using the from/toSPR channels, then we need to get the SPR address, and take a different code path. 
	//  Within the these channels MADR.SPR is always 0 on these channels (but have/use the SADR register).
	if (channelProperties.ChannelID == ChannelID_t::toSPR || channelProperties.ChannelID == ChannelID_t::fromSPR)
	{
		const u32 SPRPhysicalAddressOffset = channelRegisters.SADR->getFieldValue(EERegisterDmacSadr_t::Fields::ADDR) + addressOffset;

		if (direction == Direction_t::FROM)
		{
			// Read from the SPR to memory.
			DMAPacket_t packet = readQwordMemory(SPRPhysicalAddressOffset, true);
			writeQwordMemory(MemPhysicalAddressOffset, false, packet);
		}
		else if (direction == Direction_t::TO)
		{
			// Write from memory to SPR.
			DMAPacket_t packet = readQwordMemory(MemPhysicalAddressOffset, false);
			writeQwordMemory(SPRPhysicalAddressOffset, true, packet);
		}
	}
	// Else transfer data normally. Also check if we are accessing the SPR instead of main memory.
	else {
		const bool SPRFlag = (channelRegisters.MADR->getFieldValue(EERegisterDmacMadr_t::Fields::SPR) != 0);
		if (direction == Direction_t::FROM)
		{
			// Read from the channel to memory.
			DMAPacket_t packet = readQwordChannel(channelProperties.ChannelID);
			writeQwordMemory(MemPhysicalAddressOffset, SPRFlag, packet);
		}
		else if (direction == Direction_t::TO)
		{
			// Write from memory to the channel.
			DMAPacket_t packet = readQwordMemory(MemPhysicalAddressOffset, SPRFlag);
			writeQwordChannel(channelProperties.ChannelID, packet);
		}
	}

	// Increment the transferred packet count state
	EE->DMAC->PacketCountState[channelID] += 1;
}

void InterpreterDMAC::executionStep_Chain(u32 channelID)
{
	// TODO: implement.
	throw std::runtime_error("DMA chain mode not implemented.");
}

void InterpreterDMAC::executionStep_Interleaved(u32 channelID)
{
	// TODO: implement.
	throw std::runtime_error("DMA interleaved mode not implemented.");
}

DMAPacket_t InterpreterDMAC::readQwordChannel(ChannelID_t channel)
{
	// TODO: implement.
	throw std::runtime_error("DMA channel read qword not implemented.");
}

void InterpreterDMAC::writeQwordChannel(ChannelID_t channel, DMAPacket_t data)
{
	// TODO: implement.
	throw std::runtime_error("DMA channel write qword not implemented.");
}

DMAPacket_t InterpreterDMAC::readQwordMemory(u32 PhysicalAddressOffset, bool SPRAccess)
{
	// TODO: implement.
	throw std::runtime_error("DMA memory read qword not implemented.");
}

void InterpreterDMAC::writeQwordMemory(u32 PhysicalAddressOffset, bool SPRAccess, DMAPacket_t packet)
{
	// TODO: implement.
	throw std::runtime_error("DMA memory write qword not implemented.");
}
