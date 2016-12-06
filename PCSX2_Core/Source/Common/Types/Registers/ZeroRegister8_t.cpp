#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/ZeroRegister8_t.h"

void ZeroRegister8_t::writeByteU(u8 value)
{
	// Do not write value (zero register).
}

void ZeroRegister8_t::writeByteS(s8 value)
{
	// Do not write value (zero register).
}
