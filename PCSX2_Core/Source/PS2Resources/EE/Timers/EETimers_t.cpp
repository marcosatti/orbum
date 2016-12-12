#include "stdafx.h"

#include "PS2Resources/EE/Timers/EETimers_t.h"
#include "PS2Resources/EE/Timers/Types/EETimersTimer_t.h"

EETimers_t::EETimers_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),

	// Timers
	TIMER_0(std::make_shared<EETimersTimer_t>(0, true)),
	TIMER_1(std::make_shared<EETimersTimer_t>(1, true)),
	TIMER_2(std::make_shared<EETimersTimer_t>(2, false)),
	TIMER_3(std::make_shared<EETimersTimer_t>(3, false)),
	TIMERS{ TIMER_0, TIMER_1, TIMER_2, TIMER_3 }
{
}
