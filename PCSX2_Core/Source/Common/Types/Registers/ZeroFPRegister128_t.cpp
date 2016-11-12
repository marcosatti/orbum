#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/ZeroFPRegister128_t.h"

ZeroFPRegister128_t::ZeroFPRegister128_t()
{
	F[3] = 1.0f; // VF.w is set to constant 1.0f.
}

void ZeroFPRegister128_t::writeWordU(u32 arrayIndex, u32 value)
{
	// Do not write value (zero register).
}

void ZeroFPRegister128_t::writeWordS(u32 arrayIndex, s32 value)
{
	// Do not write value (zero register).
}

void ZeroFPRegister128_t::writeDwordU(u32 arrayIndex, u64 value)
{
	// Do not write value (zero register).
}

void ZeroFPRegister128_t::writeDwordS(u32 arrayIndex, s64 value)
{
	// Do not write value (zero register).
}

void ZeroFPRegister128_t::writeFloat(u32 arrayIndex, f32 value)
{
	// Do not write value (zero register).
}
