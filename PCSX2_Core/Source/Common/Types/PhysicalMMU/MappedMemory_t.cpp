#include "stdafx.h"

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/PhysicalMMU/MappedMemory_t.h"

MappedMemory_t::MappedMemory_t(const u32& physicalAddress, const std::shared_ptr<ByteMemory_t> & memory) :
	PhysicalMapped_t(physicalAddress),
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

u8 MappedMemory_t::readByte(const Context_t context, size_t storageIndex)
{
	return mMemory->readByte(context, storageIndex);
}

void MappedMemory_t::writeByte(const Context_t context, size_t storageIndex, u8 value)
{
	mMemory->writeByte(context, storageIndex, value);
}

u16 MappedMemory_t::readHword(const Context_t context, size_t storageIndex)
{
	return mMemory->readHword(context, storageIndex);
}

void MappedMemory_t::writeHword(const Context_t context, size_t storageIndex, u16 value)
{
	mMemory->writeHword(context, storageIndex, value);
}

u32 MappedMemory_t::readWord(const Context_t context, size_t storageIndex)
{
	return mMemory->readWord(context, storageIndex);
}

void MappedMemory_t::writeWord(const Context_t context, size_t storageIndex, u32 value)
{
	mMemory->writeWord(context, storageIndex, value);
}

u64 MappedMemory_t::readDword(const Context_t context, size_t storageIndex)
{
	return mMemory->readDword(context, storageIndex);
}

void MappedMemory_t::writeDword(const Context_t context, size_t storageIndex, u64 value)
{
	mMemory->writeDword(context, storageIndex, value);
}

u128 MappedMemory_t::readQword(const Context_t context, size_t storageIndex)
{
	return mMemory->readQword(context, storageIndex);
}

void MappedMemory_t::writeQword(const Context_t context, size_t storageIndex, u128 value)
{
	mMemory->writeQword(context, storageIndex, value);
}
