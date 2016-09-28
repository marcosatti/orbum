#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/PS2Resources/Types/Registers/BitfieldRegister32_t.h"
#include <Common/Util/MathUtil/MathUtil.h>

BitfieldRegister32_t::BitfieldRegister32_t() :
	BitfieldMap32_t(false)
{
}

u32 BitfieldRegister32_t::getRegisterValue()
{
	// Need to sync Register value with the individual fields first.
	syncMemoryFromMap();

	// Return the bitfield value;
	return UW;
}

void BitfieldRegister32_t::setRegisterValue(const u32 & value)
{
	// Need to sync the parsed value with the Register first.
	UW = value;

	// Set fields based on UW value.
	syncMapFromMemory();
}

u32 BitfieldRegister32_t::getBitRange32(u8 startPosition, u8 bitLength)
{
	return MathUtil::extractMaskedValue32(UW, startPosition, bitLength);
}

void BitfieldRegister32_t::setBitRange32(u8 startPosition, u8 bitLength, u32 value)
{
	UW = MathUtil::insertMaskedValue32(UW, value, startPosition, bitLength);
}
