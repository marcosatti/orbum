#include "stdafx.h"

#include "Common/PS2Resources/EE/EECore/EECoreExceptions/EECoreExceptions_t.h"
#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "Common/PS2Resources/EE/EECore/EECoreExceptions/Types/EECoreException_t.h"
#include "Common/PS2Resources/Types/MIPSCoprocessor/COP0_BitfieldRegisters_t.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/EE/EECore/EECore_t.h"
#include "Common/PS2Resources/EE/EECore/EECoreCOP0/EECoreCOP0_t.h"
#include "Common/PS2Resources/EE/EECore/EECoreCOP0/Types/EECore_COP0_Registers_t.h"

EECoreExceptions_t::EECoreExceptions_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources), 
	ExceptionOccurred(false),
	Exception()
{
}

bool EECoreExceptions_t::hasExceptionOccurred()
{
	bool temp = ExceptionOccurred;
	ExceptionOccurred = false;
	return temp;
}

const EECoreException_t& EECoreExceptions_t::getException() const
{
	return Exception;
}

void EECoreExceptions_t::setException(const EECoreException_t& eeCoreException)
{
	auto& EECore = getRootResources()->EE->EECore;

	// Interrupt exceptions are only taken when conditions are correct.
	// Interrupt exception checking follows the process on page 74 of the EE Core Users Manual.
	if (eeCoreException.mExType == EECoreException_t::ExType::EX_INTERRUPT)
	{
		// Check if the Status.IE and Status.EIE bit is set. Status.EXL and Status.ERL must also be 0.
		if (EECore->COP0->Status->getFieldValue(EECore_COP0RegisterStatus_t::Fields::IE)
			&& EECore->COP0->Status->getFieldValue(EECore_COP0RegisterStatus_t::Fields::EIE)
			&& !EECore->COP0->Status->getFieldValue(EECore_COP0RegisterStatus_t::Fields::EXL)
			&& !EECore->COP0->Status->getFieldValue(EECore_COP0RegisterStatus_t::Fields::ERL))
		{
			// Now check if the Status.IM corresponding bit is set.
			if (eeCoreException.mIntExceptionInfo.mInt0)
			{
				if (EECore->COP0->Status->getFieldValue(EECore_COP0RegisterStatus_t::Fields::IM) & 0x1)
				{
					Exception = eeCoreException;
					ExceptionOccurred = true;
				}
			}
			else if (eeCoreException.mIntExceptionInfo.mInt1)
			{
				if (EECore->COP0->Status->getFieldValue(EECore_COP0RegisterStatus_t::Fields::IM) & 0x2)
				{
					Exception = eeCoreException;
					ExceptionOccurred = true;
				}
			}
			else if (eeCoreException.mIntExceptionInfo.mTimerInt)
			{
				if (EECore->COP0->Status->getFieldValue(EECore_COP0RegisterStatus_t::Fields::IM7))
				{
					Exception = eeCoreException;
					ExceptionOccurred = true;
				}
			}
		}
	}
	else
	{
		Exception = eeCoreException;
		ExceptionOccurred = true;
	}
}
