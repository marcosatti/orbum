#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/Types/Memory/Memory_t.h"


Memory_t::Memory_t(const size_t& size) :
	mStorageSize(size),
	mStorage(new u8[mStorageSize]),
	mMnemonic("")
{
	// Initalise storage to 0.
	memset(mStorage, 0, mStorageSize);

#if DEBUG_LOG_ALLOCATIONS
	// Log the storage details if enabled, and if the size is above 0.
	if (mStorageSize > 0)
		logDebug("(%s, %d) Memory allocated at 0x%p (size = 0x%08zX).", __FILENAME__, __LINE__, mStorage, mStorageSize);
#endif
}

Memory_t::Memory_t(const size_t & size, const char * mnemonic) :
	mStorageSize(size),
	mStorage(new u8[mStorageSize]),
	mMnemonic(mnemonic)
{
	// Initalise storage to 0.
	memset(mStorage, 0, mStorageSize);

#if DEBUG_LOG_ALLOCATIONS
	// Log the storage details if enabled, and if the size is above 0.
	if (mStorageSize > 0)
		logDebug("(%s, %d) %s allocated at 0x%p (size = 0x%08zX).", __FILENAME__, __LINE__, mMnemonic.c_str(), mStorage, mStorageSize);
#endif
}

Memory_t::~Memory_t()
{
}

u8 Memory_t::readByte(u32 storageIndex)
{
	// Get host storage address.
	u8 * hostMemoryAddress = reinterpret_cast<u8*>(&mStorage[storageIndex]);

	// Read the value.
	return *hostMemoryAddress;
}

void Memory_t::writeByte(u32 storageIndex, u8 value)
{
	// Get host storage address.
	u8 * hostMemoryAddress = reinterpret_cast<u8*>(&mStorage[storageIndex]);

	// Write the value.
	*hostMemoryAddress = value;
}

u16 Memory_t::readHword(u32 storageIndex)
{
	// Get host storage address.
	u16 * hostMemoryAddress = reinterpret_cast<u16*>(&mStorage[storageIndex]);

	// Read the value.
	return *hostMemoryAddress;
}

void Memory_t::writeHword(u32 storageIndex, u16 value)
{
	// Get host storage address.
	u16 * hostMemoryAddress = reinterpret_cast<u16*>(&mStorage[storageIndex]);

	// Write the value.
	*hostMemoryAddress = value;
}

u32 Memory_t::readWord(u32 storageIndex)
{
	// Get host storage address.
	u32 * hostMemoryAddress = reinterpret_cast<u32*>(&mStorage[storageIndex]);

	// Read the value.
	return *hostMemoryAddress;
}

void Memory_t::writeWord(u32 storageIndex, u32 value)
{
	// Get host storage address.
	u32 * hostMemoryAddress = reinterpret_cast<u32*>(&mStorage[storageIndex]);

	// Write the value.
	*hostMemoryAddress = value;
}

u64 Memory_t::readDword(u32 storageIndex)
{
	// Get host storage address.
	u64 * hostMemoryAddress = reinterpret_cast<u64*>(&mStorage[storageIndex]);

	// Read the value.
	return *hostMemoryAddress;
}

void Memory_t::writeDword(u32 storageIndex, u64 value)
{
	// Get host storage address.
	u64 * hostMemoryAddress = reinterpret_cast<u64*>(&mStorage[storageIndex]);

	// Write the value.
	*hostMemoryAddress = value;
}

u128 Memory_t::readQword(u32 storageIndex)
{
	// Get host storage address.
	u64 * hostMemoryAddressLSB = reinterpret_cast<u64*>(&mStorage[storageIndex]);
	u64 * hostMemoryAddressMSB = reinterpret_cast<u64*>(&mStorage[storageIndex + Constants::NUMBER_BYTES_IN_DWORD]);

	// Read the value.
	return u128(*hostMemoryAddressLSB, *hostMemoryAddressMSB);
}

void Memory_t::writeQword(u32 storageIndex, u128 value)
{
	// Get host storage address.
	u64 * hostMemoryAddressLSB = reinterpret_cast<u64*>(&mStorage[storageIndex]);
	u64 * hostMemoryAddressMSB = reinterpret_cast<u64*>(&mStorage[storageIndex + Constants::NUMBER_BYTES_IN_DWORD]);

	// Write the value.
	*hostMemoryAddressLSB = value.lo;
	*hostMemoryAddressMSB = value.hi;
}

size_t Memory_t::getSize()
{
	return mStorageSize;
}

void* Memory_t::getHostMemoryAddress() const
{
	return reinterpret_cast<void*>(mStorage);
}

const char * Memory_t::getMnemonic() const
{
	return mMnemonic.c_str();
}