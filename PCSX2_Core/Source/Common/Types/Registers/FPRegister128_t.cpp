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
	return UQ;
}

void FPRegister128_t::writeQword(const Context_t& context, u128 value)
{
	UQ = value;
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

void FPRegister128_t::initalise()
{
	UQ = u128(0, 0);
}
