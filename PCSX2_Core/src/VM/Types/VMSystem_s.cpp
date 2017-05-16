#include "VM/VM.h"
#include "VM/Types/VMSystem_s.h"

#include "Resources/Resources_t.h"
#include "Resources/Clock/Clock_t.h"

VMSystem_s::VMSystem_s(VM * vm, const System_t system) :
	mThreadRun(false),
	mVM(vm),
	mSystemContext(system)
{
	mClock = getVM()->getResources()->Clock;
}

VM * VMSystem_s::getVM() const
{
	return mVM;
}

System_t VMSystem_s::getContext() const
{
	return mSystemContext;
}

void VMSystem_s::initialise()
{
}

void VMSystem_s::run()
{
	auto& Clock = getVM()->getResources()->Clock;
	for (const auto& clockState : Clock->getSystemClockTicks(mSystemContext))
	{
		int ticks = static_cast<int>(clockState.second);
		if (ticks > 0)
		{
			Clock->subSystemClockTicks(mSystemContext, clockState.first, ticks);
			while (ticks > 0)
				ticks -= step(clockState.first, ticks);
		}
	}
}

void VMSystem_s::threadLoop()
{
	mThreadRun = false;
	std::unique_lock<std::mutex> lock(mThreadMutex);

	while (getVM()->getStatus() == VM::Running)
	{
		// Wait for control thread to say run - mutex is auto unlocked during wait, relocked upon notify.
		mThreadSync.wait(lock, [this]() { return mThreadRun; });

		// Execute ticks.
		run();

		// Finished, wait for control thread again.
		mThreadRun = false;
	}
}
