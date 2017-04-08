#pragma once

#include <memory>

#include "Common/Global/Globals.h"

class IOPTimersTimer_t;
class IOPTimersTimer_TIM0_t;
class IOPTimersTimer_TIM1_t;
class IOPTimersTimer_TIM2_t;
class IOPTimersTimer_TIM3_t;
class IOPTimersTimer_TIM4_t;
class IOPTimersTimer_TIM5_t;

/*
IOP Timers resources.
Contains 3 16-bit and 3 32-bit timers.
TODO: double check and fill in.
*/
class IOPTimers_t
{
public:
	IOPTimers_t();

	/*
	IOP timers.
	No official documentation, from PCSX2.
	*/
	std::shared_ptr<IOPTimersTimer_TIM0_t> TIMER_0;
	std::shared_ptr<IOPTimersTimer_TIM1_t> TIMER_1;
	std::shared_ptr<IOPTimersTimer_TIM2_t> TIMER_2;
	std::shared_ptr<IOPTimersTimer_TIM3_t> TIMER_3;
	std::shared_ptr<IOPTimersTimer_TIM4_t> TIMER_4;
	std::shared_ptr<IOPTimersTimer_TIM5_t> TIMER_5;
	std::shared_ptr<IOPTimersTimer_t>      TIMERS[Constants::IOP::Timers::NUMBER_TIMERS];

};

