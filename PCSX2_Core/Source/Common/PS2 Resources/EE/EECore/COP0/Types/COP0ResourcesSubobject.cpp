#include "stdafx.h"

#include "Common/PS2 Resources/PS2Resources_t.h"
#include "Common/PS2 Resources/EE/EECore/COP0/Types/COP0ResourcesSubobject.h"
#include "Common/Types/PS2Exception/PS2Exception_t.h"

COP0ResourcesSubobject::COP0ResourcesSubobject(const PS2Resources_t* const PS2Resources):
	PS2ResourcesSubobject(PS2Resources)
{
}

void COP0ResourcesSubobject::checkCOP0Usable() const
{
	if (!getRootResources()->EE->EECore->COP0->isCOP0Usable())
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_COPROCESSOR_UNUSABLE);
}
