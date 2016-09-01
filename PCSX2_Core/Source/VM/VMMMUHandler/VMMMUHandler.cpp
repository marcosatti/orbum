#include "stdafx.h"

#include <stdexcept>
#include <cmath>

#include "VM/VMMain.h"
#include "VM/VMMMUHandler/VMMMUHandler.h"
#include "Common/Interfaces/VMMMUMappedStorageObject.h"

VMMMUHandler::VMMMUHandler(const VMMain* const vmMain) :
	VMMMUComponent(vmMain),
	DIRECTORY_ENTRIES(TABLE_MAX_ADDRESSABLE_SIZE_BYTES / DIRECTORY_SIZE_BYTES),
	PAGE_ENTRIES(DIRECTORY_SIZE_BYTES / PAGE_SIZE_BYTES),
	OFFSET_BITS(static_cast<u32>(log2(PAGE_SIZE_BYTES))),
	OFFSET_MASK(PAGE_SIZE_BYTES - 1),
	DIRECTORY_BITS(static_cast<u32>(log2(DIRECTORY_ENTRIES))),
	DIRECTORY_MASK(DIRECTORY_ENTRIES - 1),
	PAGE_BITS(static_cast<u32>(log2(PAGE_ENTRIES))),
	PAGE_MASK(PAGE_ENTRIES - 1)
{
	// Allocate the page table (directories).
	mPageTable = new std::shared_ptr<VMMMUMappedStorageObject>*[DIRECTORY_ENTRIES];

	// Ok... VS compiler crashes if we try to do array initalisation above... so try memset to do it? This works...
	// Sets all of the directory to nullptr's.
	memset(mPageTable, 0, DIRECTORY_ENTRIES * sizeof(mPageTable[0]));
}

VMMMUHandler::~VMMMUHandler()
{
	// Destroy any allocated pages.
	for (u32 i = 0; i < DIRECTORY_ENTRIES; i++)
	{
		if (mPageTable[i] != nullptr) delete[] mPageTable[i];
	}
	// Destroy the page table (directories).
	delete[] mPageTable;
}

void VMMMUHandler::mapMemory(const std::shared_ptr<VMMMUMappedStorageObject> & clientStorage, const u32 & PS2MemoryAddress)
{
	// Do not do anything for getStorageSize equal to 0.
	if (clientStorage->getStorageSize() == 0) return;

	// Get the base virtual directory number (VDN) and virtual page number (VPN).
	u32 baseVDN = getVDN(PS2MemoryAddress);
	u32 baseVPN = getVPN(PS2MemoryAddress);

	// Work out how many pages the memory block occupies. If it is not evenly divisible, need to add on an extra page to account for the extra length.
	// Thank you to Ian Nelson for the round up solution: http://stackoverflow.com/questions/17944/how-to-round-up-the-result-of-integer-division, very good.
	size_t pagesCount = (clientStorage->getStorageSize() + PAGE_SIZE_BYTES - 1) / PAGE_SIZE_BYTES;

	// Get absolute linear page position that we start mapping memory from.
	u32 absPageStartIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);
	
	// Set the base page index of the storage object, so it can calculate the byte(s) it needs to access later on when its used.
	clientStorage->setAbsMappedPageIndex(absPageStartIndex);

	// Iterate through the pages to set the client addresses.
	u32 absDirectoryIndex;
	u32 absPageIndex;
	for (u32 i = 0; i < pagesCount; i++)
	{
		// Get absolute directory and page index.
		absDirectoryIndex = getAbsDirectoryFromPageOffset(absPageStartIndex, i);
		absPageIndex = getAbsDirPageFromPageOffset(absPageStartIndex, i);

		// Make sure directory is allocated.
		allocDirectory(absDirectoryIndex);

		// Map memory entry.
		mPageTable[absDirectoryIndex][absPageIndex] = clientStorage;
	}
}

u32 VMMMUHandler::getVDN(u32 PS2PhysicalAddress) const
{
	return (PS2PhysicalAddress >> (OFFSET_BITS + PAGE_BITS)) & DIRECTORY_MASK;
}

u32 VMMMUHandler::getVPN(u32 PS2PhysicalAddress) const
{
	return (PS2PhysicalAddress >> OFFSET_BITS) & PAGE_MASK;
}

u32 VMMMUHandler::getOffset(u32 PS2PhysicalAddress) const
{
	return PS2PhysicalAddress & OFFSET_MASK;
}

u32 VMMMUHandler::getAbsDirectoryFromPageOffset(u32 absPageIndexStart, u32 pageOffset) const
{
	return (absPageIndexStart + pageOffset) / PAGE_ENTRIES;
}

u32 VMMMUHandler::getAbsDirPageFromPageOffset(u32 absPageIndexStart, u32 pageOffset) const
{
	return (absPageIndexStart + pageOffset) % PAGE_ENTRIES;
}

u32 VMMMUHandler::getAbsPageFromDirAndPageOffset(u32 absDirectoryIndex, u32 pageOffset) const
{
	return absDirectoryIndex* PAGE_ENTRIES + pageOffset;
}

void VMMMUHandler::allocDirectory(u32 directoryIndex) const
{
	// Allocate VDN only if empty and set to null initially.
	if (mPageTable[directoryIndex] == nullptr) {
		mPageTable[directoryIndex] = new std::shared_ptr<VMMMUMappedStorageObject>[PAGE_ENTRIES];
		// Ok... VS compiler crashes if we try to do array initalisation above... so try memset to do it? This works...
		memset(mPageTable[directoryIndex], 0, PAGE_ENTRIES * sizeof(mPageTable[directoryIndex][0]));
	}
}

std::shared_ptr<VMMMUMappedStorageObject> & VMMMUHandler::getClientStorageObject(u32 baseVDN, u32 baseVPN) const
{
	// Lookup the page in the page table to get the client storage object (aka page frame number (PFN)).
	// If the directory or client storage object comes back as nullptr (= 0), throw a runtime exception.
	std::shared_ptr<VMMMUMappedStorageObject>* tableDirectory = mPageTable[baseVDN];
	if (tableDirectory == nullptr)
	{
		char message[1000];
		sprintf_s(message, "Not found: Given baseVDN returned a null VDN. Check input for error, or maybe it has not been mapped in the first place. VDN = %X, VPN = %X.", baseVDN, baseVPN);
		throw std::runtime_error(message);
	}
	std::shared_ptr<VMMMUMappedStorageObject> & clientStorageObject = tableDirectory[baseVPN];
	if (clientStorageObject == nullptr)
	{
		char message[1000];
		sprintf_s(message, "Not found: Given baseVPN returned a null PFN. Check input for error, or maybe it has not been mapped in the first place. VDN = %X, VPN = %X.", baseVDN, baseVPN);
		throw std::runtime_error(message);
	}

	// Return storage object.
	return clientStorageObject;
}

u8 VMMMUHandler::readByteU(u32 PS2PhysicalAddress) const
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	const u32 baseVDN = getVDN(PS2PhysicalAddress);
	const u32 baseVPN = getVPN(PS2PhysicalAddress);
	const u32 pageOffset = getOffset(PS2PhysicalAddress);
	const u32 absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get client storage object and calculate the storage index to access.
	const std::shared_ptr<VMMMUMappedStorageObject> & clientStorageObject = getClientStorageObject(baseVDN, baseVPN);
	const u32 storageIndex = (absPageIndex - clientStorageObject->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the read on the storage object at the specified index.
	return clientStorageObject->readByteU(storageIndex);
}

void VMMMUHandler::writeByteU(u32 PS2PhysicalAddress, u8 value) const
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	const u32 baseVDN = getVDN(PS2PhysicalAddress);
	const u32 baseVPN = getVPN(PS2PhysicalAddress);
	const u32 pageOffset = getOffset(PS2PhysicalAddress);
	const u32 absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get client storage object and calculate the storage index to access.
	const std::shared_ptr<VMMMUMappedStorageObject> & clientStorageObject = getClientStorageObject(baseVDN, baseVPN);
	const u32 storageIndex = (absPageIndex - clientStorageObject->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the write on the storage object at the specified index.
	clientStorageObject->writeByteU(storageIndex, value);
}

s8 VMMMUHandler::readByteS(u32 PS2PhysicalAddress) const
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	u32 baseVDN = getVDN(PS2PhysicalAddress);
	u32 baseVPN = getVPN(PS2PhysicalAddress);
	u32 pageOffset = getOffset(PS2PhysicalAddress);
	u32 absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get client storage object.
	std::shared_ptr<VMMMUMappedStorageObject> & clientStorageObject = getClientStorageObject(baseVDN, baseVPN);
	const u32 storageIndex = (absPageIndex - clientStorageObject->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the read on the storage object at the specified index.
	return clientStorageObject->readByteS(storageIndex);
}

void VMMMUHandler::writeByteS(u32 PS2PhysicalAddress, s8 value) const
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	const u32 baseVDN = getVDN(PS2PhysicalAddress);
	const u32 baseVPN = getVPN(PS2PhysicalAddress);
	const u32 pageOffset = getOffset(PS2PhysicalAddress);
	const u32 absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get client storage object and calculate the storage index to access.
	const std::shared_ptr<VMMMUMappedStorageObject> & clientStorageObject = getClientStorageObject(baseVDN, baseVPN);
	const u32 storageIndex = (absPageIndex - clientStorageObject->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the write on the storage object at the specified index.
	clientStorageObject->writeByteS(storageIndex, value);
}

u16 VMMMUHandler::readHwordU(u32 PS2PhysicalAddress) const
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	const u32 baseVDN = getVDN(PS2PhysicalAddress);
	const u32 baseVPN = getVPN(PS2PhysicalAddress);
	const u32 pageOffset = getOffset(PS2PhysicalAddress);
	const u32 absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get client storage object and calculate the storage index to access.
	const std::shared_ptr<VMMMUMappedStorageObject> & clientStorageObject = getClientStorageObject(baseVDN, baseVPN);
	const u32 storageIndex = (absPageIndex - clientStorageObject->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the read on the storage object at the specified index.
	return clientStorageObject->readHwordU(storageIndex);
}

void VMMMUHandler::writeHwordU(u32 PS2PhysicalAddress, u16 value) const
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	const u32 baseVDN = getVDN(PS2PhysicalAddress);
	const u32 baseVPN = getVPN(PS2PhysicalAddress);
	const u32 pageOffset = getOffset(PS2PhysicalAddress);
	const u32 absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get client storage object and calculate the storage index to access.
	const std::shared_ptr<VMMMUMappedStorageObject> & clientStorageObject = getClientStorageObject(baseVDN, baseVPN);
	const u32 storageIndex = (absPageIndex - clientStorageObject->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the write on the storage object at the specified index.
	clientStorageObject->writeHwordU(storageIndex, value);
}

s16 VMMMUHandler::readHwordS(u32 PS2PhysicalAddress) const
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	const u32 baseVDN = getVDN(PS2PhysicalAddress);
	const u32 baseVPN = getVPN(PS2PhysicalAddress);
	const u32 pageOffset = getOffset(PS2PhysicalAddress);
	const u32 absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get client storage object and calculate the storage index to access.
	const std::shared_ptr<VMMMUMappedStorageObject> & clientStorageObject = getClientStorageObject(baseVDN, baseVPN);
	const u32 storageIndex = (absPageIndex - clientStorageObject->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the read on the storage object at the specified index.
	return clientStorageObject->readHwordS(storageIndex);
}

void VMMMUHandler::writeHwordS(u32 PS2PhysicalAddress, s16 value) const
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	const u32 baseVDN = getVDN(PS2PhysicalAddress);
	const u32 baseVPN = getVPN(PS2PhysicalAddress);
	const u32 pageOffset = getOffset(PS2PhysicalAddress);
	const u32 absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get client storage object and calculate the storage index to access.
	const std::shared_ptr<VMMMUMappedStorageObject> & clientStorageObject = getClientStorageObject(baseVDN, baseVPN);
	const u32 storageIndex = (absPageIndex - clientStorageObject->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the write on the storage object at the specified index.
	clientStorageObject->writeHwordS(storageIndex, value);
}

u32 VMMMUHandler::readWordU(u32 PS2PhysicalAddress) const
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	const u32 baseVDN = getVDN(PS2PhysicalAddress);
	const u32 baseVPN = getVPN(PS2PhysicalAddress);
	const u32 pageOffset = getOffset(PS2PhysicalAddress);
	const u32 absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get client storage object and calculate the storage index to access.
	const std::shared_ptr<VMMMUMappedStorageObject> & clientStorageObject = getClientStorageObject(baseVDN, baseVPN);
	const u32 storageIndex = (absPageIndex - clientStorageObject->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the read on the storage object at the specified index.
	return clientStorageObject->readWordU(storageIndex);
}

void VMMMUHandler::writeWordU(u32 PS2PhysicalAddress, u32 value) const
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	const u32 baseVDN = getVDN(PS2PhysicalAddress);
	const u32 baseVPN = getVPN(PS2PhysicalAddress);
	const u32 pageOffset = getOffset(PS2PhysicalAddress);
	const u32 absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get client storage object and calculate the storage index to access.
	const std::shared_ptr<VMMMUMappedStorageObject> & clientStorageObject = getClientStorageObject(baseVDN, baseVPN);
	const u32 storageIndex = (absPageIndex - clientStorageObject->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the write on the storage object at the specified index.
	clientStorageObject->writeWordU(storageIndex, value);
}

s32 VMMMUHandler::readWordS(u32 PS2PhysicalAddress) const
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	const u32 baseVDN = getVDN(PS2PhysicalAddress);
	const u32 baseVPN = getVPN(PS2PhysicalAddress);
	const u32 pageOffset = getOffset(PS2PhysicalAddress);
	const u32 absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get client storage object and calculate the storage index to access.
	const std::shared_ptr<VMMMUMappedStorageObject> & clientStorageObject = getClientStorageObject(baseVDN, baseVPN);
	const u32 storageIndex = (absPageIndex - clientStorageObject->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the read on the storage object at the specified index.
	return clientStorageObject->readWordS(storageIndex);
}

void VMMMUHandler::writeWordS(u32 PS2PhysicalAddress, s32 value) const
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	const u32 baseVDN = getVDN(PS2PhysicalAddress);
	const u32 baseVPN = getVPN(PS2PhysicalAddress);
	const u32 pageOffset = getOffset(PS2PhysicalAddress);
	const u32 absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get client storage object and calculate the storage index to access.
	const std::shared_ptr<VMMMUMappedStorageObject> & clientStorageObject = getClientStorageObject(baseVDN, baseVPN);
	const u32 storageIndex = (absPageIndex - clientStorageObject->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the write on the storage object at the specified index.
	clientStorageObject->writeWordS(storageIndex, value);
}

u64 VMMMUHandler::readDwordU(u32 PS2PhysicalAddress) const
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	const u32 baseVDN = getVDN(PS2PhysicalAddress);
	const u32 baseVPN = getVPN(PS2PhysicalAddress);
	const u32 pageOffset = getOffset(PS2PhysicalAddress);
	const u32 absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get client storage object and calculate the storage index to access.
	const std::shared_ptr<VMMMUMappedStorageObject> & clientStorageObject = getClientStorageObject(baseVDN, baseVPN);
	const u32 storageIndex = (absPageIndex - clientStorageObject->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the read on the storage object at the specified index.
	return clientStorageObject->readDwordU(storageIndex);
}

void VMMMUHandler::writeDwordU(u32 PS2PhysicalAddress, u64 value) const
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	const u32 baseVDN = getVDN(PS2PhysicalAddress);
	const u32 baseVPN = getVPN(PS2PhysicalAddress);
	const u32 pageOffset = getOffset(PS2PhysicalAddress);
	const u32 absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get client storage object and calculate the storage index to access.
	const std::shared_ptr<VMMMUMappedStorageObject> & clientStorageObject = getClientStorageObject(baseVDN, baseVPN);
	const u32 storageIndex = (absPageIndex - clientStorageObject->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the write on the storage object at the specified index.
	clientStorageObject->writeDwordU(storageIndex, value);
}

s64 VMMMUHandler::readDwordS(u32 PS2PhysicalAddress) const
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	const u32 baseVDN = getVDN(PS2PhysicalAddress);
	const u32 baseVPN = getVPN(PS2PhysicalAddress);
	const u32 pageOffset = getOffset(PS2PhysicalAddress);
	const u32 absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get client storage object and calculate the storage index to access.
	const std::shared_ptr<VMMMUMappedStorageObject> & clientStorageObject = getClientStorageObject(baseVDN, baseVPN);
	const u32 storageIndex = (absPageIndex - clientStorageObject->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the read on the storage object at the specified index.
	return clientStorageObject->readDwordS(storageIndex);
}

void VMMMUHandler::writeDwordS(u32 PS2PhysicalAddress, s64 value) const
{
	// Get the virtual directory number (VDN), virtual page number (VPN), absolute page number & offset.
	const u32 baseVDN = getVDN(PS2PhysicalAddress);
	const u32 baseVPN = getVPN(PS2PhysicalAddress);
	const u32 pageOffset = getOffset(PS2PhysicalAddress);
	const u32 absPageIndex = getAbsPageFromDirAndPageOffset(baseVDN, baseVPN);

	// Get client storage object and calculate the storage index to access.
	const std::shared_ptr<VMMMUMappedStorageObject> & clientStorageObject = getClientStorageObject(baseVDN, baseVPN);
	const u32 storageIndex = (absPageIndex - clientStorageObject->getAbsMappedPageIndex()) * PAGE_SIZE_BYTES + pageOffset;

	// Perform the write on the storage object at the specified index.
	clientStorageObject->writeDwordS(storageIndex, value);
}