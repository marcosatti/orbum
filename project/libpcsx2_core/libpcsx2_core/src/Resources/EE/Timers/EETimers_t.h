#pragma once

#include <memory>

#include "Common/Global/Globals.h"

class EETimersTimer_TIM0_t;
class EETimersTimer_TIM1_t;
class EETimersTimer_TIM2_t;
class EETimersTimer_TIM3_t;
class EETimersTimer_t;

/*
The EE Timers resources.
Defines the 4 timers within the EE, as listed on page 33 onwards of the EE Users Manual.
*/
class EETimers_t
{
public:
	EETimers_t();

	/*
	EE Timers resources. There are 4 timers in total.
	See EE Users Manual page 33 onwards.
	*/
	std::shared_ptr<EETimersTimer_TIM0_t> TIMER_0;
	std::shared_ptr<EETimersTimer_TIM1_t> TIMER_1;
	std::shared_ptr<EETimersTimer_TIM2_t> TIMER_2;
	std::shared_ptr<EETimersTimer_TIM3_t> TIMER_3;
	std::shared_ptr<EETimersTimer_t>      TIMERS[Constants::EE::Timers::NUMBER_TIMERS];

};

