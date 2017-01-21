#pragma once

#include "Common/Global/Globals.h"
#include "Common/Interfaces/VMExecutionCoreComponent.h"

#include "PS2Resources/Clock/Types/ClockSource_t.h"

class IOPIntc_t;
class IOPTimers_t;
class IOPTimersTimer_t;

/*
IOPTimers updates TIM0, TIM1, TIM2, TIM3, TIM4, TIM5.
If interrupt conditions are met, sets the corresponding interrupt bit in the IOP INTC.
The IOP Timers are dynamic and can be updated on the IOP system clock, pixel clock or HLINE clocks.
*/
class IOPTimers : public VMExecutionCoreComponent
{
public:
	explicit IOPTimers(VMMain * vmMain);
	~IOPTimers();

	/*
	Updates the timers with the specified clock source type.
	*/
	s64 executionStep(const ClockSource_t & clockSource) override;

private:
	/*
	Context resources needed.
	*/
	u32 mTimerIndex;
	IOPTimersTimer_t * mTimer;
	ClockSource_t mClockSource;
	std::shared_ptr<IOPTimers_t> mTimers;
	std::shared_ptr<IOPIntc_t> mINTC;

	/*
	Checks the timer status and count values for interrupt conditions.
	*/
	void handleTimerInterrupt() const;

	/*
	Checks for overflow conditions and handles certain conditions.
	Must be done after checking for an interrupt otherwise the interrupt may be missed.
	*/
	void handleTimerOverflow() const;

	/*
	Checks for target conditions and handles certain conditions.
	Must be done after checking for an interrupt otherwise the interrupt may be missed.
	*/
	void handleTimerTarget() const;
};
