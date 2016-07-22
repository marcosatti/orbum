#include "stdafx.h"

#include "Globals.h"
#include "Register_t.h"

Register128_t::Register128_t() : UQ()
{
}

u8 Register128_t::getBit128(u8 index) const
{
	if (index > 63) return (UQ.hi >> index) & 0x1;
	else return (UQ.lo >> index) & 0x1;
}

void Register128_t::setBit128(u8 index, u64 bitValue)
{
	u64 resetBitMask = 0x0;
	u64 oneMask = 0x1;
	if (index > 63) {
		u8 upperIndex = index - 64;
		resetBitMask = ~(resetBitMask | (oneMask << upperIndex));
		UQ.hi = (UQ.hi & resetBitMask) | (bitValue << upperIndex);
	}
	else {
		resetBitMask = ~(resetBitMask | (oneMask << index));
		UQ.lo = (UQ.lo & resetBitMask) | (bitValue << index);
	}
}

Register64_t::Register64_t() : UD(0)
{
}

u8 Register64_t::getBit64(u8 index) const
{
	return (UD >> index) & 0x1;
}

void Register64_t::setBit64(u8 index, u64 bitValue)
{
	u64 resetBitMask = 0x0;
	u64 oneMask = 0x1;
	resetBitMask = ~(resetBitMask | (oneMask << index));
	UD = (UD & resetBitMask) | (bitValue << index);
}

Register32_t::Register32_t() : UW(0)
{
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
