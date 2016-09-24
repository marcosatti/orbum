#pragma once

#include <memory>

#include "Common/Global/Globals.h"

#include "Common/Interfaces/VMExecutionCoreComponent.h"
#include "Common/PS2Resources/EE/Timers/Types/ClockSource_t.h"

/*
TimerHandler updates TIMER0, TIMER1, TIMER2, TIMER3 as defined in the EE Users Manual, starting on page 33.

The EE Timers are dynamic can be updated on the BUSCLK, BUSCLK16, BUSCLK256 or HBLNK clocks.
Therefore instead of providing one executionStep() function, 4 are supplied for each of the clock sources listed.
*/

class TimerHandler : VMExecutionCoreComponent
{
public:
	explicit TimerHandler(VMMain * vmMain);
	~TimerHandler();
	
	/*
	Update timers. Call the appropriate function when the clock source has ticked, which will update the applicable timers.
	*/
	void executionStep_BUSCLK() const;
	void executionStep_BUSCLK16() const;
	void executionStep_BUSCLK256() const;
	void executionStep_HBLNK() const;

private:

	/*
	Updates the timers with the specified clock source type. Should be run from one of the 4 executionStep() functions above.
	*/
	void updateTimers(const ClockSource_t & clockSource) const;

	/*
	Check if the clock source of the timer is equal to the type of TimerEvent_t, by looking at the Timer.Mode register (CLKS).
	*/
	bool isTimerCLKSEqual(const u32 & timerNumber, const ClockSource_t & clockSource) const;

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

