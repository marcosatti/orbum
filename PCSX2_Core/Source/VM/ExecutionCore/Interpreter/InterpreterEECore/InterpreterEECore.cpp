#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/ExecutionCore/Interpreter/InterpreterEECore/InterpreterEECore.h"
#include "VM/VMMain.h"
#include "Common/Util/EECoreInstructionUtil/EECoreInstructionUtil.h"

using R5900InstructionInfo_t = EECoreInstructionUtil::EECoreInstructionInfo_t;

InterpreterEECore::InterpreterEECore(const VMMain* const vmMain, const Interpreter* const interpreter) :
	VMInterpreterComponent(vmMain, interpreter)
{
}

InterpreterEECore::~InterpreterEECore()
{
}

void InterpreterEECore::runInterpreterComponent()
{
	// Set the instruction holder to the instruction at the current PC.
	// TODO: FIX! Not correct to use the PC value as a PS2 physical address - it is PS2 VIRTUAL! Need to use the PS2MMUHandler to get the correct PS2 physical address.
	const u32 & PC = getVM()->getResources()->EE->EECore->R5900->PC->getPCValue();
	const u32 & instructionValue = getVM()->getMMU()->readWordU(PC);
	mInstruction.setInstruction(instructionValue);

	// Get the instruction details
	R5900InstructionInfo_t instructionInfo = EECoreInstructionUtil::getInstructionInfo(mInstruction);

}

// Begin Static R5900 Instruction Implementation

void (*const InterpreterEECore::R5900_INSTRUCTION_TABLE[Constants::NUMBER_R5900_INSTRUCTIONS])(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources) = {
	INSTRUCTION_UNKNOWN
};

void InterpreterEECore::INSTRUCTION_UNKNOWN(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Unknown opcode, log if debug is enabled and increment PC by 4 regardless.
#if defined(BUILD_DEBUG)
	logDebug("Unknown R5900 opcode encountered!");
#endif

	// Set PC to next instruction.
	PS2Resources->EE->EECore->R5900->PC->setPCValueNext();
}