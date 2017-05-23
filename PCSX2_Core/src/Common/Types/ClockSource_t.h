#pragma once

#include "Common/Types/EnumMap_t.h"

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
static constexpr EnumMap_t<ClockSource_t, const char *> DEBUG_CLOCKSOURCE_STRINGS =
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
#endif