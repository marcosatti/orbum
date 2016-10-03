#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/Interpreter.h"
#include "VM/ExecutionCore/Interpreter/EE/EECore/EECoreInterpreter/EECoreInterpreter.h"
#include "VM/ExecutionCore/Interpreter/EE/DMACInterpreter/InterpreterDMAC.h"
#include "VM/ExecutionCore/Interpreter/EE/INTCHandler/INTCHandler.h"
#include "VM/ExecutionCore/Interpreter/EE/TimerHandler/TimerHandler.h"
#include "Common/Interfaces/VMExecutionCoreComponent.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/Clock/Clock_t.h"

Interpreter::Interpreter(VMMain * vmMain) :
	VMExecutionCoreComponent(vmMain),
	mEECoreInterpreter(std::make_unique<EECoreInterpreter>(vmMain)),
	mDMACInterpreter(std::make_unique<InterpreterDMAC>(vmMain)),
	mINTCHandler(std::make_unique<INTCHandler>(vmMain)),
	mTimerHandler(std::make_unique<TimerHandler>(vmMain))
{
}

void Interpreter::executionStep()
{
	auto& Clock = getVM()->getResources()->Clock;

	// Process base EE Core event (which controls the timing for components below, by updating the Clock class).
	mEECoreInterpreter->executionStep();
	
	// Process any PS2CLK components.
	// TODO: No components so far. Put VU's here?

	// Process any BUSCLK components.
	while (Clock->isTickedBUSCLK())
	{
		mINTCHandler->executionStep();
		mTimerHandler->executionStep_BUSCLK();
		mDMACInterpreter->executionStep();
	}

	// Process any BUSCLK16 components.
	while (Clock->isTickedBUSCLK16())
	{
		mTimerHandler->executionStep_BUSCLK16();
	}

	// Process any BUSCLK256 components.
	while (Clock->isTickedBUSCLK16())
	{
		mTimerHandler->executionStep_BUSCLK16();
	}

	// Process any HBLNK components.
	while (Clock->isTickedHBLNK())
	{
		// TODO: Put GS here? Shouldn't run for now as the GS hasn't been implemented (which sets Clock_t::RATIO_PS2CLK_HBLNK).
		mTimerHandler->executionStep_HBLNK();
	}
}

void Interpreter::initalise()
{
	mEECoreInterpreter->initalise();
}
