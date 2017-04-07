#include "stdafx.h"

#include "Common/Types/Register/Register32_t.h"
#include "Common/Types/Memory/ConstantByteMemory_t.h"

#include "Resources/EE/GIF/GIF_t.h"

GIF_t::GIF_t() :
	// Registers
	CTRL(std::make_shared<Register32_t>("CTRL", false, false)),
	MODE(std::make_shared<Register32_t>("MODE", false, false)),
	STAT(std::make_shared<Register32_t>("STAT", false, false)),
	MEMORY_3030(std::make_shared<ConstantByteMemory_t>("GIF 3030", false, false, 0x10)),
	TAG0(std::make_shared<Register32_t>("TAG0", false, false)),
	TAG1(std::make_shared<Register32_t>("TAG1", false, false)),
	TAG2(std::make_shared<Register32_t>("TAG2", false, false)),
	TAG3(std::make_shared<Register32_t>("TAG3", false, false)),
	CNT(std::make_shared<Register32_t>("CNT", false, false)),
	P3CNT(std::make_shared<Register32_t>("P3CNT", false, false)),
	P3TAG(std::make_shared<Register32_t>("P3TAG", false, false)),
	MEMORY_30B0(std::make_shared<ConstantByteMemory_t>("GIF 30B0", false, false, 0x750))
{
}
