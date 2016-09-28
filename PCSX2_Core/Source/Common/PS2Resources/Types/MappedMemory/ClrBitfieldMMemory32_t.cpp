#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/Types/MappedMemory/ClrBitfieldMMemory32_t.h"

ClrBitfieldMMemory32_t::ClrBitfieldMMemory32_t(const char *const mnemonic, const u32 & PS2PhysicalAddress) :
	BitfieldMMemory32_t(mnemonic, PS2PhysicalAddress)
{
}

ClrBitfieldMMemory32_t::~ClrBitfieldMMemory32_t()
{
}

void ClrBitfieldMMemory32_t::writeWordU(u32 storageIndex, u32 value)
{
	BitfieldMMemory32_t::writeWordU(storageIndex, readWordU(0) & ~value);
}
