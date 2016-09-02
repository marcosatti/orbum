#include "stdafx.h"

#include "Common/PS2Resources/EE/EECore/Exceptions/Exceptions_t.h"
#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "Common/PS2Resources/EE/EECore/Exceptions/Types/EECoreException_t.h"

Exceptions_t::Exceptions_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),
	ExceptionQueue(std::make_shared<std::queue<EECoreException_t>>())
{
}
