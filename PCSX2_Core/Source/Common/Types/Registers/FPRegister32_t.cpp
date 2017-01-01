#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/FPRegister32_t.h"

FPRegister32_t::FPRegister32_t() : 
	F(0),
	mMnemonic("")
{
}

FPRegister32_t::FPRegister32_t(const char* mnemonic) :
	F(0),
	mMnemonic(mnemonic)
{
}

u32 FPRegister32_t::readWord()
{
	return UW;
}

void FPRegister32_t::writeWord(u32 value)
{
	UW = value;
}

f32 FPRegister32_t::readFloat()
{
	return F;
}

void FPRegister32_t::writeFloat(f32 value)
{
	F = value;
}

const char* FPRegister32_t::getMnemonic() const
{
	return mMnemonic.c_str();
}
