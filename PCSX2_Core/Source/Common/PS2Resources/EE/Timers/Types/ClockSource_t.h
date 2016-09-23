#pragma once

/*
The type of clock source. The order is synced with the order on page 36 of the EE Users Manual, and needed by the TimerHandler to compare values.
Do not change the order!
*/
	
enum class ClockSource_t
{
	BUSCLK = 0,
	BUSCLK16 = 1,
	BUSCLK256 = 2,
	HBLNK = 3
};