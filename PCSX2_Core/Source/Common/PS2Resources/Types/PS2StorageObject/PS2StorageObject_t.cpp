#include "stdafx.h"
#include "Common/PS2Resources/Types/PS2StorageObject/PS2StorageObject_t.h"


PS2StorageObject_t::PS2StorageObject_t(const size_t & size, const char *const mnemonic, const u32 & PS2PhysicalAddress)
	: StorageObject_t(size, mnemonic),
	mPS2PhysicalAddress(PS2PhysicalAddress)
{
}


PS2StorageObject_t::~PS2StorageObject_t()
{
}

const u32& PS2StorageObject_t::getPS2PhysicalAddress() const
{
	return mPS2PhysicalAddress;
}
