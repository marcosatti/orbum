#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/Constant/ConstantRegister128_t.h"

ConstantRegister128_t::ConstantRegister128_t(const u64 D0, const u64 D1)
{
	UD[0] = D0;
	UD[1] = D1;
}

void ConstantRegister128_t::writeByte(const System_t context, size_t arrayIndex, u8 value)
{
	// Do not write value (constant register).
}

void ConstantRegister128_t::writeHword(const System_t context, size_t arrayIndex, u16 value)
{
	// Do not write value (constant register).
}

void ConstantRegister128_t::writeWord(const System_t context, size_t arrayIndex, u32 value)
{
	// Do not write value (constant register).
}

void ConstantRegister128_t::writeDword(const System_t context, size_t arrayIndex, u64 value)
{
	// Do not write value (constant register).
}

void ConstantRegister128_t::writeQword(const System_t context, u128 value)
{
	// Do not write value (constant register).
}

void ConstantRegister128_t::initalise()
{
}
