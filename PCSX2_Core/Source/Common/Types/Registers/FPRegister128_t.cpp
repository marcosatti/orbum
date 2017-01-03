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

FPRegister128_t::~FPRegister128_t()
{
}

u32 FPRegister128_t::readWord(const Context_t& context, u32 arrayIndex)
{
	return UW[arrayIndex];
}

void FPRegister128_t::writeWord(const Context_t& context, u32 arrayIndex, u32 value)
{
	UW[arrayIndex] = value;
}

u64 FPRegister128_t::readDword(const Context_t& context, u32 arrayIndex)
{
	return UD[arrayIndex];
}

void FPRegister128_t::writeDword(const Context_t& context, u32 arrayIndex, u64 value)
{
	UD[arrayIndex] = value;
}

u128 FPRegister128_t::readQword(const Context_t& context)
{
	return u128(UD[0], UD[1]);
}

void FPRegister128_t::writeQword(const Context_t& context, u128 value)
{
	UD[0] = value.lo;
	UD[1] = value.hi;
}

f32 FPRegister128_t::readFloat(const Context_t& context, u32 arrayIndex)
{
	return F[arrayIndex];
}

void FPRegister128_t::writeFloat(const Context_t& context, u32 arrayIndex, f32 value)
{
	F[arrayIndex] = value;
}

const char* FPRegister128_t::getMnemonic() const
{
	return mMnemonic.c_str();
}
