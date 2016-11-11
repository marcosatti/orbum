#pragma once

#include <memory>

#include "Common/Global/Globals.h"

/*
EETimersTimer defines the timers available in the EE Timers.
These include (see EE Users Manual page 34):
 - TIMER0
 - TIMER1
 - TIMER2
 - TIMER3

They are subclassed from the base channel class - EETimersTimer_t.
*/

/*
A base type representing an EE Timers Timer.
See EE Users Manual page 35 for the list of registers declared forming this type.

Subclassed by EE Timers timer 0-3 (see EETimersTimer_Timer0_t - EETimersTimer_Timer3_t).
Not all of the registers are implemented in this base class for each channel.
*/

class EETimersTimerRegister_Mode_t;
class EETimersTimerRegister_Count_t;
class Register32_t;

class EETimersTimer_t
{
public:
	explicit EETimersTimer_t(const u32 & timerID);

	/*
	The ID of this timer. Used for debug.
	*/
	const u32 mTimerID;

	/*
	EE Timers timer registers.
	See EE Users Manual page 35.

	MODE and COUNT is always defined for each timer - they are initalised in this base class.

	COUNT must be initalised before MODE due to dependency.
	*/
	std::shared_ptr<EETimersTimerRegister_Count_t> mCOUNT;
	std::shared_ptr<EETimersTimerRegister_Mode_t>  mMODE;
	std::shared_ptr<Register32_t>                  mCOMP;
	std::shared_ptr<Register32_t>                  mHOLD;
};

/*
Represents EE Timers Timer0.
MODE, COUNT, COMP and HOLD are all defined.
*/
class EETimersTimer_Timer0_t : public EETimersTimer_t
{
public:
	explicit EETimersTimer_Timer0_t();

	static constexpr u32 TIMER_ID = 0;
};

/*
Represents EE Timers Timer1.
MODE, COUNT, COMP and HOLD are all defined.
*/
class EETimersTimer_Timer1_t : public EETimersTimer_t
{
public:
	explicit EETimersTimer_Timer1_t();

	static constexpr u32 TIMER_ID = 1;
};

/*
Represents EE Timers Timer2.
MODE, COUNT and COMP are defined and HOLD is not.
*/
class EETimersTimer_Timer2_t : public EETimersTimer_t
{
public:
	explicit EETimersTimer_Timer2_t();

	static constexpr u32 TIMER_ID = 2;
};

/*
Represents EE Timers Timer3.
MODE, COUNT and COMP are defined and HOLD is not.
*/
class EETimersTimer_Timer3_t : public EETimersTimer_t
{
public:
	explicit EETimersTimer_Timer3_t();

	static constexpr u32 TIMER_ID = 3;
};