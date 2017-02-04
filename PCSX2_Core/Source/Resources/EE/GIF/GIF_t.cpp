#include "stdafx.h"

#include "Common/Types/Registers/Register32_t.h"
#include "Common/Types/Memory/ConstantMemory_t.h"

#include "Resources/EE/GIF/GIF_t.h"

GIF_t::GIF_t() :
	// Registers
	CTRL(std::make_shared<Register32_t>()),
	MODE(std::make_shared<Register32_t>()),
	STAT(std::make_shared<Register32_t>()),
	MEMORY_3030(std::make_shared<ConstantMemory_t>(0x10, "GIF: GIF_3030 (reserved)")),
	TAG0(std::make_shared<Register32_t>()),
	TAG1(std::make_shared<Register32_t>()),
	TAG2(std::make_shared<Register32_t>()),
	TAG3(std::make_shared<Register32_t>()),
	CNT(std::make_shared<Register32_t>()),
	P3CNT(std::make_shared<Register32_t>()),
	P3TAG(std::make_shared<Register32_t>()),
	MEMORY_30B0(std::make_shared<ConstantMemory_t>(0x750, "GIF: GIF_30b0 (reserved)"))
{
}
