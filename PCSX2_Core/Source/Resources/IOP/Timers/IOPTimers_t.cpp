#include "stdafx.h"

#include "Resources/IOP/Timers/IOPTimers_t.h"
#include "Resources/IOP/Timers/Types/IOPTimersTimers_t.h"

IOPTimers_t::IOPTimers_t() :

	// Timers
	TIMER_0(std::make_shared<IOPTimersTimer_TIM0_t>()),
	TIMER_1(std::make_shared<IOPTimersTimer_TIM1_t>()),
	TIMER_2(std::make_shared<IOPTimersTimer_TIM2_t>()),
	TIMER_3(std::make_shared<IOPTimersTimer_TIM3_t>()),
	TIMER_4(std::make_shared<IOPTimersTimer_TIM4_t>()),
	TIMER_5(std::make_shared<IOPTimersTimer_TIM5_t>()),
	TIMERS{ TIMER_0, TIMER_1, TIMER_2, TIMER_3, TIMER_4, TIMER_5 }
{
}
