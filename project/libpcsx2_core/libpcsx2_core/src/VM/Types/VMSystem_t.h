#pragma once

#include <memory>

#include "Common/Types/System/Context_t.h"
#include "Common/Types/System/ClockSource_t.h"
#include "Common/Types/Util/Runnable_t.h"

class VM;
class Clock_t;

/*
Base class for a VM system component.
*/
class VMSystem_t : public Runnable_t
{
public:
	VMSystem_t(VM * vm, const Context_t system);
	virtual ~VMSystem_t() = default;

	/*
	Returns the VM resources.
	*/
	VM * getVM() const;

	/*
	Returns the system context type.
	*/
    Context_t getContext() const;

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
	Context_t mContext;
	std::shared_ptr<Clock_t> mClock;
};