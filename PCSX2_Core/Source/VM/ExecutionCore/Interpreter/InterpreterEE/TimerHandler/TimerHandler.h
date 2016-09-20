#pragma once

#include <memory>

#include "Common/Global/Globals.h"

#include "Common/Interfaces/VMExecutionCoreComponent.h"
#include "Common/PS2Resources/EE/Timers/Types/TimerEvent_t.h"

using ClockSource_t = TimerEvent_t::ClockSource_t;

/*
TimerHandler updates TIMER0, TIMER1, TIMER2, TIMER3 as defined in the EE Users Manual, starting on page 33.
*/

class TimerHandler : VMExecutionCoreComponent
{
public:
	explicit TimerHandler(const VMMain* const vmMain);
	~TimerHandler();
	
	/*
	Update timers. Called on every loop of the emulator, which checks the TimerEventQueue for any pending events and updates the timers accordingly.
	If the gate function on any of the timers are enabled, it is checked here.
	*/
	void updateTimers() const;

private:

	/*
	Check if the clock source of the timer is equal to the type of TimerEvent_t, by looking at the Timer.Mode register (CLKS).
	*/
	bool isTimerCLKSEqual(const u32 & timerNumber, const TimerEvent_t & timerEvent) const;

	/*
	Checks the timer status and count values for interrupt conditions.
	*/
	void checkTimerInterrupt(const u32 & timerNumber) const;

	/*
	Check for the ZRET condition and reset counter if enabled/met.
	*/
	void checkTimerZRET(const u32 & timerNumber) const;

	/*
	Check if CLKS == H_BLNK && GATS == H_BLNK, in which case the gate function means nothing, and it should count as normal.
	*/
	bool isTimerGateSpecialHBLNK(const u32 & timerNumber) const;

	/*
	Checks the previous gate condition and resets if required.
	*/
	void checkTimerGateReset(const u32 & timerNumber) const;

	
};

