#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Register/ConstantRegister32_t.h"

ConstantRegister32_t::ConstantRegister32_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const u32 W) :
	Register32_t(mnemonic, debugReads, debugWrites)
{
	UW = W;
}

void ConstantRegister32_t::writeByte(const System_t context, const size_t arrayIndex, const u8 value)
{
	// Do not write value (zero register).
}

void ConstantRegister32_t::writeHword(const System_t context, const size_t arrayIndex, const u16 value)
{
	// Do not write value (zero register).
}

void ConstantRegister32_t::writeWord(const System_t context, const u32 value)
{
	// Do not write value (zero register).
}

void ConstantRegister32_t::initialise()
{
}
