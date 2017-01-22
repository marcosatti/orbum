#include "stdafx.h"

#include "PS2Resources/IOP/Timers/Types/IOPTimersTimers_t.h"
#include "PS2Resources/IOP/Timers/Types/IOPTimersTimerRegisters_t.h"

IOPTimersTimer_t::IOPTimersTimer_t(const u32& timerID) :
	mTimerID(timerID),
	COUNT(nullptr),
	MODE(nullptr),
	COMP(nullptr)
{
}

IOPTimersTimer_TIM0_t::IOPTimersTimer_TIM0_t() :
	IOPTimersTimer_t(TIMER_ID)
{
	COUNT = std::make_shared<IOPTimersTimerRegister_COUNT_t>("IOP Timer0 Count", false);
	MODE = std::make_shared<IOPTimersTimerRegister_MODE_t>("IOP Timer0 Mode", 0, COUNT);
	COMP = std::make_shared<Register32_t>("IOP Timer0 Compare", false, true);
}

IOPTimersTimer_TIM1_t::IOPTimersTimer_TIM1_t() :
	IOPTimersTimer_t(TIMER_ID)
{
	COUNT = std::make_shared<IOPTimersTimerRegister_COUNT_t>("IOP Timer1 Count", false);
	MODE = std::make_shared<IOPTimersTimerRegister_MODE_t>("IOP Timer1 Mode", 1, COUNT);
	COMP = std::make_shared<Register32_t>("IOP Timer1 Compare", false, true);
}

IOPTimersTimer_TIM2_t::IOPTimersTimer_TIM2_t() :
	IOPTimersTimer_t(TIMER_ID)
{
	COUNT = std::make_shared<IOPTimersTimerRegister_COUNT_t>("IOP Timer2 Count", false);
	MODE = std::make_shared<IOPTimersTimerRegister_MODE_t>("IOP Timer2 Mode", 2, COUNT);
	COMP = std::make_shared<Register32_t>("IOP Timer2 Compare", false, true);
}

IOPTimersTimer_TIM3_t::IOPTimersTimer_TIM3_t() :
	IOPTimersTimer_t(TIMER_ID)
{
	COUNT = std::make_shared<IOPTimersTimerRegister_COUNT_t>("IOP Timer3 Count", true);
	MODE = std::make_shared<IOPTimersTimerRegister_MODE_t>("IOP Timer3 Mode", 3, COUNT);
	COMP = std::make_shared<Register32_t>("IOP Timer3 Compare", false, true);
}

IOPTimersTimer_TIM4_t::IOPTimersTimer_TIM4_t() :
	IOPTimersTimer_t(TIMER_ID)
{
	COUNT = std::make_shared<IOPTimersTimerRegister_COUNT_t>("IOP Timer4 Count", true);
	MODE = std::make_shared<IOPTimersTimerRegister_MODE_t>("IOP Timer4 Mode", 4, COUNT);
	COMP = std::make_shared<Register32_t>("IOP Timer4 Compare", false, true);
}

IOPTimersTimer_TIM5_t::IOPTimersTimer_TIM5_t() :
	IOPTimersTimer_t(TIMER_ID)
{
	COUNT = std::make_shared<IOPTimersTimerRegister_COUNT_t>("IOP Timer5 Count", true);
	MODE = std::make_shared<IOPTimersTimerRegister_MODE_t>("IOP Timer5 Mode", 5, COUNT);
	COMP = std::make_shared<Register32_t>("IOP Timer5 Compare", false, true);
}
