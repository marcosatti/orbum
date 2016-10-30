#include "stdafx.h"

#include <stdexcept>

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/Types/MappedMemory/BusErrorMMemory_t.h"

BusErrorMMemory_t::BusErrorMMemory_t(const size_t & size, const char *const mnemonic, const u32 & PS2PhysicalAddress) :
	MappedMemory_t(0, mnemonic, PS2PhysicalAddress),
	mSize(size)
{
}

BusErrorMMemory_t::~BusErrorMMemory_t()
{
}

u8 BusErrorMMemory_t::readByteU(u32 storageIndex)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

void BusErrorMMemory_t::writeByteU(u32 storageIndex, u8 value)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

s8 BusErrorMMemory_t::readByteS(u32 storageIndex)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

void BusErrorMMemory_t::writeByteS(u32 storageIndex, s8 value)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

u16 BusErrorMMemory_t::readHwordU(u32 storageIndex)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

void BusErrorMMemory_t::writeHwordU(u32 storageIndex, u16 value)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

s16 BusErrorMMemory_t::readHwordS(u32 storageIndex)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

void BusErrorMMemory_t::writeHwordS(u32 storageIndex, s16 value)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

u32 BusErrorMMemory_t::readWordU(u32 storageIndex)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

void BusErrorMMemory_t::writeWordU(u32 storageIndex, u32 value)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

s32 BusErrorMMemory_t::readWordS(u32 storageIndex)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

void BusErrorMMemory_t::writeWordS(u32 storageIndex, s32 value)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

u64 BusErrorMMemory_t::readDwordU(u32 storageIndex)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

void BusErrorMMemory_t::writeDwordU(u32 storageIndex, u64 value)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

s64 BusErrorMMemory_t::readDwordS(u32 storageIndex)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

void BusErrorMMemory_t::writeDwordS(u32 storageIndex, s64 value)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

size_t BusErrorMMemory_t::getMappedSize()
{
	return mSize;
}
