#include "stdafx.h"

#include "Common/PS2Resources/EE/IPU/IPU_t.h"
#include "Common/PS2Resources/Types/MappedMemory/MappedMemory32_t.h"
#include "Common/PS2Resources/Types/MappedMemory/DeadMMemory_t.h"

IPU_t::IPU_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),

	// Registers
	IPU_REGISTER_CMD(std::make_shared<MappedMemory32_t>("IPU: IPU_CMD", 0x10002000)),
	IPU_REGISTER_CTRL(std::make_shared<MappedMemory32_t>("IPU: IPU_CTRL", 0x10002010)),
	IPU_REGISTER_BP(std::make_shared<MappedMemory32_t>("IPU: IPU_BP", 0x10002020)),
	IPU_REGISTER_TOP(std::make_shared<MappedMemory32_t>("IPU: IPU_TOP", 0x10002030)),
	IPU_REGISTER_2040(std::make_shared<DeadMMemory_t>(0xFC0, "IPU: IPU_2040 (reserved)", 0x10002040))
{
}
