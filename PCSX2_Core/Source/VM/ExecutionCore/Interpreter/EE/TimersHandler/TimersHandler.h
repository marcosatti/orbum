#pragma once

#include "Common/Global/Globals.h"

#include "Common/Interfaces/VMExecutionCoreComponent.h"
#include "Common/PS2Resources/Clock/Types/ClockSource_t.h"

/*
TimersHandler updates TIMER0, TIMER1, TIMER2, TIMER3 as defined in the EE Users Manual, starting on page 33.

The EE Timers are dynamic and can be updated on the BUSCLK, BUSCLK16, BUSCLK256 or HBLNK clocks.
*/

class TimersHandler : public VMExecutionCoreComponent
{
public:
	explicit TimersHandler(VMMain * vmMain);
	~TimersHandler();

	/*
	See VMExecutionCoreComponent for documentation.
	*/
	std::vector<ClockSource_t> mClockSources;
	const std::vector<ClockSource_t> & getClockSources() override;
	
	/*
	Updates the timers with the specified clock source type.
	*/
	s64 executionStep(const ClockSource_t & clockSource) override;

private:

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

