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

u8 MappedFIFOQueue_t::readByteU(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

void MappedFIFOQueue_t::writeByteU(u32 storageIndex, u8 value)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

s8 MappedFIFOQueue_t::readByteS(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

void MappedFIFOQueue_t::writeByteS(u32 storageIndex, s8 value)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

u16 MappedFIFOQueue_t::readHwordU(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

void MappedFIFOQueue_t::writeHwordU(u32 storageIndex, u16 value)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

s16 MappedFIFOQueue_t::readHwordS(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

void MappedFIFOQueue_t::writeHwordS(u32 storageIndex, s16 value)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

u32 MappedFIFOQueue_t::readWordU(u32 storageIndex)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueue_t with non-zero index. Not allowed.");
	return mFIFOQueue->readWordU();
}

void MappedFIFOQueue_t::writeWordU(u32 storageIndex, u32 value)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueue_t with non-zero index. Not allowed.");
	mFIFOQueue->writeWordU(value);
}

s32 MappedFIFOQueue_t::readWordS(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

void MappedFIFOQueue_t::writeWordS(u32 storageIndex, s32 value)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

u64 MappedFIFOQueue_t::readDwordU(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

void MappedFIFOQueue_t::writeDwordU(u32 storageIndex, u64 value)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

s64 MappedFIFOQueue_t::readDwordS(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

void MappedFIFOQueue_t::writeDwordS(u32 storageIndex, s64 value)
{
	throw std::runtime_error("Tried to access MappedFIFOQueue_t with invalid function. Not allowed.");
}

u128 MappedFIFOQueue_t::readQwordU(u32 storageIndex)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueue_t with non-zero index. Not allowed.");
	return mFIFOQueue->readQwordU();
}

void MappedFIFOQueue_t::writeQwordU(u32 storageIndex, u128 value)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedFIFOQueue_t with non-zero index. Not allowed.");
	mFIFOQueue->writeQwordU(value);
}
