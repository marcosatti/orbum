#include "stdafx.h"

#include "PS2Resources/EE/GIF/GIF_t.h"
#include "Common/Types/Registers/Register32_t.h"
#include "Common/Types/Memory/ZeroMemory_t.h"

GIF_t::GIF_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),

	// Registers
	REGISTER_CTRL(std::make_shared<Register32_t>()),
	REGISTER_MODE(std::make_shared<Register32_t>()),
	REGISTER_STAT(std::make_shared<Register32_t>()),
	MEMORY_3030(std::make_shared<ZeroMemory_t>(0x10, "GIF: GIF_3030 (reserved)")),
	REGISTER_TAG0(std::make_shared<Register32_t>()),
	REGISTER_TAG1(std::make_shared<Register32_t>()),
	REGISTER_TAG2(std::make_shared<Register32_t>()),
	REGISTER_TAG3(std::make_shared<Register32_t>()),
	REGISTER_CNT(std::make_shared<Register32_t>()),
	REGISTER_P3CNT(std::make_shared<Register32_t>()),
	REGISTER_P3TAG(std::make_shared<Register32_t>()),
	MEMORY_30b0(std::make_shared<ZeroMemory_t>(0x750, "GIF: GIF_30b0 (reserved)"))
{
}
