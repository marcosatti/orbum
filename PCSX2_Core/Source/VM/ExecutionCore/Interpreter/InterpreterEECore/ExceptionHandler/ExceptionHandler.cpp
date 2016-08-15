#include "stdafx.h"

#include <stdexcept>

#include "VM/ExecutionCore/Interpreter/InterpreterEECore/ExceptionHandler/ExceptionHandler.h"
#include "Common/Interfaces/VMExecutionCoreComponent.h"
#include "Common/Types/PS2Exception/PS2Exception_t.h"
#include "Common/PS2 Resources/EE/EECore/COP0/Types/COP0_BitfieldRegisters_t.h"
#include "VM/VMMain.h"


ExceptionHandler::ExceptionHandler(const VMMain *const vmMain) : VMExecutionCoreComponent(vmMain)
{
}

void ExceptionHandler::handleException(const PS2Exception_t& PS2Exception)
{
	// Call the super class method. Contains useful debugging info if needed.
#if defined(BUILD_DEBUG)
	DEBUG_HANDLED_EXCEPTION_COUNT += 1;
#endif

	// Call the Level 1 or Level 2 exception handler based on the exception, or throw runtime_error if exception type/properties does not exist.
	const ExceptionProperties_t & exceptionProperties = ExceptionProperties[PS2Exception.getExceptionType()];
	switch(exceptionProperties.mLevel)
	{
	case 1:
		handleException_L1(exceptionProperties);
		break;
	case 2:
		handleException_L2(exceptionProperties);
		break;
	default:
		throw std::runtime_error("PS2Exception parsed contained an unknown exception type.");
	}
}

void ExceptionHandler::handleException_L1(const ExceptionProperties_t & exceptionProperties) const
{
	// Exception level 1 handler code. Adapted from EE Core Users Manual page 91.

	// Vector offset value, used to set final vector address.
	u32 vectorOffset = 0x0;

	// Set Cause.ExeCode value.
	getVM()->getResources()->EE->EECore->COP0->Cause->setFieldValue(RegisterCause_t::Fields::ExcCode, exceptionProperties.mExeCode);

	// If already in exception handler (EXL == 1), do not update EPC and Cause.BD. Also use general exception handler vector.
	if (getVM()->getResources()->EE->EECore->COP0->Status->getFieldValue(RegisterStatus_t::Fields::EXL) == 1)
	{
		vectorOffset = PS2Constants::EE::EECore::OADDRESS_EXCEPTION_VECTOR_V_COMMON;
	}
	// Normal exception processing.
	else
	{
		// Set EPC and Cause.BD fields.
		if (getVM()->getResources()->EE->EECore->R5900->mIsInBranchDelaySlot) // Check if in the branch delay slot.
		{
			u32 pcValue = getVM()->getResources()->EE->EECore->R5900->PC->getPCValue() - 4;
			getVM()->getResources()->EE->EECore->COP0->EPC->setFieldValue(RegisterEPC_t::Fields::EPC, pcValue);
			getVM()->getResources()->EE->EECore->COP0->Cause->setFieldValue(RegisterCause_t::Fields::BD, 1);
		}
		else
		{
			u32 pcValue = getVM()->getResources()->EE->EECore->R5900->PC->getPCValue();
			getVM()->getResources()->EE->EECore->COP0->EPC->setFieldValue(RegisterEPC_t::Fields::EPC, pcValue);
			getVM()->getResources()->EE->EECore->COP0->Cause->setFieldValue(RegisterCause_t::Fields::BD, 0);
		}

		// Set to kernel mode and disable interrupts.
		getVM()->getResources()->EE->EECore->COP0->Status->setFieldValue(RegisterStatus_t::Fields::EXL, 1);

		// Select the vector to use (set vectorOffset).
		if (exceptionProperties.mExceptionType == PS2Exception_t::ExceptionType::EX_TLB_REFILL_INSTRUCTION_FETCH_LOAD
			|| exceptionProperties.mExceptionType == PS2Exception_t::ExceptionType::EX_TLB_REFILL_INSTRUCTION_FETCH_LOAD)
		{
			vectorOffset = PS2Constants::EE::EECore::OADDRESS_EXCEPTION_VECTOR_V_TLB_REFILL;
		}
		else if (exceptionProperties.mExceptionType == PS2Exception_t::ExceptionType::EX_INTERRUPT)
		{
			vectorOffset = PS2Constants::EE::EECore::OADDRESS_EXCEPTION_VECTOR_V_INTERRUPT;
		}
		else
		{
			vectorOffset = PS2Constants::EE::EECore::OADDRESS_EXCEPTION_VECTOR_V_COMMON;
		}

		// Select vector base to use and set PC to use the specified vector.
		if (getVM()->getResources()->EE->EECore->COP0->Status->getFieldValue(RegisterStatus_t::Fields::BEV) == 1)
		{
			getVM()->getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(PS2Constants::EE::EECore::PADDRESS_EXCEPTION_BASE_A1 + vectorOffset);
		} 
		else
		{
			getVM()->getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(PS2Constants::EE::EECore::PADDRESS_EXCEPTION_BASE_A0 + vectorOffset);
		}
	}
}

void ExceptionHandler::handleException_L2(const ExceptionProperties_t & exceptionProperties) const
{
	// Exception level 2 handler code. Adapted from EE Core Users Manual page 92.

	// Vector offset value, used to set final vector address.
	u32 vectorOffset = 0x0;

	// Set Cause.EXC2 value.
	getVM()->getResources()->EE->EECore->COP0->Cause->setFieldValue(RegisterCause_t::Fields::EXC2, exceptionProperties.mEXC2);

	// Set EPC and Cause.BD fields.
	if (getVM()->getResources()->EE->EECore->R5900->mIsInBranchDelaySlot) // Check if in the branch delay slot.
	{
		u32 pcValue = getVM()->getResources()->EE->EECore->R5900->PC->getPCValue() - 4;
		getVM()->getResources()->EE->EECore->COP0->ErrorEPC->setFieldValue(RegisterErrorEPC_t::Fields::ErrorEPC, pcValue);
		getVM()->getResources()->EE->EECore->COP0->Cause->setFieldValue(RegisterCause_t::Fields::BD2, 1);
	}
	else
	{
		u32 pcValue = getVM()->getResources()->EE->EECore->R5900->PC->getPCValue();
		getVM()->getResources()->EE->EECore->COP0->ErrorEPC->setFieldValue(RegisterErrorEPC_t::Fields::ErrorEPC, pcValue);
		getVM()->getResources()->EE->EECore->COP0->Cause->setFieldValue(RegisterCause_t::Fields::BD2, 0);
	}

	// Set to kernel mode and disable interrupts.
	getVM()->getResources()->EE->EECore->COP0->Status->setFieldValue(RegisterStatus_t::Fields::ERL, 1);

	// Select vector to use and set PC to use it.
	if (exceptionProperties.mExceptionType == PS2Exception_t::ExceptionType::EX_NMI 
		|| exceptionProperties.mExceptionType == PS2Exception_t::ExceptionType::EX_RESET) 
	{
		getVM()->getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(PS2Constants::EE::EECore::PADDRESS_EXCEPTION_BASE_V_RESET_NMI);
	}
	else
	{
		if (exceptionProperties.mExceptionType == PS2Exception_t::ExceptionType::EX_PERFORMANCE_COUNTER)
		{
			vectorOffset = PS2Constants::EE::EECore::OADDRESS_EXCEPTION_VECTOR_V_COUNTER;
		}
		else if (exceptionProperties.mExceptionType == PS2Exception_t::ExceptionType::EX_DEBUG)
		{
			vectorOffset = PS2Constants::EE::EECore::OADDRESS_EXCEPTION_VECTOR_V_DEBUG;
		}
		else
		{
			// Implicit statement to use the V_TLB_REFIL (offset 0x00000000)
			vectorOffset = PS2Constants::EE::EECore::OADDRESS_EXCEPTION_VECTOR_V_TLB_REFILL;
		}

		// Select vector base to use and set PC to use the specified vector.
		if (getVM()->getResources()->EE->EECore->COP0->Status->getFieldValue(RegisterStatus_t::Fields::DEV) == 1)
		{
			getVM()->getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(PS2Constants::EE::EECore::PADDRESS_EXCEPTION_BASE_A1 + vectorOffset);
		}
		else
		{
			getVM()->getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(PS2Constants::EE::EECore::PADDRESS_EXCEPTION_BASE_A0 + vectorOffset);
		}
	}
}
