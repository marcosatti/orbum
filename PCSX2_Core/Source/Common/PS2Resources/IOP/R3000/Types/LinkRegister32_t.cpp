#include "stdafx.h"

#include "Common/PS2Resources/IOP/R3000/Types/LinkRegister32_t.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/IOP/IOP_t.h"
#include "Common/PS2Resources/IOP/R3000/R3000_t.h"
#include "Common/PS2Resources/Types/Registers/PCRegister32_t.h"

LinkRegister32_t::LinkRegister32_t(const PS2Resources_t* const PS2Resources) : 
	PS2ResourcesSubobject(PS2Resources)
{
}

void LinkRegister32_t::setLinkAddress()
{
	writeWordU(getRootResources()->IOP->R3000->PC->getPCValue() + 8);
}
