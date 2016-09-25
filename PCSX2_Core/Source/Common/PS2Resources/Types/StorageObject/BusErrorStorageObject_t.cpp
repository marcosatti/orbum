#include "stdafx.h"

#include <stdexcept>

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/Types/StorageObject/BusErrorStorageObject_t.h"

BusErrorStorageObject_t::BusErrorStorageObject_t(const size_t & size, const char *const mnemonic, const u32 & PS2PhysicalAddress) :
	StorageObject_t(0, mnemonic, PS2PhysicalAddress),
	mSize(size)
{
}

BusErrorStorageObject_t::~BusErrorStorageObject_t()
{
}

u8 BusErrorStorageObject_t::readByteU(u32 storageIndex)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

void BusErrorStorageObject_t::writeByteU(u32 storageIndex, u8 value)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

s8 BusErrorStorageObject_t::readByteS(u32 storageIndex)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

void BusErrorStorageObject_t::writeByteS(u32 storageIndex, s8 value)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

u16 BusErrorStorageObject_t::readHwordU(u32 storageIndex)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

void BusErrorStorageObject_t::writeHwordU(u32 storageIndex, u16 value)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

s16 BusErrorStorageObject_t::readHwordS(u32 storageIndex)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

void BusErrorStorageObject_t::writeHwordS(u32 storageIndex, s16 value)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

u32 BusErrorStorageObject_t::readWordU(u32 storageIndex)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

void BusErrorStorageObject_t::writeWordU(u32 storageIndex, u32 value)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

s32 BusErrorStorageObject_t::readWordS(u32 storageIndex)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

void BusErrorStorageObject_t::writeWordS(u32 storageIndex, s32 value)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

u64 BusErrorStorageObject_t::readDwordU(u32 storageIndex)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

void BusErrorStorageObject_t::writeDwordU(u32 storageIndex, u64 value)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

s64 BusErrorStorageObject_t::readDwordS(u32 storageIndex)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

void BusErrorStorageObject_t::writeDwordS(u32 storageIndex, s64 value)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

size_t BusErrorStorageObject_t::getStorageSize()
{
	return mSize;
}
