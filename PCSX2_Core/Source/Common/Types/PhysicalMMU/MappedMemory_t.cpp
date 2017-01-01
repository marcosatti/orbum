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

u8 MappedMemory_t::readByte(u32 storageIndex)
{
	return mMemory->readByte(storageIndex);
}

void MappedMemory_t::writeByte(u32 storageIndex, u8 value)
{
	mMemory->writeByte(storageIndex, value);
}

u16 MappedMemory_t::readHword(u32 storageIndex)
{
	return mMemory->readHword(storageIndex);
}

void MappedMemory_t::writeHword(u32 storageIndex, u16 value)
{
	mMemory->writeHword(storageIndex, value);
}

u32 MappedMemory_t::readWord(u32 storageIndex)
{
	return mMemory->readWord(storageIndex);
}

void MappedMemory_t::writeWord(u32 storageIndex, u32 value)
{
	mMemory->writeWord(storageIndex, value);
}

u64 MappedMemory_t::readDword(u32 storageIndex)
{
	return mMemory->readDword(storageIndex);
}

void MappedMemory_t::writeDword(u32 storageIndex, u64 value)
{
	mMemory->writeDword(storageIndex, value);
}

u128 MappedMemory_t::readQword(u32 storageIndex)
{
	return mMemory->readQword(storageIndex);
}

void MappedMemory_t::writeQword(u32 storageIndex, u128 value)
{
	mMemory->writeQword(storageIndex, value);
}
