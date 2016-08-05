#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/ExecutionCore/Interpreter/InterpreterR5900/InterpreterR5900.h"
#include "VM/VMMain.h"
#include "Common/PS2 Types/R5900InstructionUtil/R5900InstructionUtil.h"

using R5900InstructionInfo_t = R5900InstructionUtil::R5900InstructionInfo_t;

InterpreterR5900::InterpreterR5900(const VMMain* const vmMain, const Interpreter* const interpreter) :
	VMInterpreterComponent(vmMain, interpreter)
{
}

InterpreterR5900::~InterpreterR5900()
{
}

void InterpreterR5900::runInterpreterComponent()
{
	// Set the instruction holder to the instruction at the current PC.
	// TODO: FIX! Not correct to use the PC value as a PS2 physical address - it is PS2 VIRTUAL! Need to use the PS2MMUHandler to get the correct PS2 physical address.
	const u32 & PC = getVM()->getResources()->EE.EECore.R5900.getPCValue();
	const u32 & instructionValue = getVM()->getMMU()->readWordU(PC);
	mInstruction.setInstruction(instructionValue);

	// Get the instruction details
	R5900InstructionInfo_t instructionInfo = R5900InstructionUtil::getInstructionInfo(mInstruction);

}

// Begin Static R5900 Instruction Implementation

void (*const InterpreterR5900::R5900_INSTRUCTION_TABLE[Constants::NUMBER_R5900_INSTRUCTIONS])(const MIPSInstruction_t & instruction, PS2Resources_t & PS2Resources) = {
	INSTRUCTION_UNKNOWN
};

void InterpreterR5900::INSTRUCTION_UNKNOWN(const MIPSInstruction_t & instruction, PS2Resources_t & PS2Resources)
{
	// Unknown opcode, log if debug is enabled and increment PC by 4 regardless.
#if defined(BUILD_DEBUG)
	logDebug("Unknown R5900 opcode encountered!");
#endif

	// Set PC to next instruction.
	PS2Resources.EE.EECore.R5900.setPCValueNext();
}