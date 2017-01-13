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
	// Raise the exception if not masked.
	if (!mCOP0->Status->isExceptionsMasked())
	{
		Exception = exception;
		ExceptionOccurred = true;
	}
	else
	{
		logDebug("EE Exception raised (%s), but was masked!", EECoreExceptionsTable::getExceptionInfo(exception)->mMnemonic);
	}
}
