#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VM.h"
#include "VM/Systems/EE/INTC/EEIntc_s.h"

#include "Resources/Resources_t.h"
#include "Resources/EE/EE_t.h"
#include "Resources/EE/INTC/EEIntc_t.h"
#include "Resources/EE/INTC/Types/EEIntcRegisters_t.h"
#include "Resources/EE/EECore/EECore_t.h"
#include "Resources/EE/EECore/Types/EECoreCOP0_t.h"
#include "Resources/EE/EECore/Types/EECoreCOP0Registers_t.h"

EEIntc_s::EEIntc_s(VM * vmMain) :
	VMSystem_s(vmMain)
{
	mEECOP0 = getVM()->getResources()->EE->EECore->COP0;
	mINTC = getVM()->getResources()->EE->INTC;
}

EEIntc_s::~EEIntc_s()
{
}

void EEIntc_s::run(const double& time)
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

int EEIntc_s::step(const ClockEvent_t& event)
{
	// Check the interrupt status on the stat register.
	if (mINTC->STAT->readWord(RAW) & mINTC->MASK->readWord(RAW))
		mEECOP0->Cause->setIRQLine(3);
	else
		mEECOP0->Cause->clearIRQLine(3);
	
	// INTC has completed 1 cycle.
	return 1;
}
