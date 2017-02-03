#include "stdafx.h"

#include "VM/VMMain.h"
#include "VM/Types/VMSystem_t.h"

VMSystem_t::VMSystem_t(VMMain* vmMain, const System_t& system) :
	mThreadRun(false),
	mVMMain(vmMain),
	mResources(vmMain->getResources()),
	mClockStates(vmMain->getResources()->Clock->getSystemClockState(system))
{
}

VMSystem_t::~VMSystem_t()
{
}

VMMain* VMSystem_t::getVM() const
{
	return mVMMain;
}

const std::shared_ptr<Resources_t> & VMSystem_t::getResources() const
{
	return mResources;
}

void VMSystem_t::initalise()
{
}

void VMSystem_t::produceTicks(const ClockSource_t& source, const double& ticks) const
{
	// Give each clock source the number of ticks, converted from the given source to the local source.
	// Eg: for an EECore local source, if an EEBus source was provided with ticks = 2, then 4 ticks should be given (since EEBus is 1/2 speed of EECore).
	// The bias will slow or fasten the system by multiplying linearly with the number of ticks produced.
	for (auto& state : mClockStates)
	{
		auto baseSpeed = Clock_t::getBaseClockSpeed(state.mClockSource);
		auto sourceSpeed = Clock_t::getBaseClockSpeed(source);
		state.mTicksAvailable += (baseSpeed / sourceSpeed) * ticks * state.mClockBias;
	}
}

void VMSystem_t::executeTicks()
{
	mThreadRun = false;
	std::unique_lock<std::mutex> lock(mThreadMutex);

	while (getVM()->getStatus() == VMMain::Running)
	{
		// Wait for control thread to say run - mutex is auto unlocked during wait, relocked upon notify.
		mThreadSync.wait(lock, [this]() { return mThreadRun; });

		// Run through all the different clock sources attached to this system.
		for (auto& state : mClockStates)
		{
			while (state.mTicksAvailable > 0.0)
			{
				state.mTicksAvailable -= executeStep(state.mClockSource, state.mTicksAvailable);
			}
		}

		// Finished, wait for control thread again.
		mThreadRun = false;
	}
}
