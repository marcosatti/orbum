#include "stdafx.h"

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/ByteMMU/MapperFIFOQueue8ByteMMU_t.h"

MapperFIFOQueue8ByteMMU_t::MapperFIFOQueue8ByteMMU_t(const u32 physicalAddress, const std::shared_ptr<FIFOQueue_t> & fifoQueue8) :
	MapperBaseObjectByteMMU_t(physicalAddress),
	mFIFOQueue8(fifoQueue8)
{
}

size_t MapperFIFOQueue8ByteMMU_t::getSize()
{
	return 1; 
}

u8 MapperFIFOQueue8ByteMMU_t::readByte(const System_t context, size_t storageIndex)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueue_t with non-zero index. Not allowed.");
	return mFIFOQueue8->readByte(context);
}

void MapperFIFOQueue8ByteMMU_t::writeByte(const System_t context, size_t storageIndex, u8 value)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueue_t with non-zero index. Not allowed.");
	mFIFOQueue8->writeByte(context, value);
}

u16 MapperFIFOQueue8ByteMMU_t::readHword(const System_t context, size_t storageIndex)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

void MapperFIFOQueue8ByteMMU_t::writeHword(const System_t context, size_t storageIndex, u16 value)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

u32 MapperFIFOQueue8ByteMMU_t::readWord(const System_t context, size_t storageIndex)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

void MapperFIFOQueue8ByteMMU_t::writeWord(const System_t context, size_t storageIndex, u32 value)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");	
}

u64 MapperFIFOQueue8ByteMMU_t::readDword(const System_t context, size_t storageIndex)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

void MapperFIFOQueue8ByteMMU_t::writeDword(const System_t context, size_t storageIndex, u64 value)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

u128 MapperFIFOQueue8ByteMMU_t::readQword(const System_t context, size_t storageIndex)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

void MapperFIFOQueue8ByteMMU_t::writeQword(const System_t context, size_t storageIndex, u128 value)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}
