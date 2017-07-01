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
	COUNT = std::make_shared<IOPTimersTimerRegister_HWORD_COUNT_t>("IOP Timer0 Count", false, false);
	MODE = std::make_shared<IOPTimersTimerRegister_MODE_t>("IOP Timer0 Mode", false, false, TIMER_ID, COUNT);
	COMP = std::make_shared<Register32_t>("IOP Timer0 Compare", false, false);
}

IOPTimersTimer_TIM1_t::IOPTimersTimer_TIM1_t() :
	IOPTimersTimer_t(TIMER_ID)
{
	COUNT = std::make_shared<IOPTimersTimerRegister_HWORD_COUNT_t>("IOP Timer1 Count", false, false);
	MODE = std::make_shared<IOPTimersTimerRegister_MODE_t>("IOP Timer1 Mode", false, false, TIMER_ID, COUNT);
	COMP = std::make_shared<Register32_t>("IOP Timer1 Compare", false, true);
}

IOPTimersTimer_TIM2_t::IOPTimersTimer_TIM2_t() :
	IOPTimersTimer_t(TIMER_ID)
{
	COUNT = std::make_shared<IOPTimersTimerRegister_HWORD_COUNT_t>("IOP Timer2 Count", false, false);
	MODE = std::make_shared<IOPTimersTimerRegister_MODE_t>("IOP Timer2 Mode", false, false, TIMER_ID, COUNT);
	COMP = std::make_shared<Register32_t>("IOP Timer2 Compare", false, false);
}

IOPTimersTimer_TIM3_t::IOPTimersTimer_TIM3_t() :
	IOPTimersTimer_t(TIMER_ID)
{
	COUNT = std::make_shared<IOPTimersTimerRegister_WORD_COUNT_t>("IOP Timer3 Count", false, false);
	MODE = std::make_shared<IOPTimersTimerRegister_MODE_t>("IOP Timer3 Mode", false, false, TIMER_ID, COUNT);
	COMP = std::make_shared<Register32_t>("IOP Timer3 Compare", false, false);
}

IOPTimersTimer_TIM4_t::IOPTimersTimer_TIM4_t() :
	IOPTimersTimer_t(TIMER_ID)
{
	COUNT = std::make_shared<IOPTimersTimerRegister_WORD_COUNT_t>("IOP Timer4 Count", false, false);
	MODE = std::make_shared<IOPTimersTimerRegister_MODE_t>("IOP Timer4 Mode", false, false, TIMER_ID, COUNT);
	COMP = std::make_shared<Register32_t>("IOP Timer4 Compare", false, false);
}

IOPTimersTimer_TIM5_t::IOPTimersTimer_TIM5_t() :
	IOPTimersTimer_t(TIMER_ID)
{
	COUNT = std::make_shared<IOPTimersTimerRegister_WORD_COUNT_t>("IOP Timer5 Count", false, false);
	MODE = std::make_shared<IOPTimersTimerRegister_MODE_t>("IOP Timer5 Mode", false, false, TIMER_ID, COUNT);
	COMP = std::make_shared<Register32_t>("IOP Timer5 Compare", false, false);
}
