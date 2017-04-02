#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/FPRegister32_t.h"

FPRegister32_t::FPRegister32_t() : 
	F(0.0f),
	mMnemonic("")
{
}

FPRegister32_t::FPRegister32_t(const char* mnemonic) :
	F(0.0f),
	mMnemonic(mnemonic)
{
}

u32 FPRegister32_t::readWord(const System_t context)
{
	return UW;
}

void FPRegister32_t::writeWord(const System_t context, u32 value)
{
	UW = value;
}

f32 FPRegister32_t::readFloat(const System_t context)
{
	return F;
}

void FPRegister32_t::writeFloat(const System_t context, f32 value)
{
	F = value;
}

const char* FPRegister32_t::getMnemonic() const
{
	return mMnemonic.c_str();
}

void FPRegister32_t::initalise()
{
	F = 0.0f;
}
