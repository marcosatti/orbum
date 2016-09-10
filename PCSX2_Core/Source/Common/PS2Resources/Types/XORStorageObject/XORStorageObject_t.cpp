#include "stdafx.h"
#include "XORStorageObject_t.h"

XORStorageObject_t::XORStorageObject_t(const size_t& size, const char* const mnemonic, const u32& PS2PhysicalAddress) :
	StorageObject_t(size, mnemonic, PS2PhysicalAddress)
{
}

XORStorageObject_t::~XORStorageObject_t()
{
}

void XORStorageObject_t::writeByteU(u32 storageIndex, u8 value)
{
	StorageObject_t::writeByteU(storageIndex, StorageObject_t::readByteU(storageIndex) ^ value);
}

void XORStorageObject_t::writeByteS(u32 storageIndex, s8 value)
{
	StorageObject_t::writeByteS(storageIndex, StorageObject_t::readByteS(storageIndex) ^ value);
}

void XORStorageObject_t::writeHwordU(u32 storageIndex, u16 value)
{
	StorageObject_t::writeHwordU(storageIndex, StorageObject_t::readHwordU(storageIndex) ^ value);
}

void XORStorageObject_t::writeHwordS(u32 storageIndex, s16 value)
{
	StorageObject_t::writeHwordS(storageIndex, StorageObject_t::readHwordS(storageIndex) ^ value);
}

void XORStorageObject_t::writeWordU(u32 storageIndex, u32 value)
{
	StorageObject_t::writeWordU(storageIndex, StorageObject_t::readWordU(storageIndex) ^ value);
}

void XORStorageObject_t::writeWordS(u32 storageIndex, s32 value)
{
	StorageObject_t::writeWordS(storageIndex, StorageObject_t::readWordS(storageIndex) ^ value);
}

void XORStorageObject_t::writeDwordU(u32 storageIndex, u64 value)
{
	StorageObject_t::writeDwordU(storageIndex, StorageObject_t::readDwordU(storageIndex) ^ value);
}

void XORStorageObject_t::writeDwordS(u32 storageIndex, s64 value)
{
	StorageObject_t::writeDwordS(storageIndex, StorageObject_t::readDwordS(storageIndex) ^ value);
}
