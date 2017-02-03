#pragma once

#include <memory>

#include "Common/Global/Globals.h"

class IOPTimersTimerRegister_MODE_t;
class IOPTimersTimerRegister_COUNT_t;
class Register32_t;

/*
A base type representing an IOP Timers Timer.
Documentation taken from PCSX2 and No$PSX docs.
*/
class IOPTimersTimer_t
{
public:
	explicit IOPTimersTimer_t(const u32 & timerID);

	/*
	The ID of this timer. Used for debug.
	*/
	const u32 mTimerID;

	/*
	IOP Timers timer registers.
	The Mode, Count and Compare registers are defined for each timer.
	Count must be initalised before Mode due to dependency.
	*/
	std::shared_ptr<IOPTimersTimerRegister_COUNT_t> COUNT;
	std::shared_ptr<IOPTimersTimerRegister_MODE_t>  MODE;
	std::shared_ptr<Register32_t>                   COMP;
};

/*
Represents IOP Timer0.
*/
class IOPTimersTimer_TIM0_t : public IOPTimersTimer_t
{
public:
	IOPTimersTimer_TIM0_t();

	static constexpr u32 TIMER_ID = 0;
};

/*
Represents IOP Timer1.
*/
class IOPTimersTimer_TIM1_t : public IOPTimersTimer_t
{
public:
	IOPTimersTimer_TIM1_t();

	static constexpr u32 TIMER_ID = 1;
};

/*
Represents IOP Timer2.
*/
class IOPTimersTimer_TIM2_t : public IOPTimersTimer_t
{
public:
	IOPTimersTimer_TIM2_t();

	static constexpr u32 TIMER_ID = 2;
};

/*
Represents IOP Timer3.
*/
class IOPTimersTimer_TIM3_t : public IOPTimersTimer_t
{
public:
	IOPTimersTimer_TIM3_t();

	static constexpr u32 TIMER_ID = 3;
};

/*
Represents IOP Timer4.
*/
class IOPTimersTimer_TIM4_t : public IOPTimersTimer_t
{
public:
	IOPTimersTimer_TIM4_t();

	static constexpr u32 TIMER_ID = 4;
};

/*
Represents IOP Timer5.
*/
class IOPTimersTimer_TIM5_t : public IOPTimersTimer_t
{
public:
	IOPTimersTimer_TIM5_t();

	static constexpr u32 TIMER_ID = 5;
};