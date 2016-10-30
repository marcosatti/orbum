#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/PS2Resources/Types/Registers/BitfieldRegister32_t.h"
#include "Common/Util/MathUtil/MathUtil.h"

BitfieldRegister32_t::BitfieldRegister32_t()
{
}

BitfieldRegister32_t::~BitfieldRegister32_t()
{
}

u32 BitfieldRegister32_t::getBitRange32(u8 startPosition, u8 bitLength)
{
	return MathUtil::extractMaskedValue32(UW, startPosition, bitLength);
}

void BitfieldRegister32_t::setBitRange32(u8 startPosition, u8 bitLength, u32 value)
{
	UW = MathUtil::insertMaskedValue32(UW, value, startPosition, bitLength);
}

void BitfieldRegister32_t::writeWordU(u32 value)
{
	Register32_t::writeWordU(value);
	BitfieldMap32_t::syncMapFromMemory();
}

void BitfieldRegister32_t::writeWordS(s32 value)
{
	writeWordU(static_cast<u32>(value));
}
