#include "stdafx.h"

#include <fstream>
#include <iterator>

#include "Common/Global/Globals.h"

#include "Common/Types/Memory/ByteMemory_t.h"

ByteMemory_t::ByteMemory_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const size_t byteSize) :
	DebugBaseObject_t(mnemonic, debugReads, debugWrites),
	mMemoryByteSize(byteSize),
	mMemory(mMemoryByteSize, 0)
{
#if DEBUG_LOG_MEMORY_ALLOCATIONS
	// Log the storage details if enabled, and if the size is above 0.
	if (mMemorySize > 0)
		log(Debug, "(%s, %d) %s allocated at 0x%p (size = 0x%08zX).", __FILENAME__, __LINE__, mMnemonic.c_str(), mMemory.data(), mMemorySize);
#endif
}

u8 ByteMemory_t::readByte(const System_t context, size_t byteOffset)
{
	// Get host storage address.
	u8 * hostMemoryAddress = reinterpret_cast<u8*>(&mMemory[byteOffset]);

	// Read the value.
#if defined(DEBUG_LOG_MEMORY_READ_WRITE)
	if (mDebugReads)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u8 @ 0x%08X, Value = 0x%X.", getSystemStr(context), mMnemonic.c_str(), byteOffset, *hostMemoryAddress);
#else
		log(Debug, "%s: %s Read u8 @ 0x%08X, Value = %d.", getSystemStr(context), mMnemonic.c_str(), byteOffset, *hostMemoryAddress);
#endif
	}
#endif

	return *hostMemoryAddress;
}

void ByteMemory_t::writeByte(const System_t context, size_t byteOffset, u8 value)
{
	// Get host storage address.
	u8 * hostMemoryAddress = reinterpret_cast<u8*>(&mMemory[byteOffset]);

	// Write the value.
	*hostMemoryAddress = value;

#if defined(DEBUG_LOG_MEMORY_READ_WRITE)
	if (mDebugWrites)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u8 @ 0x%08X, Value = 0x%X.", getSystemStr(context), mMnemonic.c_str(), byteOffset, *hostMemoryAddress);
#else
		log(Debug, "%s: %s Write u8 @ 0x%08X, Value = %d.", getSystemStr(context), mMnemonic.c_str(), byteOffset, *hostMemoryAddress);
#endif
	}
#endif
}

u16 ByteMemory_t::readHword(const System_t context, size_t byteOffset)
{
	// Get host storage address.
	u16 * hostMemoryAddress = reinterpret_cast<u16*>(&mMemory[byteOffset]);

	// Read the value.
#if defined(DEBUG_LOG_MEMORY_READ_WRITE)
	if (mDebugReads)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u16 @ 0x%08X, Value = 0x%X.", getSystemStr(context), mMnemonic.c_str(), byteOffset, *hostMemoryAddress);
#else
		log(Debug, "%s: %s Read u16 @ 0x%08X, Value = %d.", getSystemStr(context), mMnemonic.c_str(), byteOffset, *hostMemoryAddress);
#endif
	}
#endif

	return *hostMemoryAddress;
}

void ByteMemory_t::writeHword(const System_t context, size_t byteOffset, u16 value)
{
	// Get host storage address.
	u16 * hostMemoryAddress = reinterpret_cast<u16*>(&mMemory[byteOffset]);

	// Write the value.
	*hostMemoryAddress = value;

#if defined(DEBUG_LOG_MEMORY_READ_WRITE)
	if (mDebugWrites)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u16 @ 0x%08X, Value = 0x%X.", getSystemStr(context), mMnemonic.c_str(), byteOffset, *hostMemoryAddress);
#else
		log(Debug, "%s: %s Write u16 @ 0x%08X, Value = %d.", getSystemStr(context), mMnemonic.c_str(), byteOffset, *hostMemoryAddress);
#endif
	}
#endif
}

u32 ByteMemory_t::readWord(const System_t context, size_t byteOffset)
{
	// Get host storage address.
	u32 * hostMemoryAddress = reinterpret_cast<u32*>(&mMemory[byteOffset]);

	// Read the value.
#if defined(DEBUG_LOG_MEMORY_READ_WRITE)
	if (mDebugReads)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u32 @ 0x%08X, Value = 0x%X.", getSystemStr(context), mMnemonic.c_str(), byteOffset, *hostMemoryAddress);
#else
		log(Debug, "%s: %s Read u32 @ 0x%08X, Value = %d.", getSystemStr(context), mMnemonic.c_str(), byteOffset, *hostMemoryAddress);
#endif
	}
#endif

	return *hostMemoryAddress;
}

void ByteMemory_t::writeWord(const System_t context, size_t byteOffset, u32 value)
{
	// Get host storage address.
	u32 * hostMemoryAddress = reinterpret_cast<u32*>(&mMemory[byteOffset]);

	// Write the value.
	*hostMemoryAddress = value;

#if defined(DEBUG_LOG_MEMORY_READ_WRITE)
	if (mDebugWrites)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u32 @ 0x%08X, Value = 0x%X.", getSystemStr(context), mMnemonic.c_str(), byteOffset, *hostMemoryAddress);
#else
		log(Debug, "%s: %s Write u32 @ 0x%08X, Value = %d.", getSystemStr(context), mMnemonic.c_str(), byteOffset, *hostMemoryAddress);
#endif
	}
#endif
}

u64 ByteMemory_t::readDword(const System_t context, size_t byteOffset)
{
	// Get host storage address.
	u64 * hostMemoryAddress = reinterpret_cast<u64*>(&mMemory[byteOffset]);

	// Read the value.
#if defined(DEBUG_LOG_MEMORY_READ_WRITE)
	if (mDebugReads)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u64 @ 0x%08X, Value = 0x%X.", getSystemStr(context), mMnemonic.c_str(), byteOffset, *hostMemoryAddress);
#else
		log(Debug, "%s: %s Read u64 @ 0x%08X, Value = %d.", getSystemStr(context), mMnemonic.c_str(), byteOffset, *hostMemoryAddress);
#endif
	}
#endif

	return *hostMemoryAddress;
}

void ByteMemory_t::writeDword(const System_t context, size_t byteOffset, u64 value)
{
	// Get host storage address.
	u64 * hostMemoryAddress = reinterpret_cast<u64*>(&mMemory[byteOffset]);

	// Write the value.
	*hostMemoryAddress = value;

#if defined(DEBUG_LOG_MEMORY_READ_WRITE)
	if (mDebugWrites)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u64 @ 0x%08X, Value = 0x%X.", getSystemStr(context), mMnemonic.c_str(), byteOffset, *hostMemoryAddress);
#else
		log(Debug, "%s: %s Write u64 @ 0x%08X, Value = %d.", getSystemStr(context), mMnemonic.c_str(), byteOffset, *hostMemoryAddress);
#endif
	}
#endif
}

u128 ByteMemory_t::readQword(const System_t context, size_t byteOffset)
{
	// Get host storage address.
	u64 * hostMemoryAddressLSB = reinterpret_cast<u64*>(&mMemory[byteOffset]);
	u64 * hostMemoryAddressMSB = reinterpret_cast<u64*>(&mMemory[byteOffset + Constants::NUMBER_BYTES_IN_DWORD]);

	// Read the value.
#if defined(DEBUG_LOG_MEMORY_READ_WRITE)
	if (mDebugReads)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u128 @ 0x%08X, ValueLSB = 0x%X, ValueMSB = 0x%X.", getSystemStr(context), mMnemonic.c_str(), byteOffset, *hostMemoryAddressLSB, *hostMemoryAddressMSB);
#else
		log(Debug, "%s: %s Read u128 @ 0x%08X, ValueLSB = %d, ValueMSB = %d.", getSystemStr(context), mMnemonic.c_str(), byteOffset, *hostMemoryAddressLSB, *hostMemoryAddressMSB);
#endif
	}
#endif

	return u128(*hostMemoryAddressLSB, *hostMemoryAddressMSB);
}

void ByteMemory_t::writeQword(const System_t context, size_t byteOffset, u128 value)
{
	// Get host storage address.
	u64 * hostMemoryAddressLSB = reinterpret_cast<u64*>(&mMemory[byteOffset]);
	u64 * hostMemoryAddressMSB = reinterpret_cast<u64*>(&mMemory[byteOffset + Constants::NUMBER_BYTES_IN_DWORD]);

	// Write the value.
	*hostMemoryAddressLSB = value.lo;
	*hostMemoryAddressMSB = value.hi;

#if defined(DEBUG_LOG_MEMORY_READ_WRITE)
	if (mDebugWrites)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u128 @ 0x%08X, ValueLSB = 0x%X, ValueMSB = 0x%X.", getSystemStr(context), mMnemonic.c_str(), byteOffset, *hostMemoryAddressLSB, *hostMemoryAddressMSB);
#else
		log(Debug, "%s: %s Write u128 @ 0x%08X, ValueLSB = %d, ValueMSB = %d.", getSystemStr(context), mMnemonic.c_str(), byteOffset, *hostMemoryAddress);
#endif
	}
#endif
}

size_t ByteMemory_t::getSize()
{
	return mMemoryByteSize;
}

std::vector<u8> & ByteMemory_t::getContainer()
{
	return mMemory;
}

void ByteMemory_t::readFile(const char * fileStr, const size_t fileByteOffset, const size_t fileByteLength, const size_t memoryByteOffset)
{
	// Check it is not too big.
	if ((mMemoryByteSize - memoryByteOffset) < (fileByteLength)) // TODO: check... brain too tired...
		throw std::runtime_error("readFile() file was too big to read in.");

	// Open file.
	// MSVC bug? Using std::basic_ifstream<u8> is WAY slower than using ifstream... But they should be the same thing...
	std::ifstream file(fileStr, std::ios_base::binary);
	if (file.fail())
		throw std::runtime_error("readFile() tried to open file, but it failed! Check file exists and has read permissions.");

	// Read file in.
	file.seekg(fileByteOffset);
	file.read((char*)&mMemory[memoryByteOffset], fileByteLength);

	// STL method below super slow for some reason...
	/*
	// Read file in.
	std::istreambuf_iterator<u8> start(file);
	std::advance(start, fileByteOffset);
	std::copy_n(start, fileByteLength, mMemory.begin() + memoryByteOffset);
	*/
}

void ByteMemory_t::dump(const char * fileStr)
{
	// Open file.
	// MSVC bug? Using std::basic_ofstream<u8> is WAY slower than using ofstream... But they should be the same thing...
	std::ofstream file(fileStr, std::ios_base::binary);
	if (file.fail())
		throw std::runtime_error("dump() tried to open file, but it failed! Check file exists and has read permissions.");

	// Write file out.
	file.write((char*)&mMemory[0], mMemoryByteSize);

	// STL method below super slow for some reason...
	/*
	// Write file out.
	std::ostreambuf_iterator<u8> start(file);
	std::copy(mMemory.begin(), mMemory.end(), start);
	*/
}