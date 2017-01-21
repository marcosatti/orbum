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
	IOPCLK    = 5,
	IOPCLK8   = 6,
	IOPCLK16  = 7,
	IOPCLK256 = 8,
	PIXEL     = 9,  // aka DOTCLOCK?
	VBLNK     = 10,

	NUM_SOURCES // Provided to create arrays.
};