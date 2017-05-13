#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/ByteMMU/ByteMMU_t.h"
#include "Common/Types/Register/PCRegister32_t.h"
#include "Common/Tables/EECoreInstructionTable.h"
#include "Common/Tables/EEDmacChannelTable.h"
#include "Common/Util/MathUtil/MathUtil.h"

#include "VM/VM.h"
#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h"
#include "VM/Systems/EE/VPU/VUInterpreter/VUInterpreter_s.h"

#include "Resources/Resources_t.h"
#include "Resources/EE/EE_t.h"
#include "Resources/EE/EECore/EECore_t.h"
#include "Resources/EE/EECore/Types/EECoreException_t.h"
#include "Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "Resources/EE/EECore/Types/EECoreCOP0_t.h"
#include "Resources/EE/EECore/Types/EECoreCOP0Registers_t.h"
#include "Resources/EE/EECore/Types/EECoreFPU_t.h"
#include "Resources/EE/EECore/Types/EECoreTLB_t.h"
#include "Resources/EE/EECore/Types/EECoreTLBEntry_t.h"
#include "Resources/EE/VPU/VPU_t.h"
#include "Resources/EE/VPU/VU/VU_t.h"
#include "Resources/EE/VPU/VU/Types/VUCores_t.h"
#include "Resources/EE/INTC/EEIntc_t.h"
#include "Resources/EE/INTC/Types/EEIntcRegisters_t.h"
#include "Resources/EE/DMAC/EEDmac_t.h"
#include "Resources/EE/DMAC/Types/EEDmacRegisters_t.h"

EECoreInterpreter_s::EECoreInterpreter_s(VM * vm, const std::shared_ptr<VUInterpreter_s> & vuInterpreter) :
	VMSystem_s(vm, System_t::EECore),
	mVU0Interpreter(vuInterpreter), 
	mEECoreInstruction(0),
	mException(), 
	mExceptionProperties(nullptr) 
{
	mEECore = getVM()->getResources()->EE->EECore;
	mByteMMU = getVM()->getResources()->EE->MMU;
	mVU0 = getVM()->getResources()->EE->VPU->VU->VU0;
}

void EECoreInterpreter_s::initialise()
{
	// An EE Core reset is done according to the Reset signal/exception defined on page 95 of the EE Core Users Manual.
	handleException(EECoreException_t::EX_RESET);
}

int EECoreInterpreter_s::step(const ClockSource_t clockSource, const int ticksAvailable)
{
	// Check if any external interrupts are pending and immediately handle exception if there is one.
	handleInterruptCheck();

	// Set the instruction holder to the instruction at the current PC, and get instruction details.
	const u32 pcAddress = mEECore->R5900->PC->readWord(getContext());
	u32 physicalAddress;
	bool mmuError = getPhysicalAddress(pcAddress, READ, physicalAddress); // TODO: Add error checking for address bus error.
	mEECoreInstruction = EECoreInstruction_t(mByteMMU->readWord(getContext(), physicalAddress));

#if defined(BUILD_DEBUG)
	static u64 DEBUG_LOOP_BREAKPOINT = 0x10000000143138b;
	static u32 DEBUG_PC_BREAKPOINT = 0x0;
	if (DEBUG_LOOP_COUNTER >= DEBUG_LOOP_BREAKPOINT)
	{
		// Debug print details.
		log(Debug, "EECore cycle = 0x%llX: "
			"PC = 0x%08X, BD = %d, IntEn = %d, "
			"Instruction = %s",
			DEBUG_LOOP_COUNTER,
			pcAddress, mEECore->R5900->PC->isBranchPending(), !mEECore->COP0->Status->isInterruptsMasked(getContext()),
			(mEECoreInstruction.getValue() == 0) ? "SLL (NOP)" : mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
	}

	// Breakpoint.
	if (pcAddress == DEBUG_PC_BREAKPOINT || pcAddress == 0x0)
	{
		log(Debug, "EECore Breakpoint hit @ cycle = 0x%llX, PC = 0x%08X.", DEBUG_LOOP_COUNTER, pcAddress);
	}
#endif

	// Run the instruction, which is based on the implementation index.
	(this->*EECORE_INSTRUCTION_TABLE[mEECoreInstruction.getInfo()->mImplementationIndex])();

	// Increment PC.
	mEECore->R5900->PC->next(getContext());

	// Update the COP0.Count register, and check for interrupt. See EE Core Users Manual page 70.
	mEECore->COP0->Count->increment(getContext(), mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mCycles);
	handleCountEventCheck();

#if defined(BUILD_DEBUG)
	// Debug increment loop counter.
	DEBUG_LOOP_COUNTER++;
#endif

	// Return the number of cycles completed.
	return mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mCycles;
}

void EECoreInterpreter_s::handleInterruptCheck()
{
	auto& COP0 = mEECore->COP0;

	// Interrupt exceptions are only taken when conditions are correct.
	// Interrupt exception checking follows the process on page 74 of the EE Core Users Manual.
	if (!COP0->Status->isInterruptsMasked(getContext()))
	{
		u32 ipCause = COP0->Cause->getFieldValue(getContext(), EECoreCOP0Register_Cause_t::Fields::IP);
		u32 imStatus = COP0->Status->getFieldValue(getContext(), EECoreCOP0Register_Status_t::Fields::IM);
		if (ipCause & imStatus)
		{
#if DEBUG_LOG_EE_INTERRUPTS
			// Debug: print interrupt sources.
			printInterruptInfo();
#endif
			// Handle the interrupt immediately.
			handleException(EECoreException_t::EX_INTERRUPT);
		}
	}
}

void EECoreInterpreter_s::printInterruptInfo() const
{
	auto& COP0 = mEECore->COP0;
	auto& STAT = getVM()->getResources()->EE->INTC->STAT;
	auto& MASK = getVM()->getResources()->EE->INTC->MASK;

	u32 ipCause = COP0->Cause->getFieldValue(getContext(), EECoreCOP0Register_Cause_t::Fields::IP);
	u32 imStatus = COP0->Status->getFieldValue(getContext(), EECoreCOP0Register_Status_t::Fields::IM);

	log(Debug, "EECore interrupt exception occurred @ cycle = 0x%llX, PC = 0x%08X, BD = %d. Printing interrupt sources:",
		DEBUG_LOOP_COUNTER, mEECore->R5900->PC->readWord(getContext()), mEECore->R5900->PC->isBranchPending());

	// Check the INTC.
	if ((ipCause & imStatus) & 0x4)
	{
		for (auto& irqField : EEIntcRegister_STAT_t::Fields::IRQ_KEYS)
		{
			if (STAT->getFieldValue(getContext(), irqField) & MASK->getFieldValue(getContext(), irqField))
				log(Debug, STAT->mFields[irqField].mMnemonic.c_str());
		}
	}

	// Check the DMAC.
	if ((ipCause & imStatus) & 0x8)
	{
		log(Debug, "DMAC");

		auto& DMAC = getVM()->getResources()->EE->DMAC;
		auto& STAT = DMAC->STAT;

		log(Debug, "Printing EE DMAC interrupt sources:");

		bool dmacSourceTriggered = false;

		// Check through STAT for triggered channels.
		for (int i = 0; i < Constants::EE::DMAC::NUMBER_DMAC_CHANNELS; i++)
		{
			if (STAT->getFieldValue(getContext(), EEDmacRegister_STAT_t::Fields::CHANNEL_CIS_KEYS[i])
				&& STAT->getFieldValue(getContext(), EEDmacRegister_STAT_t::Fields::CHANNEL_CIM_KEYS[i]))
			{
				log(Debug, EEDmacChannelTable::getMnemonic(i));
				dmacSourceTriggered = true;
			}
		}

		// Maybe we missed it? :(
		if (!dmacSourceTriggered)
			log(Debug, "EE DMAC did not have any sources triggered! Too slow, buddy? Look into this!");
	}
}

void EECoreInterpreter_s::handleCountEventCheck() const
{
	// Check the COP0.Count register against the COP0.Compare register. See EE Core Users Manual page 72 for details.
	// The docs specify that an interrupt (IP[7]) is raised when the two values are equal.
	if (mEECore->COP0->Count->readWord(getContext()) == mEECore->COP0->Compare->readWord(getContext()))
		mEECore->COP0->Cause->setIRQLine(getContext(), 7);
	else
		mEECore->COP0->Cause->clearIRQLine(getContext(), 7);
}

bool EECoreInterpreter_s::handleCOP0Usable()
{
	if (!mEECore->COP0->isCoprocessorUsable(getContext()))
	{
		// Coprocessor was not usable. Raise an exception.
		mEECore->COP0->Cause->setFieldValue(getContext(), EECoreCOP0Register_Cause_t::Fields::CE, 0);
		handleException(EECoreException_t::EX_COPROCESSOR_UNUSABLE);
		return true;
	}

	// Coprocessor is usable, proceed.
	return false;
}

bool EECoreInterpreter_s::handleCOP1Usable()
{
	if (!mEECore->FPU->isCoprocessorUsable(getContext()))
	{
		// Coprocessor was not usable. Raise an exception.
		mEECore->COP0->Cause->setFieldValue(getContext(), EECoreCOP0Register_Cause_t::Fields::CE, 1);
		handleException(EECoreException_t::EX_COPROCESSOR_UNUSABLE);
		return true;
	}

	// Coprocessor is usable, proceed.
	return false;
}

bool EECoreInterpreter_s::handleCOP2Usable()
{
	if (!mVU0->isCoprocessorUsable(getContext()))
	{
		// Coprocessor was not usable. Raise an exception.
		mEECore->COP0->Cause->setFieldValue(getContext(), EECoreCOP0Register_Cause_t::Fields::CE, 2);
		handleException(EECoreException_t::EX_COPROCESSOR_UNUSABLE);
		return true;
	}

	// Coprocessor is usable, proceed.
	return false;
}

bool EECoreInterpreter_s::handleOverOrUnderflow32(const s32& x, const s32& y)
{
	if (MathUtil::testOverOrUnderflow32(x, y))
	{
		// Over/Under flow occured.
		handleException(EECoreException_t::EX_OVERFLOW);
		return true;
	}

	// No error occured.
	return false;
}

bool EECoreInterpreter_s::handleOverOrUnderflow64(const s64& x, const s64& y)
{
	if (MathUtil::testOverOrUnderflow64(x, y))
	{
		// Over/Under flow occured.
		handleException(EECoreException_t::EX_OVERFLOW);
		return true;
	}

	// No error occured.
	return false;
}

void EECoreInterpreter_s::INSTRUCTION_UNKNOWN()
{
	// Unknown instruction, log if debug is enabled.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) Unknown R5900 instruction encountered! (Lookup: %s -> %s)",
		__FILENAME__, __LINE__, mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mBaseClassMnemonic, mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
#endif
}

void EECoreInterpreter_s::handleException(const EECoreException_t& exception)
{
	auto& COP0 = mEECore->COP0;

#if defined(BUILD_DEBUG)
	DEBUG_HANDLED_EXCEPTION_COUNT += 1;
#endif

	// Set the PS2Exception pointer.
	mException = exception;

	// Get the exception properties.
	mExceptionProperties = EECoreExceptionsTable::getInfo(mException);

#if 0 // defined(BUILD_DEBUG)
	// Debug print exception type.
	log(Debug, "EECore ExceptionHandler called! Type = %s", mExceptionProperties->mMnemonic);
#endif

	// For Reset and NMI's, need some additional processing before calling the general handlers.
	if (mException == EECoreException_t::EX_RESET)
	{
		COP0->initialise();
	}
	else if (mException == EECoreException_t::EX_NMI)
	{
		COP0->Status->setFieldValue(getContext(), EECoreCOP0Register_Status_t::Fields::ERL, 1);
		COP0->Status->setFieldValue(getContext(), EECoreCOP0Register_Status_t::Fields::BEV, 1);
	}

	// Call the Level 1 or Level 2 exception handler based on the exception, or throw runtime_error if exception type/properties does not exist.
	switch (mExceptionProperties->mLevel)
	{
	case 1:
		handleException_L1(); break;
	case 2:
		handleException_L2(); break;
	default:
		throw std::runtime_error("Exception parsed contained an unknown exception type.");
	}
}

void EECoreInterpreter_s::handleException_L1() const
{
	// Exception level 1 handler code. Adapted from EE Core Users Manual page 91.
	auto& COP0 = mEECore->COP0;
	auto& PC = mEECore->R5900->PC;

	// Vector offset value, used to set final vector address.
	u32 vectorOffset = 0x0;

	// Set Cause.ExeCode value.
	COP0->Cause->setFieldValue(getContext(), EECoreCOP0Register_Cause_t::Fields::ExcCode, mExceptionProperties->mExeCode);

	// If already in exception handler (EXL == 1), do not update EPC and Cause.BD, and use general exception handler vector. Else perform normal exception processing.
	if (COP0->Status->getFieldValue(getContext(), EECoreCOP0Register_Status_t::Fields::EXL) == 1)
	{
		vectorOffset = Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_COMMON;
	}
	else
	{
		// Set EPC and Cause.BD fields.
		// Note that the EPC register should point to the instruction that caused the exception.
		// If we are in a branch delay slot, need to flush it (reset) so we dont jump after this exits.
		if (PC->isBranchPending())
		{
			u32 pcValue = PC->readWord(getContext()) - Constants::MIPS::SIZE_MIPS_INSTRUCTION;
			COP0->EPC->writeWord(getContext(), pcValue);
			COP0->Cause->setFieldValue(getContext(), EECoreCOP0Register_Cause_t::Fields::BD, 1);
			PC->resetBranch(); // Reset branch delay slot.
		}
		else
		{
			u32 pcValue = PC->readWord(getContext());
			COP0->EPC->writeWord(getContext(), pcValue);
			COP0->Cause->setFieldValue(getContext(), EECoreCOP0Register_Cause_t::Fields::BD, 0);
		}

		// Set to kernel mode and disable interrupts.
		COP0->Status->setFieldValue(getContext(), EECoreCOP0Register_Status_t::Fields::EXL, 1);

		// Select the vector to use (set vectorOffset).
		if (mException == EECoreException_t::EX_TLB_REFILL_INSTRUCTION_FETCH_LOAD
			|| mException == EECoreException_t::EX_TLB_REFILL_STORE)
		{
			vectorOffset = Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_TLB_REFILL;
		}
		else if (mException == EECoreException_t::EX_INTERRUPT)
		{
			vectorOffset = Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_INTERRUPT;
		}
		else
		{
			vectorOffset = Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_COMMON;
		}
	}

	// Select vector base to use and set PC to use the specified vector.
	if (COP0->Status->getFieldValue(getContext(), EECoreCOP0Register_Status_t::Fields::BEV) == 1)
	{
		PC->setPCValueAbsolute(getContext(), Constants::MIPS::Exceptions::Imp46::VADDRESS_EXCEPTION_BASE_A1 + vectorOffset);
	}
	else
	{
		PC->setPCValueAbsolute(getContext(), Constants::MIPS::Exceptions::Imp46::VADDRESS_EXCEPTION_BASE_A0 + vectorOffset);
	}

	// TODO: Extra code to make sure the PC is correct. Currently an external exception (eg: interrupt) is run before the instruction is executed, so the PC is correct.
	//       But for an internal interrupt (eg: syscall), the instruction has already run and so the PC will get incremented upon this function's return, which leads to a skipped instruction.
	//       This is the easiest way to fix this, not sure how to properly do it (just need to play around with the code structure).
	if (mException != EECoreException_t::EX_INTERRUPT)
	{
		PC->setPCValueRelative(getContext(), -static_cast<s32>(Constants::MIPS::SIZE_MIPS_INSTRUCTION));
	}
}

void EECoreInterpreter_s::handleException_L2() const
{
	// Exception level 2 handler code. Adapted from EE Core Users Manual page 92.
	auto& COP0 = mEECore->COP0;
	auto& PC = mEECore->R5900->PC;

	// Vector offset value, used to set final vector address.
	u32 vectorOffset = 0x0;

	// Set Cause.EXC2 value.
	COP0->Cause->setFieldValue(getContext(), EECoreCOP0Register_Cause_t::Fields::EXC2, mExceptionProperties->mExeCode);

	// Set EPC and Cause.BD fields.
	// Note that the EPC register should point to the instruction that caused the exception.
	// If we are in a branch delay slot, need to flush it (reset) so we dont jump after this exits.
	if (PC->isBranchPending())
	{
		// TODO: no idea if this code works, yet to encounter a branch delay exception.
		u32 pcValue = PC->readWord(getContext()) - Constants::MIPS::SIZE_MIPS_INSTRUCTION * 2;
		COP0->ErrorEPC->writeWord(getContext(), pcValue);
		COP0->Cause->setFieldValue(getContext(), EECoreCOP0Register_Cause_t::Fields::BD2, 1);
		PC->resetBranch(); // Reset branch delay slot.
	}
	else
	{
		u32 pcValue = PC->readWord(getContext()) - Constants::MIPS::SIZE_MIPS_INSTRUCTION;
		COP0->ErrorEPC->writeWord(getContext(), pcValue);
		COP0->Cause->setFieldValue(getContext(), EECoreCOP0Register_Cause_t::Fields::BD2, 0);
	}

	// Set to kernel mode and disable interrupts.
	COP0->Status->setFieldValue(getContext(), EECoreCOP0Register_Status_t::Fields::ERL, 1);

	// Select vector to use and set PC to use it.
	if (mException == EECoreException_t::EX_NMI
		|| mException == EECoreException_t::EX_RESET)
	{
		PC->setPCValueAbsolute(getContext(), Constants::MIPS::Exceptions::Imp46::VADDRESS_EXCEPTION_BASE_V_RESET_NMI);
	}
	else
	{
		if (mException == EECoreException_t::EX_PERFORMANCE_COUNTER)
		{
			vectorOffset = Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_COUNTER;
		}
		else if (mException == EECoreException_t::EX_DEBUG)
		{
			vectorOffset = Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_DEBUG;
		}
		else
		{
			// Use V_TLB_REFIL (offset 0x00000000) (should get optimised out).
			vectorOffset = Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_TLB_REFILL;
		}

		// Select vector base to use and set PC to use the specified vector.
		if (COP0->Status->getFieldValue(getContext(), EECoreCOP0Register_Status_t::Fields::DEV) == 1)
		{
			PC->setPCValueAbsolute(getContext(), Constants::MIPS::Exceptions::Imp46::VADDRESS_EXCEPTION_BASE_A1 + vectorOffset);
		}
		else
		{
			PC->setPCValueAbsolute(getContext(), Constants::MIPS::Exceptions::Imp46::VADDRESS_EXCEPTION_BASE_A0 + vectorOffset);
		}
	}

	// TODO: Extra code to make sure the PC is correct. Currently an external exception (eg: interrupt) is run before the instruction is executed, so the PC is correct.
	//       But for an internal interrupt (eg: syscall), the instruction has already run and so the PC will get incremented upon this function's return, which leads to a skipped instruction.
	//       This is the easiest way to fix this, not sure how to properly do it (just need to play around with the code structure).
	if (mException != EECoreException_t::EX_RESET
		&& mException != EECoreException_t::EX_NMI)
	{
		PC->setPCValueRelative(getContext(), -static_cast<s32>(Constants::MIPS::SIZE_MIPS_INSTRUCTION));
	}
}

void EECoreInterpreter_s::handleMMUError(const u32 virtualAddress, const MMUAccess_t access, const MMUError_t error, const s32 tlbEntryIndex)
{
	auto& COP0 = mEECore->COP0;
	auto& TLB = mEECore->TLB;
	EECoreException_t exception;

	// Set COP0 information. TODO: check if correct.
	COP0->BadVAddr->writeWord(getContext(), virtualAddress);
	COP0->Context->setFieldValue(getContext(), EECoreCOP0Register_System_t::Fields::BadVPN2, MathUtil::getHI19(virtualAddress));
	COP0->EntryHi->setFieldValue(getContext(), EECoreCOP0Register_EntryHi_t::Fields::VPN2, MathUtil::getHI19(virtualAddress));
	COP0->Random->setFieldValue(getContext(), EECoreCOP0Register_Random_t::Fields::Random, TLB->getNewTLBIndex());

	if (tlbEntryIndex > 0) 
		COP0->EntryHi->setFieldValue(getContext(), EECoreCOP0Register_EntryHi_t::Fields::ASID, TLB->getTLBEntry(tlbEntryIndex).mASID); // Set only if tlb entry index valid.

	// Find the right EECoreException_t to process...
	if (access == READ)
	{
		switch (error)
		{
		case ADDRESS:
			exception = EECoreException_t::EX_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD; break;
		case TLB_REFILL:
			exception = EECoreException_t::EX_TLB_REFILL_INSTRUCTION_FETCH_LOAD; break;
		case TLB_INVALID:
			exception = EECoreException_t::EX_TLB_INVALID_INSTRUCTION_FETCH_LOAD; break;
		case TLB_MODIFIED:
			exception = EECoreException_t::EX_TLB_MODIFIED; break;
		}
	}
	else
	{
		switch (error)
		{
		case ADDRESS:
			exception = EECoreException_t::EX_ADDRESS_ERROR_STORE; break;
		case TLB_REFILL:
			exception = EECoreException_t::EX_TLB_REFILL_STORE; break;
		case TLB_INVALID:
			exception = EECoreException_t::EX_TLB_INVALID_STORE; break;
		case TLB_MODIFIED:
			exception = EECoreException_t::EX_TLB_MODIFIED; break;
		}
	}

	// Pass exception to handler.
	handleException(exception);
}

bool EECoreInterpreter_s::getPhysicalAddress(const u32 virtualAddress, const MMUAccess_t access, u32 & physicalAddress)
{
	// This process follows the information and diagram given on page 121 & 122 of the EE Core Users Manual. 
	// I am unsure if this is exactly what happens, as the information is a bit vague on how to obtain the page mask and ASID, 
	//  but I'm confident this is what it meant (I also dont see another way to do it).
	// TODO: try to reduce the spaghetti code-ness of this... however the lookup process is complicated and error propogation is needed, so may not be able to do much.
	auto& COP0 = mEECore->COP0;
	auto& TLB = mEECore->TLB;

#if defined(BUILD_DEBUG)
	static u32 DEBUG_VA_BREAKPOINT = 0xFFFFFFFF;
	if (virtualAddress == DEBUG_VA_BREAKPOINT)
	{
		log(Debug, "EE MMU breakpoint hit @ cycle = 0x%llX, PC = 0x%08X, VA = 0x%08X (%s).",
			DEBUG_LOOP_COUNTER, mEECore->R5900->PC->readWord(getContext()), DEBUG_VA_BREAKPOINT, (access == READ) ? "READ" : "WRITE");
	}
#endif

	// Stage 1 - determine which CPU context we are in (user, supervisor or kernel) and check address bounds.
	// Note that a VA is valid over the full address space in kernel mode - there is no need to check bounds.
	auto context = COP0->getCPUOperatingContext(getContext());
	if (context == MIPSCPUOperatingContext_t::User)
	{
		// Operating in user mode.
		if (!(virtualAddress <= Constants::MIPS::MMU::VADDRESS_USER_UPPER_BOUND))
		{
			handleMMUError(virtualAddress, access, ADDRESS, -1);
			return true;
		}
	}
	else if (context == MIPSCPUOperatingContext_t::Supervisor)
	{
		// Operating in supervisor mode.
		if (!((virtualAddress >= Constants::MIPS::MMU::VADDRESS_SUPERVISOR_LOWER_BOUND_2 && virtualAddress <= Constants::MIPS::MMU::VADDRESS_SUPERVISOR_UPPER_BOUND_1)
			|| (virtualAddress <= Constants::MIPS::MMU::VADDRESS_SUPERVISOR_UPPER_BOUND_2)))
		{
			handleMMUError(virtualAddress, access, ADDRESS, -1);
			return true;
		}
	}

	// Stage 2 - perform TLB lookup and perform checks.
	// If we are operating in kernel mode, then SOME addreses are unmapped, and we do not need to perform a TLB lookup.
	if (context == MIPSCPUOperatingContext_t::Kernel)
	{
		// Test for kseg0
		if (virtualAddress >= Constants::MIPS::MMU::MMU::VADDRESS_KERNEL_LOWER_BOUND_2 && virtualAddress <= Constants::MIPS::MMU::MMU::VADDRESS_KERNEL_UPPER_BOUND_2)
		{
			// We are in kseg0, so to get the physical address we just minus the kseg0 base address of 0x80000000.
			// We also do not test for the Config.K0 status, as we do not involve caches unless it is an explicit request.
			physicalAddress = (virtualAddress - Constants::MIPS::MMU::MMU::VADDRESS_KERNEL_LOWER_BOUND_2);
			return false;
		}

		// Test for kseg1
		if (virtualAddress >= Constants::MIPS::MMU::MMU::VADDRESS_KERNEL_LOWER_BOUND_3 && virtualAddress <= Constants::MIPS::MMU::MMU::VADDRESS_KERNEL_UPPER_BOUND_3)
		{
			// We are in kseg1, so to get the physical address we just minus the kseg1 base address of 0xA0000000.
			physicalAddress = (virtualAddress - Constants::MIPS::MMU::MMU::VADDRESS_KERNEL_LOWER_BOUND_3);
			return false;
		}

		// Test for Status.ERL = 1 (indicating kuseg is unmapped). Note that the VA still has to be within the segment bounds for this to work.
		if (COP0->Status->getFieldValue(getContext(), EECoreCOP0Register_Status_t::Fields::ERL) == 1) 
		{
			if (virtualAddress <= Constants::MIPS::MMU::MMU::VADDRESS_KERNEL_UPPER_BOUND_1)
			{
				// We are in kuseg unmapped region, so just return the VA.
				physicalAddress = virtualAddress;
				return false;
			}
		}
	}

	// Check if its in the TLB and get the information.
	s32 tlbIndex = TLB->findTLBIndex(virtualAddress);
	if (tlbIndex == -1)
	{
		handleMMUError(virtualAddress, access, TLB_REFILL, tlbIndex);
		return true;
	}
	auto& TLBEntry = TLB->getTLBEntry(tlbIndex);

	// Check the global bit, and check ASID if needed (against the ASID value in the EntryHi COP0 register).
	// TODO: Check if ASID checking is correct.
	if (TLBEntry.mG == 0)
	{
		// Not a global page map, need to make sure ASID's are the same.
		if (COP0->EntryHi->getFieldValue(getContext(), EECoreCOP0Register_EntryHi_t::Fields::ASID) != TLBEntry.mASID)
		{
			handleMMUError(virtualAddress, access, TLB_REFILL, tlbIndex);
			return true;
		}
	}

	// Stage 3 - Assess if the page is valid and it is marked dirty. Also check for the scratchpad ram access.
	// Check if accessing scratchpad.
	if (TLBEntry.mS)
	{
		// As mentioned in the TLB implementation (see the class EECoreTLB_t), the scratchpad ram is allocated in the TLB as a continuous block of 4 x 4KB pages (16KB).
		// This means that the VPN occupies the upper 18 bits, with the 2 next lower bits selecting which 4KB page we are in (0 -> 3).
		u32 offset16KB = virtualAddress & Constants::MASK_16KB;
		physicalAddress = 0x70000000 + offset16KB;
		return false;
	}

	// Need to check now before continuing if the VPN is for a even or odd page (0 = Even, 1 = Odd). 
	// This is done by checking the LSB of the VPN from the original address accessed.
	// Neat trick: +1 to the TLB mask to get the mask for the LSB of the VPN. Note that this mask is always equal to or greater than 4KB.
	u32 indexEvenOddMask = ((TLBEntry.mMask << 12) | 0xFFF) + 1;
	u8 TLBEvenOddIndex = (virtualAddress & indexEvenOddMask) ? 1 : 0;

	// Check if the entry is valid (V bit)
	if (!TLBEntry.PhysicalInfo[TLBEvenOddIndex].mV)
	{
		handleMMUError(virtualAddress, access, TLB_INVALID, tlbIndex);
		return true;
	}

	// Check if entry is allowed writes (dirty flag) and raise TLB modified exception if writing occurs.
	if (!TLBEntry.PhysicalInfo[TLBEvenOddIndex].mD && access == WRITE)
	{
		handleMMUError(virtualAddress, access, TLB_MODIFIED, tlbIndex);
		return true;
	}

	// Stage 4 - calculate final physical address from TLB entry.
	// Cache access?
	// TODO: Maybe we actually dont need this in the emulator as the C flag only describes the cache method, not a location. The location is still refering to main memory.
	/*
	if (tlbEntry.PhysicalInfo[mIndexEvenOdd].mC > 0)
	{
	}
	*/

	// We are accessing main memory - combine PFN with offset using the TLB entry mask, to get the physical address (PhyAddr = PFN (shifted) | Offset).
	u32 offsetMask = (TLBEntry.mMask << 12) | 0xFFF;
	physicalAddress = ((TLBEntry.PhysicalInfo[TLBEvenOddIndex].mPFN << 12) | (virtualAddress & offsetMask));
	return false;
}