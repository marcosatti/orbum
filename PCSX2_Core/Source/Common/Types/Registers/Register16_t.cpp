#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/Register16_t.h"

Register16_t::Register16_t() : 
	UH(0)
{
}

u8 Register16_t::readByteU(u32 arrayIndex)
{
	return UB[arrayIndex];
}

void Register16_t::writeByteU(u32 arrayIndex, u8 value)
{
	UB[arrayIndex] = value;
}

s8 Register16_t::readByteS(u32 arrayIndex)
{
	return SB[arrayIndex];
}

void Register16_t::writeByteS(u32 arrayIndex, s8 value)
{
	SB[arrayIndex] = value;
}

u16 Register16_t::readHwordU()
{
	return UH;
}

void Register16_t::writeHwordU(u16 value)
{
	UH = value;
}

s16 Register16_t::readHwordS()
{
	return SH;
}

void Register16_t::writeHwordS(s16 value)
{
	SH = value;
}
