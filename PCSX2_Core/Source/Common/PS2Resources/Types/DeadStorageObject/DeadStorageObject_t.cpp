#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/Types/DeadStorageObject/DeadStorageObject_t.h"


DeadStorageObject_t::DeadStorageObject_t(const size_t & size, const char *const mnemonic, const u32 & PS2PhysicalAddress) :
	StorageObject_t(0, mnemonic, PS2PhysicalAddress),
	mSize(size)
{
}

DeadStorageObject_t::~DeadStorageObject_t()
{
}

u8 DeadStorageObject_t::readByteU(u32 storageIndex)
{
	return 0;
}

void DeadStorageObject_t::writeByteU(u32 storageIndex, u8 value)
{
}

s8 DeadStorageObject_t::readByteS(u32 storageIndex)
{
	return 0;
}

void DeadStorageObject_t::writeByteS(u32 storageIndex, s8 value)
{
}

u16 DeadStorageObject_t::readHwordU(u32 storageIndex)
{
	return 0;
}

void DeadStorageObject_t::writeHwordU(u32 storageIndex, u16 value)
{
}

s16 DeadStorageObject_t::readHwordS(u32 storageIndex)
{
	return 0;
}

void DeadStorageObject_t::writeHwordS(u32 storageIndex, s16 value)
{
}

u32 DeadStorageObject_t::readWordU(u32 storageIndex)
{
	return 0;
}

void DeadStorageObject_t::writeWordU(u32 storageIndex, u32 value)
{
}

s32 DeadStorageObject_t::readWordS(u32 storageIndex)
{
	return 0;
}

void DeadStorageObject_t::writeWordS(u32 storageIndex, s32 value)
{
}

u64 DeadStorageObject_t::readDwordU(u32 storageIndex)
{
	return 0;
}

void DeadStorageObject_t::writeDwordU(u32 storageIndex, u64 value)
{
}

s64 DeadStorageObject_t::readDwordS(u32 storageIndex)
{
	return 0;
}

void DeadStorageObject_t::writeDwordS(u32 storageIndex, s64 value)
{
}

size_t DeadStorageObject_t::getStorageSize()
{
	return mSize;
}
