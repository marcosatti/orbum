#include "stdafx.h"

#include "Resources/IOP/INTC/IOPIntc_t.h"
#include "Resources/IOP/INTC/Types/IOPIntcRegisters_t.h"

IOPIntc_t::IOPIntc_t() :

	// Registers
	CTRL(std::make_shared<IOPIntcRegister_CTRL_t>("IOP INTC CTRL", false, false)),
	MASK(std::make_shared<IOPIntcRegister_MASK_t>("IOP INTC MASK", false, false)),
	STAT(std::make_shared<IOPIntcRegister_STAT_t>("IOP INTC STAT", false, false))
{
}
