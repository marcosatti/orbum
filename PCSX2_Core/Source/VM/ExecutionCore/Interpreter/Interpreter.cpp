#include "stdafx.h"

#include "VM/ExecutionCore/Interpreter/Interpreter.h"
#include "VM/Component Interfaces/VMExecutionCoreComponent.h"

Interpreter::Interpreter(const VMMain* const vmMain) : VMExecutionCoreComponent(vmMain)
{
	mInterpreterR5900 = std::make_unique<InterpreterR5900>(vmMain, this);
}

void Interpreter::executionLoop() const
{
	// TODO: Implement.
	mInterpreterR5900->runInterpreterComponent();
}
