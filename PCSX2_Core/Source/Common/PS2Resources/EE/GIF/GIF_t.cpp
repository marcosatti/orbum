#include "stdafx.h"

#include "Common/PS2Resources/EE/GIF/GIF_t.h"
#include "Common/PS2Resources/Types/Registers/Register32_t.h"
#include "Common/PS2Resources/Types/MappedMemory/DeadMMemory_t.h"

GIF_t::GIF_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),

	// Registers
	GIF_REGISTER_CTRL(std::make_shared<Register32_t>()),
	GIF_REGISTER_MODE(std::make_shared<Register32_t>()),
	GIF_REGISTER_STAT(std::make_shared<Register32_t>()),
	GIF_MEMORY_3030(std::make_shared<DeadMMemory_t>(0x10, "GIF: GIF_3030 (reserved)", 0x10003030)),
	GIF_REGISTER_TAG0(std::make_shared<Register32_t>()),
	GIF_REGISTER_TAG1(std::make_shared<Register32_t>()),
	GIF_REGISTER_TAG2(std::make_shared<Register32_t>()),
	GIF_REGISTER_TAG3(std::make_shared<Register32_t>()),
	GIF_REGISTER_CNT(std::make_shared<Register32_t>()),
	GIF_REGISTER_P3CNT(std::make_shared<Register32_t>()),
	GIF_REGISTER_P3TAG(std::make_shared<Register32_t>()),
	GIF_MEMORY_30b0(std::make_shared<DeadMMemory_t>(0x750, "GIF: GIF_30b0 (reserved)", 0x100030b0))
{
}
