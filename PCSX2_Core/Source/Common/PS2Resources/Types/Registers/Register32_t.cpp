#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/PS2Resources/Types/Registers/Register32_t.h"

Register32_t::Register32_t() : UW(0)
{
}

u8 Register32_t::readByteU(u32 arrayIndex)
{
	return UB[arrayIndex];
}

void Register32_t::writeByteU(u32 arrayIndex, u8 value)
{
	UB[arrayIndex] = value;
}

s8 Register32_t::readByteS(u32 arrayIndex)
{
	return SB[arrayIndex];
}

void Register32_t::writeByteS(u32 arrayIndex, s8 value)
{
	SB[arrayIndex] = value;
}

u16 Register32_t::readHwordU(u32 arrayIndex)
{
	return UH[arrayIndex];
}

void Register32_t::writeHwordU(u32 arrayIndex, u16 value)
{
	UH[arrayIndex] = value;
}

s16 Register32_t::readHwordS(u32 arrayIndex)
{
	return SH[arrayIndex];
}

void Register32_t::writeHwordS(u32 arrayIndex, s16 value)
{
	SH[arrayIndex] = value;
}

u32 Register32_t::readWordU()
{
	return UW;
}

void Register32_t::writeWordU(u32 value)
{
	UW = value;
}

s32 Register32_t::readWordS()
{
	return SW;
}

void Register32_t::writeWordS(s32 value)
{
	SW = value;
}

u8 Register32_t::getBit32(u8 index) const
{
	return (UW >> index) & 0x1;
}

void Register32_t::setBit32(u8 index, u32 bitValue)
{
	u32 resetBitMask = 0x0;
	u32 oneMask = 0x1;
	resetBitMask = ~(resetBitMask | (oneMask << index));
	UW = (UW & resetBitMask) | (bitValue << index);
}

u32 Register32_t::getBitRange32(u8 startPosition, u8 bitLength) const
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

void Register32_t::setBitRange32(u8 startPosition, u8 bitLength, u32 value)
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
