#pragma once

/*
The TimerEvent_t class type holds information needed for processing a timer event. An object of this type should only ever be generated from the TimerHandler class.
It holds information about what kind of timer clock event just happened, and how many occured.
*/

struct TimerEvent_t
{
	/*
	The type of clock source. The order is synced with the order on page 36 of the EE Users Manual.
	Do not change the order!
	*/
	enum class ClockSource_t
	{
		BUSCLK = 0,
		BUSCLK16 = 1,
		BUSCLK256 = 2,
		HBLNK = 3
	} const mClockSourceType;

	explicit TimerEvent_t(ClockSource_t clockSourceType);
};