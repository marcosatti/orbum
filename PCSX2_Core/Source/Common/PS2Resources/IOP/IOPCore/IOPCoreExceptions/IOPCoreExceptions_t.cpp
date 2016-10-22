#include "stdafx.h"

#include "Common/PS2Resources/IOP/IOPCore/IOPCoreExceptions/IOPCoreExceptions_t.h"
#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "Common/PS2Resources/IOP/IOPCore/IOPCoreExceptions/Types/IOPCoreException_t.h"

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

void IOPCoreExceptions_t::setException(const IOPCoreException_t& eeCoreException)
{
	Exception = eeCoreException;
	ExceptionOccurred = true;
}
