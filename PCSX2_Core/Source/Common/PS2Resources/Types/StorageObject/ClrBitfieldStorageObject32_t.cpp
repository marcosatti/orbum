#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/Types/StorageObject/ClrBitfieldStorageObject32_t.h"

ClrBitfieldStorageObject32_t::ClrBitfieldStorageObject32_t(const char *const mnemonic, const u32 & PS2PhysicalAddress) :
	BitfieldStorageObject32_t(mnemonic, PS2PhysicalAddress)
{
}

ClrBitfieldStorageObject32_t::~ClrBitfieldStorageObject32_t()
{
}

void ClrBitfieldStorageObject32_t::writeWordU(u32 storageIndex, u32 value)
{
	BitfieldStorageObject32_t::writeWordU(storageIndex, readWordU(0) & ~value);
}
