#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VM.h"
#include "VM/Systems/IOP/INTC/IOPIntc_s.h"

#include "Resources/Resources_t.h"
#include "Resources/IOP/IOP_t.h"
#include "Resources/IOP/INTC/IOPIntc_t.h"
#include "Resources/IOP/INTC/Types/IOPIntcRegisters_t.h"
#include "Resources/IOP/IOPCore/IOPCore_t.h"
#include "Resources/IOP/IOPCore/Types/IOPCoreCOP0_t.h"
#include "Resources/IOP/IOPCore/Types/IOPCoreCOP0Registers_t.h"

IOPIntc_s::IOPIntc_s(VM * vmMain) : 
	VMSystem_s(vmMain)
{
	mIOPCOP0 = getVM()->getResources()->IOP->IOPCore->COP0;
	mINTC = getVM()->getResources()->IOP->INTC;
}

IOPIntc_s::~IOPIntc_s()
{
}

void IOPIntc_s::run(const double& time)
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

int IOPIntc_s::step(const ClockEvent_t& event)
{
	// Check the master CTRL register and STAT register.
	bool interrupt = false;
	if (mINTC->CTRL->readWord(RAW) > 0)
	{
		if (mINTC->STAT->readWord(RAW) & mINTC->MASK->readWord(RAW))
			interrupt = true;
	}

	// Set IRQ line 2 on IOP Core if an interrupt occured.
	if (interrupt)
		mIOPCOP0->Cause->setIRQLine(2);
	else
		mIOPCOP0->Cause->clearIRQLine(2);

	// INTC has completed 1 cycle.
	return 1;
}
