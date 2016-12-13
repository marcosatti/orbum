#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/ConstantRegister16_t.h"

ConstantRegister16_t::ConstantRegister16_t(const u16 H)
{
	UH = H;
}

void ConstantRegister16_t::writeByteU(u32 arrayIndex, u8 value)
{
	// Do not write value (zero register).
}

void ConstantRegister16_t::writeByteS(u32 arrayIndex, s8 value)
{
	// Do not write value (zero register).
}

void ConstantRegister16_t::writeHwordU(u16 value)
{
	// Do not write value (zero register).
}

void ConstantRegister16_t::writeHwordS(s16 value)
{
	// Do not write value (zero register).
}