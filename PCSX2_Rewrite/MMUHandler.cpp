#include "stdafx.h"

#include <stdexcept>

#include "Globals.h"
#include "MMUHandler.h"

MMUHandler::MMUHandler(const VMMain* const vmMain):
	VMMMUComponent(vmMain),
	pageTable(std::make_unique<void**>(new void*[PAGE_TABLE_ENTRIES]))
{
	// Ok... VS compiler crashes if we try to do array initalisation above... so try memset to do it?
	memset((*pageTable), 0, PAGE_TABLE_ENTRIES * sizeof((*pageTable)[0]));
}

MMUHandler::~MMUHandler()
{
}

void MMUHandler::mapMemory(void* clientMemoryAddress, u32 clientMemoryLength, u32 PS2MemoryAddress) const
{
	// Get the virtual page number (VPN).
	u32 vpn = getVPN(PS2MemoryAddress);

	// Work out how many pages the memory block occupies & check if 
	u32 pagesCount = clientMemoryLength / PAGE_SIZE;

	// Check that the end page number doesnt exceed the maximum allowed pages.
	if ((vpn + pagesCount) > PAGE_TABLE_ENTRIES) throw std::range_error("Not mapped: clientMemoryAddress + clientMemoryLength combined exceeds the maximum allowable address translation range.");

	// C++11 does not allow any aritmetic to be done on pointers. Need to cast to uintptr_t first (defined in <cstdint>) then cast back.
	uintptr_t clientMemoryAddressInt = reinterpret_cast<uintptr_t>(clientMemoryAddress);

	// Allocate the pages in the table.
	for (u32 i = 0; i < pagesCount; i++)
	{
		(*pageTable)[vpn + i] = reinterpret_cast<void*>(clientMemoryAddressInt + (i * PAGE_SIZE));
	}
}

u32 MMUHandler::getVPN(u32 PS2MemoryAddress)
{
	return PS2MemoryAddress >> PAGE_BITS;
}

u32 MMUHandler::getOffset(u32 PS2MemoryAddress)
{
	return PS2MemoryAddress & PAGE_MASK;
}

void* MMUHandler::getclientMemoryAddress(u32 PS2MemoryAddress) const
{
	// Get the virtual page number (VPN) & offset.
	u32 vpn = getVPN(PS2MemoryAddress);
	if (vpn > (PAGE_TABLE_ENTRIES - 1)) throw std::range_error("Not found: Given PS2MemoryAddress's VPN exceeds the number of pages indexable. Check input or you may need to increase the page table size.");
	u32 offset = getOffset(PS2MemoryAddress);

	// Lookup the page in the page table to get the client base memory address (aka page frame number (PFN)).
	// If the client memory address base comes back as nullptr (= 0), throw a runtime exception.
	// C++11 does not allow any aritmetic to be done on pointers. Need to cast to uintptr_t first (defined in <cstdint>) then cast back.
	void* clientMemoryAddressBase = (*pageTable)[vpn];
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

s8 MMUHandler::readByteS(s32 PS2MemoryAddress) const
{
	// Get client base address.
	s8 * clientMemoryAddress = reinterpret_cast<s8*>(getclientMemoryAddress(PS2MemoryAddress));

	// Read the value.
	return *clientMemoryAddress;
}

void MMUHandler::writeByteS(s32 PS2MemoryAddress, s8 value) const
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

s16 MMUHandler::readHwordS(s32 PS2MemoryAddress) const
{
	// Get client base address.
	s16 * clientMemoryAddress = reinterpret_cast<s16*>(getclientMemoryAddress(PS2MemoryAddress));

	// Read the value.
	return *clientMemoryAddress;
}

void MMUHandler::writeHwordS(s32 PS2MemoryAddress, s16 value) const
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

s32 MMUHandler::readWordS(s32 PS2MemoryAddress) const
{
	// Get client base address.
	s32 * clientMemoryAddress = reinterpret_cast<s32*>(getclientMemoryAddress(PS2MemoryAddress));

	// Read the value.
	return *clientMemoryAddress;
}

void MMUHandler::writeWordS(s32 PS2MemoryAddress, s32 value) const
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

s64 MMUHandler::readDwordS(s32 PS2MemoryAddress) const
{
	// Get client base address.
	s64 * clientMemoryAddress = reinterpret_cast<s64*>(getclientMemoryAddress(PS2MemoryAddress));

	// Read the value.
	return *clientMemoryAddress;
}

void MMUHandler::writeDwordS(s32 PS2MemoryAddress, s64 value) const
{
	// Get client base address.
	s64 * clientMemoryAddress = reinterpret_cast<s64*>(getclientMemoryAddress(PS2MemoryAddress));

	// Write the value.
	*clientMemoryAddress = value;
}
