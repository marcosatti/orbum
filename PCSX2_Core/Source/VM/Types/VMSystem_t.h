#pragma once

#include <memory>
#include <mutex>

#include "Resources/Resources_t.h"
#include "Resources/Clock/Clock_t.h"
#include "Resources/Clock/Types/System_t.h"
#include "Resources/Clock/Types/SystemClockState_t.h"

class VM;

/*
Base class for a VM system component.
*/
class VMSystem_t
{
public:
	explicit VMSystem_t(VM* vmMain, const System_t& system);
	virtual ~VMSystem_t();

	/*
	System resources.
	*/
	VM * getVM() const;
	const std::shared_ptr<Resources_t> & getResources() const;

	/*
	Initalise the system.
	*/
	virtual void initalise();

	/*
	Adds ticks that are available to be consumed by the system.
	This will automatically take care of converting the input source and ticks to the local system tick sources.
	*/
	void produceTicks(const ClockSource_t & source, const double & ticks) const;

	/*
	Run through all of the system's local clock sources, until all of the ticks have been consumed through running executeStep.
	*/
	void executeTicks();

	/*
	Runs the system logic for the given clock source.
	Returns the number of cycles processed. This does not have to be 1; the system may return more based upon ticksAvailable (which is always at least 1 or greater).
	This may be useful for eg: the DMAC, where you can skip a few cycles if there is no work to be done.
	*/
	virtual double executeStep(const ClockSource_t & source, const double & ticksAvailable) = 0;

	/*
	Threading resources.
	threadLoop() is a thin wrapper around executeTicks() that takes care of synchronising with the VM, using the variables below.
	*/
	void threadLoop();
	std::condition_variable mThreadSync;
	std::mutex mThreadMutex;
	bool mThreadRun;

private:
	/*
	VM resources.
	*/
	VM * mVMMain;
	std::shared_ptr<Resources_t> mResources;
	std::vector<SystemClockState_t> & mClockStates;
};