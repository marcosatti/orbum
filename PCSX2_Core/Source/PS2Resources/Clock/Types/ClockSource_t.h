#pragma once

/*
Represents the type of clock source. This lists all possible sources of clock events in the PS2.
See the PS2Resources_t::Clock class, which assigns clock speed ratios to the enums listed.
*/
enum class ClockSource_t
{
	PS2CLK    = 0,
	BUSCLK    = 1,
	BUSCLK16  = 2,
	BUSCLK256 = 3,
	HBLNK     = 4,
	IOP       = 5,

	NUM_SOURCES // Provided to create arrays.
};