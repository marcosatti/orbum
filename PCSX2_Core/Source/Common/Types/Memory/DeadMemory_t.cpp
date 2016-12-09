#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/Types/Memory/DeadMemory_t.h"

DeadMemory_t::DeadMemory_t(const size_t & size, const char *const mnemonic) :
	Memory_t(0, mnemonic),
	mSize(size)
{
}

DeadMemory_t::~DeadMemory_t()
{
}

u8 DeadMemory_t::readByteU(u32 storageIndex)
{
	return 0;
}

void DeadMemory_t::writeByteU(u32 storageIndex, u8 value)
{
}

s8 DeadMemory_t::readByteS(u32 storageIndex)
{
	return 0;
}

void DeadMemory_t::writeByteS(u32 storageIndex, s8 value)
{
}

u16 DeadMemory_t::readHwordU(u32 storageIndex)
{
	return 0;
}

void DeadMemory_t::writeHwordU(u32 storageIndex, u16 value)
{
}

s16 DeadMemory_t::readHwordS(u32 storageIndex)
{
	return 0;
}

void DeadMemory_t::writeHwordS(u32 storageIndex, s16 value)
{
}

u32 DeadMemory_t::readWordU(u32 storageIndex)
{
	return 0;
}

void DeadMemory_t::writeWordU(u32 storageIndex, u32 value)
{
}

s32 DeadMemory_t::readWordS(u32 storageIndex)
{
	return 0;
}

void DeadMemory_t::writeWordS(u32 storageIndex, s32 value)
{
}

u64 DeadMemory_t::readDwordU(u32 storageIndex)
{
	return 0;
}

void DeadMemory_t::writeDwordU(u32 storageIndex, u64 value)
{
}

s64 DeadMemory_t::readDwordS(u32 storageIndex)
{
	return 0;
}

void DeadMemory_t::writeDwordS(u32 storageIndex, s64 value)
{
}

size_t DeadMemory_t::getSize()
{
	return mSize;
}
