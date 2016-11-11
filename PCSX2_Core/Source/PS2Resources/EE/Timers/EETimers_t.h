#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "PS2Constants/PS2Constants.h"

class EETimersTimer_t;
class EETimersTimer_Timer0_t;
class EETimersTimer_Timer1_t;
class EETimersTimer_Timer2_t;
class EETimersTimer_Timer3_t;

class EETimers_t : public PS2ResourcesSubobject
{
public:
	explicit EETimers_t(const PS2Resources_t *const PS2Resources);

	/*
	EE Timers resources. There are 4 timers in total.
	See EE Users Manual page 33 onwards.
	Also provided is an array used in iterations.
	*/
	std::shared_ptr<EETimersTimer_Timer0_t> TIMER0;
	std::shared_ptr<EETimersTimer_Timer1_t> TIMER1;
	std::shared_ptr<EETimersTimer_Timer2_t> TIMER2;
	std::shared_ptr<EETimersTimer_Timer3_t> TIMER3;
	std::shared_ptr<EETimersTimer_t>        TIMERS[PS2Constants::EE::Timers::NUMBER_TIMERS];

};

