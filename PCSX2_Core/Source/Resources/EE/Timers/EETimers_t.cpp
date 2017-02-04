#include "stdafx.h"

#include "Resources/EE/Timers/EETimers_t.h"
#include "Resources/EE/Timers/Types/EETimersTimers_t.h"

EETimers_t::EETimers_t() :
	// Timers
	TIMER_0(std::make_shared<EETimersTimer_TIM0_t>()),
	TIMER_1(std::make_shared<EETimersTimer_TIM1_t>()),
	TIMER_2(std::make_shared<EETimersTimer_TIM2_t>()),
	TIMER_3(std::make_shared<EETimersTimer_TIM3_t>()),
	TIMERS{ TIMER_0, TIMER_1, TIMER_2, TIMER_3 }
{
}
