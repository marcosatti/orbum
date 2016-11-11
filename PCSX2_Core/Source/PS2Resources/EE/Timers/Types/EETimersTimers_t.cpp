#include "stdafx.h"

#include "PS2Resources/EE/Timers/Types/EETimersTimers_t.h"
#include "PS2Resources/EE/Timers/Types/EETimersTimerRegisters_t.h"

EETimersTimer_t::EETimersTimer_t(const u32 & timerID) :
	mTimerID(timerID),
	mCOUNT(std::make_shared<EETimersTimerRegister_Count_t>()),
	mMODE(std::make_shared<EETimersTimerRegister_Mode_t>(mCOUNT)),
	mCOMP(std::make_shared<Register32_t>()),
	mHOLD(nullptr)
{
}

EETimersTimer_Timer0_t::EETimersTimer_Timer0_t() :
	EETimersTimer_t(TIMER_ID)
{
	mHOLD = std::make_shared<Register32_t>();
}

EETimersTimer_Timer1_t::EETimersTimer_Timer1_t() :
	EETimersTimer_t(TIMER_ID)
{
	mHOLD = std::make_shared<Register32_t>();
}

EETimersTimer_Timer2_t::EETimersTimer_Timer2_t() :
	EETimersTimer_t(TIMER_ID)
{
}

EETimersTimer_Timer3_t::EETimersTimer_Timer3_t() :
	EETimersTimer_t(TIMER_ID)
{
}