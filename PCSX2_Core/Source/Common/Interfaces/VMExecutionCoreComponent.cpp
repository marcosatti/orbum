#include "stdafx.h"

#include "Common/Interfaces/VMExecutionCoreComponent.h"
#include "VM/VMMain.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/Clock/Clock_t.h"

VMExecutionCoreComponent::VMExecutionCoreComponent(VMMain * vmMain):
	VMBaseComponent(vmMain),
	mNumTicksPS2CLK{0}
{
}

VMExecutionCoreComponent::~VMExecutionCoreComponent()
{
}

s64 VMExecutionCoreComponent::executionStep(const ClockSource_t & clockSource)
{
	// Returns 0 by default, must be overriden to return a meaningful value.
	return 0;
}

void VMExecutionCoreComponent::produceTicks(const s64 & ticksPS2CLK)
{
	for (auto& sourceTicks : mNumTicksPS2CLK)
		sourceTicks += ticksPS2CLK;
}

void VMExecutionCoreComponent::consumeTicks(const ClockSource_t & clockSource, const s64 & clockSourceTicks)
{
	u32 clockSourceIdx = static_cast<u32>(clockSource);
	auto& RATIO_PS2CLK_SOURCE = getVM()->getResources()->Clock->RATIO_PS2CLK[clockSourceIdx];

	mNumTicksPS2CLK[clockSourceIdx] -= clockSourceTicks * RATIO_PS2CLK_SOURCE;
}

bool VMExecutionCoreComponent::isTicked(const ClockSource_t & clockSource) const
{
	u32 clockSourceIdx = static_cast<u32>(clockSource);
	auto& RATIO_PS2CLK_SOURCE = getVM()->getResources()->Clock->RATIO_PS2CLK[clockSourceIdx];

	if (mNumTicksPS2CLK[clockSourceIdx] >= RATIO_PS2CLK_SOURCE)
		return true;
	else
		return false;
}

void VMExecutionCoreComponent::initalise()
{
}
