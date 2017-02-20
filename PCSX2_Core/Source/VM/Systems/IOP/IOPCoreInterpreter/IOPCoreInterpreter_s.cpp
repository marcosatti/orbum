#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/MIPS/PCRegister32_t.h"
#include "Common/Tables/IOPCoreInstructionTable/IOPCoreInstructionTable.h"
#include "Common/Types/MIPSInstruction/MIPSInstruction_t.h"
#include "Common/Types/MIPSInstructionInfo/MIPSInstructionInfo_t.h"
#include "Common/Types/MIPSBranchDelay/MIPSBranchDelay_t.h"
#include "Common/Types/PhysicalMMU/PhysicalMMU_t.h"
#include "Common/Util/MathUtil/MathUtil.h"

#include "VM/VM.h"
#include "VM/Systems/IOP/IOPCoreInterpreter/IOPCoreInterpreter_s.h"

#include "Resources/Resources_t.h"
#include "Resources/IOP/IOP_t.h"
#include "Resources/IOP/IOPCore/IOPCore_t.h"
#include "Resources/IOP/IOPCore/Types/IOPCoreException_t.h"
#include "Resources/IOP/IOPCore/Types/IOPCoreR3000_t.h"
#include "Resources/IOP/IOPCore/Types/IOPCoreCOP0_t.h"
#include "Resources/IOP/IOPCore/Types/IOPCoreCOP0Registers_t.h"
#include "Resources/IOP/INTC/IOPIntc_t.h"
#include "Resources/IOP/INTC/Types/IOPIntcRegisters_t.h"
#include <Common/Tables/IOPCoreExceptionsTable/IOPCoreExceptionsTable.h>

IOPCoreInterpreter_s::IOPCoreInterpreter_s(VM * vm) :
	VMSystem_s(vm, System_t::IOPCore),
	mInstructionInfo(nullptr)
{
	mIOPCore = getVM()->getResources()->IOP->IOPCore;
	mPhysicalMMU = getVM()->getResources()->IOP->PhysicalMMU;
}

IOPCoreInterpreter_s::~IOPCoreInterpreter_s()
{
}

void IOPCoreInterpreter_s::initalise()
{
	// An IOP reset is done by raising a Reset exception.
	handleException(IOPCoreException_t::EX_RESET);
}

int IOPCoreInterpreter_s::step(const ClockSource_t clockSource, const int ticksAvailable)
{
	auto& IOPCore = getVM()->getResources()->IOP->IOPCore;

	// Check if in a branch delay slot - function will set the PC automatically to the correct location.
	IOPCore->R3000->BD->handleBranchDelay();

	// Set the instruction holder to the instruction at the current PC, and get instruction details.
	const u32 pcAddress = mIOPCore->R3000->PC->readWord(IOP);
	u32 physicalAddress;
	bool mmuError = getPhysicalAddress(pcAddress, READ, physicalAddress); // TODO: Add error checking for address bus error.
	const u32 instructionValue = mPhysicalMMU->readWord(IOP, physicalAddress);
	mInstruction.setInstructionValue(instructionValue);
	mInstructionInfo = IOPCoreInstructionTable::getInstructionInfo(mInstruction);

	// Increment PC.
	IOPCore->R3000->PC->setPCValueNext();

#if defined(BUILD_DEBUG)
	static u64 DEBUG_LOOP_BREAKPOINT = 0x100000000000; //0x1b8415; // 0x1b5aff;
	static u32 DEBUG_PC_BREAKPOINT = 0x0; // 0x2dc8;
	static u32 DEBUG_INST_VAL_BREAKPOINT = 0x42000010; // COP0 RFE

	if (DEBUG_LOOP_COUNTER >= DEBUG_LOOP_BREAKPOINT)
	{
		// Debug print details.
		log(Debug, "IOPCore cycle 0x%llX: "
			"PC = 0x%08X, BD = %d, IntEn = %d, "
			"Instruction = %s",
			DEBUG_LOOP_COUNTER,
			pcAddress, IOPCore->R3000->BD->isInBranchDelay(), !IOPCore->COP0->Status->isInterruptsMasked(),
			(instructionValue == 0) ? "SLL (NOP)" : mInstructionInfo->mMnemonic);
	}

	if (pcAddress == DEBUG_PC_BREAKPOINT)
	{
		log(Debug, "IOPCore Breakpoint hit @ cycle = 0x%llX.", DEBUG_LOOP_COUNTER);
	}
#endif

	// Run the instruction, which is based on the implementation index.
	(this->*IOP_INSTRUCTION_TABLE[mInstructionInfo->mImplementationIndex])();

	// Check if any external interrupts are pending and immediately handle exception if there is one.
	handleInterruptCheck();

#if defined(BUILD_DEBUG)
	// Debug increment loop counter.
	DEBUG_LOOP_COUNTER++;
#endif

	// Return the number of cycles the instruction took to complete.
	return mInstructionInfo->mCycles;
}

void IOPCoreInterpreter_s::handleInterruptCheck()
{
	auto& COP0 = mIOPCore->COP0;

	// Interrupt exceptions are only taken when conditions are correct.
	if (!COP0->Status->isInterruptsMasked())
	{
		u32 ipCause = COP0->Cause->getFieldValue(IOPCoreCOP0Register_Cause_t::Fields::IP);
		u32 imStatus = COP0->Status->getFieldValue(IOPCoreCOP0Register_Status_t::Fields::IM);
		if (ipCause & imStatus)
		{
#if defined(BUILD_DEBUG)
			auto& IOPCore = getVM()->getResources()->IOP->IOPCore;
			auto& STAT = getVM()->getResources()->IOP->INTC->STAT;
			auto& MASK = getVM()->getResources()->IOP->INTC->MASK;
			log(Debug, "IOP interrupt exception occurred @ cycle = 0x%llX, PC = 0x%08X, BD = %d.", 
				DEBUG_LOOP_COUNTER, IOPCore->R3000->PC->readWord(IOP), IOPCore->R3000->BD->isInBranchDelay());
			log(Debug, "Printing list of interrupt sources...");
			for (auto& irqField : IOPIntcRegister_STAT_t::Fields::IRQ_KEYS)
			{
				if (STAT->getFieldValue(irqField) & MASK->getFieldValue(irqField))
					log(Debug, STAT->mFields[irqField].mMnemonic.c_str());
			}
#endif
			// Handle the interrupt immediately.
			// TODO: Set PC next is needed as otherwise the EPC will point to an instruction that has already completed - leading to crashes. Not sure if there is a better way to do this.
			IOPCore->R3000->PC->setPCValueNext();
			handleException(IOPCoreException_t::EX_INTERRUPT);
		}
	}
}

bool IOPCoreInterpreter_s::handleCOP0Usable()
{
	if (!mIOPCore->COP0->isCoprocessorUsable())
	{
		// Coprocessor was not usable. Raise an exception.
		mIOPCore->COP0->Cause->setFieldValue(IOPCoreCOP0Register_Cause_t::Fields::CE, 0);
		handleException(IOPCoreException_t::EX_COPROCESSOR_UNUSABLE);
		return true;
	}

	// Coprocessor is usable, proceed.
	return false;
}


bool IOPCoreInterpreter_s::handleOverOrUnderflow32(const s32& x, const s32& y)
{
	if (MathUtil::testOverOrUnderflow32(x, y))
	{
		// Over/Under flow occured.
		handleException(IOPCoreException_t::EX_OVERFLOW);
		return true;
	}

	// No error occured.
	return false;
}

void IOPCoreInterpreter_s::INSTRUCTION_UNKNOWN()
{
	// Unknown instruction, log if debug is enabled.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) Unknown R3000 instruction encountered! (Lookup: %s -> %s)",
		__FILENAME__, __LINE__, mInstructionInfo->mBaseClass, mInstructionInfo->mMnemonic);
#endif
}

void IOPCoreInterpreter_s::handleException(const IOPCoreException_t & exception)
{
#if defined(BUILD_DEBUG)
	DEBUG_HANDLED_EXCEPTION_COUNT += 1;
#endif

	auto& COP0 = mIOPCore->COP0;
	auto& BD = mIOPCore->R3000->BD;
	auto& PC = mIOPCore->R3000->PC;

	// Set the PS2Exception pointer and get properties.
	auto exceptionProperties = IOPCoreExceptionsTable::getExceptionInfo(exception);

#if 0 // defined(BUILD_DEBUG)
	// Debug print exception type.
	log(Debug, "IOPCore ExceptionHandler called! Type = %s", exceptionProperties->mMnemonic);
#endif

	// If its a reset exception, initalise COP0 registers and set PC to reset vector then return.
	if (exception == IOPCoreException_t::EX_RESET)
	{
		COP0->initalise();
		PC->setPCValueAbsolute(Constants::MIPS::Exceptions::Imp0::VADDRESS_EXCEPTION_BASE_V_RESET_NMI);
		return;
	}

	// Perform general exception handler code.
	// Vector offset value, used to set final vector address.
	u32 vectorOffset = 0x0;

	// Set Cause.ExeCode value.
	COP0->Cause->setFieldValue(IOPCoreCOP0Register_Cause_t::Fields::ExcCode, exceptionProperties->mExeCode);

	// Set EPC and Cause.BD fields, based on if we are in the branch delay slot.
	// Note that the EPC register should point to the instruction that caused the exception - so it is always set to at least PC - 4.
	// If we are in a branch delay slot, need to flush it (reset) so we dont jump after this exits.
	if (BD->isInBranchDelay())
	{
		u32 pcValue = PC->readWord(IOP) - Constants::MIPS::SIZE_MIPS_INSTRUCTION * 2;
		COP0->EPC->writeWord(RAW, pcValue);
		COP0->Cause->setFieldValue(IOPCoreCOP0Register_Cause_t::Fields::BD, 1);
		BD->resetBranchDelay();
	}
	else
	{
		u32 pcValue = PC->readWord(IOP) - Constants::MIPS::SIZE_MIPS_INSTRUCTION;
		COP0->EPC->writeWord(RAW, pcValue);
		COP0->Cause->setFieldValue(IOPCoreCOP0Register_Cause_t::Fields::BD, 0);
	}

	// Select the vector to use (set vectorOffset).
	if (exception == IOPCoreException_t::EX_TLB_REFILL_INSTRUCTION_FETCH_LOAD || exception == IOPCoreException_t::EX_TLB_REFILL_STORE)
		vectorOffset = Constants::MIPS::Exceptions::Imp0::OADDRESS_EXCEPTION_VECTOR_V_TLB_REFILL;
	else
		vectorOffset = Constants::MIPS::Exceptions::Imp0::OADDRESS_EXCEPTION_VECTOR_V_COMMON;

	// Select vector base to use and set PC to use the specified vector.
	if (COP0->Status->getFieldValue(IOPCoreCOP0Register_Status_t::Fields::BEV) == 1)
		PC->setPCValueAbsolute(Constants::MIPS::Exceptions::Imp0::VADDRESS_EXCEPTION_BASE_A1 + vectorOffset);
	else
		PC->setPCValueAbsolute(Constants::MIPS::Exceptions::Imp0::VADDRESS_EXCEPTION_BASE_A0 + vectorOffset);

	// Push the exception state within the COP0.Status register (will cause IEc and KUc to switch to interrupts disabled and kernel mode respectively).
	COP0->Status->pushExceptionStack();
}

bool IOPCoreInterpreter_s::getPhysicalAddress(const u32& virtualAddress, const MMUAccess_t& access, u32& physicalAddress)
{
	auto& COP0 = mIOPCore->COP0;

	// If in kernel mode, perform a direct translation if VA is within kernel segments.
	if (COP0->isOperatingKernelMode())
	{
		// Test for kseg0
		if (virtualAddress >= Constants::MIPS::MMU::VADDRESS_KERNEL_LOWER_BOUND_2 && virtualAddress <= Constants::MIPS::MMU::VADDRESS_KERNEL_UPPER_BOUND_2)
		{
			// We are in kseg0, so to get the physical address we just minus the kseg0 base address of 0x80000000.
			// We also do not test for the Config.K0 status, as we do not involve caches unless it is an explicit request.
			physicalAddress = (virtualAddress - Constants::MIPS::MMU::VADDRESS_KERNEL_LOWER_BOUND_2);
			return false;
		}

		// Test for kseg1
		if (virtualAddress >= Constants::MIPS::MMU::VADDRESS_KERNEL_LOWER_BOUND_3 && virtualAddress <= Constants::MIPS::MMU::VADDRESS_KERNEL_UPPER_BOUND_3)
		{
			// We are in kseg1, so to get the physical address we just minus the kseg1 base address of 0xA0000000.
			physicalAddress = (virtualAddress - Constants::MIPS::MMU::VADDRESS_KERNEL_LOWER_BOUND_3);
			return false;
		}

		// Undocumented: the IOP seems to access the addresses 0xFFC00000 - 0xFFFFFFFF as if it was trying to access the BIOS (0x1FC00000)... probably related to cache modes.
		// The IOP's PhysicalMMU has an image mapping to handle this address. From PCSX2 code.
		if (virtualAddress >= Constants::IOP::IOPCore::MMU::VADDRESS_SPECIAL_2_LOWER_BOUND)
		{
			physicalAddress = virtualAddress;
			return false;
		}

		// Undocumented: the IOP accesses addresses 0x00000000 - 0x001FFFFF as if it was trying to access the main memory (2MB).
		// This is not TLB mapped. From PCSX2 code.
		if (virtualAddress <= Constants::IOP::IOPCore::MMU::VADDRESS_SPECIAL_1_UPPER_BOUND)
		{
			// Check if a write is being performed with isolate cache turned on.
			if (COP0->Status->getFieldValue(IOPCoreCOP0Register_Status_t::Fields::IsC) && access == WRITE)
			{
				// Return that an error has occurred but dont invoke the exception handler (doesn't change any instructions behaviour).
				return true;
			}

			physicalAddress = virtualAddress;
			return false;
		}
	}

	// Throw runtime error as anything else is not implemented.
	throw std::runtime_error("IOPCore MMU: VA or COP0 was not in kernel context (not implemented). Needs debugging!");
}