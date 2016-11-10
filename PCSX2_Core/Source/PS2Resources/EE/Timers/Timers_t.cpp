#include "stdafx.h"

#include "PS2Resources/EE/Timers/Timers_t.h"
#include "PS2Resources/EE/Timers/Types/EETimersTimers_t.h"

Timers_t::Timers_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),

	// Timers
	Timer0(std::make_shared<EETimersTimer_TIM0_t>()),
	Timer1(std::make_shared<EETimersTimer_TIM1_t>()),
	Timer2(std::make_shared<EETimersTimer_TIM2_t>()),
	Timer3(std::make_shared<EETimersTimer_TIM3_t>()),
	EE_TIMERS{ Timer0, Timer1, Timer2, Timer3 }
{
}
