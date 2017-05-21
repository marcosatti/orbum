#include "VM/VM.h"
#include "VM/Types/VMSystem_t.h"

#include "Resources/Resources_t.h"
#include "Resources/Clock/Clock_t.h"

VMSystem_t::VMSystem_t(VM * vm, const System_t system) :
	mVM(vm),
	mSystemContext(system)
{
	mClock = getVM()->getResources()->Clock;
}

VM * VMSystem_t::getVM() const
{
	return mVM;
}

System_t VMSystem_t::getContext() const
{
	return mSystemContext;
}

void VMSystem_t::initialise()
{
}

void VMSystem_t::run()
{
	// Execute ticks.
	for (const auto& clockState : mClock->getSystemClockTicks(mSystemContext))
	{
		// Use only whole ticks (truncate double to int).
		int ticks = static_cast<int>(clockState.second);
		if (ticks > 0)
		{
			mClock->subSystemClockTicks(mSystemContext, clockState.first, ticks);
			while (ticks > 0)
				ticks -= step(clockState.first, ticks);
		}
	}
}
