#include "stdafx.h"

#include "Common/Types/Memory/ConstantByteMemory_t.h"

#include "Resources/EE/INTC/EEIntc_t.h"
#include "Resources/EE/INTC/Types/EEIntcRegisters_t.h"

EEIntc_t::EEIntc_t() :
	// Registers
	MASK(std::make_shared<EEIntcRegister_MASK_t>("EE INTC MASK", false, false)),
	STAT(std::make_shared<EEIntcRegister_STAT_t>("EE INTC STAT", false, false)),
	MEMORY_F020(std::make_shared<ConstantByteMemory_t>("EE INTC F020", false, false, 0xE0))
{
}
