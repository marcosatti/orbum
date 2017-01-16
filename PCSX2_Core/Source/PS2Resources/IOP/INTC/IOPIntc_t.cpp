#include "stdafx.h"

#include "PS2Resources/IOP/INTC/IOPIntc_t.h"
#include "PS2Resources/IOP/INTC/Types/IOPIntcRegisters_t.h"

IOPIntc_t::IOPIntc_t(const PS2Resources_t* PS2Resources) :
	PS2ResourcesSubcategory(PS2Resources),

	// Registers
	CTRL(std::make_shared<IOPIntcRegister_CTRL_t>()),
	MASK(std::make_shared<IOPIntcRegister_MASK_t>()),
	STAT(std::make_shared<IOPIntcRegister_STAT_t>(MASK))
{
}
