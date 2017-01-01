#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/Register128_t.h"

Register128_t::Register128_t() : 
	UD{ 0 },
	mMnemonic("")
{
}

Register128_t::Register128_t(const char* mnemonic) :
	UD{ 0 },
	mMnemonic(mnemonic)
{
}

Register128_t::~Register128_t()
{
}

u8 Register128_t::readByte(u32 arrayIndex)
{
	return UB[arrayIndex];
}

void Register128_t::writeByte(u32 arrayIndex, u8 value)
{
	UB[arrayIndex] = value;
}

u16 Register128_t::readHword(u32 arrayIndex)
{
	return UH[arrayIndex];
}

void Register128_t::writeHword(u32 arrayIndex, u16 value)
{
	UH[arrayIndex] = value;
}

u32 Register128_t::readWord(u32 arrayIndex)
{
	return UW[arrayIndex];
}

void Register128_t::writeWord(u32 arrayIndex, u32 value)
{
	UW[arrayIndex] = value;
}

u64 Register128_t::readDword(u32 arrayIndex)
{
	return UD[arrayIndex];
}

void Register128_t::writeDword(u32 arrayIndex, u64 value)
{
	UD[arrayIndex] = value;
}

u128 Register128_t::readQword()
{
	return UQ;
}

void Register128_t::writeQword(u128 value)
{
	UQ = value;
}

const char* Register128_t::getMnemonic() const
{
	return mMnemonic.c_str();
}
