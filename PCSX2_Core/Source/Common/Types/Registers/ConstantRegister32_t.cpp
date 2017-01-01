#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/ConstantRegister32_t.h"

ConstantRegister32_t::ConstantRegister32_t(const u32 W)
{
	UW = W;
}

void ConstantRegister32_t::writeByte(u32 arrayIndex, u8 value)
{
	// Do not write value (zero register).
}

void ConstantRegister32_t::writeHword(u32 arrayIndex, u16 value)
{
	// Do not write value (zero register).
}

void ConstantRegister32_t::writeWord(u32 value)
{
	// Do not write value (zero register).
}