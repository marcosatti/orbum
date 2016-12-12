#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/Types/Memory/ZeroMemory_t.h"

ZeroMemory_t::ZeroMemory_t(const size_t & size, const char *const mnemonic) :
	Memory_t(0, mnemonic),
	mSize(size)
{
}

ZeroMemory_t::~ZeroMemory_t()
{
}

u8 ZeroMemory_t::readByteU(u32 storageIndex)
{
	return 0;
}

void ZeroMemory_t::writeByteU(u32 storageIndex, u8 value)
{
}

s8 ZeroMemory_t::readByteS(u32 storageIndex)
{
	return 0;
}

void ZeroMemory_t::writeByteS(u32 storageIndex, s8 value)
{
}

u16 ZeroMemory_t::readHwordU(u32 storageIndex)
{
	return 0;
}

void ZeroMemory_t::writeHwordU(u32 storageIndex, u16 value)
{
}

s16 ZeroMemory_t::readHwordS(u32 storageIndex)
{
	return 0;
}

void ZeroMemory_t::writeHwordS(u32 storageIndex, s16 value)
{
}

u32 ZeroMemory_t::readWordU(u32 storageIndex)
{
	return 0;
}

void ZeroMemory_t::writeWordU(u32 storageIndex, u32 value)
{
}

s32 ZeroMemory_t::readWordS(u32 storageIndex)
{
	return 0;
}

void ZeroMemory_t::writeWordS(u32 storageIndex, s32 value)
{
}

u64 ZeroMemory_t::readDwordU(u32 storageIndex)
{
	return 0;
}

void ZeroMemory_t::writeDwordU(u32 storageIndex, u64 value)
{
}

s64 ZeroMemory_t::readDwordS(u32 storageIndex)
{
	return 0;
}

void ZeroMemory_t::writeDwordS(u32 storageIndex, s64 value)
{
}

size_t ZeroMemory_t::getSize()
{
	return mSize;
}
