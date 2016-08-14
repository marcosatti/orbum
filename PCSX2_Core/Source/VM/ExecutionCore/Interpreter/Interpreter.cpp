#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/Interpreter.h"
#include "VM/Component Interfaces/VMExecutionCoreComponent.h"

Interpreter::Interpreter(const VMMain* const vmMain) : VMExecutionCoreComponent(vmMain)
{
	mInterpreterEECore = std::make_unique<InterpreterEECore>(vmMain);
}

void Interpreter::executionStep()
{
	// TODO: Implement.
	mInterpreterEECore->executionStep();
}

void Interpreter::initalise()
{
	// A PS2 reset is done according to the Reset signal/exception defined on page 95 of the EE Core Users Manual.
	// This means we can raise a Reset exception (to handle) and it will be equivilant to setting everything manually!
	// After this is done, call Run() to begin execution.
	
	mInterpreterEECore->getExceptionHandler()->handleException(PS2Exception_t(PS2Exception_t::ExceptionType::EX_RESET));
}
