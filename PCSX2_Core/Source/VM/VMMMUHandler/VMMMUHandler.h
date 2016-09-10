#pragma once

#include <memory>

#include "Common/Global/Globals.h"

class VMMain;
class VMMMUMappedStorageObject;
class StorageObject_t;

/*
The VM MMU component is responsible for converting the PS2's physical addresses into client storage objects (which is required to properly run a program on the client system).
The remapping method is actually just a page table... but sort of in reverse (PS2 "physical" -> client)!
This means that in the emulator, there are 2 page tables:
- One will be a page table for mapping PS2 virtual addresses into PS2 physical addresses (implmented as MMU sub components in the Interpreter & Recompliler).
- The other (this one) is a page table for mapping PS2 physical addresses into x86 virtual addresses. It is labeled the VM MMU to avoid confusion with the PS2 MMU.

The page table is implemented as a 2 level system with a primary "directory" size of 4,194,304B (4MB addressing chunks) and a secondary "page" size of 16B. 
 2 Levels are used to reduce memory usage by only allocating the page tables within a directory that are needed.

The reason that 16B is used on the second levels due to the physical memory map of the EE & GS registers (timers, vu's, dmac, etc, starting on page 21 of the EE Users Manual). 
 Each register is (at minimum) aligned on a 16B boundary, and we need to reflect this. If a larger page size was used (say 4KB which is a normal value), then we would need
 to somehow make sure that each offset within a page which is a multiple of 16 pointed to a different client storage object - but this is a problem because the physical 
 frame number only points to 1 object. Therefore for now we need to make the page size 16B until a better solution comes along.
This also means that a runtime error will happen if there is a read or write after the edge of the object.

The old PCSX2 code seems to align all of the registers continuously, so that the client memory exactly reflects the PS2's physical memory map... This works but has the side effect
 of not being able to change the order of the registers memory, which is a dangerous thing as a compiler might break this, as well as making it harder to read.

According to the PS2 docs mentioned above, the PS2's physical address space is as follows:

0x00000000 - 0x0FFFFFFF 256MB main memory (of which I assume 32MB is accessable from 0x00000000 onwards and the other space raises a bus error?).
0x10000000 - 0x11FFFFFF EE Registers (timers, vu's, dmac, etc).
0x12000000 - 0x13FFFFFF GS Registers.
0x14000000 - 0x1FBFFFFF Reserved (undefined behaviour).
0x1FC00000 - 0x1FFFFFFF Boot rom area (max 4MB).
0x20000000 - 0xFFFFFFFF Extended memory and NO MOUNT (but there is no extended memory in the PS2, so it is undefined and hence not mapped or used).

We can leave out the extended memory and NO MOUNT region from the page table, as these are never used and there is no utilised memory onwards from them.
Therefore, we can limit the map to 512MB (0x00000000 - 0x1FFFFFFF).

By using a directory size of 4MB and a page size of 16B:
 - Number of directory entries = 512MB / 4MB = 128. Therefore 7 bits are needed to represent the virtual directory number (0 -> 127).
 - Number of page table entries per directory = 4MB / 16B = 262,144. Therefore 18 bits are needed to represent the virtual page number (0 -> 262,143).
 - The offset (within 16B) requires 4 bits.
 - Total number of bits required = 29, which is correct for addressing 512MB. This is done within a 32-bit integer type (upper bits unused).
 =============================================================
 | 28            23 | 22                       5  | 4      0 |
 | VIRTUAL DIR. NUM |     VIRTUAL PAGE NUMBER     |  OFFSET  |
 =============================================================

By using this, it is up to the user to make sure no addresses overlap - they will be overwritten and existing map data lost.

It will throw different runtime errors when the following conditions occur:
 - range_error exception if more than PAGE_TABLE_MAX_SIZE in the page tableis accessed.
 - runtime_error exception if the returned PFN from the page table was null (indicates invalid entry, needs to be mapped first).

 Why is an object used instead of a raw pointer to a block of memory?
 Some memory regions of the PS2 require special attributes - such as the reserved regions of the EE registers. When writing to these regions,
  the write is disregarded. When a read is performed, an indeterminate value is returned (0 for some registers due to undocumented behaviour).

TODO: Reduce memory footprint from 256MB (see note above).
 */
class VMMMUHandler
{
public:
	explicit VMMMUHandler(const VMMain *const vmMain);
	~VMMMUHandler();

	/*
	Maps the given client virtual memory address and length to a given PS2 "physical" address.
	Once this has been executed sucesfully, you will be able to read and write to the PS2 physical address, which will automatically tranlate it to the correct client memory object.
	The functions to read and write are "{read or write}{type}{[U]nsigned or [S]igned}()" (listed below). Once the correct object has been retreived, a call will be made to the same function of that object.

	Note that this function simply remaps the memory in a linear fashion, meaning that for example, a PS2 physical address of 0x00000400 - 0x00000600 will map directly to (example mapping) 0x1234A000 - 0x1234A200

	clientStorage = An object which implements the VMMMUMappedStorageObject interface.
	PS2PhysicalAddress = The PS2 "physical" address which will be mapped.
	*/
	void mapMemory(const std::shared_ptr<VMMMUMappedStorageObject> & clientStorage, const u32 & PS2MemoryAddress);
	void mapMemory(const std::shared_ptr<StorageObject_t> & clientStorage);

	/*
	These functions, given a PS2 "physical" address, will read or write a value from/to the address.
	The address is automatically translated into the correct address through the page table.
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
	Page Table parameters.
	*/
	static constexpr u32 TABLE_MAX_ADDRESSABLE_SIZE_BYTES = Constants::SIZE_512MB;
	static constexpr u32 DIRECTORY_SIZE_BYTES = Constants::SIZE_4MB;
	static constexpr u32 PAGE_SIZE_BYTES = Constants::SIZE_16B;

	/*
	Internal parameters calculated in the constructor from the above page table parameters.
	Do not change this order - this is to do with how the C++ initalisation list order works (it is defined in the language standard).
	*/
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
	(A pointer to an array of directories, each directory pointing to an array of pages, each page pointing to some memory.)
	*/
	std::shared_ptr<VMMMUMappedStorageObject>** mPageTable;

	/*
	Translates the given PS2 physical address to the stored client object by using the page table. The returned object can then be used to read or write to an address.
	*/
	std::shared_ptr<VMMMUMappedStorageObject> & getClientStorageObject(u32 baseVDN, u32 baseVPN) const;

	/*
	Helper functions for mapMemory & others to 
	 - Determine which directory a page belongs to (if they were layed out end to end), and;
	 - The page offset in a directory.
	 - The absolute page (if they were layed out end to end).
	 - Allocate a new directory of pages if it doesnt exist.
	*/
	u32 getAbsDirectoryFromPageOffset(u32 absPageIndexStart, u32 pageOffset) const;
	u32 getAbsDirPageFromPageOffset(u32 absPageIndexStart, u32 pageOffset) const;
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
