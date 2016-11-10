#include "stdafx.h"

#include "PS2Resources/EE/Timers/Types/EETimersTimers_t.h"
#include "PS2Resources/EE/Timers/Types/EETimersTimerRegisters_t.h"

EETimersTimer_t::EETimersTimer_t(const u32 & timerID) :
	mTimerID(timerID),
	mMODE(std::make_shared<EETimersTimerRegister_Mode_t>(mCOUNT)),
	mCOUNT(std::make_shared<EETimersTimerRegister_Count_t>()),
	mCOMP(std::make_shared<Register32_t>()),
	mHOLD(nullptr)
{
}

EETimersTimer_TIM0_t::EETimersTimer_TIM0_t() :
	EETimersTimer_t(TIMER_ID)
{
	mHOLD = std::make_shared<Register32_t>();
}

EETimersTimer_TIM1_t::EETimersTimer_TIM1_t() :
	EETimersTimer_t(TIMER_ID)
{
	mHOLD = std::make_shared<Register32_t>();
}

EETimersTimer_TIM2_t::EETimersTimer_TIM2_t() :
	EETimersTimer_t(TIMER_ID)
{
}

EETimersTimer_TIM3_t::EETimersTimer_TIM3_t() :
	EETimersTimer_t(TIMER_ID)
{
}