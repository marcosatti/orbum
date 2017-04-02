#include "stdafx.h"

#include <fstream>

#include "Common/Global/Globals.h"

#include "Common/Types/Memory/ByteMemory_t.h"

ByteMemory_t::ByteMemory_t(const size_t byteSize) :
#if defined(BUILD_DEBUG)
	mDebugReads(false), mDebugWrites(false),
#endif
	mMemorySize(byteSize),
	mMemory(new u8[mMemorySize]),
	mMnemonic("")
{
	// Initalise storage to 0.
	memset(mMemory, 0, mMemorySize);

#if DEBUG_MEMORY_LOG_ALLOCATIONS
	// Log the storage details if enabled, and if the size is above 0.
	if (mStorageSize > 0)
		log(Debug, "(%s, %d) Memory allocated at 0x%p (size = 0x%08zX).", __FILENAME__, __LINE__, mStorage, mStorageSize);
#endif
}

ByteMemory_t::ByteMemory_t(const size_t byteSize, const char * mnemonic) :
#if defined(BUILD_DEBUG)
	mDebugReads(false), mDebugWrites(false),
#endif
	mMemorySize(byteSize),
	mMemory(new u8[mMemorySize]),
	mMnemonic(mnemonic)
{
	// Initalise storage to 0.
	memset(mMemory, 0, mMemorySize);

#if DEBUG_MEMORY_LOG_ALLOCATIONS
	// Log the storage details if enabled, and if the size is above 0.
	if (mStorageSize > 0)
		log(Debug, "(%s, %d) %s allocated at 0x%p (size = 0x%08zX).", __FILENAME__, __LINE__, mMnemonic.c_str(), mStorage, mStorageSize);
#endif
}

#if defined(BUILD_DEBUG)
ByteMemory_t::ByteMemory_t(const size_t byteSize, const char* mnemonic, bool debugReads, bool debugWrites) :
	mDebugReads(debugReads), mDebugWrites(debugWrites),
	mMemorySize(byteSize),
	mMemory(new u8[mMemorySize]),
	mMnemonic(mnemonic)
{
	// Initalise storage to 0.
	memset(mMemory, 0, mMemorySize);

#if DEBUG_MEMORY_LOG_ALLOCATIONS
	// Log the storage details if enabled, and if the size is above 0.
	if (mStorageSize > 0)
		log(Debug, "(%s, %d) %s allocated at 0x%p (size = 0x%08zX).", __FILENAME__, __LINE__, mMnemonic.c_str(), mStorage, mStorageSize);
#endif
}
#endif

ByteMemory_t::~ByteMemory_t()
{
	// Deallocate memory.
	delete[] mMemory;
}

u8 ByteMemory_t::readByte(const System_t context, size_t byteOffset)
{
	// Get host storage address.
	u8 * hostMemoryAddress = reinterpret_cast<u8*>(&mMemory[byteOffset]);

	// Read the value.
#if defined(BUILD_DEBUG)
	if (mDebugReads)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u8 @ 0x%08X, Value = 0x%X.", getSystemStr(context), getMnemonic(), byteOffset, *hostMemoryAddress);
#else
		log(Debug, "%s: %s Read u8 @ 0x%08X, Value = %d.", getSystemStr(context), getMnemonic(), byteOffset, *hostMemoryAddress);
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

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u8 @ 0x%08X, Value = 0x%X.", getSystemStr(context), getMnemonic(), byteOffset, *hostMemoryAddress);
#else
		log(Debug, "%s: %s Write u8 @ 0x%08X, Value = %d.", getSystemStr(context), getMnemonic(), byteOffset, *hostMemoryAddress);
#endif
	}
#endif
}

u16 ByteMemory_t::readHword(const System_t context, size_t byteOffset)
{
	// Get host storage address.
	u16 * hostMemoryAddress = reinterpret_cast<u16*>(&mMemory[byteOffset]);

	// Read the value.
#if defined(BUILD_DEBUG)
	if (mDebugReads)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u16 @ 0x%08X, Value = 0x%X.", getSystemStr(context), getMnemonic(), byteOffset, *hostMemoryAddress);
#else
		log(Debug, "%s: %s Read u16 @ 0x%08X, Value = %d.", getSystemStr(context), getMnemonic(), byteOffset, *hostMemoryAddress);
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

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u16 @ 0x%08X, Value = 0x%X.", getSystemStr(context), getMnemonic(), byteOffset, *hostMemoryAddress);
#else
		log(Debug, "%s: %s Write u16 @ 0x%08X, Value = %d.", getSystemStr(context), getMnemonic(), byteOffset, *hostMemoryAddress);
#endif
	}
#endif
}

u32 ByteMemory_t::readWord(const System_t context, size_t byteOffset)
{
	// Get host storage address.
	u32 * hostMemoryAddress = reinterpret_cast<u32*>(&mMemory[byteOffset]);

	// Read the value.
#if defined(BUILD_DEBUG)
	if (mDebugReads)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u32 @ 0x%08X, Value = 0x%X.", getSystemStr(context), getMnemonic(), byteOffset, *hostMemoryAddress);
#else
		log(Debug, "%s: %s Read u32 @ 0x%08X, Value = %d.", getSystemStr(context), getMnemonic(), byteOffset, *hostMemoryAddress);
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

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u32 @ 0x%08X, Value = 0x%X.", getSystemStr(context), getMnemonic(), byteOffset, *hostMemoryAddress);
#else
		log(Debug, "%s: %s Write u32 @ 0x%08X, Value = %d.", getSystemStr(context), getMnemonic(), byteOffset, *hostMemoryAddress);
#endif
	}
#endif
}

u64 ByteMemory_t::readDword(const System_t context, size_t byteOffset)
{
	// Get host storage address.
	u64 * hostMemoryAddress = reinterpret_cast<u64*>(&mMemory[byteOffset]);

	// Read the value.
#if defined(BUILD_DEBUG)
	if (mDebugReads)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u64 @ 0x%08X, Value = 0x%X.", getSystemStr(context), getMnemonic(), byteOffset, *hostMemoryAddress);
#else
		log(Debug, "%s: %s Read u64 @ 0x%08X, Value = %d.", getSystemStr(context), getMnemonic(), byteOffset, *hostMemoryAddress);
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

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u64 @ 0x%08X, Value = 0x%X.", getSystemStr(context), getMnemonic(), byteOffset, *hostMemoryAddress);
#else
		log(Debug, "%s: %s Write u64 @ 0x%08X, Value = %d.", getSystemStr(context), getMnemonic(), byteOffset, *hostMemoryAddress);
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
#if defined(BUILD_DEBUG)
	if (mDebugReads)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u128 @ 0x%08X, ValueLSB = 0x%X, ValueMSB = 0x%X.", getSystemStr(context), getMnemonic(), byteOffset, *hostMemoryAddressLSB, *hostMemoryAddressMSB);
#else
		log(Debug, "%s: %s Read u128 @ 0x%08X, ValueLSB = %d, ValueMSB = %d.", getSystemStr(context), getMnemonic(), byteOffset, *hostMemoryAddressLSB, *hostMemoryAddressMSB);
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

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u128 @ 0x%08X, ValueLSB = 0x%X, ValueMSB = 0x%X.", getSystemStr(context), getMnemonic(), byteOffset, *hostMemoryAddressLSB, *hostMemoryAddressMSB);
#else
		log(Debug, "%s: %s Write u128 @ 0x%08X, ValueLSB = %d, ValueMSB = %d.", getSystemStr(context), getMnemonic(), byteOffset, *hostMemoryAddress);
#endif
	}
#endif
}

size_t ByteMemory_t::getSize()
{
	return mMemorySize;
}

void * ByteMemory_t::getHostMemoryAddress() const
{
	return reinterpret_cast<void*>(mMemory);
}

const char * ByteMemory_t::getMnemonic() const
{
	return mMnemonic.c_str();
}

void ByteMemory_t::readFile(const std::string & fileStr, const size_t fileByteOffset, const size_t fileByteLength, const size_t memoryByteOffset) const
{
	// Check it is not too big.
	if ((mMemorySize - memoryByteOffset) < (fileByteLength)) // TODO: check... brain too tired...
		throw std::runtime_error("Memory_t::readFile() file was too big to read in.");

	// Read file in.
	char * memoryBase = reinterpret_cast<char*>(getHostMemoryAddress());
	std::ifstream file(fileStr, std::ifstream::binary);
	if (file.fail())
		throw std::runtime_error("Memory_t::readFile() tried to open file, but it failed! Check file exists and has read permissions.");
	file.seekg(fileByteOffset);
	file.read(memoryBase + memoryByteOffset, fileByteLength);
}
