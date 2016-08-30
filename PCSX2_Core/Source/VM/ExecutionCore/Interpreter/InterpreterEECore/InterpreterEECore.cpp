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
	// Check the exception queue to see if any are queued up - handle them first. 
	// TODO: Not sure if we need to handle them all in one go, or only 1 per step cycle, or on jump-type instructions ala PCSX2. Currently all in one go.
	checkExceptionQueue();
		
	// Check if in a branch delay slot - function will set the PC automatically to the correct location.
	checkBranchDelaySlot();

	// Set the instruction holder to the instruction at the current PC.
	auto& PC = getVM()->getResources()->EE->EECore->R5900->PC;
	const u32 & rawInstruction = getMMUHandler()->readWordU(PC->getPCValue()); // TODO: Add error checking.
	mInstruction.setInstruction(rawInstruction);

	// Get the instruction details
	mInstructionInfo = &EECoreInstructionUtil::getInstructionInfo(mInstruction);

#if defined(BUILD_DEBUG)
	// Debug print loop counter and mnemonic.
	char message[1000];
	sprintf_s(message, "InterpreterEECore loop %llu: "
					   "PC = 0x%08X, "
					   "BD = %d, "
					   "Instruction = %s",
					   DEBUG_LOOP_COUNTER, PC->getPCValue(), getVM()->getResources()->EE->EECore->R5900->mIsInBranchDelay, (rawInstruction == 0) ? "SLL (NOP)" : mInstructionInfo->mMnemonic);
	logDebug(message);

	// Breakpoint.
	if (DEBUG_LOOP_COUNTER == 10000)
		logDebug("Breakpoint hit.");
#endif

	// Run the instruction, which is based on the implementation index.
	(this->*EECORE_INSTRUCTION_TABLE[mInstructionInfo->mImplementationIndex])();

	// Increment PC.
	getVM()->getResources()->EE->EECore->R5900->PC->setPCValueNext();

#if defined(BUILD_DEBUG)
	// Debug increment loop counter.
	DEBUG_LOOP_COUNTER++;
#endif
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

void InterpreterEECore::checkExceptionQueue() const
{
	auto& ExceptionQueue = getVM()->getResources()->EE->EECore->Exceptions->ExceptionQueue;
	while (!ExceptionQueue->empty())
	{
		mExceptionHandler->handleException(ExceptionQueue->front());
		ExceptionQueue->pop();
	}
}

void InterpreterEECore::checkBranchDelaySlot() const
{
	// TODO: Logic subject to change. May not work once everything is in place.
	auto& R5900 = getVM()->getResources()->EE->EECore->R5900;
	if (R5900->mIsInBranchDelay)
	{
		if (R5900->mBranchDelayCycles == 0)
		{
			R5900->PC->setPCValueAbsolute(R5900->mBranchDelayPCTarget);
			R5900->mIsInBranchDelay = false;
		}
		else
			R5900->mBranchDelayCycles--;
	}
}

// Begin EECore Instruction Implementation

void InterpreterEECore::INSTRUCTION_UNKNOWN()
{
	// Unknown opcode, log if debug is enabled.
#if defined(BUILD_DEBUG)
	logDebug("Unknown R5900 opcode encountered!");
#endif
}
