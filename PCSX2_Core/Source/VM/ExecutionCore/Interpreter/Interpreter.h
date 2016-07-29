#pragma once

#include <memory>

#include "VM/Component Interfaces/VMExecutionCoreComponent.h"
#include "VM/ExecutionCore/Interpreter/InterpreterR5900/InterpreterR5900.h"


/*
TODO: Fill in documentation.
*/

class VMMain;

class Interpreter : public VMExecutionCoreComponent
{
public:
	explicit Interpreter(const VMMain *const vmMain);

	void executionLoop() const override;

private:
	std::unique_ptr<InterpreterR5900> mInterpreterR5900;
};

