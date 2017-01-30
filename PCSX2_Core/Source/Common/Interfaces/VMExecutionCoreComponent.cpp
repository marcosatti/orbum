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
	run = false;
	std::unique_lock<std::mutex> lock(mSyncMutex);

	while (getVM()->getStatus() == VMMain::RUNNING)
	{
		mSyncCV.wait(lock, [this]() { return run; }); // Mutex is unlocked during wait, relocked upon notify.

		for (auto& i : mClockState)
		{
			auto ratio = PS2Constants::EE::EECore::EECORE_CLK_SPEED / mClock->getClockSpeed(i.mSource);

			while (i.mTicksAvailable > ratio)
			{
				auto ticks = executionStep(i.mSource, i.mTicksAvailable);
				i.mTicksAvailable -= ticks * ratio;
			}
		}

		run = false;
	}
}

void VMExecutionCoreComponent::addClockSource(const ClockSource_t& source)
{
	mClockState.push_back({ source, 0.0 });
}
