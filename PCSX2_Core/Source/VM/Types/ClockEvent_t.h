#pragma once
#include "Resources/Clock/Types/ClockSource_t.h"

struct ClockEvent_t
{
	ClockSource_t mClockSource;
	int           mNumberTicks;
};
