#include "stdafx.h"

#include <stdexcept>

#include "Common/Global/Globals.h"

#include "Common/Types/Memory/BusErrMemory_t.h"

BusErrMemory_t::BusErrMemory_t(const size_t & size, const char *const mnemonic) :
	Memory_t(0, mnemonic),
	mSize(size)
{
}

BusErrMemory_t::~BusErrMemory_t()
{
}

u8 BusErrMemory_t::readByteU(u32 storageIndex)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

void BusErrMemory_t::writeByteU(u32 storageIndex, u8 value)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

s8 BusErrMemory_t::readByteS(u32 storageIndex)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

void BusErrMemory_t::writeByteS(u32 storageIndex, s8 value)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

u16 BusErrMemory_t::readHwordU(u32 storageIndex)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

void BusErrMemory_t::writeHwordU(u32 storageIndex, u16 value)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

s16 BusErrMemory_t::readHwordS(u32 storageIndex)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

void BusErrMemory_t::writeHwordS(u32 storageIndex, s16 value)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

u32 BusErrMemory_t::readWordU(u32 storageIndex)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

void BusErrMemory_t::writeWordU(u32 storageIndex, u32 value)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

s32 BusErrMemory_t::readWordS(u32 storageIndex)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

void BusErrMemory_t::writeWordS(u32 storageIndex, s32 value)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

u64 BusErrMemory_t::readDwordU(u32 storageIndex)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

void BusErrMemory_t::writeDwordU(u32 storageIndex, u64 value)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

s64 BusErrMemory_t::readDwordS(u32 storageIndex)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

void BusErrMemory_t::writeDwordS(u32 storageIndex, s64 value)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

u128 BusErrMemory_t::readQwordU(u32 storageIndex)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

void BusErrMemory_t::writeQwordU(u32 storageIndex, u128 value)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

size_t BusErrMemory_t::getSize()
{
	return mSize;
}
