#include "stdafx.h"

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/PhysicalMMU/MappedFIFOQueue_t.h"

MappedFIFOQueue_t::MappedFIFOQueue_t(const u32& physicalAddress, const std::shared_ptr<FIFOQueue_t> & fifoQueue) :
	PhysicalMapped_t(physicalAddress),
	mFIFOQueue(fifoQueue)
{
}

MappedFIFOQueue_t::~MappedFIFOQueue_t()
{
}

size_t MappedFIFOQueue_t::getSize()
{
	// TODO: check if return size is always 16 bytes (128-bits) regardless of max fifo size listed? Should be as this is for the mem-map size, not the fifo size.
	return Constants::NUMBER_BYTES_IN_QWORD; 
}

const char* MappedFIFOQueue_t::getMnemonic() const
{
	return mFIFOQueue->getMnemonic();
}

u8 MappedFIFOQueue_t::readByte(const Context_t& context, size_t storageIndex)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

void MappedFIFOQueue_t::writeByte(const Context_t& context, size_t storageIndex, u8 value)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

u16 MappedFIFOQueue_t::readHword(const Context_t& context, size_t storageIndex)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

void MappedFIFOQueue_t::writeHword(const Context_t& context, size_t storageIndex, u16 value)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

u32 MappedFIFOQueue_t::readWord(const Context_t& context, size_t storageIndex)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueue_t with non-zero index. Not allowed.");
	return mFIFOQueue->readWord(context);
}

void MappedFIFOQueue_t::writeWord(const Context_t& context, size_t storageIndex, u32 value)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueue_t with non-zero index. Not allowed.");
	mFIFOQueue->writeWord(context, value);
}

u64 MappedFIFOQueue_t::readDword(const Context_t& context, size_t storageIndex)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

void MappedFIFOQueue_t::writeDword(const Context_t& context, size_t storageIndex, u64 value)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

u128 MappedFIFOQueue_t::readQword(const Context_t& context, size_t storageIndex)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueue_t with non-zero index. Not allowed.");
	return mFIFOQueue->readQword(context);
}

void MappedFIFOQueue_t::writeQword(const Context_t& context, size_t storageIndex, u128 value)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueue_t with non-zero index. Not allowed.");
	mFIFOQueue->writeQword(context, value);
}
