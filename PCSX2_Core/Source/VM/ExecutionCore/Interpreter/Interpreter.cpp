#include "stdafx.h"

#include "Common/Global/Globals.h"


#include "VM/ExecutionCore/Interpreter/Interpreter.h"
#include "VM/VMMain.h"

#include "VM/ExecutionCore/Interpreter/IOP/IOPCoreInterpreter/IOPCoreInterpreter.h"
#include "VM/ExecutionCore/Interpreter/EE/VPU/VUInterpreter/VUInterpreter.h"
#include "VM/ExecutionCore/Common/EE/VPU/VIF/VIF.h"
#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreInterpreter.h"
#include "VM/ExecutionCore/Common/EE/DMAC/EEDmac.h"
#include "VM/ExecutionCore/Common/EE/INTC/EEIntc.h"
#include "VM/ExecutionCore/Common/EE/Timers/EETimers.h"


Interpreter::Interpreter(VMMain * vmMain) :
	VMExecutionCore(vmMain),
	mInterpreterVU0(std::make_shared<VUInterpreter>(vmMain, 0)),
	mInterpreterVU1(std::make_shared<VUInterpreter>(vmMain, 1)),
	mVIF0(std::make_shared<VIF>(vmMain, 0)),
	mVIF1(std::make_shared<VIF>(vmMain, 1)),
	mEECoreInterpreter(std::make_shared<EECoreInterpreter>(vmMain, mInterpreterVU0)),
	mEEDmac(std::make_shared<EEDmac>(vmMain)),
	mEEIntc(std::make_shared<EEIntc>(vmMain)),
	mEETimers(std::make_shared<EETimers>(vmMain)),
	mIOPCoreInterpreter(std::make_shared<IOPCoreInterpreter>(vmMain)),
	mComponents{ mInterpreterVU0, mInterpreterVU1, mEECoreInterpreter, mEEDmac, mEEIntc, mEETimers, mIOPCoreInterpreter },
	mComponentsBUSCLK{ mInterpreterVU0, mInterpreterVU1, mEEDmac, mEEIntc, mEETimers },
	mComponentsBUSCLK16{ mEETimers },
	mComponentsBUSCLK256{ mEETimers },
	mComponentsHBLNK{ mEETimers },
	mComponentsIOP{ mIOPCoreInterpreter }
{
}

Interpreter::~Interpreter()
{
}

void Interpreter::initalise()
{
	// Iterate through all components, initalising them.
	for (auto& component : mComponents)
		component->initalise();
}

void Interpreter::executionStep()
{
	// Process base EE Core event (in which every other component timing is based off).
	const s64 PS2CLKTicks = mEECoreInterpreter->executionStep(ClockSource_t::PS2CLK);

	// Process BUSCLK components.
	for (auto& component : mComponentsBUSCLK)
	{
		component->produceTicks(ClockSource_t::BUSCLK, PS2CLKTicks);
		while (component->isTicked(ClockSource_t::BUSCLK))
		{
			s64 componentClockSourceTicks = component->executionStep(ClockSource_t::BUSCLK);
			component->consumeTicks(ClockSource_t::BUSCLK, componentClockSourceTicks);
		}
	}

	// Process BUSCLK16 components.
	for (auto& component : mComponentsBUSCLK16)
	{
		component->produceTicks(ClockSource_t::BUSCLK16, PS2CLKTicks);
		while (component->isTicked(ClockSource_t::BUSCLK16))
		{
			s64 componentClockSourceTicks = component->executionStep(ClockSource_t::BUSCLK16);
			component->consumeTicks(ClockSource_t::BUSCLK16, componentClockSourceTicks);
		}
	}

	// Process BUSCLK256 components.
	for (auto& component : mComponentsBUSCLK256)
	{
		component->produceTicks(ClockSource_t::BUSCLK256, PS2CLKTicks);
		while (component->isTicked(ClockSource_t::BUSCLK256))
		{
			s64 componentClockSourceTicks = component->executionStep(ClockSource_t::BUSCLK256);
			component->consumeTicks(ClockSource_t::BUSCLK256, componentClockSourceTicks);
		}
	}

	// Process HBLNK components.
	for (auto& component : mComponentsHBLNK)
	{
		component->produceTicks(ClockSource_t::HBLNK, PS2CLKTicks);
		while (component->isTicked(ClockSource_t::HBLNK))
		{
			s64 componentClockSourceTicks = component->executionStep(ClockSource_t::HBLNK);
			component->consumeTicks(ClockSource_t::HBLNK, componentClockSourceTicks);
		}
	}

	// Process IOP components.
	for (auto& component : mComponentsIOP)
	{
		component->produceTicks(ClockSource_t::IOP, PS2CLKTicks);
		while (component->isTicked(ClockSource_t::IOP))
		{
			s64 componentClockSourceTicks = component->executionStep(ClockSource_t::IOP);
			component->consumeTicks(ClockSource_t::IOP, componentClockSourceTicks);
		}
	}
}
