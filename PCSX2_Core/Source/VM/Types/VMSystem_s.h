#pragma once

#include <queue>
#include <mutex>

#include "VM/Types/ClockEvent_t.h"

class VM;

/*
Base class for a VM system component.
*/
class VMSystem_s
{
public:
	explicit VMSystem_s(VM * vmMain);
	virtual ~VMSystem_s();

	/*
	System resources.
	*/
	VM * getVM() const;

	/*
	Initalise the system.
	*/
	virtual void initalise();

	/*
	Adds VM time that is available to be consumed by the system.
	*/
	virtual void run(const double & time) = 0;

	/*
	Runs the system logic for the given clock source.
	*/
	virtual int step(const ClockEvent_t & event) = 0;

	std::queue<ClockEvent_t> mClockEventQueue;

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
	VM * mVM;
};