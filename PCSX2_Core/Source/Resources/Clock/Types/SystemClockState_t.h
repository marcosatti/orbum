#pragma once

#include "Resources/Clock/Types/ClockSource_t.h"

/*
Stores information about a system's clock state (clock sources and associated number of ticks available).
*/
struct SystemClockState_t
{
	ClockSource_t mClockSource;
	double        mClockBias;
	double        mTicksAvailable;
};