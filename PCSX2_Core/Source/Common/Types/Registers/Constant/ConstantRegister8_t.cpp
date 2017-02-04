#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/Constant/ConstantRegister8_t.h"

ConstantRegister8_t::ConstantRegister8_t(const u8 B)
{
	UB = B;
}

void ConstantRegister8_t::writeByte(const Context& context, u8 value)
{
	// Do not write value (zero register).
}

void ConstantRegister8_t::initalise()
{
}
