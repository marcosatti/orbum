#pragma once

#include "Common/Types/System_t.h"
#include "Common/Types/ClockSource_t.h"
#include "Common/Types/Runnable/Runnable_t.h"

class VM;
class Clock_t;

/*
Base class for a VM system component.
Note: subclasses end with a _s suffix to signify an actual PS2 system logic component.
*/
class VMSystem_t : public Runnable_t
{
public:
	VMSystem_t(VM * vm, const System_t system);
	virtual ~VMSystem_t() = default;

	/*
	Returns the VM resources.
	*/
	VM * getVM() const;

	/*
	Returns the system context type.
	*/
#if defined(BUILD_DEBUG)
	System_t getContext() const override;
#else
    System_t getContext() const;
#endif

	/*
	Runs the system logic for each clock source event by looping through the step function.
	*/
	void run() override;

	/*
	Initialise the system.
	*/
	virtual void initialise() = 0;

	/*
	Steps the system logic for the given clock source.
	*/
	virtual int step(const ClockSource_t clockSource, const int ticksAvailable) = 0;

private:
	/*
	System resources.
	*/
	VM * mVM;
	System_t mSystemContext;
	std::shared_ptr<Clock_t> mClock;
};