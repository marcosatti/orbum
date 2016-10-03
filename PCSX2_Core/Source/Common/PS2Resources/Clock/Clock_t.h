#pragma once

#include "Common/Global/Globals.h"

/*
Clock_t provides synchronisation across components, by recording the relative times between clock speeds, such as the PS2CLK (~294 MHz) and BUSCLK (~147 MHz)
 and H-BLNK (depends on GS mode set at runtime).
By using the provided functions in an execution core, it will be able to run the different components at approximately the right speed.

PS2CLK is always used as the base clock at which the others are relatives of. For example, for every 2 PS2CLK's that happen, 1 BUSCLK will occur.
In terms of the part of the emulator that controls this, it is the EE Core component. See the EECoreInterpreter as an example.

TODO: Add in a PS2CLK event, if required. So far nothing requires this, except for the EE Core but that is already used as the base reference (which includes the COP0.Count updates).
*/

class Clock_t
{
public:
	explicit Clock_t();

	/*
	As the HBLNK clock speed is set at runtime by the GS, this variable represents the ratio of PS2CLK / HBLNK, which is then used by the updateClocks()
	 function above to time HBLNK ticks.
	Set initially to a high enough value so it wont run until the GS has come up.
	*/
	u32 RATIO_PS2CLK_HBLNK;

	/*
	Represents the number of PS2CLK ticks each clock source other than PS2CLK has completed. These are updated through the updateClocks() function.
	They are also used by the isTicked*() functions, where if they have a value above the ratio, it means it is time for that clock source to 'tick'.
	See the example in the isTicked*() documentation.
	*/
	u64 NumTicksBUSCLK;
	u64 NumTicksBUSCLK16;
	u64 NumTicksBUSCLK256;
	u64 NumTicksHBLNK;

	/*
	Updates the PS2CLK clock source based upon the number of PS2CLKs that just occured. This should only be run from an PS2CLK 'loop'.
	As an example, in the interpreter, it is run every time EECoreInterpreter runs (see EECoreInterpreter::executeInstruction()).
	 
	Call the isTicked*() functions after to check if another clock source has 'ticked' and components should be run.
	*/
	void updateClocks(const u32 & numClocksPS2CLK);

	/*
	Returns a bool if the number of PS2CLKs have caused a different source clock to 'tick', meaning that other components should be allowed to run
	 in order to synchronise.

	These functions divide the appropriate tick count above by the ratio, and return true if this is above 0. If true, it also subtracts the ratio
	 from the tick count.
	Note that there may be more than one 'tick' that has occured, meaning these functions should be run in a while(isTicked*()) loop.

	An example of the BUSCLK16 clock source is as follows:
	 1. updateClocks() is called with 12 PS2CLKs. This updates the NumTicksBUSCLK16 += 12.
	 2. In a while loop, isTickedBUSCLK16() is called, which checks that NumTicksBUSCLK16 / 16 > 0. 
	    If true, returns true and decrements the variable by the ratio (16). This means the components that rely on the BUSCLK16 source should be run.
		If false, returns false, meaning the components that rely on the BUSCLK16 source should NOT be run.
	*/
	bool isTickedBUSCLK();
	bool isTickedBUSCLK16();
	bool isTickedBUSCLK256();
	bool isTickedHBLNK();
	
};

