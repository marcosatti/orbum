#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Context_t.h"
#include "Common/Types/MIPSInstruction/MIPSInstruction_t.h"
#include "Common/Types/Registers/MIPS/PCRegister32_t.h"
#include "Common/Types/MIPSBranchDelay/MIPSBranchDelay_t.h"
#include "Common/Tables/EECoreInstructionTable/EECoreInstructionTable.h"
#include "Common/Util/MathUtil/MathUtil.h"

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreInterpreter.h"
#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreMMUHandler/EECoreMMUHandler.h"
#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreExceptionHandler/EECoreExceptionHandler.h"
#include "VM/ExecutionCore/Interpreter/EE/VPU/VUInterpreter/VUInterpreter.h"

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
	mExceptionHandler->handleException(EECoreException_t::EX_RESET);
}

s64 EECoreInterpreter::executionStep(const ClockSource_t & clockSource)
{
	auto& EECore = getResources()->EE->EECore;

	// Check if any external interrupts are pending and queue exception if there are.
	handleInterruptCheck();
	
	// Check the exception queue to see if any are queued up - handle them first before executing an instruction (since the PC will change). 
	if (EECore->Exceptions->hasExceptionOccurred())
		mExceptionHandler->handleException(EECore->Exceptions->getException());

	// Check if in a branch delay slot - function will set the PC automatically to the correct location.
	EECore->R5900->BD->handleBranchDelay();

	// Increment PC.
	EECore->R5900->PC->setPCValueNext();

	// Set the instruction holder to the instruction at the previous PC.
	const u32 pcValue = EECore->R5900->PC->readWord(Context_t::EE) - Constants::SIZE_MIPS_INSTRUCTION;;
	const u32 instructionValue = mMMUHandler->readWord(pcValue); // TODO: Add error checking for address bus error.
	mInstruction.setInstructionValue(instructionValue);

	// Get the instruction details
	mInstructionInfo = EECoreInstructionTable::getInstructionInfo(mInstruction);

#if defined(BUILD_DEBUG)
	static u64 DEBUG_LOOP_BREAKPOINT = 0x10000000fe4321;
	static u32 DEBUG_PC_BREAKPOINT = 0x0;
	if (DEBUG_LOOP_COUNTER >= DEBUG_LOOP_BREAKPOINT)
	{
		// Debug print details.
		logDebug("EECore cycle = 0x%llX: "
			"PC = 0x%08X, BD = %d, IntEn = %d, "
			"Instruction = %s",
			DEBUG_LOOP_COUNTER,
			pcValue, EECore->R5900->BD->isInBranchDelay(), !EECore->COP0->Status->isInterruptsMasked(),
			(instructionValue == 0) ? "SLL (NOP)" : mInstructionInfo->mMnemonic);
	}

	// Breakpoint.
	if (pcValue == DEBUG_PC_BREAKPOINT)
	{
		logDebug("EECore Breakpoint hit @ cycle = 0x%llX.", DEBUG_LOOP_COUNTER);
	}
#endif

	// Run the instruction, which is based on the implementation index.
	(this->*EECORE_INSTRUCTION_TABLE[mInstructionInfo->mImplementationIndex])();

	// Update the COP0.Count register, and check for interrupt. See EE Core Users Manual page 70.
	EECore->COP0->Count->increment(mInstructionInfo->mCycles);
	handleCountEventCheck();

#if defined(BUILD_DEBUG)
	// Debug increment loop counter.
	DEBUG_LOOP_COUNTER++;
#endif

	// Return the number of cycles completed.
	return mInstructionInfo->mCycles;
}

void EECoreInterpreter::handleInterruptCheck() const
{
	auto& COP0 = getResources()->EE->EECore->COP0;

	// Interrupt exceptions are only taken when conditions are correct.
	// Interrupt exception checking follows the process on page 74 of the EE Core Users Manual.
	if (!COP0->Status->isInterruptsMasked())
	{
		u32 ipCause = COP0->Cause->getFieldValue(EECoreCOP0Register_Cause_t::Fields::IP);
		u32 imStatus = COP0->Status->getFieldValue(EECoreCOP0Register_Status_t::Fields::IM);
		if (ipCause & imStatus)
		{
#if defined(BUILD_DEBUG)
			auto& IOPCore = getResources()->EE->EECore;
			logDebug("IOP interrupt exception occurred @ cycle = 0x%llX, PC = 0x%08X, BD = %d.",
				DEBUG_LOOP_COUNTER, IOPCore->R5900->PC->readWord(Context_t::IOP), IOPCore->R5900->BD->isInBranchDelay());
#endif
			auto& Exceptions = getResources()->EE->EECore->Exceptions;
			Exceptions->setException(EECoreException_t::EX_INTERRUPT);
		}
	}
}

void EECoreInterpreter::handleCountEventCheck() const
{
	auto& COP0 = getResources()->EE->EECore->COP0;

	// Check the COP0.Count register against the COP0.Compare register. See EE Core Users Manual page 72 for details.
	// The docs specify that an interrupt (IP[7]) is raised when the two values are equal.
	if (COP0->Count->readWord(Context_t::EE) == COP0->Compare->readWord(Context_t::EE))
		COP0->Cause->setIRQLine(7);
	else
		COP0->Cause->clearIRQLine(7);
}

bool EECoreInterpreter::checkCOP0Usable() const
{
	if (!getResources()->EE->EECore->COP0->isCoprocessorUsable())
	{
		// Coprocessor was not usable. Raise an exception.
		auto& COP0 = getResources()->EE->EECore->COP0;
		auto& Exceptions = getResources()->EE->EECore->Exceptions;
		COP0->Cause->setFieldValue(EECoreCOP0Register_Cause_t::Fields::CE, 0);
		Exceptions->setException(EECoreException_t::EX_COPROCESSOR_UNUSABLE);
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
		auto& COP0 = getResources()->EE->EECore->COP0;
		auto& Exceptions = getResources()->EE->EECore->Exceptions;
		COP0->Cause->setFieldValue(EECoreCOP0Register_Cause_t::Fields::CE, 1);
		Exceptions->setException(EECoreException_t::EX_COPROCESSOR_UNUSABLE);
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
		auto& COP0 = getResources()->EE->EECore->COP0;
		auto& Exceptions = getResources()->EE->EECore->Exceptions;
		COP0->Cause->setFieldValue(EECoreCOP0Register_Cause_t::Fields::CE, 2);
		Exceptions->setException(EECoreException_t::EX_COPROCESSOR_UNUSABLE);
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
		Exceptions->setException(mMMUHandler->getException());
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
		Exceptions->setException(EECoreException_t::EX_OVERFLOW);
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
		Exceptions->setException(EECoreException_t::EX_OVERFLOW);
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


