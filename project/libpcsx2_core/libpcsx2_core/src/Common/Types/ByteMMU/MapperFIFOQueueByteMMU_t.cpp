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

u8 MapperFIFOQueueByteMMU_t::readByte(const Context_t context, const size_t storageIndex)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueueByteMMU_t with non-zero index. Not allowed.");
	
	u8 value;
	if (!mFIFOQueue->read(context, reinterpret_cast<u8*>(&value), 1))
		throw std::runtime_error("MapperFIFOQueueByteMMU_t: read from FIFO queue failed. Please debug.");
	return value;
}

void MapperFIFOQueueByteMMU_t::writeByte(const Context_t context, const size_t storageIndex, const u8 value)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueueByteMMU_t with non-zero index. Not allowed.");
	
	if (!mFIFOQueue->write(context, reinterpret_cast<const u8*>(&value), 1))
		throw std::runtime_error("MapperFIFOQueueByteMMU_t: write to FIFO queue failed. Please debug.");
}

u16 MapperFIFOQueueByteMMU_t::readHword(const Context_t context, const size_t storageIndex)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueueByteMMU_t with non-zero index. Not allowed.");
	
	u16 value;
	if (!mFIFOQueue->read(context, reinterpret_cast<u8*>(&value), Constants::NUMBER_BYTES_IN_HWORD))
		throw std::runtime_error("MapperFIFOQueueByteMMU_t: read from FIFO queue failed. Please debug.");
	return value;
}

void MapperFIFOQueueByteMMU_t::writeHword(const Context_t context, const size_t storageIndex, const u16 value)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueueByteMMU_t with non-zero index. Not allowed.");
	
	if (!mFIFOQueue->write(context, reinterpret_cast<const u8*>(&value), Constants::NUMBER_BYTES_IN_HWORD))
		throw std::runtime_error("MapperFIFOQueueByteMMU_t: write to FIFO queue failed. Please debug.");
}

u32 MapperFIFOQueueByteMMU_t::readWord(const Context_t context, const size_t storageIndex)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueueByteMMU_t with non-zero index. Not allowed.");

	u32 value;
	if (!mFIFOQueue->read(context, reinterpret_cast<u8*>(&value), Constants::NUMBER_BYTES_IN_WORD))
		throw std::runtime_error("MapperFIFOQueueByteMMU_t: read from FIFO queue failed. Please debug.");
	return value;
}

void MapperFIFOQueueByteMMU_t::writeWord(const Context_t context, const size_t storageIndex, const u32 value)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueueByteMMU_t with non-zero index. Not allowed.");
	
	if (!mFIFOQueue->write(context, reinterpret_cast<const u8*>(&value), Constants::NUMBER_BYTES_IN_WORD))
		throw std::runtime_error("MapperFIFOQueueByteMMU_t: write to FIFO queue failed. Please debug.");
}

u64 MapperFIFOQueueByteMMU_t::readDword(const Context_t context, const size_t storageIndex)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueueByteMMU_t with non-zero index. Not allowed.");
	
	u64 value;
	if (!mFIFOQueue->read(context, reinterpret_cast<u8*>(&value), Constants::NUMBER_BYTES_IN_DWORD))
		throw std::runtime_error("MapperFIFOQueueByteMMU_t: read from FIFO queue failed. Please debug.");
	return value;
}

void MapperFIFOQueueByteMMU_t::writeDword(const Context_t context, const size_t storageIndex, const u64 value)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueueByteMMU_t with non-zero index. Not allowed.");
	
	if (!mFIFOQueue->write(context, reinterpret_cast<const u8*>(&value), Constants::NUMBER_BYTES_IN_DWORD))
		throw std::runtime_error("MapperFIFOQueueByteMMU_t: write to FIFO queue failed. Please debug.");
}

u128 MapperFIFOQueueByteMMU_t::readQword(const Context_t context, const size_t storageIndex)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueueByteMMU_t with non-zero index. Not allowed.");
	
	u128 value;
	if (!mFIFOQueue->read(context, reinterpret_cast<u8*>(&value), Constants::NUMBER_BYTES_IN_QWORD))
		throw std::runtime_error("MapperFIFOQueueByteMMU_t: read from FIFO queue failed. Please debug.");
	return value;
}

void MapperFIFOQueueByteMMU_t::writeQword(const Context_t context, const size_t storageIndex, const u128 value)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueueByteMMU_t with non-zero index. Not allowed.");
	
	if (!mFIFOQueue->write(context, reinterpret_cast<const u8*>(&value), Constants::NUMBER_BYTES_IN_QWORD))
		throw std::runtime_error("MapperFIFOQueueByteMMU_t: write to FIFO queue failed. Please debug.");
}
