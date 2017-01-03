#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/Types/Registers/RevBitfieldRegister32_t.h"

RevBitfieldRegister32_t::RevBitfieldRegister32_t()
{
}

RevBitfieldRegister32_t::~RevBitfieldRegister32_t()
{
}

void RevBitfieldRegister32_t::writeWord(const Context_t & context, u32 value)
{
	BitfieldRegister32_t::writeWord(Context_t::RAW, readWord(Context_t::RAW) ^ value);
}