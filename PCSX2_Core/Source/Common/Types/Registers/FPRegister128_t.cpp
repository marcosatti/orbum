#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/FPRegister128_t.h"

FPRegister128_t::FPRegister128_t() : 
	F{ 0 }
{
}

u32 FPRegister128_t::readWordU(u32 arrayIndex)
{
	return UW[arrayIndex];
}

void FPRegister128_t::writeWordU(u32 arrayIndex, u32 value)
{
	UW[arrayIndex] = value;
}

s32 FPRegister128_t::readWordS(u32 arrayIndex)
{
	return SW[arrayIndex];
}

void FPRegister128_t::writeWordS(u32 arrayIndex, s32 value)
{
	SW[arrayIndex] = value;
}

f32 FPRegister128_t::readFloat(u32 arrayIndex)
{
	return F[arrayIndex];
}

void FPRegister128_t::writeFloat(u32 arrayIndex, f32 value)
{
	F[arrayIndex] = value;
}