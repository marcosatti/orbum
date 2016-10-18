#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/EE/EECore/EECoreInterpreter/EECoreInterpreter.h"
#include "VM/ExecutionCore/Interpreter/EE/EECore/EECoreInterpreter/EECoreMMUHandler/EECoreMMUHandler.h"
#include "VM/ExecutionCore/Interpreter/EE/EECore/EECoreInterpreter/EECoreExceptionHandler/EECoreExceptionHandler.h"
#include "Common/PS2Resources/Types/MIPSInstructionInfo/MIPSInstructionInfo_t.h"
#include "Common/PS2Resources/Types/MIPSInstruction/MIPSInstruction_t.h"
#include "Common/PS2Resources/EE/EECore/EECoreExceptions/EECoreExceptions_t.h"
#include "Common/PS2Resources/EE/EECore/EECoreExceptions/Types/EECoreException_t.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/EE/EECore/EECore_t.h"
#include "Common/PS2Resources/EE/EECore/R5900/R5900_t.h"
#include "Common/PS2Resources/Types/Registers/PCRegister32_t.h"
#include "Common/PS2Resources/EE/EECore/EECoreCOP0/EECoreCOP0_t.h"
#include "Common/PS2Resources/Types/MIPSCoprocessor/COP0_BitfieldRegisters_t.h"
#include "Common/Tables/EECoreInstructionTable/EECoreInstructionTable.h"
#include "Common/PS2Resources/Clock/Clock_t.h"

using ExType = EECoreException_t::ExType;

EECoreInterpreter::EECoreInterpreter(VMMain * vmMain) :
	VMExecutionCoreComponent(vmMain),
	mClockSources{},
	mExceptionHandler(std::make_unique<EECoreExceptionHandler>(vmMain)),
	mMMUHandler(std::make_unique<EECoreMMUHandler>(vmMain)),
	mInstructionInfo(nullptr)
{
}

EECoreInterpreter::~EECoreInterpreter()
{
}

const std::vector<ClockSource_t>& EECoreInterpreter::getClockSources()
{
	return mClockSources;
}

void EECoreInterpreter::initalise()
{
	// A PS2 reset is done according to the Reset signal/exception defined on page 95 of the EE Core Users Manual.
	// This means we can raise a Reset exception (to handle) and it will be equivilant to setting everything manually!
	// After this is done, call VMMMain::Run() to begin execution.

	getExceptionHandler()->handleException(EECoreException_t(ExType::EX_RESET));
}

s64 EECoreInterpreter::executionStep(const ClockSource_t & clockSource)
{
	// Check for any COP0.Count events.
	checkCountTimerEvent();

	// Check the exception queue to see if any are queued up - handle them first before executing an instruction (since the PC will change). 
	getExceptionHandler()->checkExceptionState();
		
	// Check if in a branch delay slot - function will set the PC automatically to the correct location.
	checkBranchDelaySlot();

	// Perform instruction related activities (such as execute instruction, increment PC and update timers).
	u32 cycles = executeInstruction();

#if defined(BUILD_DEBUG)
	// Debug increment loop counter.
	DEBUG_LOOP_COUNTER++;
#endif

	return cycles;
}

const std::unique_ptr<EECoreExceptionHandler> & EECoreInterpreter::getExceptionHandler() const
{
	return mExceptionHandler;
}

const std::unique_ptr<EECoreMMUHandler>& EECoreInterpreter::getMMUHandler() const
{
	return mMMUHandler;
}

MIPSInstruction_t & EECoreInterpreter::getInstruction()
{
	return mInstruction;
}

void EECoreInterpreter::checkBranchDelaySlot() const
{
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

void EECoreInterpreter::checkCountTimerEvent() const
{
	auto& EECore = getVM()->getResources()->EE->EECore;

	// Check the COP0.Count register against the COP0.Compare register. See EE Core Users Manual page 72 for details.
	// The docs specify that an interrupt is raised when the two values are equal, but this is impossible to get correct (due to how emulation works), 
	//  so it is based on greater than or equal.
	// TODO: check for errors.
	if (EECore->COP0->Count->readWordU() >= EECore->COP0->Compare->readWordU())
	{
		// Set the IP7 field of the COP0.Cause register.
		EECore->COP0->Cause->setFieldValue(COP0RegisterCause_t::Fields::IP7, 1);

		// Set exception state.
		IntExceptionInfo_t intEx = { 0, 0, 1 };
		EECore->Exceptions->setException(EECoreException_t(ExType::EX_INTERRUPT, nullptr, &intEx, nullptr));
	}
}

u32 EECoreInterpreter::executeInstruction()
{
	auto& EECore = getVM()->getResources()->EE->EECore;

	// Set the instruction holder to the instruction at the current PC.
	const u32 & instructionValue = getMMUHandler()->readWordU(EECore->R5900->PC->getPCValue()); // TODO: Add error checking for address bus error.
	getInstruction().setInstructionValue(instructionValue);

	// Get the instruction details
	mInstructionInfo = EECoreInstructionTable::getInstructionInfo(mInstruction);

#if defined(BUILD_DEBUG)
	static u64 DEBUG_LOOP_BREAKPOINT = 0x838dc;
	static u32 DEBUG_PC_BREAKPOINT = 0x9fc43070;
	if (DEBUG_LOOP_COUNTER >= DEBUG_LOOP_BREAKPOINT)
	{
		// Debug print details.
		logDebug("(%s, %d) EECore loop 0x%llX: "
			"CPU Cycles = 0x%lX, "
			"PC = 0x%08X, "
			"BD = %d, "
			"Instruction = %s", __FILENAME__, __LINE__,
			DEBUG_LOOP_COUNTER, EECore->COP0->Count->getFieldValue(COP0RegisterCount_t::Fields::Count), 
			EECore->R5900->PC->getPCValue(), EECore->R5900->mIsInBranchDelay, 
			(instructionValue == 0) ? "SLL (NOP)" : mInstructionInfo->mMnemonic);
	
		// Breakpoint.
		if (EECore->R5900->PC->getPCValue() == DEBUG_PC_BREAKPOINT)
		{
			logDebug("(%s, %d) Breakpoint hit.", __FILENAME__, __LINE__);
			getVM()->setStatus(VMMain::VMStatus::STOPPED);
		}
	}
#endif

	// Run the instruction, which is based on the implementation index.
	(this->*EECORE_INSTRUCTION_TABLE[mInstructionInfo->mImplementationIndex])();

	// Update the COP0.Count register, which is meant to be incremented every CPU clock cycle (do it every instruction instead). See EE Core Users Manual page 70.
	EECore->COP0->Count->increment(mInstructionInfo->mCycles);
	
	// Increment PC.
	EECore->R5900->PC->setPCValueNext();

	// Return the number of cycles completed.
	return mInstructionInfo->mCycles;
}

// Begin EECore Instruction Implementation

void EECoreInterpreter::INSTRUCTION_UNKNOWN()
{
	// Unknown opcode, log if debug is enabled.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R5900 opcode encountered!", __FILENAME__, __LINE__);
#endif
}


