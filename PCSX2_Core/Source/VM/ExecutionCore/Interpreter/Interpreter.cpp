#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/Interpreter.h"
#include "VM/ExecutionCore/Interpreter/EE/EECore/EECoreInterpreter/EECoreInterpreter.h"
#include "VM/ExecutionCore/Interpreter/EE/DMACInterpreter/DMACInterpreter.h"
#include "VM/ExecutionCore/Interpreter/EE/INTCHandler/INTCHandler.h"
#include "VM/ExecutionCore/Interpreter/EE/TimersHandler/TimersHandler.h"
#include "VM/ExecutionCore/Interpreter/IOP/IOPCore/IOPCoreInterpreter/IOPCoreInterpreter.h"
#include "Common/Interfaces/VMExecutionCoreComponent.h"

Interpreter::Interpreter(VMMain * vmMain) :
	VMExecutionCoreComponent(vmMain),
	mClockSources{ ClockSource_t::VM },
	mEECoreInterpreter(std::make_shared<EECoreInterpreter>(vmMain)),
	mDMACInterpreter(std::make_shared<DMACInterpreter>(vmMain)),
	mINTCHandler(std::make_shared<INTCHandler>(vmMain)),
	mTimerHandler(std::make_shared<TimersHandler>(vmMain)),
	mIOPInterpreter(std::make_shared<IOPCoreInterpreter>(vmMain)),
	mComponents { mDMACInterpreter, mINTCHandler, mTimerHandler, mIOPInterpreter }
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
