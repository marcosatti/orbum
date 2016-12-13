#include "stdafx.h"

#include <memory>
#include <stdexcept>
#include <cmath>

#include "Common/Global/Globals.h"

#include "Common/Types/PhysicalMMU/PhysicalMMU_t.h"
#include "Common/Interfaces/PhysicalMapped.h"
#include "Common/Types/PhysicalMMU/MappedMemory_t.h"
#include "Common/Types/PhysicalMMU/MappedRegister8_t.h"
#include "Common/Types/PhysicalMMU/MappedRegister16_t.h"
#include "Common/Types/PhysicalMMU/MappedRegister32_t.h"
#include "Common/Types/PhysicalMMU/MappedRegister64_t.h"
#include "Common/Types/PhysicalMMU/MappedRegister128_t.h"
#include "Common/Types/PhysicalMMU/MappedFPRegister32_t.h"
#include "Common/Types/PhysicalMMU/MappedFPRegister128_t.h"

PhysicalMMU_t::PhysicalMMU_t(const size_t & maxAddressableSizeBytes, const u32 & directorySizeBytes, const u32 & pageSizeBytes) :
	MAX_ADDRESSABLE_SIZE_BYTES(maxAddressableSizeBytes),
	DIRECTORY_SIZE_BYTES(directorySizeBytes),
	PAGE_SIZE_BYTES(pageSizeBytes),
	DIRECTORY_ENTRIES(static_cast<u32>(MAX_ADDRESSABLE_SIZE_BYTES / DIRECTORY_SIZE_BYTES)),
	PAGE_ENTRIES(DIRECTORY_SIZE_BYTES / PAGE_SIZE_BYTES),
	OFFSET_BITS(static_cast<u32>(log2(PAGE_SIZE_BYTES))),
	OFFSET_MASK(PAGE_SIZE_BYTES - 1),
	DIRECTORY_BITS(static_cast<u32>(log2(DIRECTORY_ENTRIES))),
	DIRECTORY_MASK(DIRECTORY_ENTRIES - 1),
	PAGE_BITS(static_cast<u32>(log2(PAGE_ENTRIES))),
	PAGE_MASK(PAGE_ENTRIES - 1)
{
	// Allocate the page table (directories).
	mPageTable = new std::shared_ptr<PhysicalMapped>*[DIRECTORY_ENTRIES];

	// Ok... VS compiler crashes if we try to do array initalisation above... so try memset to do it? This works...
	// Sets all of the directory to nullptr's.
	memset(mPageTable, 0, DIRECTORY_ENTRIES * sizeof(mPageTable[0]));
}

PhysicalMMU_t::~PhysicalMMU_t()
{
	// Destroy any allocated pages.
	for (u32 i = 0; i < DIRECTORY_ENTRIES; i++)
		if (mPageTable[i] != nullptr) delete[] mPageTable[i];
	
	// Destroy the page table (directories).
	delete[] mPageTable;
}

void PhysicalMMU_t::mapObject(const std::shared_ptr<PhysicalMapped> & physicalMapped)
{
	// Do not do anything for getSize equal to 0.
	if (physicalMapped->getSize() == 0) 
		return;

	// Get the base virtual directory number (VDN) and virtual page number (VPN).
	u32 baseVDN = getVDN(physicalMapped->getMappedPhysicalAddress());
	u32 baseVPN = getVPN(physicalMapped->getMappedPhysicalAddress());

	// Work out how many pages the memory block occupies. If it is not evenly divisible, need to add on an extra page to account for the extra length.
	// Thank you to Ian Nelson for the round up solution: http://stackoverflow.com/questions/17944/how-to-round-up-the-result-of-integer-division, very good.
	size_t pagesCount = (physicalMapped->getSize() + PAGE_SIZE_BYTES - 1) / PAGE_SIZE_BYTES;

	// Get absolute linear page position that we start mapping memory from.
	u32 absPageStartIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);
	
	// Set the base page index of the storage object, so it can calculate the byte(s) it needs to access later on when its used.
	physicalMapped->setAbsMappedPageIndex(absPageStartIndex);

	// Iterate through the pages to set the host addresses.
	u32 absDirectoryIndex;
	u32 absPageIndex;
	for (u32 i = 0; i < pagesCount; i++)
	{
		// Get absolute directory and page index.
		absDirectoryIndex = getDirectoryFromPageOffset(absPageStartIndex, i);
		absPageIndex = getDirPageFromPageOffset(absPageStartIndex, i);

		// Make sure directory is allocated.
		allocDirectory(absDirectoryIndex);

		// Check that there is no existing map data - log a warning if there is.
#if defined(BUILD_DEBUG)
		if (mPageTable[absDirectoryIndex][absPageIndex] != nullptr)
			logDebug("(%s, %d) Warning! Physical MMU mapped storage object \"%s\" @ 0x%08X overwritten with object \"%s\". Please fix!",
				__FILENAME__, __LINE__,
				mPageTable[absDirectoryIndex][absPageIndex]->getMnemonic(),
				physicalMapped->getMappedPhysicalAddress(),
				physicalMapped->getMnemonic());
#endif

		// Map memory entry.
		mPageTable[absDirectoryIndex][absPageIndex] = physicalMapped;
	}
}

void PhysicalMMU_t::mapObject(const u32 & physicalAddress, const std::shared_ptr<Memory_t>& memory)
{
	mapObject(std::make_shared<MappedMemory_t>(physicalAddress, memory));
}

void PhysicalMMU_t::mapObject(const u32& physicalAddress, const std::shared_ptr<Register8_t>& register8)
{
	mapObject(std::make_shared<MappedRegister8_t>(physicalAddress, register8));
}

void PhysicalMMU_t::mapObject(const u32& physicalAddress, const std::shared_ptr<Register16_t>& register16)
{
	mapObject(std::make_shared<MappedRegister16_t>(physicalAddress, register16));
}

void PhysicalMMU_t::mapObject(const u32 & physicalAddress, const std::shared_ptr<Register32_t>& register32)
{
	mapObject(std::make_shared<MappedRegister32_t>(physicalAddress, register32));
}

void PhysicalMMU_t::mapObject(const u32& physicalAddress, const std::shared_ptr<Register64_t>& register64)
{
	mapObject(std::make_shared<MappedRegister64_t>(physicalAddress, register64));
}

void PhysicalMMU_t::mapObject(const u32& physicalAddress, const std::shared_ptr<Register128_t>& register128)
{
	mapObject(std::make_shared<MappedRegister128_t>(physicalAddress, register128));
}

void PhysicalMMU_t::mapObject(const u32& physicalAddress, const std::shared_ptr<FPRegister32_t>& fpRegister32)
{
	mapObject(std::make_shared<MappedFPRegister32_t>(physicalAddress, fpRegister32));
}

void PhysicalMMU_t::mapObject(const u32& physicalAddress, const std::shared_ptr<FPRegister128_t>& fpRegister128)
{
	mapObject(std::make_shared<MappedFPRegister128_t>(physicalAddress, fpRegister128));
}

u32 PhysicalMMU_t::getVDN(u32 PS2PhysicalAddress) const
{
	return (PS2PhysicalAddress >> (OFFSET_BITS + PAGE_BITS)) & DIRECTORY_MASK;
}

u32 PhysicalMMU_t::getVPN(u32 PS2PhysicalAddress) const
{
	return (PS2PhysicalAddress >> OFFSET_BITS) & PAGE_MASK;
}

u32 PhysicalMMU_t::getOffset(u32 PS2PhysicalAddress) const
{
	return PS2PhysicalAddress & OFFSET_MASK;
}

u32 PhysicalMMU_t::getDirectoryFromPageOffset(u32 absPageIndexStart, u32 pageOffset) const
{
	return (absPageIndexStart + pageOffset) / PAGE_ENTRIES;
}

u32 PhysicalMMU_t::getDirPageFromPageOffset(u32 absPageIndexStart, u32 pageOffset) const
{
	return (absPageIndexStart + pageOffset) % PAGE_ENTRIES;
}

u32 PhysicalMMU_t::getAbsPageFromDirAndPageOffset(u32 absDirectoryIndex, u32 pageOffset) const
{
	return absDirectoryIndex * PAGE_ENTRIES + pageOffset;
}

void PhysicalMMU_t::allocDirectory(u32 directoryIndex) const
{
	// Allocate VDN only if empty and set to null initially.
	if (mPageTable[directoryIndex] == nullptr) {
		mPageTable[directoryIndex] = new std::shared_ptr<PhysicalMapped>[PAGE_ENTRIES];
		// Ok... VS compiler crashes if we try to do array initalisation above... so try memset to do it? This works...
		memset(mPageTable[directoryIndex], 0, PAGE_ENTRIES * sizeof(mPageTable[directoryIndex][0]));
	}
}

std::shared_ptr<PhysicalMapped> & PhysicalMMU_t::getMappedMemory(u32 baseVDN, u32 baseVPN) const
{
	// Lookup the page in the page table to get the memory object (aka page frame number (PFN)).
	// If the directory or memory object comes back as nullptr, throw a runtime exception.
	std::shared_ptr<PhysicalMapped>* tableDirectory = mPageTable[baseVDN];
#if defined(BUILD_DEBUG)
	if (tableDirectory == nullptr)
	{
		char message[1000];
		sprintf_s(message, "Not found: Lookup for VA = 0x%08X returned a null VDN. Check input for error, or maybe it has not been mapped in the first place. VDN = %X, VPN = %X.", (baseVDN << (OFFSET_BITS + PAGE_BITS)) | (baseVPN << (OFFSET_BITS)), baseVDN, baseVPN);
		throw std::runtime_error(message);
	}
#endif

	std::shared_ptr<PhysicalMapped> & mappedMemory = tableDirectory[baseVPN];
#if defined(BUILD_DEBUG)
	if (mappedMemory == nullptr)
	{
		char message[1000];
		sprintf_s(message, "Not found: Lookup for VA = 0x%08X returned a null PFN. Check input for error, or maybe it has not been mapped in the first place. VDN = %X, VPN = %X.", (baseVDN << (OFFSET_BITS + PAGE_BITS)) | (baseVPN << (OFFSET_BITS)), baseVDN, baseVPN);
		throw std::runtime_error(message);
	}
#endif

	// Return storage object.
	return mappedMemory;
}

u8 PhysicalMMU_t::readByteU(u32 PS2PhysicalAddress) const
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	const u32 baseVDN = getVDN(PS2PhysicalAddress);
	const u32 baseVPN = getVPN(PS2PhysicalAddress);
	const u32 pageOffset = getOffset(PS2PhysicalAddress);
	const u32 absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<PhysicalMapped> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	const u32 storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the read on the storage object at the specified index.
	return mappedMemory->readByteU(storageIndex);
}

void PhysicalMMU_t::writeByteU(u32 PS2PhysicalAddress, u8 value) const
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	const u32 baseVDN = getVDN(PS2PhysicalAddress);
	const u32 baseVPN = getVPN(PS2PhysicalAddress);
	const u32 pageOffset = getOffset(PS2PhysicalAddress);
	const u32 absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<PhysicalMapped> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	const u32 storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the write on the storage object at the specified index.
	mappedMemory->writeByteU(storageIndex, value);
}

s8 PhysicalMMU_t::readByteS(u32 PS2PhysicalAddress) const
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	u32 baseVDN = getVDN(PS2PhysicalAddress);
	u32 baseVPN = getVPN(PS2PhysicalAddress);
	u32 pageOffset = getOffset(PS2PhysicalAddress);
	u32 absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object.
	std::shared_ptr<PhysicalMapped> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	const u32 storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the read on the storage object at the specified index.
	return mappedMemory->readByteS(storageIndex);
}

void PhysicalMMU_t::writeByteS(u32 PS2PhysicalAddress, s8 value) const
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	const u32 baseVDN = getVDN(PS2PhysicalAddress);
	const u32 baseVPN = getVPN(PS2PhysicalAddress);
	const u32 pageOffset = getOffset(PS2PhysicalAddress);
	const u32 absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<PhysicalMapped> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	const u32 storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the write on the storage object at the specified index.
	mappedMemory->writeByteS(storageIndex, value);
}

u16 PhysicalMMU_t::readHwordU(u32 PS2PhysicalAddress) const
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	const u32 baseVDN = getVDN(PS2PhysicalAddress);
	const u32 baseVPN = getVPN(PS2PhysicalAddress);
	const u32 pageOffset = getOffset(PS2PhysicalAddress);
	const u32 absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<PhysicalMapped> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	const u32 storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the read on the storage object at the specified index.
	return mappedMemory->readHwordU(storageIndex);
}

void PhysicalMMU_t::writeHwordU(u32 PS2PhysicalAddress, u16 value) const
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	const u32 baseVDN = getVDN(PS2PhysicalAddress);
	const u32 baseVPN = getVPN(PS2PhysicalAddress);
	const u32 pageOffset = getOffset(PS2PhysicalAddress);
	const u32 absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<PhysicalMapped> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	const u32 storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the write on the storage object at the specified index.
	mappedMemory->writeHwordU(storageIndex, value);
}

s16 PhysicalMMU_t::readHwordS(u32 PS2PhysicalAddress) const
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	const u32 baseVDN = getVDN(PS2PhysicalAddress);
	const u32 baseVPN = getVPN(PS2PhysicalAddress);
	const u32 pageOffset = getOffset(PS2PhysicalAddress);
	const u32 absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<PhysicalMapped> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	const u32 storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the read on the storage object at the specified index.
	return mappedMemory->readHwordS(storageIndex);
}

void PhysicalMMU_t::writeHwordS(u32 PS2PhysicalAddress, s16 value) const
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	const u32 baseVDN = getVDN(PS2PhysicalAddress);
	const u32 baseVPN = getVPN(PS2PhysicalAddress);
	const u32 pageOffset = getOffset(PS2PhysicalAddress);
	const u32 absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<PhysicalMapped> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	const u32 storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the write on the storage object at the specified index.
	mappedMemory->writeHwordS(storageIndex, value);
}

u32 PhysicalMMU_t::readWordU(u32 PS2PhysicalAddress) const
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	const u32 baseVDN = getVDN(PS2PhysicalAddress);
	const u32 baseVPN = getVPN(PS2PhysicalAddress);
	const u32 pageOffset = getOffset(PS2PhysicalAddress);
	const u32 absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<PhysicalMapped> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	const u32 storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the read on the storage object at the specified index.
	return mappedMemory->readWordU(storageIndex);
}

void PhysicalMMU_t::writeWordU(u32 PS2PhysicalAddress, u32 value) const
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	const u32 baseVDN = getVDN(PS2PhysicalAddress);
	const u32 baseVPN = getVPN(PS2PhysicalAddress);
	const u32 pageOffset = getOffset(PS2PhysicalAddress);
	const u32 absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<PhysicalMapped> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	const u32 storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the write on the storage object at the specified index.
	mappedMemory->writeWordU(storageIndex, value);
}

s32 PhysicalMMU_t::readWordS(u32 PS2PhysicalAddress) const
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	const u32 baseVDN = getVDN(PS2PhysicalAddress);
	const u32 baseVPN = getVPN(PS2PhysicalAddress);
	const u32 pageOffset = getOffset(PS2PhysicalAddress);
	const u32 absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<PhysicalMapped> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	const u32 storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the read on the storage object at the specified index.
	return mappedMemory->readWordS(storageIndex);
}

void PhysicalMMU_t::writeWordS(u32 PS2PhysicalAddress, s32 value) const
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	const u32 baseVDN = getVDN(PS2PhysicalAddress);
	const u32 baseVPN = getVPN(PS2PhysicalAddress);
	const u32 pageOffset = getOffset(PS2PhysicalAddress);
	const u32 absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<PhysicalMapped> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	const u32 storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the write on the storage object at the specified index.
	mappedMemory->writeWordS(storageIndex, value);
}

u64 PhysicalMMU_t::readDwordU(u32 PS2PhysicalAddress) const
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	const u32 baseVDN = getVDN(PS2PhysicalAddress);
	const u32 baseVPN = getVPN(PS2PhysicalAddress);
	const u32 pageOffset = getOffset(PS2PhysicalAddress);
	const u32 absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<PhysicalMapped> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	const u32 storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the read on the storage object at the specified index.
	return mappedMemory->readDwordU(storageIndex);
}

void PhysicalMMU_t::writeDwordU(u32 PS2PhysicalAddress, u64 value) const
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	const u32 baseVDN = getVDN(PS2PhysicalAddress);
	const u32 baseVPN = getVPN(PS2PhysicalAddress);
	const u32 pageOffset = getOffset(PS2PhysicalAddress);
	const u32 absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<PhysicalMapped> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	const u32 storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the write on the storage object at the specified index.
	mappedMemory->writeDwordU(storageIndex, value);
}

s64 PhysicalMMU_t::readDwordS(u32 PS2PhysicalAddress) const
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	const u32 baseVDN = getVDN(PS2PhysicalAddress);
	const u32 baseVPN = getVPN(PS2PhysicalAddress);
	const u32 pageOffset = getOffset(PS2PhysicalAddress);
	const u32 absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<PhysicalMapped> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	const u32 storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the read on the storage object at the specified index.
	return mappedMemory->readDwordS(storageIndex);
}

void PhysicalMMU_t::writeDwordS(u32 PS2PhysicalAddress, s64 value) const
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	const u32 baseVDN = getVDN(PS2PhysicalAddress);
	const u32 baseVPN = getVPN(PS2PhysicalAddress);
	const u32 pageOffset = getOffset(PS2PhysicalAddress);
	const u32 absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<PhysicalMapped> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	const u32 storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the write on the storage object at the specified index.
	mappedMemory->writeDwordS(storageIndex, value);
}