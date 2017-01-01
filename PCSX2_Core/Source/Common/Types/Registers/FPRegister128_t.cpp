#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/FPRegister128_t.h"

FPRegister128_t::FPRegister128_t() : 
	F{ 0 },
	mMnemonic("")
{
}

FPRegister128_t::FPRegister128_t(const char* mnemonic) :
	F{ 0 },
	mMnemonic(mnemonic)
{
}

u32 FPRegister128_t::readWord(u32 arrayIndex)
{
	return UW[arrayIndex];
}

void FPRegister128_t::writeWord(u32 arrayIndex, u32 value)
{
	UW[arrayIndex] = value;
}

u64 FPRegister128_t::readDword(u32 arrayIndex)
{
	return UD[arrayIndex];
}

void FPRegister128_t::writeDword(u32 arrayIndex, u64 value)
{
	UD[arrayIndex] = value;
}

u128 FPRegister128_t::readQword()
{
	return u128(UD[0], UD[1]);
}

void FPRegister128_t::writeQword(u128 value)
{
	UD[0] = value.lo;
	UD[1] = value.hi;
}

f32 FPRegister128_t::readFloat(u32 arrayIndex)
{
	return F[arrayIndex];
}

void FPRegister128_t::writeFloat(u32 arrayIndex, f32 value)
{
	F[arrayIndex] = value;
}

const char* FPRegister128_t::getMnemonic() const
{
	return mMnemonic.c_str();
}
