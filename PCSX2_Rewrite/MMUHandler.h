#pragma once

#include <memory>

#include "Globals.h"
#include "VMMMUComponent.h"

/*
The VM MMU component is responsible for converting the PS2's physical addresses into client virtual addresses (which is required to properly run a program on the client system).
The remapping method is actually just another page table... but sort of in reverse!
This means that in the emulator, there are 2 page tables:
- One will be a page table for mapping PS2 virtual addresses into PS2 physical addresses (implmented as sub components in the Interpreter & Recompliler).
- The other (this one) is a page table for mapping PS2 physical addresses into x86 virtual addresses.

The page table is implemented with a page size of 4KB. Since the PS2 has an effective physical address space of 512MB (see EE Users Manual page 20 and the note below about the Extended memory and NO MOUNT area),
this equates to 512MB / 4KB = 131,072 page table entries (and assuming that we are using a 64-bit x86 address space, the table occupies 131,072 * 8 bytes = 1MB of memory; not much).

According to the PS2 docs mentioned above, the PS2's physical address space is as follows:

0x00000000 - 0x0FFFFFFF 256MB main memory (of which I assume 32MB is accessable from 0x00000000 onwards and the other space has undefined behaviour?).
0x10000000 - 0x11FFFFFF EE Registers.
0x12000000 - 0x13FFFFFF GS Registers.
0x14000000 - 0x1FBFFFFF Reserved (undefined behaviour).
0x1FC00000 - 0x1FFFFFFF Boot rom area (max 4MB).
0x20000000 - 0xFFFFFFFF Extended memory and NO MOUNT (but there is no extended memory in the PS2, so it is undefined and hence not mapped or used).

Assuming the PS2 never tries to access the extended memory or the NO MOUNT area, this will work.

By using a 4KB page size with a 512MB remap space, 12 bits are used as an offset, and 17 bits are used as the page number (for a total of 29 bits).
The least sized unit this fits into is still 32-bits however.

By using this, it is up to the user to make sure no addresses overlap - they will be overwritten and existing data lost.

It will throw different runtime errors when the following conditions occur:
 - range_error exception if more than PAGE_TABLE_MAX_SIZE in the page tableis accessed.
 - runtime_error exception if the returned PFN from the page table was null (indicates invalid entry).
 */
class MMUHandler : public VMMMUComponent
{
public:
	static constexpr u32 PAGE_SIZE = 4096;
	static constexpr u32 PAGE_BITS = 12;
	static constexpr u32 PAGE_MASK = PAGE_SIZE - 1;
	static constexpr u32 PAGE_TABLE_MAX_SIZE = Constants::SIZE_512MB;
	static constexpr u32 PAGE_TABLE_ENTRIES =  PAGE_TABLE_MAX_SIZE/ PAGE_SIZE;

	MMUHandler(const VMMain *const vmMain);
	~MMUHandler();

	/*
	Maps the given client virtual memory address and length to a given PS2 "physical" address.
	Once this has been executed sucesfully, you will be able to read and write to the PS2 physical address, which will automatically tranlate it to the correct client virtual memory address.
	The functions to read and write are "{read or write}{type}{[U]nsigned or [S]igned}()" (listed below).

	Note that this function simply remaps the memory in a linear fashion, meaning that for example, a PS2 physical address of 0x00000400 - 0x00000600 will map directly to (example mapping) 0x1234A000 - 0x1234A200

	clientMemoryAddress = Base address of memory to map (ie: parse the base address of a block of memory allocated in code).
	clientMemoryLength = Length of memory parsed into clientMemoryAddress. This will be used to divide the map into pages.
	PS2MemoryAddress = The PS2 "physical" address which will be mapped.
	*/
	void mapMemory(void* clientMemoryAddress, u32 clientMemoryLength, u32 PS2MemoryAddress) const;

	/*
	These functions, given a PS2 "physical" address, will read or write a value from/to the address.
	The address is automatically translated into the correct address through the page table.
	You cannot use these functions before mapMemory() has been called - it will return an runtime_error exception otherwise.
	The functions have the syntax "{read or write}{type}{[U]nsigned or [S]igned}()".
	*/
	u8 readByteU(u32 PS2MemoryAddress) const;
	void writeByteU(u32 PS2MemoryAddress, u8 value) const;
	s8 readByteS(s32 PS2MemoryAddress) const;
	void writeByteS(s32 PS2MemoryAddress, s8 value) const;
	u16 readHwordU(u32 PS2MemoryAddress) const;
	void writeHwordU(u32 PS2MemoryAddress, u16 value) const;
	s16 readHwordS(s32 PS2MemoryAddress) const;
	void writeHwordS(s32 PS2MemoryAddress, s16 value) const;
	u32 readWordU(u32 PS2MemoryAddress) const;
	void writeWordU(u32 PS2MemoryAddress, u32 value) const;
	s32 readWordS(s32 PS2MemoryAddress) const;
	void writeWordS(s32 PS2MemoryAddress, s32 value) const;
	u64 readDwordU(u32 PS2MemoryAddress) const;
	void writeDwordU(u32 PS2MemoryAddress, u64 value) const;
	s64 readDwordS(s32 PS2MemoryAddress) const;
	void writeDwordS(s32 PS2MemoryAddress, s64 value) const;

private:
	/*
	The page table which holds all of the page table entries, mapping the addresses.
	*/
	const std::unique_ptr<void**> pageTable; // Allocate new array of pointers (double pointer variable). Remember, a pointer on x86 is 8 bytes in 64 bit mode, and so will take up 8 * PAGE_TABLE_SIZE bytes.

	/*
	Gets the VPN from a given PS2 physical address.
	*/
	static u32 getVPN(u32 PS2MemoryAddress);

	/*
	Gets the offset from a given PS2 physical address.
	*/
	static u32 getOffset(u32 PS2MemoryAddress);

	/*
	Translates the given PS2 physical address to the client memory address by using the page table.
	*/
	void* getclientMemoryAddress(u32 PS2MemoryAddress) const;
};
