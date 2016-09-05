#include "stdafx.h"
#include "Common/PS2Resources/Types/PS2DeadStorageObject/PS2DeadStorageObject_t.h"


PS2DeadStorageObject_t::PS2DeadStorageObject_t(const size_t & size, const char *const mnemonic, const u32 & PS2PhysicalAddress)
	: PS2StorageObject_t(size, mnemonic, PS2PhysicalAddress) 
{
}

PS2DeadStorageObject_t::~PS2DeadStorageObject_t()
{
}

u8 PS2DeadStorageObject_t::readByteU(u32 storageIndex)
{
	return 0;
}

void PS2DeadStorageObject_t::writeByteU(u32 storageIndex, u8 value)
{
}

s8 PS2DeadStorageObject_t::readByteS(u32 storageIndex)
{
	return 0;
}

void PS2DeadStorageObject_t::writeByteS(u32 storageIndex, s8 value)
{
}

u16 PS2DeadStorageObject_t::readHwordU(u32 storageIndex)
{
	return 0;
}

void PS2DeadStorageObject_t::writeHwordU(u32 storageIndex, u16 value)
{
}

s16 PS2DeadStorageObject_t::readHwordS(u32 storageIndex)
{
	return 0;
}

void PS2DeadStorageObject_t::writeHwordS(u32 storageIndex, s16 value)
{
}

u32 PS2DeadStorageObject_t::readWordU(u32 storageIndex)
{
	return 0;
}

void PS2DeadStorageObject_t::writeWordU(u32 storageIndex, u32 value)
{
}

s32 PS2DeadStorageObject_t::readWordS(u32 storageIndex)
{
	return 0;
}

void PS2DeadStorageObject_t::writeWordS(u32 storageIndex, s32 value)
{
}

u64 PS2DeadStorageObject_t::readDwordU(u32 storageIndex)
{
	return 0;
}

void PS2DeadStorageObject_t::writeDwordU(u32 storageIndex, u64 value)
{
}

s64 PS2DeadStorageObject_t::readDwordS(u32 storageIndex)
{
	return 0;
}

void PS2DeadStorageObject_t::writeDwordS(u32 storageIndex, s64 value)
{
}