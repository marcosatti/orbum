#include "stdafx.h"

#include "Common/PS2Resources/EE/IPU/IPU_t.h"
#include "Common/PS2Resources/Types/Registers/Register32_t.h"
#include "Common/PS2Resources/Types/MappedMemory/DeadMMemory_t.h"

IPU_t::IPU_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),

	// Registers
	IPU_REGISTER_CMD(std::make_shared<Register32_t>()),
	IPU_REGISTER_CTRL(std::make_shared<Register32_t>()),
	IPU_REGISTER_BP(std::make_shared<Register32_t>()),
	IPU_REGISTER_TOP(std::make_shared<Register32_t>()),
	IPU_MEMORY_2040(std::make_shared<DeadMMemory_t>(0xFC0, "IPU: IPU_2040 (reserved)", 0x10002040))
{
}
