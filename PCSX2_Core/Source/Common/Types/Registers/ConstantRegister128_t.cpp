#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/ConstantRegister128_t.h"

ConstantRegister128_t::ConstantRegister128_t(const u64 D0, const u64 D1)
{
	UD[0] = D0;
	UD[1] = D1;
}

void ConstantRegister128_t::writeByte(u32 arrayIndex, u8 value)
{
	// Do not write value (constant register).
}

void ConstantRegister128_t::writeHword(u32 arrayIndex, u16 value)
{
	// Do not write value (constant register).
}

void ConstantRegister128_t::writeWord(u32 arrayIndex, u32 value)
{
	// Do not write value (constant register).
}

void ConstantRegister128_t::writeDword(u32 arrayIndex, u64 value)
{
	// Do not write value (constant register).
}

void ConstantRegister128_t::writeQword(u128 value)
{
	// Do not write value (constant register).
}
