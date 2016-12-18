#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/ConstantRegister128_t.h"

ConstantRegister128_t::ConstantRegister128_t(const u64 D0, const u64 D1)
{
	UD[0] = D0;
	UD[1] = D1;
}

void ConstantRegister128_t::writeByteU(u32 arrayIndex, u8 value)
{
	// Do not write value (constant register).
}

void ConstantRegister128_t::writeByteS(u32 arrayIndex, s8 value)
{
	// Do not write value (constant register).
}

void ConstantRegister128_t::writeHwordU(u32 arrayIndex, u16 value)
{
	// Do not write value (constant register).
}

void ConstantRegister128_t::writeHwordS(u32 arrayIndex, s16 value)
{
	// Do not write value (constant register).
}

void ConstantRegister128_t::writeWordU(u32 arrayIndex, u32 value)
{
	// Do not write value (constant register).
}

void ConstantRegister128_t::writeWordS(u32 arrayIndex, s32 value)
{
	// Do not write value (constant register).
}

void ConstantRegister128_t::writeDwordU(u32 arrayIndex, u64 value)
{
	// Do not write value (constant register).
}

void ConstantRegister128_t::writeDwordS(u32 arrayIndex, s64 value)
{
	// Do not write value (constant register).
}

void ConstantRegister128_t::writeQwordU(u128 value)
{
	// Do not write value (constant register).
}
