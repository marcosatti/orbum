#include "stdafx.h"

#include "Resources/EE/IPU/IPU_t.h"
#include "Common/Types/Register/Register32_t.h"
#include "Common/Types/Memory/ConstantByteMemory_t.h"

IPU_t::IPU_t() :
	// Registers
	CMD(std::make_shared<Register32_t>("IPU CMD", false, false)),
	CTRL(std::make_shared<Register32_t>("IPU CTRL", false, false)),
	BP(std::make_shared<Register32_t>("IPU BP", false, false)),
	TOP(std::make_shared<Register32_t>("IPU TOP", false, false)),
	MEMORY_2040(std::make_shared<ConstantByteMemory_t>("IPU 2040", false, false, 0xFC0))
{
}
