#include "stdafx.h"

#include <stdexcept>

#include "Common/Types/Context_t.h"
#include "Common/Types/Registers/MIPS/PCRegister32_t.h"
#include "Common/Types/MIPSBranchDelay/MIPSBranchDelay_t.h"
#include "Common/Tables/EECoreExceptionsTable/EECoreExceptionsTable.h"

#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreExceptionHandler/EECoreExceptionHandler.h"

#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0Registers_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreException_t.h"

EECoreExceptionHandler::EECoreExceptionHandler(VMMain * vmMain) : 
	VMExecutionCoreComponent(vmMain), 
	mEECoreException(EECoreException_t::EX_RESET), 
	mExceptionProperties(nullptr)
{
}

void EECoreExceptionHandler::handleException(const EECoreException_t & exception)
{
#if defined(BUILD_DEBUG)
	DEBUG_HANDLED_EXCEPTION_COUNT += 1;
#endif

	// Set the PS2Exception pointer.
	mEECoreException = exception;

	// Get the exception properties.
	mExceptionProperties = EECoreExceptionsTable::getExceptionInfo(mEECoreException);

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
	auto& COP0 = getResources()->EE->EECore->COP0;
	auto& PC = getResources()->EE->EECore->R5900->PC;
	auto& BD = getResources()->EE->EECore->R5900->BD;

	// Vector offset value, used to set final vector address.
	u32 vectorOffset = 0x0;

	// Set Cause.ExeCode value.
	COP0->Cause->setFieldValue(EECoreCOP0Register_Cause_t::Fields::ExcCode, mExceptionProperties->mExeCode);

	// If already in exception handler (EXL == 1), do not update EPC and Cause.BD. Also use general exception handler vector.
	if (COP0->Status->getFieldValue(EECoreCOP0Register_Status_t::Fields::EXL) == 1)
	{
		vectorOffset = PS2Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_COMMON;
	}
	// Normal exception processing.
	else
	{
		// Set EPC and Cause.BD fields.
		// Note that the EPC register should point to the instruction that caused the exception - so it is always set to at least PC - 4.
		if (BD->isInBranchDelay())
		{
			u32 pcValue = PC->readWord(Context_t::EE) - Constants::SIZE_MIPS_INSTRUCTION * 2;
			COP0->EPC->writeWord(Context_t::EE, pcValue);
			COP0->Cause->setFieldValue(EECoreCOP0Register_Cause_t::Fields::BD, 1);
			BD->resetBranchDelay(); // Reset branch delay slot.
		}
		else
		{
			u32 pcValue = PC->readWord(Context_t::EE) - Constants::SIZE_MIPS_INSTRUCTION;
			COP0->EPC->writeWord(Context_t::EE, pcValue);
			COP0->Cause->setFieldValue(EECoreCOP0Register_Cause_t::Fields::BD, 0);
		}

		// Set to kernel mode and disable interrupts.
		COP0->Status->setFieldValue(EECoreCOP0Register_Status_t::Fields::EXL, 1);

		// Select the vector to use (set vectorOffset).
		if (mEECoreException == EECoreException_t::EX_TLB_REFILL_INSTRUCTION_FETCH_LOAD
			|| mEECoreException == EECoreException_t::EX_TLB_REFILL_STORE)
		{
			vectorOffset = PS2Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_TLB_REFILL;
		}
		else if (mEECoreException == EECoreException_t::EX_INTERRUPT)
		{
			vectorOffset = PS2Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_INTERRUPT;
		}
		else
		{
			vectorOffset = PS2Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_COMMON;
		}

		// Select vector base to use and set PC to use the specified vector.
		if (COP0->Status->getFieldValue(EECoreCOP0Register_Status_t::Fields::BEV) == 1)
		{
			PC->setPCValueAbsolute(PS2Constants::MIPS::Exceptions::Imp46::VADDRESS_EXCEPTION_BASE_A1 + vectorOffset);
		} 
		else
		{
			PC->setPCValueAbsolute(PS2Constants::MIPS::Exceptions::Imp46::VADDRESS_EXCEPTION_BASE_A0 + vectorOffset);
		}
	}
}

void EECoreExceptionHandler::handleException_L2() const
{
	// Exception level 2 handler code. Adapted from EE Core Users Manual page 92.
	auto& COP0 = getResources()->EE->EECore->COP0;
	auto& PC = getResources()->EE->EECore->R5900->PC;
	auto& BD = getResources()->EE->EECore->R5900->BD;

	// Vector offset value, used to set final vector address.
	u32 vectorOffset = 0x0;

	// Set Cause.EXC2 value.
	COP0->Cause->setFieldValue(EECoreCOP0Register_Cause_t::Fields::EXC2, mExceptionProperties->mEXC2);

	// Set EPC and Cause.BD fields.
	// Note that the EPC register should point to the instruction that caused the exception - so it is always set to at least PC - 4.
	if (BD->isInBranchDelay())
	{
		// TODO: no idea if this code works, yet to encounter a branch delay exception.
		u32 pcValue = PC->readWord(Context_t::EE) - Constants::SIZE_MIPS_INSTRUCTION * 2;
		COP0->ErrorEPC->writeWord(Context_t::EE, pcValue);
		COP0->Cause->setFieldValue(EECoreCOP0Register_Cause_t::Fields::BD2, 1);
		BD->resetBranchDelay(); // Reset branch delay slot.
	}
	else
	{
		u32 pcValue = PC->readWord(Context_t::EE) - Constants::SIZE_MIPS_INSTRUCTION;
		COP0->ErrorEPC->writeWord(Context_t::EE, pcValue);
		COP0->Cause->setFieldValue(EECoreCOP0Register_Cause_t::Fields::BD2, 0);
	}

	// Set to kernel mode and disable interrupts.
	COP0->Status->setFieldValue(EECoreCOP0Register_Status_t::Fields::ERL, 1);

	// Select vector to use and set PC to use it.
	if (mEECoreException == EECoreException_t::EX_NMI 
		|| mEECoreException == EECoreException_t::EX_RESET) 
	{
		PC->setPCValueAbsolute(PS2Constants::MIPS::Exceptions::Imp46::VADDRESS_EXCEPTION_BASE_V_RESET_NMI);
	}
	else
	{
		if (mEECoreException == EECoreException_t::EX_PERFORMANCE_COUNTER)
		{
			vectorOffset = PS2Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_COUNTER;
		}
		else if (mEECoreException == EECoreException_t::EX_DEBUG)
		{
			vectorOffset = PS2Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_DEBUG;
		}
		else
		{
			// Use V_TLB_REFIL (offset 0x00000000) (should get optimised out).
			vectorOffset = PS2Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_TLB_REFILL;
		}

		// Select vector base to use and set PC to use the specified vector.
		if (COP0->Status->getFieldValue(EECoreCOP0Register_Status_t::Fields::DEV) == 1)
		{
			PC->setPCValueAbsolute(PS2Constants::MIPS::Exceptions::Imp46::VADDRESS_EXCEPTION_BASE_A1 + vectorOffset);
		}
		else
		{
			PC->setPCValueAbsolute(PS2Constants::MIPS::Exceptions::Imp46::VADDRESS_EXCEPTION_BASE_A0 + vectorOffset);
		}
	}
}

void EECoreExceptionHandler::EX_HANDLER_RESET()
{
	auto& COP0 = getResources()->EE->EECore->COP0;

	// Initalise all of the COP0 registers.
	COP0->initalise();
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
	// No additional processing needed.
}

void EECoreExceptionHandler::EX_HANDLER_TLB_MODIFIED()
{
	// No additional processing needed.
}

void EECoreExceptionHandler::EX_HANDLER_TLB_REFILL_INSTRUCTION_FETCH_LOAD()
{
	// No additional processing needed.
}

void EECoreExceptionHandler::EX_HANDLER_TLB_REFILL_STORE()
{
	// No additional processing needed.
}

void EECoreExceptionHandler::EX_HANDLER_TLB_INVALID_INSTRUCTION_FETCH_LOAD()
{
	// No additional processing needed.
}

void EECoreExceptionHandler::EX_HANDLER_TLB_INVALID_STORE()
{
	// No additional processing needed.
}

void EECoreExceptionHandler::EX_HANDLER_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD()
{
	// No additional processing needed.
}

void EECoreExceptionHandler::EX_HANDLER_ADDRESS_ERROR_STORE()
{
	// No additional processing needed.
}

void EECoreExceptionHandler::EX_HANDLER_BUS_ERROR_INSTRUCTION_FETCH()
{
	// No additional processing needed.
}

void EECoreExceptionHandler::EX_HANDLER_BUS_ERROR_LOAD_STORE()
{
	// No additional processing needed.
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
	// No additional processing needed.
}

void EECoreExceptionHandler::EX_HANDLER_OVERFLOW()
{
	// No additional processing needed.
}

void EECoreExceptionHandler::EX_HANDLER_TRAP()
{
	// No additional processing needed.
}
