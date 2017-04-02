#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/Types/Memory/ConstantByteMemory_t.h"

ConstantByteMemory_t::ConstantByteMemory_t(const size_t & size, const u64 D) :
	ByteMemory_t(0),
	mSize(size),
	mConstantValue(D)
{
}

ConstantByteMemory_t::ConstantByteMemory_t(const size_t& size, const char* mnemonic, const u64 D) :
	ByteMemory_t(0, mnemonic),
	mSize(size),
	mConstantValue(D)
{
}

u8 ConstantByteMemory_t::readByte(const System_t context, size_t byteOffset)
{
	return static_cast<u8>(mConstantValue);
}

void ConstantByteMemory_t::writeByte(const System_t context, size_t byteOffset, u8 value)
{
}

u16 ConstantByteMemory_t::readHword(const System_t context, size_t byteOffset)
{
	return static_cast<u16>(mConstantValue);
}

void ConstantByteMemory_t::writeHword(const System_t context, size_t byteOffset, u16 value)
{
}

u32 ConstantByteMemory_t::readWord(const System_t context, size_t byteOffset)
{
	return static_cast<u32>(mConstantValue);
}

void ConstantByteMemory_t::writeWord(const System_t context, size_t byteOffset, u32 value)
{
}

u64 ConstantByteMemory_t::readDword(const System_t context, size_t byteOffset)
{
	return static_cast<u64>(mConstantValue);
}

void ConstantByteMemory_t::writeDword(const System_t context, size_t byteOffset, u64 value)
{
}

u128 ConstantByteMemory_t::readQword(const System_t context, size_t byteOffset)
{
	return u128(mConstantValue, mConstantValue);
}

void ConstantByteMemory_t::writeQword(const System_t context, size_t byteOffset, u128 value)
{
}

size_t ConstantByteMemory_t::getSize()
{
	return mSize;
}
