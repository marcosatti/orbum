#pragma once

#include <memory>

#include "Common/Global/Globals.h"

/*
PhysicalMMU_t is responsible for converting the PS2's physical memory into host memory.
The mapping method is actually just a 2 level (directory and pages) page table! 
It supports remapping up to 4GB only, due to the use of 32-bit value addresses.

This means that for each separate physical memory space in the PS2, there are 2 "MMU's":
- One will be a MMU for translating a given PS2 virtual address into a PS2 physical address.
- The other (this one) is for translating a given PS2 physical address into a host address (aka MappedMemory_t).

By using this, it is up to the user to make sure no addresses overlap - they will be overwritten and existing map data lost.

It will throw different runtime errors when the following conditions occur:
- range_error exception if more than PAGE_TABLE_MAX_SIZE in the page tableis accessed.
- runtime_error exception if the returned PFN from the page table was null (indicates invalid entry, needs to be mapped first).

* Why is an MemoryMapped_t object used instead of a raw pointer to a block of memory?
Some memory regions of the PS2 require special attributes - such as the reserved regions of the EE registers. When writing to these regions, the write is disregarded. 
When a read is performed, an indeterminate value is returned (0 for some registers due to undocumented behaviour).
By using this class, we can override the read and writes performed very easily.

* Why is two levels used instead of one?
Some mapped storage such as the EE registers are separated only by 16 bytes. This means that in order to support every register, the page size would have to be 16B. 
This creates a sort of wasteful memory problem, as we would need to have 4GB / 16B = 268,435,456 page table entries (pointers).
At 8 bytes a pointer (running in 64-bit mode), we would use up 2GB of memory, just for pointers! Even with todays PC's, this is very bad.
Instead, if we use a two level structure with for example a directory size of 4MB, we only allocate pointers for the directories used.
For the directory table, we require 4GB / 4MB = 1,024 directories, and 1,024 * 8B = 8KB of memory.
For a single directory, we require 4M * 8B = 32MB of memory for pointers. Still not ideal, but certainly not nearly as bad. 
However, this works well with the EE physical map, where registers are often clumped together. This means that typically only a handful of directories are created.
The advantage of keeping a page size of 16B is we have more fine grained control of memory, rather than having to allocate a big block of memory.

* Example of how constructor parameters effects addresses.
By using a directory size of 4MB and a page size of 16B, with a 512 MB max address range:
 - Number of directory entries = 512MB / 4MB = 128. Therefore 7 bits are needed to represent the virtual directory number (0 -> 127).
 - Number of page table entries per directory = 4MB / 16B = 262,144. Therefore 18 bits are needed to represent the virtual page number (0 -> 262,143).
 - The offset (within 16B) requires 4 bits.
 - Total number of bits required = 29, which is correct for addressing 512MB. This is done within a 32-bit integer type (upper bits unused / will throw error).
 =============================================================================================
 | 31                         29 | 28            22 | 21                       4  | 3      0 |
 | (throws error if any bit set) | VIRTUAL DIR. NUM |     VIRTUAL PAGE NUMBER     |  OFFSET  |
 =============================================================================================
 */

class PhysicalMapped;

class PhysicalMMU_t
{
public:
	explicit PhysicalMMU_t(const size_t & maxAddressableSizeBytes, const u32 & directorySizeBytes, const u32 & pageSizeBytes);
	~PhysicalMMU_t();

	/*
	Maps the given memory object into the PS2 physical address space.
	Once this has been executed sucesfully, you will be able to use the read and write functions below to read/write to the PS2 physical addresses defined in the object.
	Once the correct object has been retreived, a call will be made to the same function of that object.

	Note that this function simply remaps the memory in a linear fashion, meaning that for example, a PS2 physical address of 0x00000400 - 0x00000600 will map directly to (example mapping) 0x1234A000 - 0x1234A200
	*/
	void mapMemory(const std::shared_ptr<PhysicalMapped> & mappedMemory);

	/*
	These functions, given a PS2 physical address, will read or write a value from/to the address.
	The address is automatically translated to the allocated memory object, which passes on the read/write call to it.
	You cannot use these functions before mapMemory() has been called - it will return an runtime_error exception otherwise.
	The functions have the syntax "{read or write}{type}{[U]nsigned or [S]igned}()".
	Unfortunately C++ does not allow templating of virtual functions defined in the parent class, so a read/write for each type has to be made.
	*/
	u8 readByteU(u32 PS2PhysicalAddress) const;
	void writeByteU(u32 PS2PhysicalAddress, u8 value) const;
	s8 readByteS(u32 PS2PhysicalAddress) const;
	void writeByteS(u32 PS2PhysicalAddress, s8 value) const;
	u16 readHwordU(u32 PS2PhysicalAddress) const;
	void writeHwordU(u32 PS2PhysicalAddress, u16 value) const;
	s16 readHwordS(u32 PS2PhysicalAddress) const;
	void writeHwordS(u32 PS2PhysicalAddress, s16 value) const;
	u32 readWordU(u32 PS2PhysicalAddress) const;
	void writeWordU(u32 PS2PhysicalAddress, u32 value) const;
	s32 readWordS(u32 PS2PhysicalAddress) const;
	void writeWordS(u32 PS2PhysicalAddress, s32 value) const;
	u64 readDwordU(u32 PS2PhysicalAddress) const;
	void writeDwordU(u32 PS2PhysicalAddress, u64 value) const;
	s64 readDwordS(u32 PS2PhysicalAddress) const;
	void writeDwordS(u32 PS2PhysicalAddress, s64 value) const;

private:
	/*
	Internal parameters calculated in the constructor.
	*/
	const size_t MAX_ADDRESSABLE_SIZE_BYTES; // Needs to be of type size_t as 4GB (which is the max supported size) does not fit into u32.
	const u32 DIRECTORY_SIZE_BYTES;
	const u32 PAGE_SIZE_BYTES;
	const u32 DIRECTORY_ENTRIES;
	const u32 PAGE_ENTRIES;
	const u32 OFFSET_BITS;
	const u32 OFFSET_MASK;
	const u32 DIRECTORY_BITS;
	const u32 DIRECTORY_MASK;
	const u32 PAGE_BITS;
	const u32 PAGE_MASK;

	/*
	The page table which holds all of the page table entries, mapping the addresses.
	The directories are kept in this, which point to individual pages.
	The individual pages are only allocated on access, thereby saving memory.
	(An array of directories, each directory pointing to an mComponents of pages, each page pointing to some memory.)
	*/
	std::shared_ptr<PhysicalMapped>** mPageTable;

	/*
	Translates the given PS2 physical address to the stored memory object by using the page table. The returned object can then be used to read or write to an address.
	*/
	std::shared_ptr<PhysicalMapped> & getMappedMemory(u32 baseVDN, u32 baseVPN) const;

	/*
	Helper functions for mapMemory & others to 
	 - Determine which directory a page belongs to (if they were layed out end to end).
	 - The page offset in a directory.
	 - The absolute page (if they were layed out end to end).
	 - Allocate a new directory of pages if it doesnt exist.
	*/
	u32 getDirectoryFromPageOffset(u32 absPageIndexStart, u32 pageOffset) const;
	u32 getDirPageFromPageOffset(u32 absPageIndexStart, u32 pageOffset) const;
	u32 getAbsPageFromDirAndPageOffset(u32 absDirectoryIndex, u32 pageOffset) const;
	void allocDirectory(u32 directoryIndex) const;

	/*
	Gets the VDN (virtual directory number) from a given PS2 physical address.
	*/
	u32 getVDN(u32 PS2MemoryAddress) const;

	/*
	Gets the VPN (virtual page number) from a given PS2 physical address.
	*/
	u32 getVPN(u32 PS2MemoryAddress) const;

	/*
	Gets the offset from a given PS2 physical address.
	*/
	u32 getOffset(u32 PS2MemoryAddress) const;
};
