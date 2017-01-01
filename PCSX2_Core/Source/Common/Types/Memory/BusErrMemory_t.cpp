#include "stdafx.h"

#include <stdexcept>

#include "Common/Global/Globals.h"

#include "Common/Types/Memory/BusErrMemory_t.h"

BusErrMemory_t::BusErrMemory_t(const size_t & size, const char * mnemonic) :
	Memory_t(0, mnemonic),
	mSize(size)
{
}

BusErrMemory_t::~BusErrMemory_t()
{
}

u8 BusErrMemory_t::readByte(u32 storageIndex)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

void BusErrMemory_t::writeByte(u32 storageIndex, u8 value)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

u16 BusErrMemory_t::readHword(u32 storageIndex)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

void BusErrMemory_t::writeHword(u32 storageIndex, u16 value)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

u32 BusErrMemory_t::readWord(u32 storageIndex)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

void BusErrMemory_t::writeWord(u32 storageIndex, u32 value)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

u64 BusErrMemory_t::readDword(u32 storageIndex)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

void BusErrMemory_t::writeDword(u32 storageIndex, u64 value)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

u128 BusErrMemory_t::readQword(u32 storageIndex)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

void BusErrMemory_t::writeQword(u32 storageIndex, u128 value)
{
	throw std::runtime_error("Bus Error occured, but not implemented as an exception.");
}

size_t BusErrMemory_t::getSize()
{
	return mSize;
}
