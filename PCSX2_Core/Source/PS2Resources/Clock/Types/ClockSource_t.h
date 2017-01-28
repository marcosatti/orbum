#pragma once

/*
Represents the type of clock source. This lists all possible sources of clock events in the PS2.
*/
enum class ClockSource_t
{
	EECore    = 0,
	EEBus     = 1,
	EEBus16   = 2,
	EEBus256  = 3,
	IOPCore   = 4,
	IOPBus    = 5,
	IOPBus8   = 6,
	IOPBus16  = 7,
	IOPBus256 = 8,
	HBLNK     = 9,

	NUM_SOURCES // Provided to create arrays.
};