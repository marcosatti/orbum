#pragma once

#include "Common/Global/Globals.h"

#include "VM/Types/VMSystem_t.h"

class EEIntc_t;
class EETimers_t;
class GS_t;
class EETimersTimer_t;

/*
EETimers updates TIMER_0, TIMER_1, TIMER_2, TIMER_3 as defined in the EE Users Manual, starting on page 33.
If interrupt conditions are met, sets the corresponding interrupt bit in the EE INTC.

The EE Timers are dynamic and can be updated on the BUSCLK, BUSCLK16, BUSCLK256 or HBLNK clocks.
*/
class EETimers_s : public VMSystem_t
{
public:
	EETimers_s(VM * vm);
	virtual ~EETimers_s() = default;

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
	std::shared_ptr<EETimers_t> mTimers;
	std::shared_ptr<EEIntc_t> mINTC;
	std::shared_ptr<GS_t> mGS;
	EETimersTimer_t * mTimer;

	/*
	Checks the timer status and count values for interrupt conditions.
	*/
	void handleTimerInterrupt() const;

	/*
	Check for the ZRET condition and reset counter if enabled/met.
	*/
	void handleTimerZRET() const;

	/*
	Checks the previous gate condition and resets if required.
	*/
	void handleTimerGateReset() const;
	
};

