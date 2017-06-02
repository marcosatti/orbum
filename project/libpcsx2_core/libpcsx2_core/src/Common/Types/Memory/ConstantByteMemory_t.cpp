#include "Common/Global/Globals.h"

#include "Common/Types/Memory/ConstantByteMemory_t.h"

ConstantByteMemory_t::ConstantByteMemory_t(const char * mnemonic, bool debugReads, bool debugWrites, const size_t byteSize, const u64 D) :
	ByteMemory_t(mnemonic, debugReads, debugWrites, 0),
	mSize(byteSize),
	mConstantValue(D)
{
}

u8 ConstantByteMemory_t::readByte(const Context_t context, const size_t byteOffset)
{
	return static_cast<u8>(mConstantValue);
}

void ConstantByteMemory_t::writeByte(const Context_t context, const size_t byteOffset, const u8 value)
{
}

u16 ConstantByteMemory_t::readHword(const Context_t context, const size_t byteOffset)
{
	return static_cast<u16>(mConstantValue);
}

void ConstantByteMemory_t::writeHword(const Context_t context, const size_t byteOffset, const u16 value)
{
}

u32 ConstantByteMemory_t::readWord(const Context_t context, const size_t byteOffset)
{
	return static_cast<u32>(mConstantValue);
}

void ConstantByteMemory_t::writeWord(const Context_t context, const size_t byteOffset, const u32 value)
{
}

u64 ConstantByteMemory_t::readDword(const Context_t context, const size_t byteOffset)
{
	return static_cast<u64>(mConstantValue);
}

void ConstantByteMemory_t::writeDword(const Context_t context, const size_t byteOffset, const u64 value)
{
}

u128 ConstantByteMemory_t::readQword(const Context_t context, const size_t byteOffset)
{
	return u128(mConstantValue, mConstantValue);
}

void ConstantByteMemory_t::writeQword(const Context_t context, const size_t byteOffset, const u128 value)
{
}

size_t ConstantByteMemory_t::getSize()
{
	return mSize;
}
