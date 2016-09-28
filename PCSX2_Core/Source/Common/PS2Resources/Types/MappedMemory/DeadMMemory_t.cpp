#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/Types/MappedMemory/DeadMMemory_t.h"


DeadMMemory_t::DeadMMemory_t(const size_t & size, const char *const mnemonic, const u32 & PS2PhysicalAddress) :
	MappedMemory_t(0, mnemonic, PS2PhysicalAddress),
	mSize(size)
{
}

DeadMMemory_t::~DeadMMemory_t()
{
}

u8 DeadMMemory_t::readByteU(u32 storageIndex)
{
	return 0;
}

void DeadMMemory_t::writeByteU(u32 storageIndex, u8 value)
{
}

s8 DeadMMemory_t::readByteS(u32 storageIndex)
{
	return 0;
}

void DeadMMemory_t::writeByteS(u32 storageIndex, s8 value)
{
}

u16 DeadMMemory_t::readHwordU(u32 storageIndex)
{
	return 0;
}

void DeadMMemory_t::writeHwordU(u32 storageIndex, u16 value)
{
}

s16 DeadMMemory_t::readHwordS(u32 storageIndex)
{
	return 0;
}

void DeadMMemory_t::writeHwordS(u32 storageIndex, s16 value)
{
}

u32 DeadMMemory_t::readWordU(u32 storageIndex)
{
	return 0;
}

void DeadMMemory_t::writeWordU(u32 storageIndex, u32 value)
{
}

s32 DeadMMemory_t::readWordS(u32 storageIndex)
{
	return 0;
}

void DeadMMemory_t::writeWordS(u32 storageIndex, s32 value)
{
}

u64 DeadMMemory_t::readDwordU(u32 storageIndex)
{
	return 0;
}

void DeadMMemory_t::writeDwordU(u32 storageIndex, u64 value)
{
}

s64 DeadMMemory_t::readDwordS(u32 storageIndex)
{
	return 0;
}

void DeadMMemory_t::writeDwordS(u32 storageIndex, s64 value)
{
}

size_t DeadMMemory_t::getStorageSize()
{
	return mSize;
}
