#include "stdafx.h"

#include "PS2Resources/IOP/Timers/IOPTimers_t.h"
#include "PS2Resources/IOP/Timers/Types/IOPTimersTimer_t.h"

IOPTimers_t::IOPTimers_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),

	// Timers
	TIMER_0(std::make_shared<IOPTimersTimer_t>(0)),
	TIMER_1(std::make_shared<IOPTimersTimer_t>(1)),
	TIMER_2(std::make_shared<IOPTimersTimer_t>(2)),
	TIMER_3(std::make_shared<IOPTimersTimer_t>(3)),
	TIMER_4(std::make_shared<IOPTimersTimer_t>(4)),
	TIMER_5(std::make_shared<IOPTimersTimer_t>(5)),
	TIMERS{ TIMER_0, TIMER_1, TIMER_2, TIMER_3, TIMER_4, TIMER_5 }
{
}
