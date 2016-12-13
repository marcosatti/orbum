#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/ConstantRegister8_t.h"

ConstantRegister8_t::ConstantRegister8_t(const u8 B)
{
	UB = B;
}

void ConstantRegister8_t::writeByteU(u8 value)
{
	// Do not write value (zero register).
}

void ConstantRegister8_t::writeByteS(s8 value)
{
	// Do not write value (zero register).
}
