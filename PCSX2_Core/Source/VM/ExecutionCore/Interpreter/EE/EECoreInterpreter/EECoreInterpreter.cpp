#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreInterpreter.h"
#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreMMUHandler/EECoreMMUHandler.h"
#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreExceptionHandler/EECoreExceptionHandler.h"
#include "VM/ExecutionCore/Interpreter/EE/VPU/VUInterpreter/VUInterpreter.h"
#include "Common/Types/MIPSInstructionInfo/MIPSInstructionInfo_t.h"
#include "Common/Types/MIPSInstruction/MIPSInstruction_t.h"
#include "Common/Types/Registers/PCRegister32_t.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreExceptions_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreException_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0Registers_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreFPU_t.h"
#include "PS2Resources/EE/VPU/VPU_t.h"
#include "PS2Resources/EE/VPU/VU/VU_t.h"
#include "PS2Resources/EE/VPU/VU/Types/VuUnits_t.h"
#include "Common/Types/MIPSCoprocessor/COP0Registers_t.h"
#include "Common/Tables/EECoreInstructionTable/EECoreInstructionTable.h"
#include "Common/Util/MathUtil/MathUtil.h"

using ExType = EECoreException_t::ExType;

EECoreInterpreter::EECoreInterpreter(VMMain * vmMain, const std::shared_ptr<VUInterpreter> & vuInterpreter) :
	VMExecutionCoreComponent(vmMain),
	mExceptionHandler(std::make_unique<EECoreExceptionHandler>(vmMain)),
	mMMUHandler(std::make_unique<EECoreMMUHandler>(vmMain)),
	mInstructionInfo(nullptr),
	mVU0Interpreter(vuInterpreter)
{
}

EECoreInterpreter::~EECoreInterpreter()
{
}

void EECoreInterpreter::initalise()
{
	// A PS2 reset is done according to the Reset signal/exception defined on page 95 of the EE Core Users Manual.
	// This means we can raise a Reset exception (to handle) and it will be equivilant to setting everything manually!
	// After this is done, call VMMMain::Run() to begin execution.

	mExceptionHandler->handleException(EECoreException_t(ExType::EX_RESET));
}

s64 EECoreInterpreter::executionStep(const ClockSource_t & clockSource)
{
	// Check for any COP0.Count events.
	checkCountTimerEvent();

	// Check the exception queue to see if any are queued up - handle them first before executing an instruction (since the PC will change). 
	mExceptionHandler->checkExceptionState();
		
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

void EECoreInterpreter::checkBranchDelaySlot() const
{
	auto& R5900 = getResources()->EE->EECore->R5900;
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
	auto& EECore = getResources()->EE->EECore;

	// Check the COP0.Count register against the COP0.Compare register. See EE Core Users Manual page 72 for details.
	// The docs specify that an interrupt is raised when the two values are equal, but this is impossible to get correct (due to how emulation works), 
	//  so it is based on greater than or equal.
	// TODO: check for errors.
	if (EECore->COP0->Count->readWord() >= EECore->COP0->Compare->readWord())
	{
		// Set the IP7 field of the COP0.Cause register.
		EECore->COP0->Cause->setFieldValue(EECoreCOP0Register_Cause_t::Fields::IP7, 1);

		// Set exception state.
		IntExceptionInfo_t intEx = { 0, 0, 1 };
		EECore->Exceptions->setException(EECoreException_t(ExType::EX_INTERRUPT, nullptr, &intEx, nullptr));
	}
}

u32 EECoreInterpreter::executeInstruction()
{
	auto& EECore = getResources()->EE->EECore;

	// Set the instruction holder to the instruction at the current PC.
	const u32 instructionValue = mMMUHandler->readWord(EECore->R5900->PC->readWord()); // TODO: Add error checking for address bus error.
	mInstruction.setInstructionValue(instructionValue);

	// Get the instruction details
	mInstructionInfo = EECoreInstructionTable::getInstructionInfo(mInstruction);

#if 0 //defined(BUILD_DEBUG)
	static u64 DEBUG_LOOP_BREAKPOINT = 0x1445b25;
	static u32 DEBUG_PC_BREAKPOINT = 0x80006c18;
	if (DEBUG_LOOP_COUNTER >= DEBUG_LOOP_BREAKPOINT)
	{
		// Debug print details.
		logDebug("EECore cycle = 0x%llX: "
			"PC = 0x%08X, BD = %d, "
			"Instruction = %s",
			DEBUG_LOOP_COUNTER,
			EECore->R5900->PC->readWordU(), EECore->R5900->mIsInBranchDelay, 
			(instructionValue == 0) ? "SLL (NOP)" : mInstructionInfo->mMnemonic);
	
	}

	// Breakpoint.
	if (EECore->R5900->PC->readWordU() == DEBUG_PC_BREAKPOINT)
	{
		logDebug("EECore Breakpoint hit @ cycle = 0x%llX.", DEBUG_LOOP_COUNTER);
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

bool EECoreInterpreter::checkCOP0Usable() const
{
	if (!getResources()->EE->EECore->COP0->isCoprocessorUsable())
	{
		// Coprocessor was not usable. Raise an exception.
		auto& Exceptions = getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return false;
	}

	// Coprocessor is usable, proceed.
	return true;
}

bool EECoreInterpreter::checkCOP1Usable() const
{
	if (!getResources()->EE->EECore->FPU->isCoprocessorUsable())
	{
		// Coprocessor was not usable. Raise an exception.
		auto& Exceptions = getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 1 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return false;
	}

	// Coprocessor is usable, proceed.
	return true;
}

bool EECoreInterpreter::checkCOP2Usable() const
{
	if (!getResources()->EE->VPU->VU->VU0->isCoprocessorUsable())
	{
		// Coprocessor was not usable. Raise an exception.
		auto& Exceptions = getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return false;
	}

	// Coprocessor is usable, proceed.
	return true;
}

bool EECoreInterpreter::checkNoMMUError() const
{
	if (mMMUHandler->hasExceptionOccurred())
	{
		// Something went wrong in the MMU.
		auto& Exceptions = getResources()->EE->EECore->Exceptions;
		Exceptions->setException(mMMUHandler->getExceptionInfo());
		return false;
	}

	// MMU was ok.
	return true;
}

bool EECoreInterpreter::checkNoOverOrUnderflow32(const s32& x, const s32& y) const
{
	if (MathUtil::testOverOrUnderflow32(x, y))
	{
		// Over/Under flow occured.
		auto& Exceptions = getResources()->EE->EECore->Exceptions;
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_OVERFLOW));
		return false;
	}

	// No error occured.
	return true;
}

bool EECoreInterpreter::checkNoOverOrUnderflow64(const s64& x, const s64& y) const
{
	if (MathUtil::testOverOrUnderflow64(x, y))
	{
		// Over/Under flow occured.
		auto& Exceptions = getResources()->EE->EECore->Exceptions;
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_OVERFLOW));
		return false;
	}

	// No error occured.
	return true;
}

void EECoreInterpreter::INSTRUCTION_UNKNOWN()
{
	// Unknown instruction, log if debug is enabled.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R5900 instruction encountered! (Lookup: %s -> %s)",
		__FILENAME__, __LINE__, mInstructionInfo->mBaseClass, mInstructionInfo->mMnemonic);
#endif
}


