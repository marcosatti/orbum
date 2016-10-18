#pragma once

/*
Represents the type of clock source. 
*/
enum class ClockSource_t
{
	VM = 0, // Value included to represent a VM loop.
	PS2CLK = 1,
	BUSCLK = 2,
	BUSCLK16 = 3,
	BUSCLK256 = 4,
	HBLNK = 5,
	IOP = 6,
	NUMBER_SOURCES // Trick to determine the number of clock sources in total, used for creating arrays.
};