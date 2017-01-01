#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/Register64_t.h"

Register64_t::Register64_t() : 
	UD(0),
	mMnemonic("")
{
}

Register64_t::Register64_t(const char* mnemonic) :
	UD(0),
	mMnemonic(mnemonic)
{
}

Register64_t::~Register64_t()
{
}

u8 Register64_t::readByte(u32 arrayIndex)
{
	return UB[arrayIndex];
}

void Register64_t::writeByte(u32 arrayIndex, u8 value)
{
	UB[arrayIndex] = value;
}

u16 Register64_t::readHword(u32 arrayIndex)
{
	return UH[arrayIndex];
}

void Register64_t::writeHword(u32 arrayIndex, u16 value)
{
	UH[arrayIndex] = value;
}

u32 Register64_t::readWord(u32 arrayIndex)
{
	return UW[arrayIndex];
}

void Register64_t::writeWord(u32 arrayIndex, u32 value)
{
	UW[arrayIndex] = value;
}

u64 Register64_t::readDword()
{
	return UD;
}

void Register64_t::writeDword(u64 value)
{
	UD = value;
}

const char* Register64_t::getMnemonic() const
{
	return mMnemonic.c_str();
}
