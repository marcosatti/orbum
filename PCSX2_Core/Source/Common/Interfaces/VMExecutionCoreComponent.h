#pragma once

#include <vector>

#include "Common/Global/Globals.h"

#include "Common/Interfaces/VMBaseComponent.h"
#include "PS2Resources/Clock/Types/ClockSource_t.h"

struct ClockState_t
{
	ClockSource_t mSource;
	double mTicksAvailable;
};

class Clock_t;

class VMExecutionCoreComponent : public VMBaseComponent
{
public:
	explicit VMExecutionCoreComponent(VMMain * vmMain);
	virtual ~VMExecutionCoreComponent();

	virtual void initalise();

	void produceTicks(const double & EECoreTicks);
	void executeBlock();
	virtual double executionStep(const ClockSource_t & clockSource, const double & ticksAvailable) = 0;

	void addClockSource(const ClockSource_t & source);
	std::vector<ClockState_t> mClockState;
	std::shared_ptr<Clock_t> mClock;
private:
};

