#include "stdafx.h"

#include "PS2Resources/EE/INTC/INTC_t.h"
#include "PS2Resources/EE/INTC/Types/EEIntcRegisters_t.h"
#include "Common/Types/Memory/DeadMemory_t.h"

INTC_t::INTC_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),

	// Registers
	INTC_REGISTER_I_STAT(std::make_shared<EEIntcRegister_STAT_t>()),
	INTC_REGISTER_I_MASK(std::make_shared<EEIntcRegister_MASK_t>()),
	INTC_MEMORY_f020(std::make_shared<DeadMemory_t>(0xE0, "INTC: INTC_f020 (reserved)"))
{
}
