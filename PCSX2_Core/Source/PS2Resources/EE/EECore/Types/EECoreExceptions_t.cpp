#include "stdafx.h"

#include "Common/Tables/EECoreExceptionsTable/EECoreExceptionsTable.h"

#include "PS2Resources/EE/EECore/Types/EECoreExceptions_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreException_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0Registers_t.h"

EECoreExceptions_t::EECoreExceptions_t(const std::shared_ptr<EECoreCOP0_t> & cop0) :
	ExceptionOccurred(false),
	Exception(),
	mCOP0(cop0)
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

void EECoreExceptions_t::setException(const EECoreException_t& exception)
{
	// Interrupt exceptions are only taken when conditions are correct.
	// Interrupt exception checking follows the process on page 74 of the EE Core Users Manual.
	// Determines if the exception should be raised at the end.
	bool masked = mCOP0->Status->isExceptionsMasked();

	// If its from an interrupt, need to check the interrupt source is not masked.
	if (exception.mExType == ExType::EX_INTERRUPT)
	{
		if (mCOP0->Status->isInterruptsMasked() || mCOP0->Status->isIRQMasked(exception.mIntExceptionInfo.mIRQLine))
			masked = true;
	}

	// TODO: need to add NMI checks here (always raised)?
	// if (exception.mExType == of NMI type (ie: reset))
	//     masked = false;

	// Finally raise the exception if not masked.
	if (!masked)
	{
		Exception = exception;
		ExceptionOccurred = true;
	}
	else
	{
		logDebug("EE Exception raised (%s), but was masked!", EECoreExceptionsTable::getExceptionInfo(exception.mExType)->mMnemonic);
	}
}
