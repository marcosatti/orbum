#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/Types/MappedMemory/MappedMemory_t.h"


MappedMemory_t::MappedMemory_t(const size_t & size, const char *const mnemonic, const u32 & PS2PhysicalAddress) :
	mStorageSize(size),
	mStorage(new u8[mStorageSize]),
	mMnemonic(mnemonic),
	mPS2PhysicalAddress(PS2PhysicalAddress)
{
	// Initalise storage to 0.
	memset(mStorage, 0, mStorageSize);

#if DEBUG_LOG_ALLOCATIONS
	// Log the storage details if enabled, and if the size is above 0.
	if (mStorageSize > 0)
		logDebug("(%s, %d) %s allocated at 0x%p (size = 0x%08zX).", __FILENAME__, __LINE__, mMnemonic.c_str(), mStorage, mStorageSize);
#endif
}

MappedMemory_t::~MappedMemory_t()
{
}

u8 MappedMemory_t::readByteU(u32 storageIndex)
{
	// Get host storage address.
	u8 * hostMemoryAddress = reinterpret_cast<u8*>(&mStorage[storageIndex]);

	// Read the value.
	return *hostMemoryAddress;
}

void MappedMemory_t::writeByteU(u32 storageIndex, u8 value)
{
	// Get host storage address.
	u8 * hostMemoryAddress = reinterpret_cast<u8*>(&mStorage[storageIndex]);

	// Write the value.
	*hostMemoryAddress = value;
}

s8 MappedMemory_t::readByteS(u32 storageIndex)
{
	// Get host storage address.
	s8 * hostMemoryAddress = reinterpret_cast<s8*>(&mStorage[storageIndex]);

	// Read the value.
	return *hostMemoryAddress;
}

void MappedMemory_t::writeByteS(u32 storageIndex, s8 value)
{
	// Get host storage address.
	s8 * hostMemoryAddress = reinterpret_cast<s8*>(&mStorage[storageIndex]);

	// Write the value.
	*hostMemoryAddress = value;
}

u16 MappedMemory_t::readHwordU(u32 storageIndex)
{
	// Get host storage address.
	u16 * hostMemoryAddress = reinterpret_cast<u16*>(&mStorage[storageIndex]);

	// Read the value.
	return *hostMemoryAddress;
}

void MappedMemory_t::writeHwordU(u32 storageIndex, u16 value)
{
	// Get host storage address.
	u16 * hostMemoryAddress = reinterpret_cast<u16*>(&mStorage[storageIndex]);

	// Write the value.
	*hostMemoryAddress = value;
}

s16 MappedMemory_t::readHwordS(u32 storageIndex)
{
	// Get host storage address.
	s16 * hostMemoryAddress = reinterpret_cast<s16*>(&mStorage[storageIndex]);

	// Read the value.
	return *hostMemoryAddress;
}

void MappedMemory_t::writeHwordS(u32 storageIndex, s16 value)
{
	// Get host storage address.
	s16 * hostMemoryAddress = reinterpret_cast<s16*>(&mStorage[storageIndex]);

	// Write the value.
	*hostMemoryAddress = value;
}

u32 MappedMemory_t::readWordU(u32 storageIndex)
{
	// Get host storage address.
	u32 * hostMemoryAddress = reinterpret_cast<u32*>(&mStorage[storageIndex]);

	// Read the value.
	return *hostMemoryAddress;
}

void MappedMemory_t::writeWordU(u32 storageIndex, u32 value)
{
	// Get host storage address.
	u32 * hostMemoryAddress = reinterpret_cast<u32*>(&mStorage[storageIndex]);

	// Write the value.
	*hostMemoryAddress = value;
}

s32 MappedMemory_t::readWordS(u32 storageIndex)
{
	// Get host storage address.
	s32 * hostMemoryAddress = reinterpret_cast<s32*>(&mStorage[storageIndex]);

	// Read the value.
	return *hostMemoryAddress;
}

void MappedMemory_t::writeWordS(u32 storageIndex, s32 value)
{
	// Get host storage address.
	s32 * hostMemoryAddress = reinterpret_cast<s32*>(&mStorage[storageIndex]);

	// Write the value.
	*hostMemoryAddress = value;
}

u64 MappedMemory_t::readDwordU(u32 storageIndex)
{
	// Get host storage address.
	u64 * hostMemoryAddress = reinterpret_cast<u64*>(&mStorage[storageIndex]);

	// Read the value.
	return *hostMemoryAddress;
}

void MappedMemory_t::writeDwordU(u32 storageIndex, u64 value)
{
	// Get host storage address.
	u64 * hostMemoryAddress = reinterpret_cast<u64*>(&mStorage[storageIndex]);

	// Write the value.
	*hostMemoryAddress = value;
}

s64 MappedMemory_t::readDwordS(u32 storageIndex)
{
	// Get host storage address.
	s64 * hostMemoryAddress = reinterpret_cast<s64*>(&mStorage[storageIndex]);

	// Read the value.
	return *hostMemoryAddress;
}

void MappedMemory_t::writeDwordS(u32 storageIndex, s64 value)
{
	// Get host storage address.
	s64 * hostMemoryAddress = reinterpret_cast<s64*>(&mStorage[storageIndex]);

	// Write the value.
	*hostMemoryAddress = value;
}

size_t MappedMemory_t::getStorageSize()
{
	return mStorageSize;
}

void* MappedMemory_t::getHostMemoryAddress() const
{
	return reinterpret_cast<void*>(mStorage);
}

const char * MappedMemory_t::getMnemonic() const
{
	return mMnemonic.c_str();
}

const u32 & MappedMemory_t::getPS2PhysicalAddress() const
{
	return mPS2PhysicalAddress;
}

u32 MappedMemory_t::getAbsMappedPageIndex() const
{
	return mAbsMappedPageIndex;
}

void MappedMemory_t::setAbsMappedPageIndex(u32 absPageIndex)
{
	mAbsMappedPageIndex = absPageIndex;
}