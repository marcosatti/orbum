#include "stdafx.h"

#include "PS2Resources/EE/Timers/EETimers_t.h"
#include "PS2Resources/EE/Timers/Types/EETimersTimers_t.h"

EETimers_t::EETimers_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),

	// Timers
	TIMER0(std::make_shared<EETimersTimer_Timer0_t>()),
	TIMER1(std::make_shared<EETimersTimer_Timer1_t>()),
	TIMER2(std::make_shared<EETimersTimer_Timer2_t>()),
	TIMER3(std::make_shared<EETimersTimer_Timer3_t>()),
	TIMERS{ TIMER0, TIMER1, TIMER2, TIMER3 }
{
}
