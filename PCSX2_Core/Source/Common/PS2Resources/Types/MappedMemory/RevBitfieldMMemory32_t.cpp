#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/Types/MappedMemory/RevBitfieldMMemory32_t.h"

RevBitfieldMMemory32_t::RevBitfieldMMemory32_t(const char *const mnemonic, const u32 & PS2PhysicalAddress) :
	BitfieldMMemory32_t(mnemonic, PS2PhysicalAddress)
{
}

RevBitfieldMMemory32_t::~RevBitfieldMMemory32_t()
{
}

void RevBitfieldMMemory32_t::writeWordU(u32 storageIndex, u32 value)
{
	BitfieldMMemory32_t::writeWordU(storageIndex, readWordU(0) ^ value);
}