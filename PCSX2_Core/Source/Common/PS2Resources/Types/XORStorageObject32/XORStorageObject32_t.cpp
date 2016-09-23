#include "stdafx.h"

#include "XORStorageObject32_t.h"

XORStorageObject32_t::XORStorageObject32_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	StorageObject32_t(mnemonic, PS2PhysicalAddress)
{
}

XORStorageObject32_t::~XORStorageObject32_t()
{
}

void XORStorageObject32_t::writeByteU(u32 storageIndex, u8 value)
{
	StorageObject32_t::writeByteU(storageIndex, StorageObject32_t::readByteU(storageIndex) ^ value);
}

void XORStorageObject32_t::writeByteS(u32 storageIndex, s8 value)
{
	StorageObject32_t::writeByteS(storageIndex, StorageObject32_t::readByteS(storageIndex) ^ value);
}

void XORStorageObject32_t::writeHwordU(u32 storageIndex, u16 value)
{
	StorageObject32_t::writeHwordU(storageIndex, StorageObject32_t::readHwordU(storageIndex) ^ value);
}

void XORStorageObject32_t::writeHwordS(u32 storageIndex, s16 value)
{
	StorageObject32_t::writeHwordS(storageIndex, StorageObject32_t::readHwordS(storageIndex) ^ value);
}

void XORStorageObject32_t::writeWordU(u32 storageIndex, u32 value)
{
	StorageObject32_t::writeWordU(storageIndex, StorageObject32_t::readWordU(storageIndex) ^ value);
}

void XORStorageObject32_t::writeWordS(u32 storageIndex, s32 value)
{
	StorageObject32_t::writeWordS(storageIndex, StorageObject32_t::readWordS(storageIndex) ^ value);
}

void XORStorageObject32_t::writeDwordU(u32 storageIndex, u64 value)
{
	StorageObject32_t::writeDwordU(storageIndex, StorageObject32_t::readDwordU(storageIndex) ^ value);
}

void XORStorageObject32_t::writeDwordS(u32 storageIndex, s64 value)
{
	StorageObject32_t::writeDwordS(storageIndex, StorageObject32_t::readDwordS(storageIndex) ^ value);
}
