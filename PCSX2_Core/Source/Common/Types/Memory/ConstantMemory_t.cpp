#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/Types/Memory/ConstantMemory_t.h"

ConstantMemory_t::ConstantMemory_t(const size_t & size, const u64 D) :
	Memory_t(0),
	mSize(size),
	mConstantValue(D)
{
}

ConstantMemory_t::ConstantMemory_t(const size_t& size, const char* mnemonic, const u64 D) :
	Memory_t(0, mnemonic),
	mSize(size),
	mConstantValue(D)
{
}

ConstantMemory_t::~ConstantMemory_t()
{
}

u8 ConstantMemory_t::readByte(const Context_t& context, size_t storageIndex)
{
	return static_cast<u8>(mConstantValue);
}

void ConstantMemory_t::writeByte(const Context_t& context, size_t storageIndex, u8 value)
{
}

u16 ConstantMemory_t::readHword(const Context_t& context, size_t storageIndex)
{
	return static_cast<u16>(mConstantValue);
}

void ConstantMemory_t::writeHword(const Context_t& context, size_t storageIndex, u16 value)
{
}

u32 ConstantMemory_t::readWord(const Context_t& context, size_t storageIndex)
{
	return static_cast<u32>(mConstantValue);
}

void ConstantMemory_t::writeWord(const Context_t& context, size_t storageIndex, u32 value)
{
}

u64 ConstantMemory_t::readDword(const Context_t& context, size_t storageIndex)
{
	return static_cast<u64>(mConstantValue);
}

void ConstantMemory_t::writeDword(const Context_t& context, size_t storageIndex, u64 value)
{
}

u128 ConstantMemory_t::readQword(const Context_t& context, size_t storageIndex)
{
	return u128(mConstantValue, mConstantValue);
}

void ConstantMemory_t::writeQword(const Context_t& context, size_t storageIndex, u128 value)
{
}

size_t ConstantMemory_t::getSize()
{
	return mSize;
}
