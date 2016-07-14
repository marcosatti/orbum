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

	/*
	The instruction holder, used as a temporary holder for the current instruction.
	This is used in the interpreter whilst looking up the instruction to determine what operation to perform.
	Convenience funcions are also defined as part of the Instruction object to access differnt parts of the opcode, but you will need to cast the Instruction_t to one of the sub-classes (I, J, R).
	This is done in the instruction lookup table.
	*/
	Instruction_t instruction;

	void emulationLoop();
};

