#pragma once

#include "Common/Global/Globals.h"

#include "Common/Interfaces/PS2ResourcesSubcategory.h"
#include "PS2Resources/Clock/Types/ClockSource_t.h"

/*
Clock_t helps with synchronisation across components.
It defines the clock speed ratios of components within the PS2 system to the base clock used (PS2CLK, which is equal to the EE Core clock speed of ~294 MHz).
The values can be updated at runtime. For the HBLNK clock source, this is controled by the GS.
This class is tightly coupled with VMExecutionCoreComponent - see for more details.
*/

class Clock_t : public PS2ResourcesSubcategory
{
public:
	explicit Clock_t(const PS2Resources_t * PS2Resources);

	/*
	Get/set ratio values for each clock source (within ClockSource_t) to the PS2CLK.
	It should be accessed based upon the ClockSource_t enum index.
	Use these to determine the relative timing of components (ie: see VMExecutionCoreComponent).
	These functions will throw a runtime error if the clock source is not valid.
	*/
	inline const u32 & getClockRatio(const ClockSource_t & clockSource) const;
	inline void setClockRatio(const ClockSource_t & clockSource, const u32 & ratioPS2CLK);

private:
	/*
	Clock speed ratios (relative to PS2CLK) for each valid clock source.
	Use the get/setClockRatio() functions to access these values.
	Most of the time these values will stay constant through emulation. However it allows for under/overclocking of the PS2 components.
	They are initalised to the default values of a PS2 system, with the exception of HBLNK which is set at runtime.
	Initially HBLNK is set to the max u32 value so a clock event will (likely) not occur before being set at runtime.
	*/
	u32 mClockRatio[static_cast<u32>(ClockSource_t::NUM_SOURCES)];
};

const u32& Clock_t::getClockRatio(const ClockSource_t& clockSource) const
{
	return mClockRatio[static_cast<u32>(clockSource)];
}

void Clock_t::setClockRatio(const ClockSource_t& clockSource, const u32& PS2CLKRatio)
{
	mClockRatio[static_cast<u32>(clockSource)] = PS2CLKRatio;
}
