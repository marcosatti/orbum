#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Register/PCRegister32_t.h"
#include "Common/Tables/IOPCoreInstructionTable.h"
#include "Common/Tables/IOPCoreExceptionsTable.h"
#include "Common/Types/ByteMMU/ByteMMU_t.h"
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

IOPCoreInterpreter_s::IOPCoreInterpreter_s(VM * vm) :
	VMSystem_s(vm, System_t::IOPCore),
	mIOPCoreInstruction(0)
{
	mIOPCore = getVM()->getResources()->IOP->IOPCore;
	mByteMMU = getVM()->getResources()->IOP->MMU;
}

void IOPCoreInterpreter_s::initalise()
{
	// An IOP reset is done by raising a Reset exception.
	handleException(IOPCoreException_t::EX_RESET);
}

int IOPCoreInterpreter_s::step(const ClockSource_t clockSource, const int ticksAvailable)
{
	// Check if any external interrupts are pending and immediately handle exception if there is one.
	handleInterruptCheck();

	// Set the instruction holder to the instruction at the current PC, and get instruction details.
	const u32 pcAddress = mIOPCore->R3000->PC->readWord(getContext());
	u32 physicalAddress;
	bool mmuError = getPhysicalAddress(pcAddress, READ, physicalAddress); // TODO: Add error checking for address bus error.
	mIOPCoreInstruction = IOPCoreInstruction_t(mByteMMU->readWord(getContext(), physicalAddress));

#if defined(BUILD_DEBUG)
	static u64 DEBUG_LOOP_BREAKPOINT = 0x439A41;
	static u32 DEBUG_PC_BREAKPOINT = 0x0;
	static u32 DEBUG_INST_VAL_BREAKPOINT = 0x42000010; // COP0 RFE

	if (DEBUG_LOOP_COUNTER >= DEBUG_LOOP_BREAKPOINT)
	{
		// Debug print details.
		log(Debug, "IOPCore cycle 0x%llX: "
			"PC = 0x%08X, BD = %d, IntEn = %d, "
			"Instruction = %s",
			DEBUG_LOOP_COUNTER,
			pcAddress, mIOPCore->R3000->PC->isBranchPending(), !mIOPCore->COP0->Status->isInterruptsMasked(getContext()),
			(mIOPCoreInstruction.getValue() == 0) ? "SLL (NOP)" : mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
	}

	if (pcAddress == DEBUG_PC_BREAKPOINT || pcAddress == 0x0)
	{
		log(Debug, "IOPCore PC breakpoint hit @ cycle = 0x%llX, PC = 0x%08X.", DEBUG_LOOP_COUNTER, pcAddress);
	}
#endif

	// Run the instruction, which is based on the implementation index.
	(this->*IOP_INSTRUCTION_TABLE[mIOPCoreInstruction.getInfo()->mImplementationIndex])();

	// Increment PC.
	mIOPCore->R3000->PC->next(getContext());

#if defined(BUILD_DEBUG)
	// Debug increment loop counter.
	DEBUG_LOOP_COUNTER++;
#endif

	// Return the number of cycles the instruction took to complete.
	return mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mCycles;
}

void IOPCoreInterpreter_s::handleInterruptCheck()
{
	auto& COP0 = mIOPCore->COP0;

	// Interrupt exceptions are only taken when conditions are correct.
	if (!COP0->Status->isInterruptsMasked(getContext()))
	{
		u32 ipCause = COP0->Cause->getFieldValue(getContext(), IOPCoreCOP0Register_Cause_t::Fields::IP);
		u32 imStatus = COP0->Status->getFieldValue(getContext(), IOPCoreCOP0Register_Status_t::Fields::IM);
		if (ipCause & imStatus)
		{
#if DEBUG_LOG_IOP_INTERRUPTS
			auto& IOPCore = getVM()->getResources()->IOP->IOPCore;
			auto& STAT = getVM()->getResources()->IOP->INTC->STAT;
			auto& MASK = getVM()->getResources()->IOP->INTC->MASK;
			log(Debug, "IOP interrupt exception occurred @ cycle = 0x%llX, PC = 0x%08X, BD = %d.", 
				DEBUG_LOOP_COUNTER, IOPCore->R3000->PC->readWord(getContext()), IOPCore->R3000->PC->isBranchPending());
			log(Debug, "Printing list of interrupt sources...");
			for (auto& irqField : IOPIntcRegister_STAT_t::Fields::IRQ_KEYS)
			{
				if (STAT->getFieldValue(getContext(), irqField) & MASK->getFieldValue(getContext(), irqField))
					log(Debug, STAT->mFields[irqField].mMnemonic.c_str());
			}
#endif
			// Handle the interrupt immediately.
			handleException(IOPCoreException_t::EX_INTERRUPT);
		}
	}
}

bool IOPCoreInterpreter_s::handleCOP0Usable()
{
	if (!mIOPCore->COP0->isCoprocessorUsable(getContext()))
	{
		// Coprocessor was not usable. Raise an exception.
		mIOPCore->COP0->Cause->setFieldValue(getContext(), IOPCoreCOP0Register_Cause_t::Fields::CE, 0);
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
		__FILENAME__, __LINE__, mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mBaseClassMnemonic, mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
#endif
}

void IOPCoreInterpreter_s::handleException(const IOPCoreException_t & exception)
{
#if defined(BUILD_DEBUG)
	DEBUG_HANDLED_EXCEPTION_COUNT += 1;
#endif

	auto& COP0 = mIOPCore->COP0;
	auto& PC = mIOPCore->R3000->PC;

	// Set the PS2Exception pointer and get properties.
	auto exceptionProperties = IOPCoreExceptionsTable::getInfo(exception);

#if 0 // defined(BUILD_DEBUG)
	// Debug print exception type.
	log(Debug, "IOPCore ExceptionHandler called! Type = %s", exceptionProperties->mMnemonic);
#endif

	// If its a reset exception, initalise COP0 registers and set PC to reset vector then return.
	if (exception == IOPCoreException_t::EX_RESET)
	{
		COP0->initalise();
		PC->setPCValueAbsolute(getContext(), Constants::MIPS::Exceptions::Imp0::VADDRESS_EXCEPTION_BASE_V_RESET_NMI);
		return;
	}

	// Perform general exception handler code.
	// Vector offset value, used to set final vector address.
	u32 vectorOffset = 0x0;

	// Set Cause.ExeCode value.
	COP0->Cause->setFieldValue(getContext(), IOPCoreCOP0Register_Cause_t::Fields::ExcCode, exceptionProperties->mExeCode);

	// Set EPC and Cause.BD fields, based on if we are in the branch delay slot.
	// Note that the EPC register should point to the instruction that caused the exception.
	// If we are in a branch delay slot, need to flush it (reset) so we dont jump after this exits.
	if (PC->isBranchPending())
	{
		u32 pcValue = PC->readWord(getContext()) - Constants::MIPS::SIZE_MIPS_INSTRUCTION;
		COP0->EPC->writeWord(getContext(), pcValue);
		COP0->Cause->setFieldValue(getContext(), IOPCoreCOP0Register_Cause_t::Fields::BD, 1);
		PC->resetBranch();
	}
	else
	{
		u32 pcValue = PC->readWord(getContext());
		COP0->EPC->writeWord(getContext(), pcValue);
		COP0->Cause->setFieldValue(getContext(), IOPCoreCOP0Register_Cause_t::Fields::BD, 0);
	}

	// Select the vector to use (set vectorOffset).
	if (exception == IOPCoreException_t::EX_TLB_REFILL_INSTRUCTION_FETCH_LOAD || exception == IOPCoreException_t::EX_TLB_REFILL_STORE)
		vectorOffset = Constants::MIPS::Exceptions::Imp0::OADDRESS_EXCEPTION_VECTOR_V_TLB_REFILL;
	else
		vectorOffset = Constants::MIPS::Exceptions::Imp0::OADDRESS_EXCEPTION_VECTOR_V_COMMON;

	// Select vector base to use and set PC to use the specified vector.
	if (COP0->Status->getFieldValue(getContext(), IOPCoreCOP0Register_Status_t::Fields::BEV) == 1)
		PC->setPCValueAbsolute(getContext(), Constants::MIPS::Exceptions::Imp0::VADDRESS_EXCEPTION_BASE_A1 + vectorOffset);
	else
		PC->setPCValueAbsolute(getContext(), Constants::MIPS::Exceptions::Imp0::VADDRESS_EXCEPTION_BASE_A0 + vectorOffset);

	// Push the exception state within the COP0.Status register (will cause IEc and KUc to switch to interrupts disabled and kernel mode respectively).
	COP0->Status->pushExceptionStack(getContext());

	// TODO: Extra code to make sure the PC is correct. Currently an external exception (eg: interrupt) is run before the instruction is executed, so the PC is correct.
	//       But for an internal interrupt (eg: syscall), the instruction has already run and so the PC will get incremented upon this function's return, which leads to a skipped instruction.
	//       This is the easiest way to fix this, not sure how to properly do it (just need to play around with the code structure).
	if (exception != IOPCoreException_t::EX_INTERRUPT 
		&& exception != IOPCoreException_t::EX_RESET)
	{
		PC->setPCValueRelative(getContext(), -static_cast<s32>(Constants::MIPS::SIZE_MIPS_INSTRUCTION));
	}
}

bool IOPCoreInterpreter_s::getPhysicalAddress(const u32 virtualAddress, const MMUAccess_t access, u32 & physicalAddress)
{
	auto& COP0 = mIOPCore->COP0;

#if defined(BUILD_DEBUG)
	static u32 DEBUG_VA_BREAKPOINT = 0xFFFFFFFF;
	if (virtualAddress == DEBUG_VA_BREAKPOINT)
	{
		log(Debug, "IOP MMU breakpoint hit @ cycle = 0x%llX, PC = 0x%08X, VA = 0x%08X (%s).",
			DEBUG_LOOP_COUNTER, mIOPCore->R3000->PC->readWord(getContext()), DEBUG_VA_BREAKPOINT, (access == READ) ? "READ" : "WRITE");
	}
#endif

	// If in kernel mode, perform a direct translation if VA is within kernel segments.
	auto context = COP0->getCPUOperatingContext(getContext());
	if (context == MIPSCPUOperatingContext_t::Kernel)
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
		// The IOP's MMU has an image mapping to handle this address. From PCSX2 code.
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
			if (COP0->Status->getFieldValue(getContext(), IOPCoreCOP0Register_Status_t::Fields::IsC) && access == WRITE)
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