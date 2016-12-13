#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/Types/Memory/ConstantMemory_t.h"

ConstantMemory_t::ConstantMemory_t(const size_t & size, const char *const mnemonic, const u64 D) :
	Memory_t(0, mnemonic),
	mSize(size),
	mConstantValue(D)
{
}

ConstantMemory_t::~ConstantMemory_t()
{
}

u8 ConstantMemory_t::readByteU(u32 storageIndex)
{
	return static_cast<u8>(mConstantValue);
}

void ConstantMemory_t::writeByteU(u32 storageIndex, u8 value)
{
}

s8 ConstantMemory_t::readByteS(u32 storageIndex)
{
	return static_cast<s8>(mConstantValue);
}

void ConstantMemory_t::writeByteS(u32 storageIndex, s8 value)
{
}

u16 ConstantMemory_t::readHwordU(u32 storageIndex)
{
	return static_cast<u16>(mConstantValue);
}

void ConstantMemory_t::writeHwordU(u32 storageIndex, u16 value)
{
}

s16 ConstantMemory_t::readHwordS(u32 storageIndex)
{
	return static_cast<s16>(mConstantValue);
}

void ConstantMemory_t::writeHwordS(u32 storageIndex, s16 value)
{
}

u32 ConstantMemory_t::readWordU(u32 storageIndex)
{
	return static_cast<u32>(mConstantValue);
}

void ConstantMemory_t::writeWordU(u32 storageIndex, u32 value)
{
}

s32 ConstantMemory_t::readWordS(u32 storageIndex)
{
	return static_cast<s32>(mConstantValue);
}

void ConstantMemory_t::writeWordS(u32 storageIndex, s32 value)
{
}

u64 ConstantMemory_t::readDwordU(u32 storageIndex)
{
	return static_cast<u64>(mConstantValue);
}

void ConstantMemory_t::writeDwordU(u32 storageIndex, u64 value)
{
}

s64 ConstantMemory_t::readDwordS(u32 storageIndex)
{
	return static_cast<s64>(mConstantValue);
}

void ConstantMemory_t::writeDwordS(u32 storageIndex, s64 value)
{
}

size_t ConstantMemory_t::getSize()
{
	return mSize;
}
