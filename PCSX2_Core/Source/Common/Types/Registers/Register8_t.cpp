#include "stdafx.h"

#include "Common/Types/Registers/Register8_t.h"

Register8_t::Register8_t() :
	UB(0),
	mMnemonic("")
{
}

Register8_t::Register8_t(const char* mnemonic) :
	UB(0),
	mMnemonic(mnemonic)
{
}

Register8_t::~Register8_t()
{
}

u8 Register8_t::readByte()
{
	return UB;
}

void Register8_t::writeByte(u8 value)
{
	UB = value;
}

const char* Register8_t::getMnemonic() const
{
	return mMnemonic.c_str();
}
