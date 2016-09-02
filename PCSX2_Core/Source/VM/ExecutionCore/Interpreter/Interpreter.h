#pragma once

#include <memory>

#include "Common/Interfaces/VMExecutionCoreComponent.h"


/*
TODO: Fill in documentation.
*/

class VMMain;
class InterpreterEECore;

class Interpreter : public VMExecutionCoreComponent
{
public:
	explicit Interpreter(const VMMain *const vmMain);

	void executionStep() override;

	void initalise() override;

private:
	std::unique_ptr<InterpreterEECore> mInterpreterEECore;
};

