#include "stdafx.h"

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/PhysicalMMU/MappedFIFOQueue_t.h"

MappedFIFOQueue_t::MappedFIFOQueue_t(const u32& physicalAddress, const std::shared_ptr<FIFOQueue_t> & fifoQueue) :
	PhysicalMapped(physicalAddress),
	mFIFOQueue(fifoQueue)
{
}

MappedFIFOQueue_t::~MappedFIFOQueue_t()
{
}

size_t MappedFIFOQueue_t::getSize()
{
	// TODO: check if return size is always 16 bytes (128-bit) regardless of max fifo size listed?
	return Constants::NUMBER_BYTES_IN_QWORD; 
}

const char* MappedFIFOQueue_t::getMnemonic() const
{
	return mFIFOQueue->getMnemonic();
}

u8 MappedFIFOQueue_t::readByte(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

void MappedFIFOQueue_t::writeByte(u32 storageIndex, u8 value)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

u16 MappedFIFOQueue_t::readHword(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

void MappedFIFOQueue_t::writeHword(u32 storageIndex, u16 value)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

u32 MappedFIFOQueue_t::readWord(u32 storageIndex)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueue_t with non-zero index. Not allowed.");
	return mFIFOQueue->readWord();
}

void MappedFIFOQueue_t::writeWord(u32 storageIndex, u32 value)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueue_t with non-zero index. Not allowed.");
	mFIFOQueue->writeWord(value);
}

u64 MappedFIFOQueue_t::readDword(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

void MappedFIFOQueue_t::writeDword(u32 storageIndex, u64 value)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

u128 MappedFIFOQueue_t::readQword(u32 storageIndex)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueue_t with non-zero index. Not allowed.");
	return mFIFOQueue->readQword();
}

void MappedFIFOQueue_t::writeQword(u32 storageIndex, u128 value)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueue_t with non-zero index. Not allowed.");
	mFIFOQueue->writeQword(value);
}
