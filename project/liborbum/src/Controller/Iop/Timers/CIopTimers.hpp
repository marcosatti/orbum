#pragma once



#include "VM/Types/VMSystem_t.h"

class RIopIntc;
class IOPTimers_t;
class IOPTimersTimer_t;

/*
IOPTimers updates TIM0, TIM1, TIM2, TIM3, TIM4, TIM5.
If interrupt conditions are met, sets the corresponding interrupt bit in the IOP INTC.
The IOP Timers are dynamic and can be updated on the IOP system clock, pixel clock or HLINE clocks.
*/
class IOPTimers_s : public VMSystem_t
{
public:
	IOPTimers_s(VM * vm);
	virtual ~IOPTimers_s() = default;

	/*
	Initialisation.
	*/
	void initialise() override;

	/*
	Updates the timers with the specified clock source type.
	*/
	int step(const Event_t & event) override;

	/*
	Context resources needed.
	*/
	IOPTimers_t mTimers;
	RIopIntc mINTC;
	IOPTimersTimer_t * mTimer;

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
