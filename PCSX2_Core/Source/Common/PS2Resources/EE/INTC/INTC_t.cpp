#include "stdafx.h"

#include "Common/PS2Resources/EE/INTC/INTC_t.h"
#include "Common/PS2Resources/EE/INTC/Types/INTC_Registers_t.h"
#include "Common/PS2Resources/Types/MappedMemory/DeadMMemory_t.h"

INTC_t::INTC_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),

	// Registers
	INTC_REGISTER_I_STAT(std::make_shared<IntcRegisterStat_t>()),
	INTC_REGISTER_I_MASK(std::make_shared<IntcRegisterMask_t>()),
	INTC_MEMORY_f020(std::make_shared<DeadMMemory_t>(0xE0, "INTC: INTC_f020 (reserved)", 0x1000f020))
{
}
