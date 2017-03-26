#include "stdafx.h"

#include "Resources/EE/IPU/IPU_t.h"
#include "Common/Types/Registers/Register32_t.h"
#include "Common/Types/Memory/ConstantByteMemory_t.h"

IPU_t::IPU_t() :
	// Registers
	CMD(std::make_shared<Register32_t>()),
	CTRL(std::make_shared<Register32_t>()),
	BP(std::make_shared<Register32_t>()),
	TOP(std::make_shared<Register32_t>()),
	MEMORY_2040(std::make_shared<ConstantByteMemory_t>(0xFC0, "IPU: IPU_2040 (reserved)"))
{
}
