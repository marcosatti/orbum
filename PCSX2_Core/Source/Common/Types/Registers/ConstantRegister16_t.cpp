#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/ConstantRegister16_t.h"

ConstantRegister16_t::ConstantRegister16_t(const u16 H)
{
	UH = H;
}

void ConstantRegister16_t::writeByte(u32 arrayIndex, u8 value)
{
	// Do not write value (zero register).
}

void ConstantRegister16_t::writeHword(u16 value)
{
	// Do not write value (zero register).
}
