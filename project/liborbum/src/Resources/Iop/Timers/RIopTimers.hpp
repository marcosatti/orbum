#pragma once

#include "Common/Constants.hpp"

#include "Resources/Iop/Timers/IopTimersUnits.hpp"

/// IOP timers.
struct RIopTimers
{
	RIopTimers();
	
	/// Contains 16-bit (0 -> 2) and 32-bit (3 -> 5) timers.
	IopTimersUnit_Base unit_0;
	IopTimersUnit_Base unit_1;
	IopTimersUnit_Base unit_2;
	IopTimersUnit_Base unit_3;
	IopTimersUnit_Base unit_4;
	IopTimersUnit_Base unit_5;

	/// Timer abstractions.
	IopTimersUnit_Base * units[Constants::IOP::Timers::NUMBER_TIMERS];
};