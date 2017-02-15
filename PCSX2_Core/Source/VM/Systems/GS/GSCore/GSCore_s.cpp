#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/Systems/GS/GSCore/GSCore_s.h"

GSCore_s::GSCore_s(VM* vmMain) :
	VMSystem_s(vmMain)
{
}

GSCore_s::~GSCore_s()
{
}

void GSCore_s::run(const double& time)
{
	// Create VM tick event.
	ClockEvent_t vmClockEvent =
	{
		ClockSource_t::GSCoreClock,
		time / 1.0e6 * Constants::GS::GSCore::GSCORE_CLK_SPEED
	};
	mClockEventQueue.push(vmClockEvent);

	// Run through events.
	while (!mClockEventQueue.empty())
	{
		auto event = mClockEventQueue.front();
		mClockEventQueue.pop();

		while (event.mNumberTicks >= 1)
		{
			auto ticks = step(event);
			event.mNumberTicks -= ticks;
		}
	}
}

int GSCore_s::step(const ClockEvent_t& event)
{
	return 1;
}
