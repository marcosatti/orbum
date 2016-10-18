#include "stdafx.h"

#include "Common/PS2Resources/IOP/IOPExceptions/IOPExceptions_t.h"
#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "Common/PS2Resources/IOP/IOPExceptions/Types/IOPException_t.h"

IOPExceptions_t::IOPExceptions_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources), 
	ExceptionOccurred(false),
	Exception()
{
}

bool IOPExceptions_t::hasExceptionOccurred()
{
	bool temp = ExceptionOccurred;
	ExceptionOccurred = false;
	return temp;
}

const IOPException_t& IOPExceptions_t::getException() const
{
	return Exception;
}

void IOPExceptions_t::setException(const IOPException_t& eeCoreException)
{
	Exception = eeCoreException;
	ExceptionOccurred = true;
}
