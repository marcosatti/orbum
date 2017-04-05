#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Register/ConstantRegister32_t.h"

ConstantRegister32_t::ConstantRegister32_t(const u32 W)
{
	UW = W;
}

void ConstantRegister32_t::writeByte(const System_t context, size_t arrayIndex, u8 value)
{
	// Do not write value (zero register).
}

void ConstantRegister32_t::writeHword(const System_t context, size_t arrayIndex, u16 value)
{
	// Do not write value (zero register).
}

void ConstantRegister32_t::writeWord(const System_t context, u32 value)
{
	// Do not write value (zero register).
}

void ConstantRegister32_t::initalise()
{
}
