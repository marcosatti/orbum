#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/ZeroRegister16_t.h"

void ZeroRegister16_t::writeByteU(u32 arrayIndex, u8 value)
{
	// Do not write value (zero register).
}

void ZeroRegister16_t::writeByteS(u32 arrayIndex, s8 value)
{
	// Do not write value (zero register).
}

void ZeroRegister16_t::writeHwordU(u16 value)
{
	// Do not write value (zero register).
}

void ZeroRegister16_t::writeHwordS(s16 value)
{
	// Do not write value (zero register).
}