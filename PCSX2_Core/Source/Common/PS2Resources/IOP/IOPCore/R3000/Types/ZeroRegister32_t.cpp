#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/PS2Resources/IOP/IOPCore/R3000/Types/ZeroRegister32_t.h"

void ZeroRegister32_t::writeByteU(u32 arrayIndex, u8 value)
{
	// Do not write value (zero register).
}

void ZeroRegister32_t::writeByteS(u32 arrayIndex, s8 value)
{
	// Do not write value (zero register).
}

void ZeroRegister32_t::writeHwordU(u32 arrayIndex, u16 value)
{
	// Do not write value (zero register).
}

void ZeroRegister32_t::writeHwordS(u32 arrayIndex, s16 value)
{
	// Do not write value (zero register).
}

void ZeroRegister32_t::writeWordU(u32 value)
{
	// Do not write value (zero register).
}

void ZeroRegister32_t::writeWordS(s32 value)
{
	// Do not write value (zero register).
}