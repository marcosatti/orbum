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

u32 FPRegister128_t::readWord(const System_t context, size_t arrayIndex)
{
	return UW[arrayIndex];
}

void FPRegister128_t::writeWord(const System_t context, size_t arrayIndex, u32 value)
{
	UW[arrayIndex] = value;
}

u64 FPRegister128_t::readDword(const System_t context, size_t arrayIndex)
{
	return UD[arrayIndex];
}

void FPRegister128_t::writeDword(const System_t context, size_t arrayIndex, u64 value)
{
	UD[arrayIndex] = value;
}

u128 FPRegister128_t::readQword(const System_t context)
{
	return UQ;
}

void FPRegister128_t::writeQword(const System_t context, u128 value)
{
	UQ = value;
}

f32 FPRegister128_t::readFloat(const System_t context, size_t arrayIndex)
{
	return F[arrayIndex];
}

void FPRegister128_t::writeFloat(const System_t context, size_t arrayIndex, f32 value)
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
