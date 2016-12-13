#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/ConstantRegister32_t.h"

ConstantRegister32_t::ConstantRegister32_t(const u32 W)
{
	UW = W;
}

void ConstantRegister32_t::writeByteU(u32 arrayIndex, u8 value)
{
	// Do not write value (zero register).
}

void ConstantRegister32_t::writeByteS(u32 arrayIndex, s8 value)
{
	// Do not write value (zero register).
}

void ConstantRegister32_t::writeHwordU(u32 arrayIndex, u16 value)
{
	// Do not write value (zero register).
}

void ConstantRegister32_t::writeHwordS(u32 arrayIndex, s16 value)
{
	// Do not write value (zero register).
}

void ConstantRegister32_t::writeWordU(u32 value)
{
	// Do not write value (zero register).
}

void ConstantRegister32_t::writeWordS(s32 value)
{
	// Do not write value (zero register).
}