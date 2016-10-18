#include "stdafx.h"

#include <stdexcept>

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/IOP/IOPInterpreter/IOPExceptionHandler/IOPExceptionHandler.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/IOP/IOP_t.h"
#include "Common/PS2Resources/IOP/R3000/R3000_t.h"
#include "Common/PS2Resources/Types/Registers/PCRegister32_t.h"
#include "Common/PS2Resources/IOP/IOPCOP0/IOPCOP0_t.h"
#include "Common/PS2Resources/Types/MIPSCoprocessor/COP0_BitfieldRegisters_t.h"
#include "Common/PS2Resources/IOP/IOPExceptions/IOPExceptions_t.h"
#include "Common/PS2Resources/IOP/IOPExceptions/Types/IOPException_t.h"
#include "Common/Tables/IOPExceptionsTable/IOPExceptionsTable.h"

IOPExceptionHandler::IOPExceptionHandler(VMMain * vmMain) : 
	VMExecutionCoreComponent(vmMain), 
	mClockSources{},
	mIOPException(nullptr), 
	mExceptionProperties(nullptr)
{
}

const std::vector<ClockSource_t>& IOPExceptionHandler::getClockSources()
{
	return mClockSources;
}

void IOPExceptionHandler::checkExceptionState()
{
	auto& Exceptions = getVM()->getResources()->IOP->Exceptions;
	if (Exceptions->hasExceptionOccurred())
	{
		handleException(Exceptions->getException());
	}
}

void IOPExceptionHandler::handleException(const IOPException_t& PS2Exception)
{
#if defined(BUILD_DEBUG)
	DEBUG_HANDLED_EXCEPTION_COUNT += 1;
#endif

	// Set the PS2Exception pointer.
	mIOPException = &PS2Exception;

	// Get the exception properties.
	mExceptionProperties = IOPExceptionsTable::getExceptionInfo(PS2Exception.mExType);

#if defined(BUILD_DEBUG)
	// Debug print exception type.
	logDebug("(%s, %d) IOPExceptionHandler called! Type = %s", __FILENAME__, __LINE__, mExceptionProperties->mMnemonic);
#endif

	// Call the exception specific handler contained in the ExceptionProperties_t.
	(this->*EXCEPTION_HANDLERS[mExceptionProperties->mImplementationIndex])();

	// Perform general exception handler code.
	// Vector offset value, used to set final vector address.
	u32 vectorOffset = 0x0;

	// Set Cause.ExeCode value.
	getVM()->getResources()->IOP->COP0->Cause->setFieldValue(COP0RegisterCause_t::Fields::ExcCode, mExceptionProperties->mExeCode);

	// If already in exception handler (EXL == 1), do not update EPC and Cause.BD. Also use general exception handler vector.
	if (getVM()->getResources()->IOP->COP0->Status->getFieldValue(COP0RegisterStatus_t::Fields::EXL) == 1)
	{
		vectorOffset = PS2Constants::MIPS::Exceptions::OADDRESS_EXCEPTION_VECTOR_V_COMMON;
	}
	// Normal exception processing.
	else
	{
		// Set EPC and Cause.BD fields.
		if (getVM()->getResources()->IOP->R3000->isInBranchDelaySlot()) // Check if in the branch delay slot.
		{
			u32 pcValue = getVM()->getResources()->IOP->R3000->PC->getPCValue() - 4;
			getVM()->getResources()->IOP->COP0->EPC->setFieldValue(COP0RegisterEPC_t::Fields::EPC, pcValue);
			getVM()->getResources()->IOP->COP0->Cause->setFieldValue(COP0RegisterCause_t::Fields::BD, 1);
		}
		else
		{
			u32 pcValue = getVM()->getResources()->IOP->R3000->PC->getPCValue();
			getVM()->getResources()->IOP->COP0->EPC->setFieldValue(COP0RegisterEPC_t::Fields::EPC, pcValue);
			getVM()->getResources()->IOP->COP0->Cause->setFieldValue(COP0RegisterCause_t::Fields::BD, 0);
		}

		// Set to kernel mode and disable interrupts.
		getVM()->getResources()->IOP->COP0->Status->setFieldValue(COP0RegisterStatus_t::Fields::EXL, 1);

		// If its a reset exception, set PC to reset vector and return.
		if (mIOPException->mExType == IOPException_t::ExType::EX_RESET)
		{
			getVM()->getResources()->IOP->R3000->PC->setPCValueAbsolute(PS2Constants::MIPS::Exceptions::VADDRESS_EXCEPTION_BASE_V_RESET_NMI);
			return;
		}

		// Select the vector to use (set vectorOffset).
		if (mIOPException->mExType == IOPException_t::ExType::EX_TLB_REFILL_INSTRUCTION_FETCH_LOAD
			|| mIOPException->mExType == IOPException_t::ExType::EX_TLB_REFILL_STORE)
		{
			vectorOffset = PS2Constants::MIPS::Exceptions::OADDRESS_EXCEPTION_VECTOR_V_TLB_REFILL;
		}
		else if (mIOPException->mExType == IOPException_t::ExType::EX_INTERRUPT)
		{
			vectorOffset = PS2Constants::MIPS::Exceptions::OADDRESS_EXCEPTION_VECTOR_V_INTERRUPT;
		}
		else
		{
			vectorOffset = PS2Constants::MIPS::Exceptions::OADDRESS_EXCEPTION_VECTOR_V_COMMON;
		}

		// Select vector base to use and set PC to use the specified vector.
		if (getVM()->getResources()->IOP->COP0->Status->getFieldValue(COP0RegisterStatus_t::Fields::BEV) == 1)
		{
			getVM()->getResources()->IOP->R3000->PC->setPCValueAbsolute(PS2Constants::MIPS::Exceptions::VADDRESS_EXCEPTION_BASE_A1 + vectorOffset);
		}
		else
		{
			getVM()->getResources()->IOP->R3000->PC->setPCValueAbsolute(PS2Constants::MIPS::Exceptions::VADDRESS_EXCEPTION_BASE_A0 + vectorOffset);
		}
	}
	
}

void IOPExceptionHandler::EX_HANDLER_INTERRUPT()
{
	auto& COP0 = getVM()->getResources()->IOP->COP0;
	
	// The EE Core Users Manual page 99 mentions that if an interrupt signal is asserted and deasserted in a very short time, the Cause.IP[i] may not
	//  be reliable to rely on for information. This may need investigation if the timing is critical to some games.
	// TODO: check for timing issues.
	
	// COP0->Cause->setFieldValue(COP0RegisterCause_t::Fields::IP2, mIOPException->mIntExceptionInfo.mInt1);
}

void IOPExceptionHandler::EX_HANDLER_TLB_MODIFIED()
{
	auto& COP0 = getVM()->getResources()->IOP->COP0;

	COP0->BadVAddr->setFieldValue(COP0RegisterBadVAddr_t::Fields::BadVAddr, mIOPException->mTLBExceptionInfo.mPS2VirtualAddress);
	COP0->Context->setFieldValue(COP0RegisterContext_t::Fields::PTEBase, mIOPException->mTLBExceptionInfo.mPageTableAddress);
	COP0->Context->setFieldValue(COP0RegisterContext_t::Fields::BadVPN2, mIOPException->mTLBExceptionInfo.mPS2VirtualAddress_HI_19);
	COP0->EntryHi->setFieldValue(COP0RegisterEntryHi_t::Fields::VPN2, mIOPException->mTLBExceptionInfo.mPS2VirtualAddress_HI_19);
	COP0->EntryHi->setFieldValue(COP0RegisterEntryHi_t::Fields::ASID, mIOPException->mTLBExceptionInfo.mASID);
	COP0->EntryLo0->setRegisterValue(0);
	COP0->EntryLo1->setRegisterValue(0);
}

void IOPExceptionHandler::EX_HANDLER_TLB_REFILL_INSTRUCTION_FETCH_LOAD()
{
	auto& COP0 = getVM()->getResources()->IOP->COP0;

	COP0->BadVAddr->setFieldValue(COP0RegisterBadVAddr_t::Fields::BadVAddr, mIOPException->mTLBExceptionInfo.mPS2VirtualAddress);
	COP0->Context->setFieldValue(COP0RegisterContext_t::Fields::PTEBase, mIOPException->mTLBExceptionInfo.mPageTableAddress);
	COP0->Context->setFieldValue(COP0RegisterContext_t::Fields::BadVPN2, mIOPException->mTLBExceptionInfo.mPS2VirtualAddress_HI_19);
	COP0->EntryHi->setFieldValue(COP0RegisterEntryHi_t::Fields::VPN2, mIOPException->mTLBExceptionInfo.mPS2VirtualAddress_HI_19);
	COP0->EntryHi->setFieldValue(COP0RegisterEntryHi_t::Fields::ASID, mIOPException->mTLBExceptionInfo.mASID);
	COP0->EntryLo0->setRegisterValue(0);
	COP0->EntryLo1->setRegisterValue(0);
	COP0->Random->setFieldValue(COP0RegisterRandom_t::Fields::Random, mIOPException->mTLBExceptionInfo.mTLBIndex);
}

void IOPExceptionHandler::EX_HANDLER_TLB_REFILL_STORE()
{
	auto& COP0 = getVM()->getResources()->IOP->COP0;

	COP0->BadVAddr->setFieldValue(COP0RegisterBadVAddr_t::Fields::BadVAddr, mIOPException->mTLBExceptionInfo.mPS2VirtualAddress);
	COP0->Context->setFieldValue(COP0RegisterContext_t::Fields::PTEBase, mIOPException->mTLBExceptionInfo.mPageTableAddress);
	COP0->Context->setFieldValue(COP0RegisterContext_t::Fields::BadVPN2, mIOPException->mTLBExceptionInfo.mPS2VirtualAddress_HI_19);
	COP0->EntryHi->setFieldValue(COP0RegisterEntryHi_t::Fields::VPN2, mIOPException->mTLBExceptionInfo.mPS2VirtualAddress_HI_19);
	COP0->EntryHi->setFieldValue(COP0RegisterEntryHi_t::Fields::ASID, mIOPException->mTLBExceptionInfo.mASID);
	COP0->EntryLo0->setRegisterValue(0);
	COP0->EntryLo1->setRegisterValue(0);
	COP0->Random->setFieldValue(COP0RegisterRandom_t::Fields::Random, mIOPException->mTLBExceptionInfo.mTLBIndex);
}

void IOPExceptionHandler::EX_HANDLER_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD()
{
	auto& COP0 = getVM()->getResources()->IOP->COP0;

	COP0->BadVAddr->setFieldValue(COP0RegisterBadVAddr_t::Fields::BadVAddr, mIOPException->mTLBExceptionInfo.mPS2VirtualAddress);
	COP0->Context->setRegisterValue(0);
	COP0->EntryHi->setFieldValue(COP0RegisterEntryHi_t::Fields::VPN2, 0);
	COP0->EntryLo0->setRegisterValue(0);
	COP0->EntryLo1->setRegisterValue(0);
}

void IOPExceptionHandler::EX_HANDLER_ADDRESS_ERROR_STORE()
{
	auto& COP0 = getVM()->getResources()->IOP->COP0;

	COP0->BadVAddr->setFieldValue(COP0RegisterBadVAddr_t::Fields::BadVAddr, mIOPException->mTLBExceptionInfo.mPS2VirtualAddress);
	COP0->Context->setRegisterValue(0);
	COP0->EntryHi->setFieldValue(COP0RegisterEntryHi_t::Fields::VPN2, 0);
	COP0->EntryLo0->setRegisterValue(0);
	COP0->EntryLo1->setRegisterValue(0);
}

void IOPExceptionHandler::EX_HANDLER_BUS_ERROR_INSTRUCTION_FETCH()
{
	// TODO: Look at later, but since this is an external interrupt which is not a part of normal operation, will probably never have to be implemented.
}

void IOPExceptionHandler::EX_HANDLER_BUS_ERROR_LOAD_STORE()
{
	// TODO: Look at later, but since this is an external interrupt which is not a part of normal operation, will probably never have to be implemented.
}

void IOPExceptionHandler::EX_HANDLER_SYSTEMCALL()
{
	// No additional processing needed.
}

void IOPExceptionHandler::EX_HANDLER_BREAK()
{
	// No additional processing needed.
}

void IOPExceptionHandler::EX_HANDLER_RESERVED_INSTRUCTION()
{
	// No additional processing needed.
}

void IOPExceptionHandler::EX_HANDLER_COPROCESSOR_UNUSABLE()
{
	auto& COP0 = getVM()->getResources()->IOP->COP0;

	COP0->Cause->setFieldValue(COP0RegisterCause_t::Fields::CE, mIOPException->mCOPExceptionInfo.mCOPUnusable);
}

void IOPExceptionHandler::EX_HANDLER_OVERFLOW()
{
	// No additional processing needed.
}

void IOPExceptionHandler::EX_HANDLER_RESET()
{
	auto& COP0 = getVM()->getResources()->IOP->COP0;

	// Initalise all of the COP0 registers.
	COP0->initalise();

	COP0->Status->setFieldValue(COP0RegisterStatus_t::Fields::ERL, 1);
	COP0->Status->setFieldValue(COP0RegisterStatus_t::Fields::BEV, 1);
	COP0->Status->setFieldValue(COP0RegisterStatus_t::Fields::BEM, 0);

	COP0->Config->setFieldValue(COP0RegisterConfig_t::Fields::DIE, 0);
	COP0->Config->setFieldValue(COP0RegisterConfig_t::Fields::ICE, 0);
	COP0->Config->setFieldValue(COP0RegisterConfig_t::Fields::DCE, 0);
	COP0->Config->setFieldValue(COP0RegisterConfig_t::Fields::NBE, 0);
	COP0->Config->setFieldValue(COP0RegisterConfig_t::Fields::BPE, 0);

	COP0->Random->setFieldValue(COP0RegisterRandom_t::Fields::Random, 47);

	COP0->Wired->setFieldValue(COP0RegisterWired_t::Fields::Wired, 0);
}