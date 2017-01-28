#pragma once

#include <vector>

#include "Common/Global/Globals.h"

#include "Common/Interfaces/VMBaseComponent.h"

/*
Inherited by the Interpreter and Recompiler execution cores.
Allows them to be initalised and defines the executionStep() function used in a while(1) loop or equivilant.
*/

class VMMain;

class VMExecutionCore : public VMBaseComponent
{
public:
	explicit VMExecutionCore(VMMain * vmMain);
	virtual ~VMExecutionCore();

	/*
	Function to initalise the execution core and PS2 state - for example, call the EE Core exception handler with type EX_RESET.
	*/
	virtual void initalise() = 0;

	virtual void execute() = 0;

};

