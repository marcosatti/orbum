#include "stdafx.h"

#include "Common/PS2 Resources/PS2Resources_t.h"
#include "Common/PS2 Resources/EE/EECore/COP1/Types/COP1ResourcesSubobject.h"
#include <Common/Types/PS2Exception/PS2Exception_t.h>

COP1ResourcesSubobject::COP1ResourcesSubobject(const PS2Resources_t* const PS2Resources):
	PS2ResourcesSubobject(PS2Resources)
{
}

void COP1ResourcesSubobject::checkCOP1Usable() const
{
	if (!getRootResources()->EE->EECore->COP1->isCOP1Usable())
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_COPROCESSOR_UNUSABLE);
}
