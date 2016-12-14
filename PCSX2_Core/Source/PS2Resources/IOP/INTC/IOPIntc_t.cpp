#include "stdafx.h"

#include "PS2Resources/IOP/INTC/IOPIntc_t.h"
#include "Common/Types/Registers/Register32_t.h"

IOPIntc_t::IOPIntc_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),

	// Registers
	STAT(std::make_shared<Register32_t>()),
	MASK(std::make_shared<Register32_t>()),
	CTRL(std::make_shared<Register32_t>())
{
}
