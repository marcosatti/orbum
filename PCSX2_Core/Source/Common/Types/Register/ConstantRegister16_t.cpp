#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Register/ConstantRegister16_t.h"

ConstantRegister16_t::ConstantRegister16_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const u16 H) :
	Register16_t(mnemonic, debugReads, debugWrites)
{
	UH = H;
}

void ConstantRegister16_t::writeByte(const System_t context, size_t arrayIndex, u8 value)
{
	// Do not write value (zero register).
}

void ConstantRegister16_t::writeHword(const System_t context, u16 value)
{
	// Do not write value (zero register).
}

void ConstantRegister16_t::initalise()
{
}
