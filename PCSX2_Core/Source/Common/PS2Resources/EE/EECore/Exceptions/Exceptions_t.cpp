#include "stdafx.h"

#include "Common/PS2Resources/EE/EECore/Exceptions/Exceptions_t.h"
#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "Common/PS2Resources/EE/EECore/Exceptions/Types/EECoreException_t.h"

Exceptions_t::Exceptions_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources), 
	ExceptionOccured(false),
	Exception()
{
}

bool Exceptions_t::hasExceptionOccured()
{
	if (ExceptionOccured)
	{
		ExceptionOccured = false;
		return true;
	}

	return false;
}

const EECoreException_t& Exceptions_t::getException() const
{
	return Exception;
}

void Exceptions_t::setException(const EECoreException_t& eeCoreException)
{
	Exception = eeCoreException;
	ExceptionOccured = true;
}
