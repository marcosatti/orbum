#pragma once

#include <vector>

#include "Common/Global/Globals.h"

#include "Resources/Clock/Types/System_t.h"
#include "Resources/Clock/Types/ClockSource_t.h"
#include "Resources/Clock/Types/SystemClockState_t.h"

/*
Clock_t helps with synchronisation across components.
*/
class Clock_t
{
public:
	explicit Clock_t();

	/*
	Gets the default clock speed for a given system.
	*/
	static const double & getBaseClockSpeed(const ClockSource_t & source);

	/*
	Returns the system clock state for the given system.
	*/
	std::vector<SystemClockState_t> & getSystemClockState(const System_t & system);


	/*
	Sets the bias for a given system.
	*/
	void setSystemSpeedBias(const System_t & system, const double & bias);

private:
	/*
	Array of component clock states.
	*/
	std::vector<SystemClockState_t> mSystemClockStates[static_cast<int>(System_t::NUMBER_SYSTEMS)];
};

