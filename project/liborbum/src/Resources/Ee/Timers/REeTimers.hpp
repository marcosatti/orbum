#pragma once

#include "Common/Constants.hpp"

#include "Resources/Ee/Timers/EeTimersUnits.hpp"

/// The EE Timers resources.
/// Defines the 4 timers within the EE, as listed on page 33 onwards of the EE Users Manual.
struct REeTimers
{
	REeTimers();
	
	EeTimersUnit_Hold timer_0;
	EeTimersUnit_Hold timer_1;
	EeTimersUnit_Base timer_2;
	EeTimersUnit_Base timer_3;

	/// Timer abstractions.
	// EeTimersUnit * timers[Constants::EE::Timers::NUMBER_TIMERS];
};

