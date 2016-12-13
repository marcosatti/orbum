#include "stdafx.h"

#include "PS2Resources/IOP/DMAC/IOPDmac_t.h"
#include "Common/Types/Registers/Register32_t.h"

IOPDmac_t::IOPDmac_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),
	REGISTER_PCR(std::make_shared<Register32_t>()),
	REGISTER_ICR(std::make_shared<Register32_t>()),
	REGISTER_PCR2(std::make_shared<Register32_t>()),
	REGISTER_ICR2(std::make_shared<Register32_t>())
{
}
