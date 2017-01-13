#include "stdafx.h"

#include "Common/Tables/IOPCoreExceptionsTable/IOPCoreExceptionsTable.h"

#include "PS2Resources/IOP/IOPCore/Types/IOPCoreExceptions_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreException_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreCOP0_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreCOP0Registers_t.h"

IOPCoreExceptions_t::IOPCoreExceptions_t(const std::shared_ptr<IOPCoreCOP0_t>& cop0) :
	ExceptionOccurred(false),
	Exception(),
	mCOP0(cop0)
{
}

bool IOPCoreExceptions_t::hasExceptionOccurred()
{
	bool temp = ExceptionOccurred;
	ExceptionOccurred = false;
	return temp;
}

const IOPCoreException_t & IOPCoreExceptions_t::getException() const
{
	return Exception;
}

void IOPCoreExceptions_t::setException(const IOPCoreException_t & exception)
{
	// Raise the exception if not masked.
	if (!mCOP0->Status->isExceptionsMasked())
	{
		Exception = exception;
		ExceptionOccurred = true;
	}
	else
	{
		logDebug("IOP Exception raised (%s), but was masked!", IOPCoreExceptionsTable::getExceptionInfo(exception)->mMnemonic);
	}
}
