#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/ConstantFPRegister128_t.h"

ConstantFPRegister128_t::ConstantFPRegister128_t(const f32 f0, const f32 f1, const f32 f2, const f32 f3)
{
	F[0] = f0;
	F[1] = f1;
	F[2] = f2;
	F[3] = f3;
}

void ConstantFPRegister128_t::writeWordU(u32 arrayIndex, u32 value)
{
	// Do not write value (constant register).
}

void ConstantFPRegister128_t::writeWordS(u32 arrayIndex, s32 value)
{
	// Do not write value (constant register).
}

void ConstantFPRegister128_t::writeDwordU(u32 arrayIndex, u64 value)
{
	// Do not write value (constant register).
}

void ConstantFPRegister128_t::writeDwordS(u32 arrayIndex, s64 value)
{
	// Do not write value (constant register).
}

void ConstantFPRegister128_t::writeQwordU(u128 value)
{
	// Do not write value (constant register).
}

void ConstantFPRegister128_t::writeFloat(u32 arrayIndex, f32 value)
{
	// Do not write value (constant register).
}
