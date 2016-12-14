#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "PS2Constants/PS2Constants.h"

class IOPTimersTimer_t;

/*
IOP Timers resources.
Contains 3 16-bit and 3 32-bit timers.
TODO: double check and fill in.
*/
class IOPTimers_t : public PS2ResourcesSubobject
{
public:
	explicit IOPTimers_t(const PS2Resources_t *const PS2Resources);

	/*
	IOP timers.
	No official documentation, from PCSX2.
	*/
	std::shared_ptr<IOPTimersTimer_t> TIMER_0;
	std::shared_ptr<IOPTimersTimer_t> TIMER_1;
	std::shared_ptr<IOPTimersTimer_t> TIMER_2;
	std::shared_ptr<IOPTimersTimer_t> TIMER_3;
	std::shared_ptr<IOPTimersTimer_t> TIMER_4;
	std::shared_ptr<IOPTimersTimer_t> TIMER_5;
	std::shared_ptr<IOPTimersTimer_t> TIMERS[PS2Constants::IOP::Timers::NUMBER_TIMERS];

};

