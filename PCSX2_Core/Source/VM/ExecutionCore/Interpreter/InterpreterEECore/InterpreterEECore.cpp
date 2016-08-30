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
	mMMUHandler(std::make_unique<MMUHandler>(vmMain)),
	mTimerHandler(std::make_unique<TimerHandler>(vmMain))
{
}

InterpreterEECore::~InterpreterEECore()
{
}

void InterpreterEECore::executionStep()
{
	// Check for any timer events.
	getTimerHandler()->checkTimerEvents();

	// Check the exception queue to see if any are queued up - handle them first before executing an instruction (since the PC will change). 
	getExceptionHandler()->checkExceptionQueue();
		
	// Check if in a branch delay slot - function will set the PC automatically to the correct location.
	checkBranchDelaySlot();

	// Perform instruction related activities (such as execute instruction, increment PC and update timers).
	executeInstruction();

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

const std::unique_ptr<TimerHandler>& InterpreterEECore::getTimerHandler() const
{
	return mTimerHandler;
}

MIPSInstruction_t & InterpreterEECore::getInstruction()
{
	return mInstruction;
}

void InterpreterEECore::checkBranchDelaySlot() const
{
	// TODO: Logic subject to change. May not work once everything is in place. Also it may warrant its own sub-component, but it is quite small, so I have kept it wihtin the InterpreterEECore class for now.
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

void InterpreterEECore::executeInstruction()
{
	// Set the instruction holder to the instruction at the current PC.
	auto& EECore = getVM()->getResources()->EE->EECore;
	const u32 & instructionValue = getMMUHandler()->readWordU(EECore->R5900->PC->getPCValue()); // TODO: Add error checking.
	getInstruction().setInstructionValue(instructionValue);

	// Get the instruction details
	mInstructionInfo = &EECoreInstructionUtil::getInstructionInfo(mInstruction);

#if defined(BUILD_DEBUG)
	// Debug print details.
	char message[1000];
	sprintf_s(message, "EECore loop %llu: "
		"CPU Cycles = %lu, "
		"PC = 0x%08X, "
		"BD = %d, "
		"Instruction = %s",
		DEBUG_LOOP_COUNTER, EECore->COP0->Count->getFieldValue(RegisterCount_t::Fields::Count), EECore->R5900->PC->getPCValue(), EECore->R5900->mIsInBranchDelay, (instructionValue == 0) ? "SLL (NOP)" : mInstructionInfo->mMnemonic);
	logDebug(message);

	// Breakpoint.
	if (DEBUG_LOOP_COUNTER == 10000)
		logDebug("Breakpoint hit.");
#endif

	// Run the instruction, which is based on the implementation index.
	(this->*EECORE_INSTRUCTION_TABLE[mInstructionInfo->mImplementationIndex])();

	// Update the COP0.Count register, which is meant to be incremented every CPU clock cycle (do it every instruction instead). See EE Core Users Manual page 70.
	getTimerHandler()->incrementCountTimer(mInstructionInfo->mCycles);

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
