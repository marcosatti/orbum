#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/Types/StorageObject/RevBitfieldStorageObject32_t.h"

RevBitfieldStorageObject32_t::RevBitfieldStorageObject32_t(const char *const mnemonic, const u32 & PS2PhysicalAddress) :
	BitfieldStorageObject32_t(mnemonic, PS2PhysicalAddress)
{
}

RevBitfieldStorageObject32_t::~RevBitfieldStorageObject32_t()
{
}

void RevBitfieldStorageObject32_t::writeWordU(u32 storageIndex, u32 value)
{
	BitfieldStorageObject32_t::writeWordU(storageIndex, readWordU(0) ^ value);
}