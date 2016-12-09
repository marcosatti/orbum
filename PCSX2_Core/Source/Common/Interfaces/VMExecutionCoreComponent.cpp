#include "stdafx.h"

#include "Common/Interfaces/VMExecutionCoreComponent.h"
#include "VM/VMMain.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/Clock/Clock_t.h"

VMExecutionCoreComponent::VMExecutionCoreComponent(VMMain * vmMain):
	VMBaseComponent(vmMain), 
	mClockTicks{0}
{
}

VMExecutionCoreComponent::~VMExecutionCoreComponent()
{
}

s64 VMExecutionCoreComponent::executionStep(const ClockSource_t & clockSource)
{
	// Throws runtime error by default (valid for reactive components).
	// Must be overriden for proactive components.
	throw std::runtime_error("executionStep() called for a reactive component. Not allowed.");
}

void VMExecutionCoreComponent::initalise()
{
}

void VMExecutionCoreComponent::produceTicks(const ClockSource_t& clockSource, const s64 & PS2CLKTicks)
{
	mClockTicks[static_cast<u32>(clockSource)] += PS2CLKTicks;
}


bool VMExecutionCoreComponent::isTicked(const ClockSource_t & clockSource) const
{
	auto& ratio = getResources()->Clock->getClockRatio(clockSource);

	if (mClockTicks[static_cast<u32>(clockSource)] >= ratio)
		return true;
	else
		return false;
}

void VMExecutionCoreComponent::consumeTicks(const ClockSource_t & clockSource, const s64 & clockSourceTicks)
{
	auto& ratio = getResources()->Clock->getClockRatio(clockSource);
	mClockTicks[static_cast<u32>(clockSource)] -= clockSourceTicks * ratio;
}
