#pragma once

#include "VM/Component Interfaces/VMExecutionCoreComponent.h"

/*
TODO: Fill in documentation.
*/

class VMMain;

class Interpreter : public VMExecutionCoreComponent
{
public:
	explicit Interpreter(const VMMain *const vmMain);

	void emulationLoop();
};

