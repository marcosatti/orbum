#include "stdafx.h"

#include "Common/Types/Memory/ConstantByteMemory_t.h"

#include "Resources/EE/INTC/EEIntc_t.h"
#include "Resources/EE/INTC/Types/EEIntcRegisters_t.h"

EEIntc_t::EEIntc_t() :
	// Registers
	MASK(std::make_shared<EEIntcRegister_MASK_t>()),
	STAT(std::make_shared<EEIntcRegister_STAT_t>(MASK)),
	MEMORY_F020(std::make_shared<ConstantByteMemory_t>(0xE0, "INTC: INTC_f020 (reserved)"))
{
}
