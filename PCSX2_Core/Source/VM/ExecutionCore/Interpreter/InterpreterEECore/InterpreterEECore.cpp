#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/ExecutionCore/Interpreter/InterpreterEECore/InterpreterEECore.h"
#include "VM/VMMain.h"
#include "Common/Util/EECoreInstructionUtil/EECoreInstructionUtil.h"

using R5900InstructionInfo_t = EECoreInstructionUtil::EECoreInstructionInfo_t;

InterpreterEECore::InterpreterEECore(const VMMain* const vmMain) :
	VMExecutionCoreComponent(vmMain)
{
}

InterpreterEECore::~InterpreterEECore()
{
}

void InterpreterEECore::executionStep()
{
	try
	{
		// Set the instruction holder to the instruction at the current PC.
		const u32 & PC = getVM()->getResources()->EE->EECore->R5900->PC->getPCValue();
		const u32 & instructionValue = getMMUHandler()->readWordU(PC);
		mInstruction.setInstruction(instructionValue);

		// Get the instruction details
		R5900InstructionInfo_t instructionInfo = EECoreInstructionUtil::getInstructionInfo(mInstruction);

		// Run the instruction, which is based on the implementation index.
		EECORE_INSTRUCTION_TABLE[instructionInfo.mImplementationIndex];
	}
	catch (const PS2Exception_t& PS2Exception)
	{
		mExceptionHandler->handleException(PS2Exception);
	}
}

const std::unique_ptr<ExceptionHandler> & InterpreterEECore::getExceptionHandler() const
{
	return mExceptionHandler;
}

const std::unique_ptr<MMUHandler>& InterpreterEECore::getMMUHandler() const
{
	return mMMUHandler;
}

const MIPSInstruction_t & InterpreterEECore::getInstruction() const
{
	return mInstruction;
}

// Begin EECore Instruction Implementation

void InterpreterEECore::INSTRUCTION_UNKNOWN()
{
	// Unknown opcode, log if debug is enabled and increment PC by 4 regardless.
#if defined(BUILD_DEBUG)
	logDebug("Unknown R5900 opcode encountered!");
#endif

	// Set PC to next instruction.
	getVM()->getResources()->EE->EECore->R5900->PC->setPCValueNext();
}