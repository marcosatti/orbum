#include "stdafx.h"

#include <memory>
#include <stdexcept>
#include <cmath>

#include "Common/Global/Globals.h"

#include "Common/Types/ByteMMU/ByteMMU_t.h"
#include "Common/Types/ByteMMU/MapperBaseObjectByteMMU_t.h"
#include "Common/Types/ByteMMU/MapperByteMemoryByteMMU_t.h"
#include "Common/Types/ByteMMU/MapperRegister8ByteMMU_t.h"
#include "Common/Types/ByteMMU/MapperRegister16ByteMMU_t.h"
#include "Common/Types/ByteMMU/MapperRegister32ByteMMU_t.h"
#include "Common/Types/ByteMMU/MapperRegister64ByteMMU_t.h"
#include "Common/Types/ByteMMU/MapperRegister128ByteMMU_t.h"
#include "Common/Types/ByteMMU/MapperFIFOQueue32ByteMMU_t.h"

ByteMMU_t::ByteMMU_t(const size_t & maxAddressableSizeBytes, const size_t & directorySizeBytes, const size_t & pageSizeBytes) :
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

void ByteMMU_t::mapObject(const std::shared_ptr<MapperBaseObjectByteMMU_t> & mapperObject)
{
	// Do not do anything for getSize equal to 0.
	if (mapperObject->getSize() == 0) 
		return;

	// Get the base virtual directory number (VDN) and virtual page number (VPN).
	auto baseVDN = getVDN(mapperObject->getMappedPhysicalAddress());
	auto baseVPN = getVPN(mapperObject->getMappedPhysicalAddress());

	// Work out how many pages the memory block occupies. If it is not evenly divisible, need to add on an extra page to account for the extra length.
	// Thank you to Ian Nelson for the round up solution: http://stackoverflow.com/questions/17944/how-to-round-up-the-result-of-integer-division, very good.
	size_t pagesCount = (mapperObject->getSize() + PAGE_SIZE_BYTES - 1) / PAGE_SIZE_BYTES;

	// Get absolute linear page position that we start mapping memory from.
	auto absPageStartIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);
	
	// Set the base page index of the storage object, so it can calculate the byte(s) it needs to access later on when its used.
	mapperObject->setAbsMappedPageIndex(absPageStartIndex);

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
			log(Debug, "(%s, %d) Warning! ByteMMU_t mapped storage object \"%s\" @ 0x%08X overwritten with object \"%s\". Please fix!",
				__FILENAME__, __LINE__,
				mPageTable[absDirectoryIndex][absPageIndex]->getMnemonic(),
				mapperObject->getMappedPhysicalAddress(),
				mapperObject->getMnemonic());
#endif

		// Map memory entry.
		mPageTable[absDirectoryIndex][absPageIndex] = mapperObject;
	}
}

void ByteMMU_t::mapObject(const u32 physicalAddress, const std::shared_ptr<ByteMemory_t>& memory)
{
	mapObject(std::make_shared<MapperByteMemoryByteMMU_t>(physicalAddress, memory));
}

void ByteMMU_t::mapObject(const u32 physicalAddress, const std::shared_ptr<Register8_t>& register8)
{
	mapObject(std::make_shared<MapperRegister8ByteMMU_t>(physicalAddress, register8));
}

void ByteMMU_t::mapObject(const u32 physicalAddress, const std::shared_ptr<Register16_t>& register16)
{
	mapObject(std::make_shared<MapperRegister16ByteMMU_t>(physicalAddress, register16));
}

void ByteMMU_t::mapObject(const u32 physicalAddress, const std::shared_ptr<Register32_t>& register32)
{
	mapObject(std::make_shared<MapperRegister32ByteMMU_t>(physicalAddress, register32));
}

void ByteMMU_t::mapObject(const u32 physicalAddress, const std::shared_ptr<Register64_t>& register64)
{
	mapObject(std::make_shared<MapperRegister64ByteMMU_t>(physicalAddress, register64));
}

void ByteMMU_t::mapObject(const u32 physicalAddress, const std::shared_ptr<Register128_t>& register128)
{
	mapObject(std::make_shared<MapperRegister128ByteMMU_t>(physicalAddress, register128));
}

void ByteMMU_t::mapObject(const u32 physicalAddress, const std::shared_ptr<FIFOQueue32_t>& fifoQueue32)
{
	mapObject(std::make_shared<MapperFIFOQueue32ByteMMU_t>(physicalAddress, fifoQueue32));
}

size_t ByteMMU_t::getVDN(u32 PS2PhysicalAddress) const
{
	return (PS2PhysicalAddress >> (OFFSET_BITS + PAGE_BITS)) & DIRECTORY_MASK;
}

size_t ByteMMU_t::getVPN(u32 PS2PhysicalAddress) const
{
	return (PS2PhysicalAddress >> OFFSET_BITS) & PAGE_MASK;
}

size_t ByteMMU_t::getOffset(u32 PS2PhysicalAddress) const
{
	return PS2PhysicalAddress & OFFSET_MASK;
}

size_t ByteMMU_t::getDirectoryFromPageOffset(size_t absPageIndexStart, size_t pageOffset) const
{
	return (absPageIndexStart + pageOffset) / PAGE_ENTRIES;
}

size_t ByteMMU_t::getDirPageFromPageOffset(size_t absPageIndexStart, size_t pageOffset) const
{
	return (absPageIndexStart + pageOffset) % PAGE_ENTRIES;
}

size_t ByteMMU_t::getAbsPageFromDirAndPageOffset(size_t absDirectoryIndex, size_t pageOffset) const
{
	return absDirectoryIndex * PAGE_ENTRIES + pageOffset;
}

std::shared_ptr<MapperBaseObjectByteMMU_t> & ByteMMU_t::getMappedMemory(size_t baseVDN, size_t baseVPN)
{
	// Lookup the page in the page table to get the memory object (aka page frame number (PFN)).
	std::shared_ptr<MapperBaseObjectByteMMU_t> & mappedMemory = mPageTable[baseVDN][baseVPN];
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

u8 ByteMMU_t::readByte(const System_t context, u32 PS2PhysicalAddress)
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	auto baseVDN = getVDN(PS2PhysicalAddress);
	auto baseVPN = getVPN(PS2PhysicalAddress);
	auto pageOffset = getOffset(PS2PhysicalAddress);
	auto absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<MapperBaseObjectByteMMU_t> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	size_t storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the read on the storage object at the specified index.
	return mappedMemory->readByte(context, storageIndex);
}

void ByteMMU_t::writeByte(const System_t context, u32 PS2PhysicalAddress, u8 value)
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	auto baseVDN = getVDN(PS2PhysicalAddress);
	auto baseVPN = getVPN(PS2PhysicalAddress);
	auto pageOffset = getOffset(PS2PhysicalAddress);
	auto absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<MapperBaseObjectByteMMU_t> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	size_t storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the write on the storage object at the specified index.
	mappedMemory->writeByte(context, storageIndex, value);
}

u16 ByteMMU_t::readHword(const System_t context, u32 PS2PhysicalAddress) 
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	auto baseVDN = getVDN(PS2PhysicalAddress);
	auto baseVPN = getVPN(PS2PhysicalAddress);
	auto pageOffset = getOffset(PS2PhysicalAddress);
	auto absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<MapperBaseObjectByteMMU_t> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	size_t storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the read on the storage object at the specified index.
	return mappedMemory->readHword(context, storageIndex);
}

void ByteMMU_t::writeHword(const System_t context, u32 PS2PhysicalAddress, u16 value) 
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	auto baseVDN = getVDN(PS2PhysicalAddress);
	auto baseVPN = getVPN(PS2PhysicalAddress);
	auto pageOffset = getOffset(PS2PhysicalAddress);
	auto absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<MapperBaseObjectByteMMU_t> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	size_t storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the write on the storage object at the specified index.
	mappedMemory->writeHword(context, storageIndex, value);
}

u32 ByteMMU_t::readWord(const System_t context, u32 PS2PhysicalAddress) 
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	auto baseVDN = getVDN(PS2PhysicalAddress);
	auto baseVPN = getVPN(PS2PhysicalAddress);
	auto pageOffset = getOffset(PS2PhysicalAddress);
	auto absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<MapperBaseObjectByteMMU_t> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	size_t storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the read on the storage object at the specified index.
	return mappedMemory->readWord(context, storageIndex);
}

void ByteMMU_t::writeWord(const System_t context, u32 PS2PhysicalAddress, u32 value) 
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	auto baseVDN = getVDN(PS2PhysicalAddress);
	auto baseVPN = getVPN(PS2PhysicalAddress);
	auto pageOffset = getOffset(PS2PhysicalAddress);
	auto absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<MapperBaseObjectByteMMU_t> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	size_t storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the write on the storage object at the specified index.
	mappedMemory->writeWord(context, storageIndex, value);
}

u64 ByteMMU_t::readDword(const System_t context, u32 PS2PhysicalAddress)
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	auto baseVDN = getVDN(PS2PhysicalAddress);
	auto baseVPN = getVPN(PS2PhysicalAddress);
	auto pageOffset = getOffset(PS2PhysicalAddress);
	auto absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<MapperBaseObjectByteMMU_t> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	size_t storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the read on the storage object at the specified index.
	return mappedMemory->readDword(context, storageIndex);
}

void ByteMMU_t::writeDword(const System_t context, u32 PS2PhysicalAddress, u64 value)
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	auto baseVDN = getVDN(PS2PhysicalAddress);
	auto baseVPN = getVPN(PS2PhysicalAddress);
	auto pageOffset = getOffset(PS2PhysicalAddress);
	auto absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<MapperBaseObjectByteMMU_t> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	size_t storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the write on the storage object at the specified index.
	mappedMemory->writeDword(context, storageIndex, value);
}

u128 ByteMMU_t::readQword(const System_t context, u32 PS2PhysicalAddress) 
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	auto baseVDN = getVDN(PS2PhysicalAddress);
	auto baseVPN = getVPN(PS2PhysicalAddress);
	auto pageOffset = getOffset(PS2PhysicalAddress);
	auto absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<MapperBaseObjectByteMMU_t> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	size_t storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the read on the storage object at the specified index.
	return mappedMemory->readQword(context, storageIndex);
}

void ByteMMU_t::writeQword(const System_t context, u32 PS2PhysicalAddress, u128 value)
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	auto baseVDN = getVDN(PS2PhysicalAddress);
	auto baseVPN = getVPN(PS2PhysicalAddress);
	auto pageOffset = getOffset(PS2PhysicalAddress);
	auto absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get host storage object and calculate the storage index to access.
	const std::shared_ptr<MapperBaseObjectByteMMU_t> & mappedMemory = getMappedMemory(baseVDN, baseVPN);
	size_t storageIndex = (absPageIndex - mappedMemory->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the write on the storage object at the specified index.
	mappedMemory->writeQword(context, storageIndex, value);
}
