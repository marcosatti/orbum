#include "stdafx.h"

#include "Common/PS2Resources/EE/Timers/Timers_t.h"
#include "Common/PS2Resources/EE/Timers/Types/TimerEvent_t.h"
#include "Common/PS2Resources/EE/EE_t.h"

Timers_t::Timers_t() :
	mNumPS2CLKEvents(0),
	TimerEventQueue(std::make_shared<std::queue<TimerEvent_t>>())
{
}

void Timers_t::raiseTimerEventPS2CLK(const u32 & cycles)
{
	// Add the number of PS2CLK's that just occured.
	mNumPS2CLKEvents += cycles;

	if (mNumPS2CLKEvents % 2 == 0) // Check for BUSCLK (PS2CLK / 2) event.
	{
		TimerEventQueue->push(TimerEvent_t(TimerEvent_t::ClockEvent_t::BUSCLK));
	}
	else if (mNumPS2CLKEvents % 32 == 0) // Check for BUSCLK / 16 (PS2CLK / 32) event.
	{
		TimerEventQueue->push(TimerEvent_t(TimerEvent_t::ClockEvent_t::BUSCLK16));
	}
	else if (mNumPS2CLKEvents % 512 == 0) // Check for BUSCLK / 256 (PS2CLK / 512) event.
	{
		TimerEventQueue->push(TimerEvent_t(TimerEvent_t::ClockEvent_t::BUSCLK256));
	}
}

void Timers_t::raiseTimerEventHBLNK()
{
	TimerEventQueue->push(TimerEvent_t(TimerEvent_t::ClockEvent_t::HBLNK));
}
