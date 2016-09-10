#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/Interpreter.h"
#include "VM/ExecutionCore/Interpreter/InterpreterEECore/InterpreterEECore.h"
#include "VM/ExecutionCore/Interpreter/InterpreterEE/InterpreterEE.h"
#include "Common/Interfaces/VMExecutionCoreComponent.h"

Interpreter::Interpreter(const VMMain* const vmMain) :
	VMExecutionCoreComponent(vmMain),
	mInterpreterEE(std::make_unique<InterpreterEE>(vmMain)),
	mInterpreterEECore(std::make_unique<InterpreterEECore>(vmMain))
{
}

void Interpreter::executionStep()
{
	// TODO: Implement.
	mInterpreterEE->executionStep();
	mInterpreterEECore->executionStep();
}

void Interpreter::initalise()
{
	mInterpreterEE->initalise();
	mInterpreterEECore->initalise();
}
