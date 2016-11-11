#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/Interpreter.h"
#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreInterpreter.h"
#include "VM/ExecutionCore/Common/EE/DMAC/EEDmac.h"
#include "VM/ExecutionCore/Common/EE/INTC/EEIntc.h"
#include "VM/ExecutionCore/Common/EE/Timers/EETimers.h"
#include "VM/ExecutionCore/Interpreter/IOP/IOPCoreInterpreter/IOPCoreInterpreter.h"
#include "Common/Interfaces/VMExecutionCoreComponent.h"

Interpreter::Interpreter(VMMain * vmMain) :
	VMExecutionCoreComponent(vmMain),
	mClockSources{ ClockSource_t::VM },
	mEECoreInterpreter(std::make_shared<EECoreInterpreter>(vmMain)),
	mEEDmac(std::make_shared<EEDmac>(vmMain)),
	mEEIntc(std::make_shared<EEIntc>(vmMain)),
	mEETimers(std::make_shared<EETimers>(vmMain)),
	mIOPCoreInterpreter(std::make_shared<IOPCoreInterpreter>(vmMain)),
	mComponents { mEEDmac, mEEIntc, mEETimers, mIOPCoreInterpreter }
{
}

const std::vector<ClockSource_t>& Interpreter::getClockSources()
{
	return mClockSources;
}

s64 Interpreter::executionStep(const ClockSource_t & clockSource)
{
	// Process base EE Core event (in which every other component timing is based off).
	s64 PS2CLKTicks = mEECoreInterpreter->executionStep(ClockSource_t::PS2CLK);

	// Process the other components.
	for (auto& component : mComponents)
	{
		component->produceTicks(PS2CLKTicks);

		for (auto& componentClockSource : component->getClockSources())
		{
			while (component->isTicked(componentClockSource))
			{
				s64 componentClockSourceTicks = component->executionStep(componentClockSource);
				component->consumeTicks(componentClockSource, componentClockSourceTicks);
			}
		}
	}

	// Returns 1 "VM" cycle, although this is not actually used.
	return 1;
}

void Interpreter::initalise()
{
	// Always done as its not apart of the mComponents array.
	mEECoreInterpreter->initalise();

	// Iterate through the other components.
	for (auto& component : mComponents)
		component->initalise();
}
