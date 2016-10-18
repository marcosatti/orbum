#pragma once

#include "Common/Global/Globals.h"
#include "Common/PS2Resources/Clock/Types/ClockSource_t.h"

/*
Clock_t helps with synchronisation across components.

It defines an array which defines the clock speed ratios of components within the PS2 system to the base clock used (PS2CLK, which is equal to the EE Core clock speed of ~294 MHz).

The values can be updated at runtime. For the HBLNK clock source, this is controled by the GS.

This class is tightly coupled with VMExecutionCoreComponent - see for more details.
*/

class Clock_t
{
public:
	explicit Clock_t();

	/*
	An array of ratio values for each clock source (within ClockSource_t) to the PS2CLK.
	It should be accessed based upon the ClockSource_t enum index.
	Use these to determine the relative timing of components.
	*/
	u32 RATIO_PS2CLK[static_cast<u32>(ClockSource_t::NUMBER_SOURCES)];
	
};

