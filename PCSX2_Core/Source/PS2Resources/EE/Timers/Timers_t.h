#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "PS2Constants/PS2Constants.h"

class EETimersTimer_t;
class EETimersTimer_TIM0_t;
class EETimersTimer_TIM1_t;
class EETimersTimer_TIM2_t;
class EETimersTimer_TIM3_t;

class Timers_t : public PS2ResourcesSubobject
{
public:
	explicit Timers_t(const PS2Resources_t *const PS2Resources);

	/*
	EE Timers resources. There are 4 timers in total.
	See EE Users Manual page 33 onwards.
	Also provided is an array used in iterations.
	*/
	std::shared_ptr<EETimersTimer_TIM0_t> Timer0;
	std::shared_ptr<EETimersTimer_TIM1_t> Timer1;
	std::shared_ptr<EETimersTimer_TIM2_t> Timer2;
	std::shared_ptr<EETimersTimer_TIM3_t> Timer3;
	std::shared_ptr<EETimersTimer_t>      EE_TIMERS[PS2Constants::EE::Timers::NUMBER_TIMERS];

};

