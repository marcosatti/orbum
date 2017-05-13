#include "stdafx.h"

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/ByteMMU/MapperFIFOQueueByteMMU_t.h"

MapperFIFOQueueByteMMU_t::MapperFIFOQueueByteMMU_t(const u32 physicalAddress, const std::shared_ptr<FIFOQueue_t> & fifoQueue) :
	MapperBaseObjectByteMMU_t(physicalAddress),
	mFIFOQueue(fifoQueue)
{
}

size_t MapperFIFOQueueByteMMU_t::getSize()
{
	// FIFO queue maps to a single byte.
	return 1;
}

u8 MapperFIFOQueueByteMMU_t::readByte(const System_t context, const size_t storageIndex)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueueByteMMU_t with non-zero index. Not allowed.");
	return mFIFOQueue->readByte(context);
}

void MapperFIFOQueueByteMMU_t::writeByte(const System_t context, const size_t storageIndex, const u8 value)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueueByteMMU_t with non-zero index. Not allowed.");
	mFIFOQueue->writeByte(context, value);
}

u16 MapperFIFOQueueByteMMU_t::readHword(const System_t context, const size_t storageIndex)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueueByteMMU_t with non-zero index. Not allowed.");
	return mFIFOQueue->readHword(context);
}

void MapperFIFOQueueByteMMU_t::writeHword(const System_t context, const size_t storageIndex, const u16 value)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueueByteMMU_t with non-zero index. Not allowed.");
	mFIFOQueue->writeHword(context, value);
}

u32 MapperFIFOQueueByteMMU_t::readWord(const System_t context, const size_t storageIndex)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueueByteMMU_t with non-zero index. Not allowed.");
	return mFIFOQueue->readWord(context);
}

void MapperFIFOQueueByteMMU_t::writeWord(const System_t context, const size_t storageIndex, const u32 value)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueueByteMMU_t with non-zero index. Not allowed.");
	mFIFOQueue->writeWord(context, value);
}

u64 MapperFIFOQueueByteMMU_t::readDword(const System_t context, const size_t storageIndex)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueueByteMMU_t with non-zero index. Not allowed.");
	return mFIFOQueue->readDword(context);
}

void MapperFIFOQueueByteMMU_t::writeDword(const System_t context, const size_t storageIndex, const u64 value)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueueByteMMU_t with non-zero index. Not allowed.");
	mFIFOQueue->writeDword(context, value);
}

u128 MapperFIFOQueueByteMMU_t::readQword(const System_t context, const size_t storageIndex)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueueByteMMU_t with non-zero index. Not allowed.");
	return mFIFOQueue->readQword(context);
}

void MapperFIFOQueueByteMMU_t::writeQword(const System_t context, const size_t storageIndex, const u128 value)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueueByteMMU_t with non-zero index. Not allowed.");
	mFIFOQueue->writeQword(context, value);
}
