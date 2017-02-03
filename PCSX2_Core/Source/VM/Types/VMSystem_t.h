#pragma once

#include <memory>
#include <mutex>

#include "Resources/Resources_t.h"
#include "Resources/Clock/Clock_t.h"
#include "Resources/Clock/Types/System_t.h"
#include "Resources/Clock/Types/SystemClockState_t.h"

class VMMain;

/*
Base class for a VM system component.
*/
class VMSystem_t
{
public:
	explicit VMSystem_t(VMMain* vmMain, const System_t& system);
	virtual ~VMSystem_t();

	VMMain * getVM() const;
	const std::shared_ptr<Resources_t> & getResources() const;

	virtual void initalise();

	void produceTicks(const ClockSource_t & source, const double & ticks) const;
	void executeTicks();

	/*
	Threading resources.
	*/
	std::condition_variable mThreadSync;
	std::mutex mThreadMutex;
	bool mThreadRun;

protected:
	virtual double executeStep(const ClockSource_t & source, const double & ticksAvailable) = 0;

private:
	/*
	VM resources.
	*/
	VMMain * mVMMain;
	std::shared_ptr<Resources_t> mResources;
	std::vector<SystemClockState_t> & mClockStates;
};