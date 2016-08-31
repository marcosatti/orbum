#include "stdafx.h"
#include "Common/Types/StorageObject/DeadStorage_t.h"


DeadStorage_t::DeadStorage_t(const size_t & size, const std::string mnemonic)
	: StorageObject_t(size, mnemonic) 
{
}

DeadStorage_t::~DeadStorage_t()
{
}

u8 DeadStorage_t::readByteU(u32 storageIndex) const
{
	return 0;
}

void DeadStorage_t::writeByteU(u32 storageIndex, u8 value)
{
}

s8 DeadStorage_t::readByteS(u32 storageIndex) const
{
	return 0;
}

void DeadStorage_t::writeByteS(u32 storageIndex, s8 value)
{
}

u16 DeadStorage_t::readHwordU(u32 storageIndex) const
{
	return 0;
}

void DeadStorage_t::writeHwordU(u32 storageIndex, u16 value)
{
}

s16 DeadStorage_t::readHwordS(u32 storageIndex) const
{
	return 0;
}

void DeadStorage_t::writeHwordS(u32 storageIndex, s16 value)
{
}

u32 DeadStorage_t::readWordU(u32 storageIndex) const
{
	return 0;
}

void DeadStorage_t::writeWordU(u32 storageIndex, u32 value)
{
}

s32 DeadStorage_t::readWordS(u32 storageIndex) const
{
	return 0;
}

void DeadStorage_t::writeWordS(u32 storageIndex, s32 value)
{
}

u64 DeadStorage_t::readDwordU(u32 storageIndex) const
{
	return 0;
}

void DeadStorage_t::writeDwordU(u32 storageIndex, u64 value)
{
}

s64 DeadStorage_t::readDwordS(u32 storageIndex) const
{
	return 0;
}

void DeadStorage_t::writeDwordS(u32 storageIndex, s64 value)
{
}