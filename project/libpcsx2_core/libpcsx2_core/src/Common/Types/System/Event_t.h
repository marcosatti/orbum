#pragma once

#include "Common/Global/Globals.h"
#include "Common/Types/Util/EnumMap_t.h"

/*
Describes an event, contaning the source and the amount of this event that occurred (batched).
Use this quantity value in a loop to process all of the events.
ie: while (event.mQuantity > 0)
        event.mQuantity -= step(event);
*/
class Event_t
{
public:
	enum class Source
	{
		ClockTick,
		Pixel,
		HBlank,
		VBlank,
		COUNT
	}; 

	Event_t() = default;
	Event_t(const Source source, const int quantity) :
		mSource(source),
		mQuantity(quantity)
	{
	}

	Source mSource;
	int    mQuantity;
};

#if defined(BUILD_DEBUG)
/*
Static array of event source names used for debug logging.
*/
static constexpr EnumMap_t<Event_t::Source, const char *> DEBUG_EVENTSOURCE_STRINGS =
{
	"ClockTick",
	"Pixel",
	"HBlank",
	"VBlank"
};
#endif