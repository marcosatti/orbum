#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/Types/Registers/ClrBitfieldRegister32_t.h"

ClrBitfieldRegister32_t::ClrBitfieldRegister32_t() 
{
}

ClrBitfieldRegister32_t::~ClrBitfieldRegister32_t()
{
}

void ClrBitfieldRegister32_t::writeWordU(u32 value)
{
	BitfieldRegister32_t::writeWordU(readWordU() & ~value);
}
