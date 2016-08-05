#pragma once


#include "VM/Component Interfaces/VMInterpreterComponent.h"
#include "Common/PS2 Types/MIPSInstruction/MIPSInstruction_t.h"

class PS2Resources_t;
class VMMain;
class InterpreterR5900 : public VMInterpreterComponent
{
public:
	InterpreterR5900(const VMMain *const vmMain, const Interpreter *const interpreter);
	~InterpreterR5900();

	/*
	This is the "main loop" function called by the base interpreter component.
	*/
	void runInterpreterComponent() override;

private:

	// Component state functions

	/*
	The is used as a temporary holder for the current instruction, while the operation to perform is being determined.
	*/
	MIPSInstruction_t mInstruction;

	// Static R5900 Instruction functions.

	/*
	Instruction Table. This table provides pointers to instruction implementations, which is accessed by the implementation index. See R5900InstructionUtil for more details.
	*/
	static void(*const R5900_INSTRUCTION_TABLE[Constants::NUMBER_R5900_INSTRUCTIONS])(PS2Resources_t & PS2Resources);

	/*
	Unknown instruction function - does nothing when executed. Used for any instructions with implementation index 0 (ie: reserved, unknown or otherwise).
	If the PCSX2_DEBUG macro is enabled, can be used to debug an unknown opcode by logging a message.
	Will increase PC by 4 regardless.
	*/
	static void INSTRUCTION_UNKNOWN(PS2Resources_t & PS2Resources);
};

