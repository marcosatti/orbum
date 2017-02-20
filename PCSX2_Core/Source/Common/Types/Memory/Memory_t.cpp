#include "stdafx.h"

#include <fstream>

#include "Common/Global/Globals.h"

#include "Common/Types/Memory/Memory_t.h"

Memory_t::Memory_t(const size_t& size) :
#if defined(BUILD_DEBUG)
	mDebugReads(false), mDebugWrites(false),
#endif
	mStorageSize(size),
	mStorage(new u8[mStorageSize]),
	mMnemonic("")
{
	// Initalise storage to 0.
	memset(mStorage, 0, mStorageSize);

#if DEBUG_MEMORY_LOG_ALLOCATIONS
	// Log the storage details if enabled, and if the size is above 0.
	if (mStorageSize > 0)
		log(Debug, "(%s, %d) Memory allocated at 0x%p (size = 0x%08zX).", __FILENAME__, __LINE__, mStorage, mStorageSize);
#endif
}

Memory_t::Memory_t(const size_t & size, const char * mnemonic) :
#if defined(BUILD_DEBUG)
	mDebugReads(false), mDebugWrites(false),
#endif
	mStorageSize(size),
	mStorage(new u8[mStorageSize]),
	mMnemonic(mnemonic)
{
	// Initalise storage to 0.
	memset(mStorage, 0, mStorageSize);

#if DEBUG_MEMORY_LOG_ALLOCATIONS
	// Log the storage details if enabled, and if the size is above 0.
	if (mStorageSize > 0)
		log(Debug, "(%s, %d) %s allocated at 0x%p (size = 0x%08zX).", __FILENAME__, __LINE__, mMnemonic.c_str(), mStorage, mStorageSize);
#endif
}

#if defined(BUILD_DEBUG)
Memory_t::Memory_t(const size_t& size, const char* mnemonic, bool debugReads, bool debugWrites) :
	mDebugReads(debugReads), mDebugWrites(debugWrites),
	mStorageSize(size),
	mStorage(new u8[mStorageSize]),
	mMnemonic(mnemonic)
{
	// Initalise storage to 0.
	memset(mStorage, 0, mStorageSize);

#if DEBUG_MEMORY_LOG_ALLOCATIONS
	// Log the storage details if enabled, and if the size is above 0.
	if (mStorageSize > 0)
		log(Debug, "(%s, %d) %s allocated at 0x%p (size = 0x%08zX).", __FILENAME__, __LINE__, mMnemonic.c_str(), mStorage, mStorageSize);
#endif
}
#endif

Memory_t::~Memory_t()
{
	// Deallocate memory.
	delete[] mStorage;
}

u8 Memory_t::readByte(const Context_t& context, size_t storageIndex)
{
	// Get host storage address.
	u8 * hostMemoryAddress = reinterpret_cast<u8*>(&mStorage[storageIndex]);

	// Read the value.
#if defined(BUILD_DEBUG)
	if (mDebugReads)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u8 @ 0x%08X, Value = 0x%X.", getContextStr(context), getMnemonic(), storageIndex, *hostMemoryAddress);
#else
		log(Debug, "%s: %s Read u8 @ 0x%08X, Value = %d.", getContextStr(context), getMnemonic(), storageIndex, *hostMemoryAddress);
#endif
	}
#endif

	return *hostMemoryAddress;
}

void Memory_t::writeByte(const Context_t& context, size_t storageIndex, u8 value)
{
	// Get host storage address.
	u8 * hostMemoryAddress = reinterpret_cast<u8*>(&mStorage[storageIndex]);

	// Write the value.
	*hostMemoryAddress = value;

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u8 @ 0x%08X, Value = 0x%X.", getContextStr(context), getMnemonic(), storageIndex, *hostMemoryAddress);
#else
		log(Debug, "%s: %s Write u8 @ 0x%08X, Value = %d.", getContextStr(context), getMnemonic(), storageIndex, *hostMemoryAddress);
#endif
	}
#endif
}

u16 Memory_t::readHword(const Context_t& context, size_t storageIndex)
{
	// Get host storage address.
	u16 * hostMemoryAddress = reinterpret_cast<u16*>(&mStorage[storageIndex]);

	// Read the value.
#if defined(BUILD_DEBUG)
	if (mDebugReads)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u16 @ 0x%08X, Value = 0x%X.", getContextStr(context), getMnemonic(), storageIndex, *hostMemoryAddress);
#else
		log(Debug, "%s: %s Read u16 @ 0x%08X, Value = %d.", getContextStr(context), getMnemonic(), storageIndex, *hostMemoryAddress);
#endif
	}
#endif

	return *hostMemoryAddress;
}

void Memory_t::writeHword(const Context_t& context, size_t storageIndex, u16 value)
{
	// Get host storage address.
	u16 * hostMemoryAddress = reinterpret_cast<u16*>(&mStorage[storageIndex]);

	// Write the value.
	*hostMemoryAddress = value;

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u16 @ 0x%08X, Value = 0x%X.", getContextStr(context), getMnemonic(), storageIndex, *hostMemoryAddress);
#else
		log(Debug, "%s: %s Write u16 @ 0x%08X, Value = %d.", getContextStr(context), getMnemonic(), storageIndex, *hostMemoryAddress);
#endif
	}
#endif
}

u32 Memory_t::readWord(const Context_t& context, size_t storageIndex)
{
	// Get host storage address.
	u32 * hostMemoryAddress = reinterpret_cast<u32*>(&mStorage[storageIndex]);

	// Read the value.
#if defined(BUILD_DEBUG)
	if (mDebugReads)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u32 @ 0x%08X, Value = 0x%X.", getContextStr(context), getMnemonic(), storageIndex, *hostMemoryAddress);
#else
		log(Debug, "%s: %s Read u32 @ 0x%08X, Value = %d.", getContextStr(context), getMnemonic(), storageIndex, *hostMemoryAddress);
#endif
	}
#endif

	return *hostMemoryAddress;
}

void Memory_t::writeWord(const Context_t& context, size_t storageIndex, u32 value)
{
	// Get host storage address.
	u32 * hostMemoryAddress = reinterpret_cast<u32*>(&mStorage[storageIndex]);

	// Write the value.
	*hostMemoryAddress = value;

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u32 @ 0x%08X, Value = 0x%X.", getContextStr(context), getMnemonic(), storageIndex, *hostMemoryAddress);
#else
		log(Debug, "%s: %s Write u32 @ 0x%08X, Value = %d.", getContextStr(context), getMnemonic(), storageIndex, *hostMemoryAddress);
#endif
	}
#endif
}

u64 Memory_t::readDword(const Context_t& context, size_t storageIndex)
{
	// Get host storage address.
	u64 * hostMemoryAddress = reinterpret_cast<u64*>(&mStorage[storageIndex]);

	// Read the value.
#if defined(BUILD_DEBUG)
	if (mDebugReads)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u64 @ 0x%08X, Value = 0x%X.", getContextStr(context), getMnemonic(), storageIndex, *hostMemoryAddress);
#else
		log(Debug, "%s: %s Read u64 @ 0x%08X, Value = %d.", getContextStr(context), getMnemonic(), storageIndex, *hostMemoryAddress);
#endif
	}
#endif

	return *hostMemoryAddress;
}

void Memory_t::writeDword(const Context_t& context, size_t storageIndex, u64 value)
{
	// Get host storage address.
	u64 * hostMemoryAddress = reinterpret_cast<u64*>(&mStorage[storageIndex]);

	// Write the value.
	*hostMemoryAddress = value;

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u64 @ 0x%08X, Value = 0x%X.", getContextStr(context), getMnemonic(), storageIndex, *hostMemoryAddress);
#else
		log(Debug, "%s: %s Write u64 @ 0x%08X, Value = %d.", getContextStr(context), getMnemonic(), storageIndex, *hostMemoryAddress);
#endif
	}
#endif
}

u128 Memory_t::readQword(const Context_t& context, size_t storageIndex)
{
	// Get host storage address.
	u64 * hostMemoryAddressLSB = reinterpret_cast<u64*>(&mStorage[storageIndex]);
	u64 * hostMemoryAddressMSB = reinterpret_cast<u64*>(&mStorage[storageIndex + Constants::NUMBER_BYTES_IN_DWORD]);

	// Read the value.
#if defined(BUILD_DEBUG)
	if (mDebugReads)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u128 @ 0x%08X, ValueLSB = 0x%X, ValueMSB = 0x%X.", getContextStr(context), getMnemonic(), storageIndex, *hostMemoryAddressLSB, *hostMemoryAddressMSB);
#else
		log(Debug, "%s: %s Read u128 @ 0x%08X, ValueLSB = %d, ValueMSB = %d.", getContextStr(context), getMnemonic(), storageIndex, *hostMemoryAddressLSB, *hostMemoryAddressMSB);
#endif
	}
#endif

	return u128(*hostMemoryAddressLSB, *hostMemoryAddressMSB);
}

void Memory_t::writeQword(const Context_t& context, size_t storageIndex, u128 value)
{
	// Get host storage address.
	u64 * hostMemoryAddressLSB = reinterpret_cast<u64*>(&mStorage[storageIndex]);
	u64 * hostMemoryAddressMSB = reinterpret_cast<u64*>(&mStorage[storageIndex + Constants::NUMBER_BYTES_IN_DWORD]);

	// Write the value.
	*hostMemoryAddressLSB = value.lo;
	*hostMemoryAddressMSB = value.hi;

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u128 @ 0x%08X, ValueLSB = 0x%X, ValueMSB = 0x%X.", getContextStr(context), getMnemonic(), storageIndex, *hostMemoryAddressLSB, *hostMemoryAddressMSB);
#else
		log(Debug, "%s: %s Write u128 @ 0x%08X, ValueLSB = %d, ValueMSB = %d.", getContextStr(context), getMnemonic(), storageIndex, *hostMemoryAddress);
#endif
	}
#endif
}

size_t Memory_t::getSize()
{
	return mStorageSize;
}

void * Memory_t::getHostMemoryAddress() const
{
	return reinterpret_cast<void*>(mStorage);
}

const char * Memory_t::getMnemonic() const
{
	return mMnemonic.c_str();
}

void Memory_t::readFile(const std::string& fileStr, const size_t& fileOffset, const size_t& fileLength, const size_t& storageOffset) const
{
	// Check it is not too big.
	if ((mStorageSize - storageOffset) < (fileLength)) // TODO: check... brain too tired...
		throw std::runtime_error("Memory_t::readFile() too big to read in.");

	// Read file in.
	char * memoryBase = reinterpret_cast<char*>(getHostMemoryAddress());
	std::ifstream file(fileStr, std::ifstream::binary);
	if (file.fail())
		throw std::runtime_error("Memory_t::readFile() tried to open file, but it failed! Check file exists and has read permissions.");
	file.seekg(fileOffset);
	file.read(memoryBase + storageOffset, fileLength);
}
