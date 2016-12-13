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

u8 Register64_t::readByteU(u32 arrayIndex)
{
	return UB[arrayIndex];
}

void Register64_t::writeByteU(u32 arrayIndex, u8 value)
{
	UB[arrayIndex] = value;
}

s8 Register64_t::readByteS(u32 arrayIndex)
{
	return SB[arrayIndex];
}

void Register64_t::writeByteS(u32 arrayIndex, s8 value)
{
	SB[arrayIndex] = value;
}

u16 Register64_t::readHwordU(u32 arrayIndex)
{
	return UH[arrayIndex];
}

void Register64_t::writeHwordU(u32 arrayIndex, u16 value)
{
	UH[arrayIndex] = value;
}

s16 Register64_t::readHwordS(u32 arrayIndex)
{
	return SH[arrayIndex];
}

void Register64_t::writeHwordS(u32 arrayIndex, s16 value)
{
	SH[arrayIndex] = value;
}

u32 Register64_t::readWordU(u32 arrayIndex)
{
	return UW[arrayIndex];
}

void Register64_t::writeWordU(u32 arrayIndex, u32 value)
{
	UW[arrayIndex] = value;
}

s32 Register64_t::readWordS(u32 arrayIndex)
{
	return SW[arrayIndex];
}

void Register64_t::writeWordS(u32 arrayIndex, s32 value)
{
	SW[arrayIndex] = value;
}

u64 Register64_t::readDwordU()
{
	return UD;
}

void Register64_t::writeDwordU(u64 value)
{
	UD = value;
}

s64 Register64_t::readDwordS()
{
	return SD;
}

void Register64_t::writeDwordS(s64 value)
{
	SD = value;
}

const char* Register64_t::getMnemonic() const
{
	return mMnemonic.c_str();
}
