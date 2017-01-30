#pragma once

#include "Common/Global/Globals.h"

#include "Common/Interfaces/PS2ResourcesSubcategory.h"
#include "PS2Resources/Clock/Types/ClockSource_t.h"

/*
Clock_t helps with synchronisation across components.
It defines the speeds of different clock sources within the PS2 system.
The values can be updated at runtime.
*/
class Clock_t : public PS2ResourcesSubcategory
{
public:
	explicit Clock_t(const PS2Resources_t * PS2Resources);

	inline const double & getClockSpeed(const ClockSource_t & clockSource) const;
	inline void setClockSpeed(const ClockSource_t & clockSource, const double & ticksPerSecond);

private:
	double mClockSpeeds[static_cast<u32>(ClockSource_t::NUM_SOURCES)];
};

const double & Clock_t::getClockSpeed(const ClockSource_t & clockSource) const
{
	return mClockSpeeds[static_cast<u32>(clockSource)];
}

void Clock_t::setClockSpeed(const ClockSource_t & clockSource, const double & ticksPerSecond)
{
	mClockSpeeds[static_cast<u32>(clockSource)] = ticksPerSecond;
}
