#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/ByteMMU/MapperByteMemoryByteMMU_t.h"

MapperByteMemoryByteMMU_t::MapperByteMemoryByteMMU_t(const u32 physicalAddress, const std::shared_ptr<ByteMemory_t> & memory) :
	MapperBaseObjectByteMMU_t(physicalAddress),
	mMemory(memory)
{
}

size_t MapperByteMemoryByteMMU_t::getSize()
{
	return mMemory->getSize();
}

u8 MapperByteMemoryByteMMU_t::readByte(const Context_t context, const size_t storageIndex)
{
	return mMemory->readByte(context, storageIndex);
}

void MapperByteMemoryByteMMU_t::writeByte(const Context_t context, const size_t storageIndex, const u8 value)
{
	mMemory->writeByte(context, storageIndex, value);
}

u16 MapperByteMemoryByteMMU_t::readHword(const Context_t context, const size_t storageIndex)
{
	return mMemory->readHword(context, storageIndex);
}

void MapperByteMemoryByteMMU_t::writeHword(const Context_t context, const size_t storageIndex, const u16 value)
{
	mMemory->writeHword(context, storageIndex, value);
}

u32 MapperByteMemoryByteMMU_t::readWord(const Context_t context, const size_t storageIndex)
{
	return mMemory->readWord(context, storageIndex);
}

void MapperByteMemoryByteMMU_t::writeWord(const Context_t context, const size_t storageIndex, const u32 value)
{
	mMemory->writeWord(context, storageIndex, value);
}

u64 MapperByteMemoryByteMMU_t::readDword(const Context_t context, const size_t storageIndex)
{
	return mMemory->readDword(context, storageIndex);
}

void MapperByteMemoryByteMMU_t::writeDword(const Context_t context, const size_t storageIndex, const u64 value)
{
	mMemory->writeDword(context, storageIndex, value);
}

u128 MapperByteMemoryByteMMU_t::readQword(const Context_t context, const size_t storageIndex)
{
	return mMemory->readQword(context, storageIndex);
}

void MapperByteMemoryByteMMU_t::writeQword(const Context_t context, const size_t storageIndex, const u128 value)
{
	mMemory->writeQword(context, storageIndex, value);
}
