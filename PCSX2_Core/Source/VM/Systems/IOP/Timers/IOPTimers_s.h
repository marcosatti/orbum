#pragma once

#include "Common/Global/Globals.h"

#include "VM/Types/VMSystem_s.h"

class IOPIntc_t;
class IOPTimers_t;
class IOPTimersTimer_t;

/*
IOPTimers updates TIM0, TIM1, TIM2, TIM3, TIM4, TIM5.
If interrupt conditions are met, sets the corresponding interrupt bit in the IOP INTC.
The IOP Timers are dynamic and can be updated on the IOP system clock, pixel clock or HLINE clocks.
*/
class IOPTimers_s : public VMSystem_s
{
public:
	explicit IOPTimers_s(VM * vm);
	virtual ~IOPTimers_s();

	/*
	Updates the timers with the specified clock source type.
	*/
	int step(const ClockSource_t clockSource, const int ticksAvailable) override;

private:
	/*
	Context resources needed.
	*/
	u32 mTimerIndex;
	IOPTimersTimer_t * mTimer;
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
