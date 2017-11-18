#pragma once

#include "Common/Constants.hpp"

#include "Resources/Iop/Timers/IopTimersUnits.hpp"

/// IOP timers.
struct RIopTimers
{
	RIopTimers();
	
	/// Contains 16-bit (0 -> 2) and 32-bit (3 -> 5) timers.
	IopTimersUnit timer_0;
	IopTimersUnit timer_1;
	IopTimersUnit timer_2;
	IopTimersUnit timer_3;
	IopTimersUnit timer_4;
	IopTimersUnit timer_5;

	/// Timer abstractions.
	// IopTimersUnit * timers[Constants::IOP::Timers::NUMBER_TIMERS];
};