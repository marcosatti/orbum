#include "stdafx.h"

#include "VM/VM.h"
#include "VM/Types/VMSystem_s.h"

VMSystem_s::VMSystem_s(VM * vmMain) :
	mThreadRun(false),
	mVM(vmMain),
	mClockEventQueue()
{
}

VMSystem_s::~VMSystem_s()
{
}

VM* VMSystem_s::getVM() const
{
	return mVM;
}

void VMSystem_s::initalise()
{
}

void VMSystem_s::threadLoop()
{
	throw std::runtime_error("VM MT mode needs reworking.");
	/*
	mThreadRun = false;
	std::unique_lock<std::mutex> lock(mThreadMutex);

	while (getVM()->getStatus() == VM::Running)
	{
		// Wait for control thread to say run - mutex is auto unlocked during wait, relocked upon notify.
		mThreadSync.wait(lock, [this]() { return mThreadRun; });

		// Execute ticks.
		executeTicks();

		// Finished, wait for control thread again.
		mThreadRun = false;
	}
	*/
}
