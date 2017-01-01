#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/Register32_t.h"

Register32_t::Register32_t() : 
	UW(0),
	mMnemonic("")
{
}

Register32_t::Register32_t(const char* mnemonic) :
	UW(0),
	mMnemonic(mnemonic)
{
}

Register32_t::~Register32_t()
{
}

u8 Register32_t::readByte(u32 arrayIndex)
{
	return UB[arrayIndex];
}

void Register32_t::writeByte(u32 arrayIndex, u8 value)
{
	UB[arrayIndex] = value;
}

u16 Register32_t::readHword(u32 arrayIndex)
{
	return UH[arrayIndex];
}

void Register32_t::writeHword(u32 arrayIndex, u16 value)
{
	UH[arrayIndex] = value;
}

u32 Register32_t::readWord()
{
	return UW;
}

void Register32_t::writeWord(u32 value)
{
	UW = value;
}

const char* Register32_t::getMnemonic() const
{
	return mMnemonic.c_str();
}
