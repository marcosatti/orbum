#pragma once

#include "Globals.h"

#include "Instruction_t.h"
#include "VMExecutionCoreComponent.h"

/*
TODO: Fill in documentation.
*/

class VMMain;

class Interpreter : public VMExecutionCoreComponent
{
public:
	explicit Interpreter(const VMMain *const _mainVM);

	void emulationLoop();
};

