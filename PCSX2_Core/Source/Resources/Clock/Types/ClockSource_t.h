#pragma once

/*
Represents the type of clock source. This lists all possible sources of clock events in the PS2.
*/
enum class ClockSource_t
{
	EECore,
	EEBus,
	EEBus16,
	EEBus256,
	IOPCore,
	IOPBus,
	IOPBus8,
	IOPBus16,
	IOPBus256,
	HBLNK,

	NUMBER_SOURCES
};