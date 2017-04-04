#include "stdafx.h"

#include <memory>
#include <stdexcept>
#include <cmath>

#include "Common/Global/Globals.h"

#include "Common/Types/PhysicalMMU/PhysicalMMU_t.h"
#include "Common/Types/PhysicalMMU/PhysicalMapped_t.h"
#include "Common/Types/PhysicalMMU/MappedMemory_t.h"
#include "Common/Types/PhysicalMMU/MappedRegister8_t.h"
#include "Common/Types/PhysicalMMU/MappedRegister16_t.h"
#include "Common/Types/PhysicalMMU/MappedRegister32_t.h"
#include "Common/Types/PhysicalMMU/MappedRegister64_t.h"
#include "Common/Types/PhysicalMMU/MappedRegister128_t.h"
#include "Common/Types/PhysicalMMU/MappedFPRegister32_t.h"
#include "Common/Types/PhysicalMMU/MappedFPRegister128_t.h"
#include "Common/Types/PhysicalMMU/MappedFIFOQueue32_t.h"

PhysicalMMU_t::PhysicalMMU_t(const size_t & maxAddressableSizeBytes, const size_t & directorySizeBytes, const size_t & pageSizeBytes) :
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
	// Allocate base directories.
	mPageTable.resize(DIRECTORY_ENTRIES);
}

void PhysicalMMU_t::mapObject(const std::shared_ptr<PhysicalMapped_t> & physicalMapped)
{
	// Do not do anything for getSize equal to 0.
	if (physicalMapped->getSize() == 0) 
		return;

	// Get the base virtual directory number (VDN) and virtual page number (VPN).
	auto baseVDN = getVDN(physicalMapped->getMappedPhysicalAddress());
	auto baseVPN = getVPN(physicalMapped->getMappedPhysicalAddress());

	// Work out how many pages the memory block occupies. If it is not evenly divisible, need to add on an extra page to account for the extra length.
	// Thank you to Ian Nelson for the round up solution: http://stackoverflow.com/questions/17944/how-to-round-up-the-result-of-integer-division, very good.
	size_t pagesCount = (physicalMapped->getSize() + PAGE_SIZE_BYTES - 1) / PAGE_SIZE_BYTES;

	// Get absolute linear page position that we start mapping memory from.
	auto absPageStartIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);
	
	// Set the base page index of the storage object, so it can calculate the byte(s) it needs to access later on when its used.
	physicalMapped->setAbsMappedPageIndex(absPageStartIndex);

	// Iterate through the pages to set the host addresses.
	size_t absDirectoryIndex;
	size_t absPageIndex;
	for (size_t i = 0; i < pagesCount; i++)
	{
		// Get absolute directory and page index.
		absDirectoryIndex = getDirectoryFromPageOffset(absPageStartIndex, i);
		absPageIndex = getDirPageFromPageOffset(absPageStartIndex, i);

		// Allocate pages within directory if needed.
		mPageTable[absDirectoryIndex].resize(PAGE_ENTRIES);

		// Check that there is no existing map data - log a warning if there is.
#if defined(BUILD_DEBUG)
		if (mPageTable[absDirectoryIndex][absPageIndex] != nullptr)
			log(Debug, "(%s, %d) Warning! Physical MMU mapped storage object \"%s\" @ 0x%08X overwritten with object \"%s\". Please fix!",
				__FILENAME__, __LINE__,
				mPageTable[absDirectoryIndex][absPageIndex]->getMnemonic(),
				physicalMapped->getMappedPhysicalAddress(),
				physicalMapped->getMnemonic());
#endif

		// Map memory entry.
		mPageTable[absDirectoryIndex][absPageIndex] = physicalMapped;
	}
}

void PhysicalMMU_t::mapObject(const u32 physicalAddress, const std::shared_ptr<ByteMemory_t>& memory)
{
	mapObject(std::make_shared<MappedMemory_t>(physicalAddress, memory));
}

void PhysicalMMU_t::mapObject(const u32 physicalAddress, const std::shared_ptr<Register8_t>& register8)
{
	mapObject(std::make_shared<MappedRegister8_t>(physicalAddress, register8));
}

void PhysicalMMU_t::mapObject(const u32 physicalAddress, const std::shared_ptr<Register16_t>& register16)
{
	mapObject(std::make_shared<MappedRegister16_t>(physicalAddress, register16));
}

void PhysicalMMU_t::mapObject(const u32 physicalAddress, const std::shared_ptr<Register32_t>& register32)
{
	mapObject(std::make_shared<MappedRegister32_t>(physicalAddress, register32));
}

void PhysicalMMU_t::mapObject(const u32 physicalAddress, const std::shared_ptr<Register64_t>& register64)
{
	mapObject(std::make_shared<MappedRegister64_t>(physicalAddress, register64));
}

void PhysicalMMU_t::mapObject(const u32 physicalAddress, const std::shared_ptr<Register128_t>& register128)
{
	mapObject(std::make_shared<MappedRegister128_t>(physicalAddress, register128));
}

void PhysicalMMU_t::mapObject(const u32 physicalAddress, const std::shared_ptr<FPRegister32_t>& fpRegister32)
{
	mapObject(std::make_shared<MappedFPRegister32_t>(physicalAddress, fpRegister32));
}

void PhysicalMMU_t::mapObject(const u32 physicalAddress, const std::shared_ptr<FPRegister128_t>& fpRegister128)
{
	mapObject(std::make_shared<MappedFPRegister128_t>(physicalAddress, fpRegister128));
}

void PhysicalMMU_t::mapObject(const u32 physicalAddress, const std::shared_ptr<FIFOQueue32_t>& fifoQueue32)
{
	mapObject(std::make_shared<MappedFIFOQueue32_t>(physicalAddress, fifoQueue32));
}

size_t PhysicalMMU_t::getVDN(u32 PS2PhysicalAddress) const
{
	return (PS2PhysicalAddress >> (OFFSET_BITS + PAGE_BITS)) & DIRECTORY_MASK;
}

size_t PhysicalMMU_t::getVPN(u32 PS2PhysicalAddress) const
{
	return (PS2PhysicalAddress >> OFFSET_BITS) & PAGE_MASK;
}

size_t PhysicalMMU_t::getOffset(u32 PS2PhysicalAddress) const
{
	return PS2PhysicalAddress & OFFSET_MASK;
}

size_t PhysicalMMU_t::getDirectoryFromPageOffset(size_t absPageIndexStart, size_t pageOffset) const
{
	return (absPageIndexStart + pageOffset) / PAGE_ENTRIES;
}

size_t PhysicalMMU_t::getDirPageFromPageOffset(size_t absPageIndexStart, size_t pageOffset) const
{
	return (absPageIndexStart + pageOffset) % PAGE_ENTRIES;
}

size_t PhysicalMMU_t::getAbsPageFromDirAndPageOffset(size_t absDirectoryIndex, size_t pageOffset) const
{
	return absDirectoryIndex * PAGE_ENTRIES + pageOffset;
}

std::shared_ptr<PhysicalMapped_t> & PhysicalMMU_t::getMappedMemory(size_t baseVDN, size_t baseVPN)
{
	// Lookup the page in the page table to get the memory object (aka page frame number (PFN)).
	std::shared_ptr<PhysicalMapped_t> & mappedMemory = mPageTable[baseVDN][baseVPN];
#if defined(BUILD_DEBUG)
	if (mappedMemory == nullptr)
	{
		char message[1000];
		sprintf_s(message, "Not found: Lookup for VA = 0x%08X returned a null PFN. Check input for error, or maybe it has not been mapped in the first place. VDN = %zX, VPN = %zX.", static_cast<u32>((baseVDN << (OFFSET_BITS + PAGE_BITS)) | (baseVPN << (OFFSET_BITS))), baseVDN, baseVPN);
		throw std::runtime_error(message);
	}
#endif

	// Return storage object.
	return mappedMemory;
}

u8 PhysicalMMU_t::readByte(const System_t context, u32 PS2PhysicalAddress)
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	auto baseVDN = getVDN(PS2PhysicalAddress);
	auto baseVPN = getVPN(PS2PhysicalAddress);
	auto pageOffset = getOffset(PS2PhysicalAddress);
	auto absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<PhysicalMapped_t> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	size_t storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the read on the storage object at the specified index.
	return mappedMemory->readByte(context, storageIndex);
}

void PhysicalMMU_t::writeByte(const System_t context, u32 PS2PhysicalAddress, u8 value)
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	auto baseVDN = getVDN(PS2PhysicalAddress);
	auto baseVPN = getVPN(PS2PhysicalAddress);
	auto pageOffset = getOffset(PS2PhysicalAddress);
	auto absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<PhysicalMapped_t> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	size_t storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the write on the storage object at the specified index.
	mappedMemory->writeByte(context, storageIndex, value);
}

u16 PhysicalMMU_t::readHword(const System_t context, u32 PS2PhysicalAddress) 
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	auto baseVDN = getVDN(PS2PhysicalAddress);
	auto baseVPN = getVPN(PS2PhysicalAddress);
	auto pageOffset = getOffset(PS2PhysicalAddress);
	auto absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<PhysicalMapped_t> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	size_t storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the read on the storage object at the specified index.
	return mappedMemory->readHword(context, storageIndex);
}

void PhysicalMMU_t::writeHword(const System_t context, u32 PS2PhysicalAddress, u16 value) 
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	auto baseVDN = getVDN(PS2PhysicalAddress);
	auto baseVPN = getVPN(PS2PhysicalAddress);
	auto pageOffset = getOffset(PS2PhysicalAddress);
	auto absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<PhysicalMapped_t> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	size_t storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the write on the storage object at the specified index.
	mappedMemory->writeHword(context, storageIndex, value);
}

u32 PhysicalMMU_t::readWord(const System_t context, u32 PS2PhysicalAddress) 
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	auto baseVDN = getVDN(PS2PhysicalAddress);
	auto baseVPN = getVPN(PS2PhysicalAddress);
	auto pageOffset = getOffset(PS2PhysicalAddress);
	auto absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<PhysicalMapped_t> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	size_t storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the read on the storage object at the specified index.
	return mappedMemory->readWord(context, storageIndex);
}

void PhysicalMMU_t::writeWord(const System_t context, u32 PS2PhysicalAddress, u32 value) 
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	auto baseVDN = getVDN(PS2PhysicalAddress);
	auto baseVPN = getVPN(PS2PhysicalAddress);
	auto pageOffset = getOffset(PS2PhysicalAddress);
	auto absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<PhysicalMapped_t> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	size_t storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the write on the storage object at the specified index.
	mappedMemory->writeWord(context, storageIndex, value);
}

u64 PhysicalMMU_t::readDword(const System_t context, u32 PS2PhysicalAddress)
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	auto baseVDN = getVDN(PS2PhysicalAddress);
	auto baseVPN = getVPN(PS2PhysicalAddress);
	auto pageOffset = getOffset(PS2PhysicalAddress);
	auto absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<PhysicalMapped_t> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	size_t storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the read on the storage object at the specified index.
	return mappedMemory->readDword(context, storageIndex);
}

void PhysicalMMU_t::writeDword(const System_t context, u32 PS2PhysicalAddress, u64 value)
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	auto baseVDN = getVDN(PS2PhysicalAddress);
	auto baseVPN = getVPN(PS2PhysicalAddress);
	auto pageOffset = getOffset(PS2PhysicalAddress);
	auto absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<PhysicalMapped_t> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	size_t storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the write on the storage object at the specified index.
	mappedMemory->writeDword(context, storageIndex, value);
}

u128 PhysicalMMU_t::readQword(const System_t context, u32 PS2PhysicalAddress) 
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	auto baseVDN = getVDN(PS2PhysicalAddress);
	auto baseVPN = getVPN(PS2PhysicalAddress);
	auto pageOffset = getOffset(PS2PhysicalAddress);
	auto absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<PhysicalMapped_t> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	size_t storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the read on the storage object at the specified index.
	return mappedMemory->readQword(context, storageIndex);
}

void PhysicalMMU_t::writeQword(const System_t context, u32 PS2PhysicalAddress, u128 value)
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	auto baseVDN = getVDN(PS2PhysicalAddress);
	auto baseVPN = getVPN(PS2PhysicalAddress);
	auto pageOffset = getOffset(PS2PhysicalAddress);
	auto absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<PhysicalMapped_t> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	size_t storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the write on the storage object at the specified index.
	mappedMemory->writeQword(context, storageIndex, value);
}
