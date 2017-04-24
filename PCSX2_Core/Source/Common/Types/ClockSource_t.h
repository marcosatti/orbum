#pragma once

#include "Common/Global/Globals.h"

enum class ClockSource_t
{
	EECoreClock,
	EEBusClock,
	VUClock,
	IOPCoreClock,
	IOPBusClock,
	CDVDClock,
	SPU2Clock,
	GSCoreClock,
	PixelClock,
	HBlankClock,
	VBlankClock,

	COUNT
};

#if defined(BUILD_DEBUG)
/*
Static array of names used for debug logging.
*/
static constexpr char * CLOCKSOURCE_STR[static_cast<int>(ClockSource_t::COUNT)] =
{
	"EECoreClock",
	"EEBusClock",
	"VUClock",
	"IOPCoreClock",
	"IOPBusClock",
	"CDVDClock",
	"SPU2Clock",
	"GSCoreClock",
	"PixelClock",
	"HBlankClock",
	"VBlankClock"
};
static const char* getClockSourceStr(const ClockSource_t & system)
{
	return CLOCKSOURCE_STR[static_cast<int>(system)];
}
#endif