#include "stdafx.h"

#include "PS2Resources/IOP/IOPCore/Types/IOPCoreExceptions_t.h"
#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreException_t.h"

IOPCoreExceptions_t::IOPCoreExceptions_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources), 
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
