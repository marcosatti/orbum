#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/Register16_t.h"

Register16_t::Register16_t() : 
	UH(0),
	mMnemonic("")
{
}

Register16_t::Register16_t(const char* mnemonic) :
	UH(0),
	mMnemonic(mnemonic)
{
}

u8 Register16_t::readByte(u32 arrayIndex)
{
	return UB[arrayIndex];
}

void Register16_t::writeByte(u32 arrayIndex, u8 value)
{
	UB[arrayIndex] = value;
}

u16 Register16_t::readHword()
{
	return UH;
}

void Register16_t::writeHword(u16 value)
{
	UH = value;
}

const char* Register16_t::getMnemonic() const
{
	return mMnemonic.c_str();
}
