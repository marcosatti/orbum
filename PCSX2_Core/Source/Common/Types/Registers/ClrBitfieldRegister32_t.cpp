#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/Types/Registers/ClrBitfieldRegister32_t.h"

ClrBitfieldRegister32_t::ClrBitfieldRegister32_t() 
{
}

ClrBitfieldRegister32_t::~ClrBitfieldRegister32_t()
{
}

void ClrBitfieldRegister32_t::writeWord(const Context_t & context, u32 value)
{
	BitfieldRegister32_t::writeWord(Context_t::RAW, readWord(Context_t::RAW) & ~value);
}
