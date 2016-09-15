#pragma once

/*
The TimerEvent_t class type holds information needed for processing a timer event. An object of this type should only ever be generated from the TimerHandler class.
It holds information about what kind of timer clock event just happened, and how many occured.
*/

struct TimerEvent_t
{
	enum class ClockEvent_t
	{
		BUSCLK,
		BUSCLK16,
		BUSCLK256,
		HBLNK
	} const mClockEventType;

	explicit TimerEvent_t(ClockEvent_t ClockEventType);
};