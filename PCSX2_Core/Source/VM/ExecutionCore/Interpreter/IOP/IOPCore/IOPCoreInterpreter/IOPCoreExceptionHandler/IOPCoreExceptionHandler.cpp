#include "stdafx.h"

#include <stdexcept>

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/IOP/IOPCore/IOPCoreInterpreter/IOPCoreExceptionHandler/IOPCoreExceptionHandler.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/IOP/IOP_t.h"
#include "Common/PS2Resources/IOP/IOPCore/IOPCore_t.h"
#include "Common/PS2Resources/IOP/IOPCore/R3000/R3000_t.h"
#include "Common/PS2Resources/Types/Registers/PCRegister32_t.h"
#include "Common/PS2Resources/IOP/IOPCore/IOPCoreCOP0/IOPCoreCOP0_t.h"
#include "Common/PS2Resources/IOP/IOPCore/IOPCoreCOP0/Types/IOPCore_COP0_Registers_t.h"
#include "Common/PS2Resources/Types/MIPSCoprocessor/COP0_BitfieldRegisters_t.h"
#include "Common/PS2Resources/IOP/IOPCore/IOPCoreExceptions/IOPCoreExceptions_t.h"
#include "Common/PS2Resources/IOP/IOPCore/IOPCoreExceptions/Types/IOPCoreException_t.h"
#include "Common/Tables/IOPExceptionsTable/IOPExceptionsTable.h"

IOPCoreExceptionHandler::IOPCoreExceptionHandler(VMMain * vmMain) : 
	VMExecutionCoreComponent(vmMain), 
	mClockSources{},
	mIOPException(nullptr), 
	mExceptionProperties(nullptr)
{
}

const std::vector<ClockSource_t>& IOPCoreExceptionHandler::getClockSources()
{
	return mClockSources;
}

void IOPCoreExceptionHandler::checkExceptionState()
{
	auto& Exceptions = getVM()->getResources()->IOP->IOPCore->Exceptions;
	if (Exceptions->hasExceptionOccurred())
	{
		handleException(Exceptions->getException());
	}
}

void IOPCoreExceptionHandler::handleException(const IOPCoreException_t& PS2Exception)
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
	logDebug("(%s, %d) IOPCoreExceptionHandler called! Type = %s", __FILENAME__, __LINE__, mExceptionProperties->mMnemonic);
#endif

	// Call the exception specific handler contained in the ExceptionProperties_t.
	(this->*EXCEPTION_HANDLERS[mExceptionProperties->mImplementationIndex])();

	// If its a reset exception, set PC to reset vector and return.
	if (mIOPException->mExType == IOPCoreException_t::ExType::EX_RESET)
	{
		getVM()->getResources()->IOP->IOPCore->R3000->PC->setPCValueAbsolute(PS2Constants::MIPS::Exceptions::VADDRESS_EXCEPTION_BASE_V_RESET_NMI);
		return;
	}

	// Perform general exception handler code.
	// Vector offset value, used to set final vector address.
	u32 vectorOffset = 0x0;

	// Set Cause.ExeCode value.
	getVM()->getResources()->IOP->IOPCore->COP0->Cause->setFieldValue(IOPCore_COP0RegisterCause_t::Fields::ExcCode, mExceptionProperties->mExeCode);

	// Set EPC and Cause.BD fields.
	if (getVM()->getResources()->IOP->IOPCore->R3000->isInBranchDelaySlot()) // Check if in the branch delay slot.
	{
		u32 pcValue = getVM()->getResources()->IOP->IOPCore->R3000->PC->getPCValue() - 4;
		getVM()->getResources()->IOP->IOPCore->COP0->EPC->setFieldValue(COP0RegisterEPC_t::Fields::EPC, pcValue);
		getVM()->getResources()->IOP->IOPCore->COP0->Cause->setFieldValue(IOPCore_COP0RegisterCause_t::Fields::BD, 1);
	}
	else
	{
		u32 pcValue = getVM()->getResources()->IOP->IOPCore->R3000->PC->getPCValue();
		getVM()->getResources()->IOP->IOPCore->COP0->EPC->setFieldValue(COP0RegisterEPC_t::Fields::EPC, pcValue);
		getVM()->getResources()->IOP->IOPCore->COP0->Cause->setFieldValue(IOPCore_COP0RegisterCause_t::Fields::BD, 0);
	}

	// Select the vector to use (set vectorOffset).
	if (mIOPException->mExType == IOPCoreException_t::ExType::EX_TLB_REFILL_INSTRUCTION_FETCH_LOAD
		|| mIOPException->mExType == IOPCoreException_t::ExType::EX_TLB_REFILL_STORE)
	{
		vectorOffset = PS2Constants::MIPS::Exceptions::OADDRESS_EXCEPTION_VECTOR_V_TLB_REFILL;
	}
	else if (mIOPException->mExType == IOPCoreException_t::ExType::EX_INTERRUPT)
	{
		vectorOffset = PS2Constants::MIPS::Exceptions::OADDRESS_EXCEPTION_VECTOR_V_INTERRUPT;
	}
	else
	{
		vectorOffset = PS2Constants::MIPS::Exceptions::OADDRESS_EXCEPTION_VECTOR_V_COMMON;
	}

	// Select vector base to use and set PC to use the specified vector.
	if (getVM()->getResources()->IOP->IOPCore->COP0->Status->getFieldValue(IOPCore_COP0RegisterStatus_t::Fields::BEV) == 1)
	{
		getVM()->getResources()->IOP->IOPCore->R3000->PC->setPCValueAbsolute(PS2Constants::MIPS::Exceptions::VADDRESS_EXCEPTION_BASE_A1 + vectorOffset);
	}
	else
	{
		getVM()->getResources()->IOP->IOPCore->R3000->PC->setPCValueAbsolute(PS2Constants::MIPS::Exceptions::VADDRESS_EXCEPTION_BASE_A0 + vectorOffset);
	}
	
}

void IOPCoreExceptionHandler::EX_HANDLER_INTERRUPT()
{
	auto& COP0 = getVM()->getResources()->IOP->IOPCore->COP0;
	
	// The EE Core Users Manual page 99 mentions that if an interrupt signal is asserted and deasserted in a very short time, the Cause.IP[i] may not
	//  be reliable to rely on for information. This may need investigation if the timing is critical to some games.
	// TODO: check for timing issues.
	
	// COP0->Cause->setFieldValue(IOPCore_COP0RegisterCause_t::Fields::IP2, mIOPException->mIntExceptionInfo.mInt1);
}

void IOPCoreExceptionHandler::EX_HANDLER_TLB_MODIFIED()
{
	auto& COP0 = getVM()->getResources()->IOP->IOPCore->COP0;

	throw std::runtime_error("IOP exception handler function not implemented.");
}

void IOPCoreExceptionHandler::EX_HANDLER_TLB_REFILL_INSTRUCTION_FETCH_LOAD()
{
	auto& COP0 = getVM()->getResources()->IOP->IOPCore->COP0;

	throw std::runtime_error("IOP exception handler function not implemented.");
}

void IOPCoreExceptionHandler::EX_HANDLER_TLB_REFILL_STORE()
{
	auto& COP0 = getVM()->getResources()->IOP->IOPCore->COP0;

	throw std::runtime_error("IOP exception handler function not implemented.");
}

void IOPCoreExceptionHandler::EX_HANDLER_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD()
{
	auto& COP0 = getVM()->getResources()->IOP->IOPCore->COP0;

	throw std::runtime_error("IOP exception handler function not implemented.");
}

void IOPCoreExceptionHandler::EX_HANDLER_ADDRESS_ERROR_STORE()
{
	auto& COP0 = getVM()->getResources()->IOP->IOPCore->COP0;

	throw std::runtime_error("IOP exception handler function not implemented.");
}

void IOPCoreExceptionHandler::EX_HANDLER_BUS_ERROR_INSTRUCTION_FETCH()
{
	// TODO: Look at later, but since this is an external interrupt which is not a part of normal operation, will probably never have to be implemented.
}

void IOPCoreExceptionHandler::EX_HANDLER_BUS_ERROR_LOAD_STORE()
{
	// TODO: Look at later, but since this is an external interrupt which is not a part of normal operation, will probably never have to be implemented.
}

void IOPCoreExceptionHandler::EX_HANDLER_SYSTEMCALL()
{
	// No additional processing needed.
}

void IOPCoreExceptionHandler::EX_HANDLER_BREAK()
{
	// No additional processing needed.
}

void IOPCoreExceptionHandler::EX_HANDLER_RESERVED_INSTRUCTION()
{
	// No additional processing needed.
}

void IOPCoreExceptionHandler::EX_HANDLER_COPROCESSOR_UNUSABLE()
{
	auto& COP0 = getVM()->getResources()->IOP->IOPCore->COP0;

	COP0->Cause->setFieldValue(IOPCore_COP0RegisterCause_t::Fields::CE, mIOPException->mCOPExceptionInfo.mCOPUnusable);
}

void IOPCoreExceptionHandler::EX_HANDLER_OVERFLOW()
{
	// No additional processing needed.
}

void IOPCoreExceptionHandler::EX_HANDLER_RESET()
{
	auto& COP0 = getVM()->getResources()->IOP->IOPCore->COP0;

	// Initalise all of the COP0 registers.
	COP0->initalise();

	COP0->Status->setFieldValue(IOPCore_COP0RegisterStatus_t::Fields::SwC, 0);
	COP0->Status->setFieldValue(IOPCore_COP0RegisterStatus_t::Fields::KUc, 0);
	COP0->Status->setFieldValue(IOPCore_COP0RegisterStatus_t::Fields::IEc, 0);
	COP0->Status->setFieldValue(IOPCore_COP0RegisterStatus_t::Fields::BEV, 1);
}