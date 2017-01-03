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

u8 MappedMemory_t::readByte(const Context_t& context, u32 storageIndex)
{
	return mMemory->readByte(storageIndex);
}

void MappedMemory_t::writeByte(const Context_t& context, u32 storageIndex, u8 value)
{
	mMemory->writeByte(storageIndex, value);
}

u16 MappedMemory_t::readHword(const Context_t& context, u32 storageIndex)
{
	return mMemory->readHword(storageIndex);
}

void MappedMemory_t::writeHword(const Context_t& context, u32 storageIndex, u16 value)
{
	mMemory->writeHword(storageIndex, value);
}

u32 MappedMemory_t::readWord(const Context_t& context, u32 storageIndex)
{
	return mMemory->readWord(storageIndex);
}

void MappedMemory_t::writeWord(const Context_t& context, u32 storageIndex, u32 value)
{
	mMemory->writeWord(storageIndex, value);
}

u64 MappedMemory_t::readDword(const Context_t& context, u32 storageIndex)
{
	return mMemory->readDword(storageIndex);
}

void MappedMemory_t::writeDword(const Context_t& context, u32 storageIndex, u64 value)
{
	mMemory->writeDword(storageIndex, value);
}

u128 MappedMemory_t::readQword(const Context_t& context, u32 storageIndex)
{
	return mMemory->readQword(storageIndex);
}

void MappedMemory_t::writeQword(const Context_t& context, u32 storageIndex, u128 value)
{
	mMemory->writeQword(storageIndex, value);
}
