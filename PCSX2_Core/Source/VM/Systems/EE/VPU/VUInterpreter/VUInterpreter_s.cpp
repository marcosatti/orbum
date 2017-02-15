#include "stdafx.h"

#include "VM/Systems/EE/VPU/VUInterpreter/VUInterpreter_s.h"

VUInterpreter_s::VUInterpreter_s(VM* vmMain, u32 vuUnitIndex) :
	VMSystem_s(vmMain),
	mVUUnitIndex(vuUnitIndex)
{
}

VUInterpreter_s::~VUInterpreter_s()
{
}

void VUInterpreter_s::run(const double& time)
{
	// Create VM tick event.
	ClockEvent_t vmClockEvent =
	{
		ClockSource_t::EEBusClock,
		time / 1.0e6 * Constants::EE::EEBUS_CLK_SPEED
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

int VUInterpreter_s::step(const ClockEvent_t& event)
{
	// TODO: Implement.
	return 1;
}
