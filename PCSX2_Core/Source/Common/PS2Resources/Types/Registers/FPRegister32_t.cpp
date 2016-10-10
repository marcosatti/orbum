#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/PS2Resources/Types/Registers/FPRegister32_t.h"

FPRegister32_t::FPRegister32_t() : 
	F(0)
{
}

u32 FPRegister32_t::readWordU()
{
	return UW;
}

void FPRegister32_t::writeWordU(u32 value)
{
	UW = value;
}

s32 FPRegister32_t::readWordS()
{
	return SW;
}

void FPRegister32_t::writeWordS(s32 value)
{
	SW = value;
}

f32 FPRegister32_t::readFloat()
{
	return F;
}

void FPRegister32_t::writeFloat(f32 value)
{
	F = value;
}

u8 FPRegister32_t::getBit32(u8 index) const
{
	return (UW >> index) & 0x1;
}

void FPRegister32_t::setBit32(u8 index, u32 bitValue)
{
	u32 resetBitMask = 0x0;
	u32 oneMask = 0x1;
	resetBitMask = ~(resetBitMask | (oneMask << index));
	UW = (UW & resetBitMask) | (bitValue << index);
}

u32 FPRegister32_t::getBitRange32(u8 startPosition, u8 bitLength) const
{
	u32 endPos = startPosition + bitLength;
	u32 maskTemp1 = (static_cast<u32>(~0x0) << startPosition);
	u32 maskTemp2 = static_cast<u32>(~0x0);

	// This workaround is needed due to how x86 shifts - it only allows for 0 -> 31 in the shl/shr instruction. Therefore if we want to mask the end bit, maskTemp2 will not be shifted as endPos = 32.
	// I have not accounted for if startPosition >= 32 as it is assumed that the user wouldn't try it.
	if (endPos >= 32) maskTemp2 = 0;
	else maskTemp2 = (maskTemp2 << endPos);

	u32 mask = (maskTemp1 ^ maskTemp2);
	u32 value = (UW & mask) >> startPosition;
	return value;
}

void FPRegister32_t::setBitRange32(u8 startPosition, u8 bitLength, u32 value)
{
	u32 endPos = startPosition + bitLength;
	u32 maskTemp1 = (static_cast<u32>(~0x0) << startPosition);
	u32 maskTemp2 = static_cast<u32>(~0x0);

	// This workaround is needed due to how x86 shifts - it only allows for 0 -> 31 in the shl/shr instruction. Therefore if we want to mask the end bit, maskTemp2 will not be shifted as endPos = 32.
	// I have not accounted for if startPosition >= 32 as it is assumed that the user wouldn't try it.
	if (endPos >= 32) maskTemp2 = 0;
	else maskTemp2 = (maskTemp2 << endPos);

	u32 mask = (maskTemp1 ^ maskTemp2);
	u32 maskNot = (~mask);
	UW = (UW & maskNot);
	value = ((value << startPosition) & mask);
	UW = (value | UW);
}