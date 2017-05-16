#include "Resources/EE/Timers/Types/EETimersTimers_t.h"
#include "Resources/EE/Timers/Types/EETimersTimerRegisters_t.h"

EETimersTimer_t::EETimersTimer_t(const int timerID) :
	COUNT(nullptr),
	MODE(nullptr),
	COMP(nullptr),
	HOLD(nullptr),
	mTimerID(timerID)
{
}

int EETimersTimer_t::getTimerID() const
{
	return mTimerID;
}

EETimersTimer_TIM0_t::EETimersTimer_TIM0_t() :
	EETimersTimer_t(TIMER_ID)
{
	COUNT = std::make_shared<EETimersTimerRegister_COUNT_t>("EE Timer0 Count", false, false);
	MODE = std::make_shared<EETimersTimerRegister_MODE_t>("EE Timer0 Mode", false, false, COUNT);
	COMP = std::make_shared<Register32_t>("EE Timer0 Compare", false, false);
	HOLD = std::make_shared<Register32_t>("EE Timer0 Hold", false, false);
}

EETimersTimer_TIM1_t::EETimersTimer_TIM1_t() :
	EETimersTimer_t(TIMER_ID)
{
	COUNT = std::make_shared<EETimersTimerRegister_COUNT_t>("EE Timer1 Count", false, false);
	MODE = std::make_shared<EETimersTimerRegister_MODE_t>("EE Timer1 Mode", false, false, COUNT);
	COMP = std::make_shared<Register32_t>("EE Timer1 Compare", false, false);
	HOLD = std::make_shared<Register32_t>("EE Timer1 Hold", false, false);
}

EETimersTimer_TIM2_t::EETimersTimer_TIM2_t() :
	EETimersTimer_t(TIMER_ID)
{
	COUNT = std::make_shared<EETimersTimerRegister_COUNT_t>("EE Timer2 Count", false, false);
	MODE = std::make_shared<EETimersTimerRegister_MODE_t>("EE Timer2 Mode", false, false, COUNT);
	COMP = std::make_shared<Register32_t>("EE Timer2 Compare", false, false);
}

EETimersTimer_TIM3_t::EETimersTimer_TIM3_t() :
	EETimersTimer_t(TIMER_ID)
{
	COUNT = std::make_shared<EETimersTimerRegister_COUNT_t>("EE Timer3 Count", false, false);
	MODE = std::make_shared<EETimersTimerRegister_MODE_t>("EE Timer3 Mode", false, false, COUNT);
	COMP = std::make_shared<Register32_t>("EE Timer3 Compare", false, false);
}
