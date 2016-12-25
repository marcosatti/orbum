#include "stdafx.h"

#include "PS2Resources/EE/EECore/Types/EECoreExceptions_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreException_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0Registers_t.h"

EECoreExceptions_t::EECoreExceptions_t(const std::shared_ptr<EECoreCOP0_t> & cop0) :
	ExceptionOccurred(false),
	Exception(),
	COP0(cop0)
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
	// Interrupt exceptions are only taken when conditions are correct.
	// Interrupt exception checking follows the process on page 74 of the EE Core Users Manual.
	if (eeCoreException.mExType == EECoreException_t::ExType::EX_INTERRUPT)
	{
		// Check if the Status.IE and Status.EIE bit is set. Status.EXL and Status.ERL must also be 0.
		if (COP0->Status->getFieldValue(EECoreCOP0Register_Status_t::Fields::IE)
			&& COP0->Status->getFieldValue(EECoreCOP0Register_Status_t::Fields::EIE)
			&& !COP0->Status->getFieldValue(EECoreCOP0Register_Status_t::Fields::EXL)
			&& !COP0->Status->getFieldValue(EECoreCOP0Register_Status_t::Fields::ERL))
		{
			// Now check if the Status.IM corresponding bit is set.
			if (eeCoreException.mIntExceptionInfo.mInt0)
			{
				if (COP0->Status->getFieldValue(EECoreCOP0Register_Status_t::Fields::IM) & 0x1)
				{
					Exception = eeCoreException;
					ExceptionOccurred = true;
				}
			}
			else if (eeCoreException.mIntExceptionInfo.mInt1)
			{
				if (COP0->Status->getFieldValue(EECoreCOP0Register_Status_t::Fields::IM) & 0x2)
				{
					Exception = eeCoreException;
					ExceptionOccurred = true;
				}
			}
			else if (eeCoreException.mIntExceptionInfo.mTimerInt)
			{
				if (COP0->Status->getFieldValue(EECoreCOP0Register_Status_t::Fields::IM7))
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
