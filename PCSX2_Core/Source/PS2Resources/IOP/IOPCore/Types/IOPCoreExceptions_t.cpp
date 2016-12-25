#include "stdafx.h"

#include "PS2Resources/IOP/IOPCore/Types/IOPCoreExceptions_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreException_t.h"

IOPCoreExceptions_t::IOPCoreExceptions_t() :
	ExceptionOccurred(false),
	Exception()
{
}

bool IOPCoreExceptions_t::hasExceptionOccurred()
{
	bool temp = ExceptionOccurred;
	ExceptionOccurred = false;
	return temp;
}

const IOPCoreException_t& IOPCoreExceptions_t::getException() const
{
	return Exception;
}

void IOPCoreExceptions_t::setException(const IOPCoreException_t& exception)
{
	Exception = exception;
	ExceptionOccurred = true;
}
