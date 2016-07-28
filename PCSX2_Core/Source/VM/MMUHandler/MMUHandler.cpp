#include "stdafx.h"

#include <stdexcept>
#include <cmath>

#include "VM/VMMain.h"
#include "VM/MMUHandler/MMUHandler.h"

MMUHandler::MMUHandler(const VMMain* const vmMain):
	VMMMUComponent(vmMain),
	DIRECTORY_ENTRIES(TABLE_MAX_SIZE / DIRECTORY_SIZE_BYTES),
	PAGE_ENTRIES(DIRECTORY_SIZE_BYTES / PAGE_SIZE_BYTES),
	OFFSET_BITS(static_cast<u32>(log2(PAGE_SIZE_BYTES))),
	OFFSET_MASK(PAGE_SIZE_BYTES - 1),
	DIRECTORY_BITS(static_cast<u32>(log2(DIRECTORY_ENTRIES))),
	DIRECTORY_MASK(DIRECTORY_ENTRIES - 1),
	PAGE_BITS(static_cast<u32>(log2(PAGE_ENTRIES))),
	PAGE_MASK(PAGE_ENTRIES - 1)
{
	// Allocate the page table (directories).
	mPageTable = new void**[DIRECTORY_ENTRIES];

	// Ok... VS compiler crashes if we try to do array initalisation above... so try memset to do it? This works...
	// Sets all of the directory to nullptr's.
	memset(mPageTable, 0, DIRECTORY_ENTRIES * sizeof(mPageTable[0]));
}

MMUHandler::~MMUHandler()
{
	// Destroy any allocated pages.
	for (u32 i = 0; i < DIRECTORY_ENTRIES; i++)
	{
		if (mPageTable[i] != nullptr) delete[] mPageTable[i];
	}
	// Destroy the page table (directories).
	delete[] mPageTable;
}

void MMUHandler::mapMemory(void* clientMemoryAddress, u32 clientMemoryLength, u32 PS2MemoryAddress) const
{
	// Do not do anything for clientMemoryLength equal to 0.
	if (clientMemoryLength == 0) return;

	// C++11 does not allow any aritmetic to be done on pointers. Need to cast to uintptr_t first (defined in <cstdint>) then cast back. This is to get the memory addresses.
	uintptr_t clientMemoryAddressInt = reinterpret_cast<uintptr_t>(clientMemoryAddress);

	// Get the base virtual directory number (VDN) and virtual page number (VPN).
	u32 baseVDN = getVDN(PS2MemoryAddress);
	u32 baseVPN = getVPN(PS2MemoryAddress);

	// Work out how many pages the memory block occupies. If it is not evenly divisible, need to add on an extra page to account for the extra length.
	// Thank you to Ian Nelson: http://stackoverflow.com/questions/17944/how-to-round-up-the-result-of-integer-division, a very good solution.
	u32 pagesCount = (clientMemoryLength + PAGE_SIZE_BYTES - 1) / PAGE_SIZE_BYTES;

	// Get absolute linear page position that we start mapping memory from.
	u32 absPageStartIndex = baseVDN * PAGE_ENTRIES + baseVPN;

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
		mPageTable[absDirectoryIndex][absPageIndex] = reinterpret_cast<void*>(clientMemoryAddressInt + i * PAGE_SIZE_BYTES);
	}
}

u32 MMUHandler::getVDN(u32 PS2MemoryAddress) const
{
	return (PS2MemoryAddress >> (OFFSET_BITS + PAGE_BITS)) & DIRECTORY_MASK;
}

u32 MMUHandler::getVPN(u32 PS2MemoryAddress) const
{
	return (PS2MemoryAddress >> OFFSET_BITS) & PAGE_MASK;
}

u32 MMUHandler::getOffset(u32 PS2MemoryAddress) const
{
	return PS2MemoryAddress & OFFSET_MASK;
}

u32 MMUHandler::getAbsDirectoryFromPageOffset(u32 absPageIndexStart, u32 pageOffset) const
{
	return (absPageIndexStart + pageOffset) / PAGE_ENTRIES;
}

u32 MMUHandler::getAbsDirPageFromPageOffset(u32 absPageIndexStart, u32 pageOffset) const
{
	return (absPageIndexStart + pageOffset) % PAGE_ENTRIES;
}

void MMUHandler::allocDirectory(u32 directoryIndex) const
{
	// Allocate VDN only if empty and set to null initially.
	if (mPageTable[directoryIndex] == nullptr) {
		mPageTable[directoryIndex] = new void*[PAGE_ENTRIES];
		// Ok... VS compiler crashes if we try to do array initalisation above... so try memset to do it? This works...
		memset(mPageTable[directoryIndex], 0, PAGE_ENTRIES * sizeof(mPageTable[directoryIndex][0]));
	}
}

void* MMUHandler::getclientMemoryAddress(u32 PS2MemoryAddress) const
{
	// Get the virtual directory number (VDN), virtual page number (VPN) & offset.
	u32 baseVDN = getVDN(PS2MemoryAddress);
	u32 baseVPN = getVPN(PS2MemoryAddress);
	u32 offset = getOffset(PS2MemoryAddress);

	// Lookup the page in the page table to get the client base memory address (aka page frame number (PFN)).
	// If the directory or client memory address base comes back as nullptr (= 0), throw a runtime exception.
	// C++11 does not allow any aritmetic to be done on pointers. Need to cast to uintptr_t first (defined in <cstdint>) then cast back.
	void** tableDirectory = mPageTable[baseVDN];
	if (tableDirectory == nullptr) throw std::runtime_error("Not found: Given PS2MemoryAddress returned a null VDN. Check input for error, or maybe it has not been mapped in the first place.");
	void* clientMemoryAddressBase = tableDirectory[baseVPN];
	if (clientMemoryAddressBase == nullptr) throw std::runtime_error("Not found: Given PS2MemoryAddress returned a null PFN. Check input for error, or maybe it has not been mapped in the first place.");
	uintptr_t clientMemoryAddressInt = reinterpret_cast<uintptr_t>(clientMemoryAddressBase);

	// Add the offset to the PFN to complete the address.
	clientMemoryAddressInt += offset;

	// Return address.
	return reinterpret_cast<void*>(clientMemoryAddressInt);
}

u8 MMUHandler::readByteU(u32 PS2MemoryAddress) const
{
	// Get client base address.
	u8 * clientMemoryAddress = reinterpret_cast<u8*>(getclientMemoryAddress(PS2MemoryAddress));

	// Read the value.
	return *clientMemoryAddress;
}

void MMUHandler::writeByteU(u32 PS2MemoryAddress, u8 value) const
{
	// Get client base address.
	u8 * clientMemoryAddress = reinterpret_cast<u8*>(getclientMemoryAddress(PS2MemoryAddress));

	// Write the value.
	*clientMemoryAddress = value;
}

s8 MMUHandler::readByteS(u32 PS2MemoryAddress) const
{
	// Get client base address.
	s8 * clientMemoryAddress = reinterpret_cast<s8*>(getclientMemoryAddress(PS2MemoryAddress));

	// Read the value.
	return *clientMemoryAddress;
}

void MMUHandler::writeByteS(u32 PS2MemoryAddress, s8 value) const
{
	// Get client base address.
	s8 * clientMemoryAddress = reinterpret_cast<s8*>(getclientMemoryAddress(PS2MemoryAddress));

	// Write the value.
	*clientMemoryAddress = value;
}

u16 MMUHandler::readHwordU(u32 PS2MemoryAddress) const
{
	// Get client base address.
	u16 * clientMemoryAddress = reinterpret_cast<u16*>(getclientMemoryAddress(PS2MemoryAddress));

	// Read the value.
	return *clientMemoryAddress;
}

void MMUHandler::writeHwordU(u32 PS2MemoryAddress, u16 value) const
{
	// Get client base address.
	u16 * clientMemoryAddress = reinterpret_cast<u16*>(getclientMemoryAddress(PS2MemoryAddress));

	// Write the value.
	*clientMemoryAddress = value;
}

s16 MMUHandler::readHwordS(u32 PS2MemoryAddress) const
{
	// Get client base address.
	s16 * clientMemoryAddress = reinterpret_cast<s16*>(getclientMemoryAddress(PS2MemoryAddress));

	// Read the value.
	return *clientMemoryAddress;
}

void MMUHandler::writeHwordS(u32 PS2MemoryAddress, s16 value) const
{
	// Get client base address.
	s16 * clientMemoryAddress = reinterpret_cast<s16*>(getclientMemoryAddress(PS2MemoryAddress));

	// Write the value.
	*clientMemoryAddress = value;
}

u32 MMUHandler::readWordU(u32 PS2MemoryAddress) const
{
	// Get client base address.
	u32 * clientMemoryAddress = reinterpret_cast<u32*>(getclientMemoryAddress(PS2MemoryAddress));

	// Read the value.
	return *clientMemoryAddress;
}

void MMUHandler::writeWordU(u32 PS2MemoryAddress, u32 value) const
{
	// Get client base address.
	u32 * clientMemoryAddress = reinterpret_cast<u32*>(getclientMemoryAddress(PS2MemoryAddress));

	// Write the value.
	*clientMemoryAddress = value;
}

s32 MMUHandler::readWordS(u32 PS2MemoryAddress) const
{
	// Get client base address.
	s32 * clientMemoryAddress = reinterpret_cast<s32*>(getclientMemoryAddress(PS2MemoryAddress));

	// Read the value.
	return *clientMemoryAddress;
}

void MMUHandler::writeWordS(u32 PS2MemoryAddress, s32 value) const
{
	// Get client base address.
	s32 * clientMemoryAddress = reinterpret_cast<s32*>(getclientMemoryAddress(PS2MemoryAddress));

	// Write the value.
	*clientMemoryAddress = value;
}

u64 MMUHandler::readDwordU(u32 PS2MemoryAddress) const
{
	// Get client base address.
	u64 * clientMemoryAddress = reinterpret_cast<u64*>(getclientMemoryAddress(PS2MemoryAddress));

	// Read the value.
	return *clientMemoryAddress;
}

void MMUHandler::writeDwordU(u32 PS2MemoryAddress, u64 value) const
{
	// Get client base address.
	u64 * clientMemoryAddress = reinterpret_cast<u64*>(getclientMemoryAddress(PS2MemoryAddress));

	// Write the value.
	*clientMemoryAddress = value;
}

s64 MMUHandler::readDwordS(u32 PS2MemoryAddress) const
{
	// Get client base address.
	s64 * clientMemoryAddress = reinterpret_cast<s64*>(getclientMemoryAddress(PS2MemoryAddress));

	// Read the value.
	return *clientMemoryAddress;
}

void MMUHandler::writeDwordS(u32 PS2MemoryAddress, s64 value) const
{
	// Get client base address.
	s64 * clientMemoryAddress = reinterpret_cast<s64*>(getclientMemoryAddress(PS2MemoryAddress));

	// Write the value.
	*clientMemoryAddress = value;
}

u32 MMUHandler::getTotalPageEntries() const
{
	return DIRECTORY_ENTRIES*PAGE_ENTRIES;
}

u32 MMUHandler::getTableMaxSize() const
{
	return TABLE_MAX_SIZE;
}

u32 MMUHandler::getPageSizeBytes() const
{
	return PAGE_SIZE_BYTES;
}
