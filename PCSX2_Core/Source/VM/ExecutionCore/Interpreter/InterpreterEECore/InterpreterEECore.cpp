#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/ExecutionCore/Interpreter/InterpreterEECore/InterpreterEECore.h"
#include "VM/VMMain.h"
#include "Common/Util/EECoreInstructionUtil/EECoreInstructionUtil.h"

using EECoreInstructionInfo_t = EECoreInstructionUtil::EECoreInstructionInfo_t;

InterpreterEECore::InterpreterEECore(const VMMain* const vmMain) :
	VMExecutionCoreComponent(vmMain), 
	mInstructionInfo(nullptr),
	mExceptionHandler(std::make_unique<ExceptionHandler>(vmMain)),
	mMMUHandler(std::make_unique<MMUHandler>(vmMain))
{
}

InterpreterEECore::~InterpreterEECore()
{
}

void InterpreterEECore::executionStep()
{
	try
	{
		// Pre instruction execution processing.
		executionStep_Pre();

		// Set the instruction holder to the instruction at the current PC.
		auto& PC = getVM()->getResources()->EE->EECore->R5900->PC;
		const u32 & rawInstruction = getMMUHandler()->readWordU(PC->getPCValue());
		mInstruction.setInstruction(rawInstruction);

		// Get the instruction details
		mInstructionInfo = &EECoreInstructionUtil::getInstructionInfo(mInstruction);

		// Run the instruction, which is based on the implementation index.
		(this->*EECORE_INSTRUCTION_TABLE[mInstructionInfo->mImplementationIndex])();

		// Post instruction execution processing.
		executionStep_Post();
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


void InterpreterEECore::executionStep_Pre() const
{
	// Check if in a branch delay slot - function will set the PC automatically to the correct location.
	getVM()->getResources()->EE->EECore->R5900->checkBranchDelaySlot();
}

void InterpreterEECore::executionStep_Post() const
{
	// Increment PC.
	getVM()->getResources()->EE->EECore->R5900->PC->setPCValueNext();
}

// Begin EECore Instruction Implementation

void InterpreterEECore::INSTRUCTION_UNKNOWN()
{
	// Unknown opcode, log if debug is enabled.
#if defined(BUILD_DEBUG)
	logDebug("Unknown R5900 opcode encountered!");
#endif
}
