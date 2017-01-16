#include "stdafx.h"

#include "PS2Resources/EE/INTC/EEIntc_t.h"
#include "PS2Resources/EE/INTC/Types/EEIntcRegisters_t.h"
#include "Common/Types/Memory/ConstantMemory_t.h"

EEIntc_t::EEIntc_t(const PS2Resources_t* PS2Resources) :
	PS2ResourcesSubcategory(PS2Resources),

	// Registers
	MASK(std::make_shared<EEIntcRegister_MASK_t>()),
	STAT(std::make_shared<EEIntcRegister_STAT_t>(MASK)),
	MEMORY_F020(std::make_shared<ConstantMemory_t>(0xE0, "INTC: INTC_f020 (reserved)"))
{
}
