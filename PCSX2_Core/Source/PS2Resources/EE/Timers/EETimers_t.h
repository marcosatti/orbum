#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "PS2Constants/PS2Constants.h"

class EETimersTimer_t;

/*
The EE Timers resources.
Defines the 4 timers within the EE, as listed on page 33 onwards of the EE Users Manual.
*/
class EETimers_t : public PS2ResourcesSubobject
{
public:
	explicit EETimers_t(const PS2Resources_t *const PS2Resources);

	/*
	EE Timers resources. There are 4 timers in total.
	See EE Users Manual page 33 onwards.
	Also provided is an array used in iterations.
	*/
	std::shared_ptr<EETimersTimer_t> TIMER_0;
	std::shared_ptr<EETimersTimer_t> TIMER_1;
	std::shared_ptr<EETimersTimer_t> TIMER_2;
	std::shared_ptr<EETimersTimer_t> TIMER_3;
	std::shared_ptr<EETimersTimer_t> TIMERS[PS2Constants::EE::Timers::NUMBER_TIMERS];

};

