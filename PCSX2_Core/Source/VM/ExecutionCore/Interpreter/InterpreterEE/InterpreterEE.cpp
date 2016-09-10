#include "stdafx.h"

#include "VM/ExecutionCore/Interpreter/InterpreterEE/InterpreterEE.h"
#include "VM/ExecutionCore/Interpreter/InterpreterEE/INTCHandler/INTCHandler.h"

InterpreterEE::InterpreterEE(const VMMain* const vmMain) : 
	VMExecutionCoreComponent(vmMain),
	mINTCHandler(std::make_unique<INTCHandler>(vmMain))
{
}

void InterpreterEE::executionStep()
{
	mINTCHandler->checkInterrupt();
}

void InterpreterEE::initalise()
{
}
