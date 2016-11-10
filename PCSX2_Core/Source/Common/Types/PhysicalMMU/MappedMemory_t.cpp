#include "stdafx.h"

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/PhysicalMMU/MappedMemory_t.h"

MappedMemory_t::MappedMemory_t(const u32& physicalAddress, const std::shared_ptr<Memory_t> & memory) :
	PhysicalMapped(physicalAddress),
	mMemory(memory)
{
}

MappedMemory_t::~MappedMemory_t()
{
}

size_t MappedMemory_t::getSize()
{
	return mMemory->getSize();
}

const char* MappedMemory_t::getMnemonic() const
{
	return mMemory->getMnemonic();
}

u8 MappedMemory_t::readByteU(u32 storageIndex)
{
	return mMemory->readByteU(storageIndex);
}

void MappedMemory_t::writeByteU(u32 storageIndex, u8 value)
{
	mMemory->writeByteU(storageIndex, value);
}

s8 MappedMemory_t::readByteS(u32 storageIndex)
{
	return mMemory->readByteS(storageIndex);	
}

void MappedMemory_t::writeByteS(u32 storageIndex, s8 value)
{
	mMemory->writeByteS(storageIndex, value);
}

u16 MappedMemory_t::readHwordU(u32 storageIndex)
{
	return mMemory->readHwordU(storageIndex);
}

void MappedMemory_t::writeHwordU(u32 storageIndex, u16 value)
{
	mMemory->writeHwordU(storageIndex, value);
}

s16 MappedMemory_t::readHwordS(u32 storageIndex)
{
	return mMemory->readHwordS(storageIndex);
}

void MappedMemory_t::writeHwordS(u32 storageIndex, s16 value)
{
	mMemory->writeHwordS(storageIndex, value);
}

u32 MappedMemory_t::readWordU(u32 storageIndex)
{
	return mMemory->readWordU(storageIndex);
}

void MappedMemory_t::writeWordU(u32 storageIndex, u32 value)
{
	mMemory->writeWordU(storageIndex, value);
}

s32 MappedMemory_t::readWordS(u32 storageIndex)
{
	return mMemory->readWordS(storageIndex);
}

void MappedMemory_t::writeWordS(u32 storageIndex, s32 value)
{
	mMemory->writeWordS(storageIndex, value);
}

u64 MappedMemory_t::readDwordU(u32 storageIndex)
{
	return mMemory->readDwordU(storageIndex);
}

void MappedMemory_t::writeDwordU(u32 storageIndex, u64 value)
{
	mMemory->writeDwordU(storageIndex, value);
}

s64 MappedMemory_t::readDwordS(u32 storageIndex)
{
	return mMemory->readDwordS(storageIndex);
}

void MappedMemory_t::writeDwordS(u32 storageIndex, s64 value)
{
	mMemory->writeDwordS(storageIndex, value);
}