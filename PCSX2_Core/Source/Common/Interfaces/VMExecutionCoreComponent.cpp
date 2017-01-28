#include "stdafx.h"

#include "Common/Interfaces/VMExecutionCoreComponent.h"

#include "VM/VMMain.h"

#include "PS2Constants/PS2Constants.h"

#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/Clock/Clock_t.h"

VMExecutionCoreComponent::VMExecutionCoreComponent(VMMain * vmMain):
	VMBaseComponent(vmMain), 
	mClockState{}
{
	mClock = getResources()->Clock;
}

VMExecutionCoreComponent::~VMExecutionCoreComponent()
{
}

void VMExecutionCoreComponent::initalise()
{
}

void VMExecutionCoreComponent::produceTicks(const double& EECoreTicks)
{
	for (auto& i : mClockState)
		i.mTicksAvailable += EECoreTicks;
}

void VMExecutionCoreComponent::executeBlock()
{
	for (auto& i : mClockState)
	{
		auto ratio = PS2Constants::EE::EECore::EECORE_CLK_SPEED / mClock->getClockRatio(i.mSource);

		while (i.mTicksAvailable > ratio)
		{
			auto ticks = executionStep(i.mSource, i.mTicksAvailable);
			i.mTicksAvailable -= ticks * ratio;
		}
	}
}

void VMExecutionCoreComponent::addClockSource(const ClockSource_t& source)
{
	mClockState.push_back({ source, 0.0 });
}
