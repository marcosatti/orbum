#pragma once

#include <mutex>

#include "Common/Types/System_t.h"
#include "Common/Types/ClockSource_t.h"

class VM;
class Clock_t;

/*
Base class for a VM system component.
*/
class VMSystem_s
{
public:
	VMSystem_s(VM * vm, const System_t system);
	virtual ~VMSystem_s() = default;

	/*
	Returns the VM resources.
	*/
	VM * getVM() const;

	/*
	Returns the system context type.
	*/
	System_t getContext() const;

	/*
	Initalise the system.
	*/
	virtual void initalise() = 0;

	/*
	Runs the system logic for each clock source event by looping through the step function.
	*/
	void run();

	/*
	Steps the system logic for the given clock source.
	*/
	virtual int step(const ClockSource_t clockSource, const int ticksAvailable) = 0;

	/*
	Threading resources.
	threadLoop() is a thin wrapper around executeTicks() that takes care of synchronising with the VM, using the variables below.
	TODO: cleanup, do properly.
	*/
	void threadLoop();
	std::condition_variable mThreadSync;
	std::mutex mThreadMutex;
	bool mThreadRun;

private:
	/*
	VM resources.
	*/
	VM * mVM;
	System_t mSystemContext;
	std::shared_ptr<Clock_t> mClock;
};