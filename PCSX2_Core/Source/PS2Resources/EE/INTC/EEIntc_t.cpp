#include "stdafx.h"

#include "PS2Resources/EE/INTC/EEIntc_t.h"
#include "PS2Resources/EE/INTC/Types/EEIntcRegisters_t.h"
#include "Common/Types/Memory/ZeroMemory_t.h"

EEIntc_t::EEIntc_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),

	// Registers
	REGISTER_STAT(std::make_shared<EEIntcRegister_STAT_t>()),
	REGISTER_MASK(std::make_shared<EEIntcRegister_MASK_t>()),
	MEMORY_f020(std::make_shared<ZeroMemory_t>(0xE0, "INTC: INTC_f020 (reserved)"))
{
}
