#include "stdafx.h"

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/ByteMMU/MapperFIFOQueue32ByteMMU_t.h"

MapperFIFOQueue32ByteMMU_t::MapperFIFOQueue32ByteMMU_t(const u32 physicalAddress, const std::shared_ptr<FIFOQueue32_t> & fifoQueue32) :
	MapperBaseObjectByteMMU_t(physicalAddress),
	mFIFOQueue32(fifoQueue32)
{
}

size_t MapperFIFOQueue32ByteMMU_t::getSize()
{
	// TODO: check if return size is always 16 bytes (128-bits) regardless of max fifo size listed? Should be as this is for the mem-map size, not the fifo size.
	return Constants::NUMBER_BYTES_IN_QWORD; 
}

u8 MapperFIFOQueue32ByteMMU_t::readByte(const System_t context, size_t storageIndex)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

void MapperFIFOQueue32ByteMMU_t::writeByte(const System_t context, size_t storageIndex, u8 value)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

u16 MapperFIFOQueue32ByteMMU_t::readHword(const System_t context, size_t storageIndex)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

void MapperFIFOQueue32ByteMMU_t::writeHword(const System_t context, size_t storageIndex, u16 value)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

u32 MapperFIFOQueue32ByteMMU_t::readWord(const System_t context, size_t storageIndex)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueue_t with non-zero index. Not allowed.");
	return mFIFOQueue32->readWord(context);
}

void MapperFIFOQueue32ByteMMU_t::writeWord(const System_t context, size_t storageIndex, u32 value)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueue_t with non-zero index. Not allowed.");
	mFIFOQueue32->writeWord(context, value);
}

u64 MapperFIFOQueue32ByteMMU_t::readDword(const System_t context, size_t storageIndex)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

void MapperFIFOQueue32ByteMMU_t::writeDword(const System_t context, size_t storageIndex, u64 value)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

u128 MapperFIFOQueue32ByteMMU_t::readQword(const System_t context, size_t storageIndex)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueue_t with non-zero index. Not allowed.");
	return mFIFOQueue32->readQword(context);
}

void MapperFIFOQueue32ByteMMU_t::writeQword(const System_t context, size_t storageIndex, u128 value)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueue_t with non-zero index. Not allowed.");
	mFIFOQueue32->writeQword(context, value);
}
