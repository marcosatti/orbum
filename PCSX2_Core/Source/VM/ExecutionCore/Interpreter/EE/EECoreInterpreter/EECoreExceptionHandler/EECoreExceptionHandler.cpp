#include "stdafx.h"

#include <stdexcept>

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreExceptionHandler/EECoreExceptionHandler.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "Common/Types/Registers/PCRegister32_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0Registers_t.h"
#include "Common/Types/MIPSCoprocessor/COP0Registers_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreExceptions_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreException_t.h"
#include "Common/Tables/EECoreExceptionsTable/EECoreExceptionsTable.h"

EECoreExceptionHandler::EECoreExceptionHandler(VMMain * vmMain) : 
	VMExecutionCoreComponent(vmMain), 
	mEECoreException(nullptr), 
	mExceptionProperties(nullptr)
{
}

void EECoreExceptionHandler::checkExceptionState()
{
	auto& Exceptions = getResources()->EE->EECore->Exceptions;
	if (Exceptions->hasExceptionOccurred())
	{
		handleException(Exceptions->getException());
	}
}

void EECoreExceptionHandler::handleException(const EECoreException_t& PS2Exception)
{
#if defined(BUILD_DEBUG)
	DEBUG_HANDLED_EXCEPTION_COUNT += 1;
#endif

	// Set the PS2Exception pointer.
	mEECoreException = &PS2Exception;

	// Get the exception properties.
	mExceptionProperties = EECoreExceptionsTable::getExceptionInfo(PS2Exception.mExType);

#if 0 // defined(BUILD_DEBUG)
	// Debug print exception type.
	logDebug("EECore ExceptionHandler called! Type = %s", mExceptionProperties->mMnemonic);
#endif

	// Call the exception specific handler contained in the ExceptionProperties_t.
	(this->*EXCEPTION_HANDLERS[mExceptionProperties->mImplementationIndex])();

	// Call the Level 1 or Level 2 exception handler based on the exception, or throw runtime_error if exception type/properties does not exist.
	switch(mExceptionProperties->mLevel)
	{
	case 1:
		handleException_L1(); break;
	case 2:
		handleException_L2(); break;
	default:
		throw std::runtime_error("PS2Exception parsed contained an unknown exception type.");
	}
}

void EECoreExceptionHandler::handleException_L1() const
{
	// Exception level 1 handler code. Adapted from EE Core Users Manual page 91.

	// Vector offset value, used to set final vector address.
	u32 vectorOffset = 0x0;

	// Set Cause.ExeCode value.
	getResources()->EE->EECore->COP0->Cause->setFieldValue(EECoreCOP0Register_Cause_t::Fields::ExcCode, mExceptionProperties->mExeCode);

	// If already in exception handler (EXL == 1), do not update EPC and Cause.BD. Also use general exception handler vector.
	if (getResources()->EE->EECore->COP0->Status->getFieldValue(EECoreCOP0Register_Status_t::Fields::EXL) == 1)
	{
		vectorOffset = PS2Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_COMMON;
	}
	// Normal exception processing.
	else
	{
		// Set EPC and Cause.BD fields.
		// Note that the EPC register should point to the instruction that caused the exception - so it is always set to at least PC - 4.
		if (getResources()->EE->EECore->R5900->isInBranchDelaySlot())
		{
			// TODO: no idea if this code works, yet to encounter a branch delay exception.
			u32 pcValue = getResources()->EE->EECore->R5900->PC->readWord() - Constants::SIZE_MIPS_INSTRUCTION * 2;
			getResources()->EE->EECore->COP0->EPC->setFieldValue(COP0RegisterEPC_t::Fields::EPC, pcValue);
			getResources()->EE->EECore->COP0->Cause->setFieldValue(EECoreCOP0Register_Cause_t::Fields::BD, 1);
		}
		else
		{
			u32 pcValue = getResources()->EE->EECore->R5900->PC->readWord() - Constants::SIZE_MIPS_INSTRUCTION;
			getResources()->EE->EECore->COP0->EPC->setFieldValue(COP0RegisterEPC_t::Fields::EPC, pcValue);
			getResources()->EE->EECore->COP0->Cause->setFieldValue(EECoreCOP0Register_Cause_t::Fields::BD, 0);
		}

		// Set to kernel mode and disable interrupts.
		getResources()->EE->EECore->COP0->Status->setFieldValue(EECoreCOP0Register_Status_t::Fields::EXL, 1);

		// Select the vector to use (set vectorOffset).
		if (mEECoreException->mExType == ExType::EX_TLB_REFILL_INSTRUCTION_FETCH_LOAD
			|| mEECoreException->mExType == ExType::EX_TLB_REFILL_STORE)
		{
			vectorOffset = PS2Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_TLB_REFILL;
		}
		else if (mEECoreException->mExType == ExType::EX_INTERRUPT)
		{
			vectorOffset = PS2Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_INTERRUPT;
		}
		else
		{
			vectorOffset = PS2Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_COMMON;
		}

		// Select vector base to use and set PC to use the specified vector.
		if (getResources()->EE->EECore->COP0->Status->getFieldValue(EECoreCOP0Register_Status_t::Fields::BEV) == 1)
		{
			getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(PS2Constants::MIPS::Exceptions::Imp46::VADDRESS_EXCEPTION_BASE_A1 + vectorOffset);
		} 
		else
		{
			getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(PS2Constants::MIPS::Exceptions::Imp46::VADDRESS_EXCEPTION_BASE_A0 + vectorOffset);
		}
	}
}

void EECoreExceptionHandler::handleException_L2() const
{
	// Exception level 2 handler code. Adapted from EE Core Users Manual page 92.

	// Vector offset value, used to set final vector address.
	u32 vectorOffset = 0x0;

	// Set Cause.EXC2 value.
	getResources()->EE->EECore->COP0->Cause->setFieldValue(EECoreCOP0Register_Cause_t::Fields::EXC2, mExceptionProperties->mEXC2);

	// Set EPC and Cause.BD fields.
	// Note that the EPC register should point to the instruction that caused the exception - so it is always set to at least PC - 4.
	if (getResources()->EE->EECore->R5900->isInBranchDelaySlot())
	{
		// TODO: no idea if this code works, yet to encounter a branch delay exception.
		u32 pcValue = getResources()->EE->EECore->R5900->PC->readWord() - Constants::SIZE_MIPS_INSTRUCTION * 2;
		getResources()->EE->EECore->COP0->ErrorEPC->setFieldValue(EECoreCOP0Register_ErrorEPC_t::Fields::ErrorEPC, pcValue);
		getResources()->EE->EECore->COP0->Cause->setFieldValue(EECoreCOP0Register_Cause_t::Fields::BD2, 1);
	}
	else
	{
		u32 pcValue = getResources()->EE->EECore->R5900->PC->readWord() - Constants::SIZE_MIPS_INSTRUCTION;
		getResources()->EE->EECore->COP0->ErrorEPC->setFieldValue(EECoreCOP0Register_ErrorEPC_t::Fields::ErrorEPC, pcValue);
		getResources()->EE->EECore->COP0->Cause->setFieldValue(EECoreCOP0Register_Cause_t::Fields::BD2, 0);
	}

	// Set to kernel mode and disable interrupts.
	getResources()->EE->EECore->COP0->Status->setFieldValue(EECoreCOP0Register_Status_t::Fields::ERL, 1);

	// Select vector to use and set PC to use it.
	if (mEECoreException->mExType == ExType::EX_NMI 
		|| mEECoreException->mExType == ExType::EX_RESET) 
	{
		getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(PS2Constants::MIPS::Exceptions::Imp46::VADDRESS_EXCEPTION_BASE_V_RESET_NMI);
	}
	else
	{
		if (mEECoreException->mExType == ExType::EX_PERFORMANCE_COUNTER)
		{
			vectorOffset = PS2Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_COUNTER;
		}
		else if (mEECoreException->mExType == ExType::EX_DEBUG)
		{
			vectorOffset = PS2Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_DEBUG;
		}
		else
		{
			// Use V_TLB_REFIL (offset 0x00000000) (should get optimised out).
			vectorOffset = PS2Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_TLB_REFILL;
		}

		// Select vector base to use and set PC to use the specified vector.
		if (getResources()->EE->EECore->COP0->Status->getFieldValue(EECoreCOP0Register_Status_t::Fields::DEV) == 1)
		{
			getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(PS2Constants::MIPS::Exceptions::Imp46::VADDRESS_EXCEPTION_BASE_A1 + vectorOffset);
		}
		else
		{
			getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(PS2Constants::MIPS::Exceptions::Imp46::VADDRESS_EXCEPTION_BASE_A0 + vectorOffset);
		}
	}
}

void EECoreExceptionHandler::EX_HANDLER_RESET()
{
	auto& COP0 = getResources()->EE->EECore->COP0;

	// Initalise all of the COP0 registers.
	COP0->initalise();
	
	// Other funcionality in "operation", just in case the inital values are different.
	COP0->Status->setFieldValue(EECoreCOP0Register_Status_t::Fields::ERL, 1);
	COP0->Status->setFieldValue(EECoreCOP0Register_Status_t::Fields::BEV, 1);
	COP0->Status->setFieldValue(EECoreCOP0Register_Status_t::Fields::BEM, 0);

	COP0->Cause->setFieldValue(EECoreCOP0Register_Cause_t::Fields::EXC2, 0);

	COP0->Config->setFieldValue(EECoreCOP0Register_Config_t::Fields::DIE, 0);
	COP0->Config->setFieldValue(EECoreCOP0Register_Config_t::Fields::ICE, 0);
	COP0->Config->setFieldValue(EECoreCOP0Register_Config_t::Fields::DCE, 0);
	COP0->Config->setFieldValue(EECoreCOP0Register_Config_t::Fields::NBE, 0);
	COP0->Config->setFieldValue(EECoreCOP0Register_Config_t::Fields::BPE, 0);

	COP0->Random->setFieldValue(EECoreCOP0Register_Random_t::Fields::Random, 47);

	COP0->Wired->setFieldValue(EECoreCOP0Register_Wired_t::Fields::Wired, 0);

	// I think this is a typo. In manual it says CCR.CTE where it should be PCCR.CTE.
	COP0->PCCR->setFieldValue(EECoreCOP0Register_PCCR_t::Fields::CTE, 0);

	COP0->BPC->setFieldValue(EECoreCOP0Register_BPC_t::Fields::IAE, 0);
	COP0->BPC->setFieldValue(EECoreCOP0Register_BPC_t::Fields::DRE, 0);
	COP0->BPC->setFieldValue(EECoreCOP0Register_BPC_t::Fields::DWE, 0);

	// TODO: Set cache flags (data and instruction caches) as described.
}

void EECoreExceptionHandler::EX_HANDLER_NMI()
{
	auto& COP0 = getResources()->EE->EECore->COP0;
	COP0->Status->setFieldValue(EECoreCOP0Register_Status_t::Fields::ERL, 1);
	COP0->Status->setFieldValue(EECoreCOP0Register_Status_t::Fields::BEV, 1);
}

void EECoreExceptionHandler::EX_HANDLER_PERFORMANCE_COUNTER()
{
	// No additional processing needed.
}

void EECoreExceptionHandler::EX_HANDLER_DEBUG()
{
	// No additional processing needed.
}

void EECoreExceptionHandler::EX_HANDLER_INTERRUPT()
{
	auto& COP0 = getResources()->EE->EECore->COP0;
	
	// The EE Core Users Manual page 99 mentions that if an interrupt signal is asserted and deasserted in a very short time, the Cause.IP[i] may not
	//  be reliable to rely on for information. This may need investigation if the timing is critical to some games.
	// TODO: check for timing issues.
	COP0->Cause->setFieldValue(EECoreCOP0Register_Cause_t::Fields::IP2, mEECoreException->mIntExceptionInfo.mInt1);
	COP0->Cause->setFieldValue(EECoreCOP0Register_Cause_t::Fields::IP3, mEECoreException->mIntExceptionInfo.mInt0);
	COP0->Cause->setFieldValue(EECoreCOP0Register_Cause_t::Fields::IP7, mEECoreException->mIntExceptionInfo.mTimerInt);
}

void EECoreExceptionHandler::EX_HANDLER_TLB_MODIFIED()
{
	auto& COP0 = getResources()->EE->EECore->COP0;

	COP0->BadVAddr->setFieldValue(EECoreCOP0Register_BadVAddr_t::Fields::BadVAddr, mEECoreException->mTLBExceptionInfo.mPS2VirtualAddress);
	COP0->Context->setFieldValue(EECoreCOP0Register_Context_t::Fields::PTEBase, mEECoreException->mTLBExceptionInfo.mPageTableAddress);
	COP0->Context->setFieldValue(EECoreCOP0Register_Context_t::Fields::BadVPN2, mEECoreException->mTLBExceptionInfo.mPS2VirtualAddress_HI_19);
	COP0->EntryHi->setFieldValue(EECoreCOP0Register_EntryHi_t::Fields::VPN2, mEECoreException->mTLBExceptionInfo.mPS2VirtualAddress_HI_19);
	COP0->EntryHi->setFieldValue(EECoreCOP0Register_EntryHi_t::Fields::ASID, mEECoreException->mTLBExceptionInfo.mASID);
	COP0->EntryLo0->writeWord(0);
	COP0->EntryLo1->writeWord(0);
}

void EECoreExceptionHandler::EX_HANDLER_TLB_REFILL_INSTRUCTION_FETCH_LOAD()
{
	auto& COP0 = getResources()->EE->EECore->COP0;

	COP0->BadVAddr->setFieldValue(EECoreCOP0Register_BadVAddr_t::Fields::BadVAddr, mEECoreException->mTLBExceptionInfo.mPS2VirtualAddress);
	COP0->Context->setFieldValue(EECoreCOP0Register_Context_t::Fields::PTEBase, mEECoreException->mTLBExceptionInfo.mPageTableAddress);
	COP0->Context->setFieldValue(EECoreCOP0Register_Context_t::Fields::BadVPN2, mEECoreException->mTLBExceptionInfo.mPS2VirtualAddress_HI_19);
	COP0->EntryHi->setFieldValue(EECoreCOP0Register_EntryHi_t::Fields::VPN2, mEECoreException->mTLBExceptionInfo.mPS2VirtualAddress_HI_19);
	COP0->EntryHi->setFieldValue(EECoreCOP0Register_EntryHi_t::Fields::ASID, mEECoreException->mTLBExceptionInfo.mASID);
	COP0->EntryLo0->writeWord(0);
	COP0->EntryLo1->writeWord(0);
	COP0->Random->setFieldValue(EECoreCOP0Register_Random_t::Fields::Random, mEECoreException->mTLBExceptionInfo.mTLBIndex);
}

void EECoreExceptionHandler::EX_HANDLER_TLB_REFILL_STORE()
{
	auto& COP0 = getResources()->EE->EECore->COP0;

	COP0->BadVAddr->setFieldValue(EECoreCOP0Register_BadVAddr_t::Fields::BadVAddr, mEECoreException->mTLBExceptionInfo.mPS2VirtualAddress);
	COP0->Context->setFieldValue(EECoreCOP0Register_Context_t::Fields::PTEBase, mEECoreException->mTLBExceptionInfo.mPageTableAddress);
	COP0->Context->setFieldValue(EECoreCOP0Register_Context_t::Fields::BadVPN2, mEECoreException->mTLBExceptionInfo.mPS2VirtualAddress_HI_19);
	COP0->EntryHi->setFieldValue(EECoreCOP0Register_EntryHi_t::Fields::VPN2, mEECoreException->mTLBExceptionInfo.mPS2VirtualAddress_HI_19);
	COP0->EntryHi->setFieldValue(EECoreCOP0Register_EntryHi_t::Fields::ASID, mEECoreException->mTLBExceptionInfo.mASID);
	COP0->EntryLo0->writeWord(0);
	COP0->EntryLo1->writeWord(0);
	COP0->Random->setFieldValue(EECoreCOP0Register_Random_t::Fields::Random, mEECoreException->mTLBExceptionInfo.mTLBIndex);
}

void EECoreExceptionHandler::EX_HANDLER_TLB_INVALID_INSTRUCTION_FETCH_LOAD()
{
	auto& COP0 = getResources()->EE->EECore->COP0;
	auto& Exceptions = getResources()->EE->EECore->Exceptions;

	COP0->BadVAddr->setFieldValue(EECoreCOP0Register_BadVAddr_t::Fields::BadVAddr, mEECoreException->mTLBExceptionInfo.mPS2VirtualAddress);
	COP0->Context->setFieldValue(EECoreCOP0Register_Context_t::Fields::PTEBase, mEECoreException->mTLBExceptionInfo.mPageTableAddress);
	COP0->Context->setFieldValue(EECoreCOP0Register_Context_t::Fields::BadVPN2, mEECoreException->mTLBExceptionInfo.mPS2VirtualAddress_HI_19);
	COP0->EntryHi->setFieldValue(EECoreCOP0Register_EntryHi_t::Fields::VPN2, mEECoreException->mTLBExceptionInfo.mPS2VirtualAddress_HI_19);
	COP0->EntryHi->setFieldValue(EECoreCOP0Register_EntryHi_t::Fields::ASID, mEECoreException->mTLBExceptionInfo.mASID);
	COP0->EntryLo0->writeWord(0);
	COP0->EntryLo1->writeWord(0);
	COP0->Random->setFieldValue(EECoreCOP0Register_Random_t::Fields::Random, mEECoreException->mTLBExceptionInfo.mTLBIndex);
}

void EECoreExceptionHandler::EX_HANDLER_TLB_INVALID_STORE()
{
	auto& COP0 = getResources()->EE->EECore->COP0;

	COP0->BadVAddr->setFieldValue(EECoreCOP0Register_BadVAddr_t::Fields::BadVAddr, mEECoreException->mTLBExceptionInfo.mPS2VirtualAddress);
	COP0->Context->setFieldValue(EECoreCOP0Register_Context_t::Fields::PTEBase, mEECoreException->mTLBExceptionInfo.mPageTableAddress);
	COP0->Context->setFieldValue(EECoreCOP0Register_Context_t::Fields::BadVPN2, mEECoreException->mTLBExceptionInfo.mPS2VirtualAddress_HI_19);
	COP0->EntryHi->setFieldValue(EECoreCOP0Register_EntryHi_t::Fields::VPN2, mEECoreException->mTLBExceptionInfo.mPS2VirtualAddress_HI_19);
	COP0->EntryHi->setFieldValue(EECoreCOP0Register_EntryHi_t::Fields::ASID, mEECoreException->mTLBExceptionInfo.mASID);
	COP0->EntryLo0->writeWord(0);
	COP0->EntryLo1->writeWord(0);
	COP0->Random->setFieldValue(EECoreCOP0Register_Random_t::Fields::Random, mEECoreException->mTLBExceptionInfo.mTLBIndex);
}

void EECoreExceptionHandler::EX_HANDLER_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD()
{
	auto& COP0 = getResources()->EE->EECore->COP0;

	COP0->BadVAddr->setFieldValue(EECoreCOP0Register_BadVAddr_t::Fields::BadVAddr, mEECoreException->mTLBExceptionInfo.mPS2VirtualAddress);
	COP0->Context->writeWord(0);
	COP0->EntryHi->setFieldValue(EECoreCOP0Register_EntryHi_t::Fields::VPN2, 0);
	COP0->EntryLo0->writeWord(0);
	COP0->EntryLo1->writeWord(0);
}

void EECoreExceptionHandler::EX_HANDLER_ADDRESS_ERROR_STORE()
{
	auto& COP0 = getResources()->EE->EECore->COP0;

	COP0->BadVAddr->setFieldValue(EECoreCOP0Register_BadVAddr_t::Fields::BadVAddr, mEECoreException->mTLBExceptionInfo.mPS2VirtualAddress);
	COP0->Context->writeWord(0);
	COP0->EntryHi->setFieldValue(EECoreCOP0Register_EntryHi_t::Fields::VPN2, 0);
	COP0->EntryLo0->writeWord(0);
	COP0->EntryLo1->writeWord(0);
}

void EECoreExceptionHandler::EX_HANDLER_BUS_ERROR_INSTRUCTION_FETCH()
{
	// TODO: Look at later, but since this is an external interrupt which is not a part of normal operation, will probably never have to be implemented.
}

void EECoreExceptionHandler::EX_HANDLER_BUS_ERROR_LOAD_STORE()
{
	// TODO: Look at later, but since this is an external interrupt which is not a part of normal operation, will probably never have to be implemented.
}

void EECoreExceptionHandler::EX_HANDLER_SYSTEMCALL()
{
	// No additional processing needed.
}

void EECoreExceptionHandler::EX_HANDLER_BREAK()
{
	// No additional processing needed.
}

void EECoreExceptionHandler::EX_HANDLER_RESERVED_INSTRUCTION()
{
	// No additional processing needed.
}

void EECoreExceptionHandler::EX_HANDLER_COPROCESSOR_UNUSABLE()
{
	auto& COP0 = getResources()->EE->EECore->COP0;

	COP0->Cause->setFieldValue(EECoreCOP0Register_Cause_t::Fields::CE, mEECoreException->mCOPExceptionInfo.mCOPUnusable);
}

void EECoreExceptionHandler::EX_HANDLER_OVERFLOW()
{
	// No additional processing needed.
}

void EECoreExceptionHandler::EX_HANDLER_TRAP()
{
	// No additional processing needed.
}
