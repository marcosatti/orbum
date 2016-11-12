#include "stdafx.h"

#include "VM/ExecutionCore/Common/EE/VPU/VIF.h"
#include "VM/VMMain.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/VPU/VPU_t.h"

VIF::VIF(VMMain* vmMain) :
	VMExecutionCoreComponent(vmMain),
	mClockSources{ ClockSource_t::BUSCLK },
	mDMAPacket()
{
}

VIF::~VIF()
{
}

const std::vector<ClockSource_t>& VIF::getClockSources()
{
	return mClockSources;
}

s64 VIF::executionStep(const ClockSource_t& clockSource)
{
	auto& VPU = getVM()->getResources()->EE->VPU;

	// Check the FIFO queue for incoming DMA packet. Return if there is nothing to process.
	if (!checkIncomingDMAPacket())
		return 1;

	// Process DMA packet.


	// VIF has completed 1 cycle.
	return 1;
}

bool VIF::checkIncomingDMAPacket()
{
	throw std::runtime_error("Not implemented.");
}

void VIF::INSTRUCTION_UNSUPPORTED()
{
	throw std::runtime_error("VIFcode CMD field was invalid! Please fix.");
}

void VIF::NOP()
{
}
