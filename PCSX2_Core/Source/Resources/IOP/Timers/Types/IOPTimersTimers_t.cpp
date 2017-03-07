#include "stdafx.h"

#include "Resources/IOP/Timers/Types/IOPTimersTimers_t.h"
#include "Resources/IOP/Timers/Types/IOPTimersTimerRegisters_t.h"

IOPTimersTimer_t::IOPTimersTimer_t(const int timerID) :
	COUNT(nullptr),
	MODE(nullptr),
	COMP(nullptr),
	mTimerID(timerID)
{
}

int IOPTimersTimer_t::getTimerID() const
{
	return mTimerID;
}

IOPTimersTimer_TIM0_t::IOPTimersTimer_TIM0_t() :
	IOPTimersTimer_t(TIMER_ID)
{
	COUNT = std::make_shared<IOPTimersTimerRegister_HWORD_COUNT_t>("IOP Timer0 Count");
	MODE = std::make_shared<IOPTimersTimerRegister_MODE_t>("IOP Timer0 Mode", TIMER_ID, COUNT);
	COMP = std::make_shared<Register32_t>("IOP Timer0 Compare", false, true);
}

IOPTimersTimer_TIM1_t::IOPTimersTimer_TIM1_t() :
	IOPTimersTimer_t(TIMER_ID)
{
	COUNT = std::make_shared<IOPTimersTimerRegister_HWORD_COUNT_t>("IOP Timer1 Count");
	MODE = std::make_shared<IOPTimersTimerRegister_MODE_t>("IOP Timer1 Mode", TIMER_ID, COUNT);
	COMP = std::make_shared<Register32_t>("IOP Timer1 Compare", false, true);
}

IOPTimersTimer_TIM2_t::IOPTimersTimer_TIM2_t() :
	IOPTimersTimer_t(TIMER_ID)
{
	COUNT = std::make_shared<IOPTimersTimerRegister_HWORD_COUNT_t>("IOP Timer2 Count");
	MODE = std::make_shared<IOPTimersTimerRegister_MODE_t>("IOP Timer2 Mode", TIMER_ID, COUNT);
	COMP = std::make_shared<Register32_t>("IOP Timer2 Compare", false, true);
}

IOPTimersTimer_TIM3_t::IOPTimersTimer_TIM3_t() :
	IOPTimersTimer_t(TIMER_ID)
{
	COUNT = std::make_shared<IOPTimersTimerRegister_WORD_COUNT_t>("IOP Timer3 Count");
	MODE = std::make_shared<IOPTimersTimerRegister_MODE_t>("IOP Timer3 Mode", TIMER_ID, COUNT);
	COMP = std::make_shared<Register32_t>("IOP Timer3 Compare", false, true);
}

IOPTimersTimer_TIM4_t::IOPTimersTimer_TIM4_t() :
	IOPTimersTimer_t(TIMER_ID)
{
	COUNT = std::make_shared<IOPTimersTimerRegister_WORD_COUNT_t>("IOP Timer4 Count");
	MODE = std::make_shared<IOPTimersTimerRegister_MODE_t>("IOP Timer4 Mode", TIMER_ID, COUNT);
	COMP = std::make_shared<Register32_t>("IOP Timer4 Compare", false, true);
}

IOPTimersTimer_TIM5_t::IOPTimersTimer_TIM5_t() :
	IOPTimersTimer_t(TIMER_ID)
{
	COUNT = std::make_shared<IOPTimersTimerRegister_WORD_COUNT_t>("IOP Timer5 Count");
	MODE = std::make_shared<IOPTimersTimerRegister_MODE_t>("IOP Timer5 Mode", TIMER_ID, COUNT);
	COMP = std::make_shared<Register32_t>("IOP Timer5 Compare", false, true);
}
