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