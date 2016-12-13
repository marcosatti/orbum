#include "stdafx.h"

#include "PS2Resources/EE/IPU/IPU_t.h"
#include "Common/Types/Registers/Register32_t.h"
#include "Common/Types/Memory/ConstantMemory_t.h"

IPU_t::IPU_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),

	// Registers
	REGISTER_CMD(std::make_shared<Register32_t>()),
	REGISTER_CTRL(std::make_shared<Register32_t>()),
	REGISTER_BP(std::make_shared<Register32_t>()),
	REGISTER_TOP(std::make_shared<Register32_t>()),
	MEMORY_2040(std::make_shared<ConstantMemory_t>(0xFC0, "IPU: IPU_2040 (reserved)"))
{
}
