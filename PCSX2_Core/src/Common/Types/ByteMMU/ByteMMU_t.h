#pragma once

#include <memory>
#include <vector>

#include "Common/Global/Globals.h"
#include "Common/Types/System/Context_t.h"

class MapperBaseObjectByteMMU_t;
class ByteMemory_t;
class Register8_t;
class Register16_t;
class Register32_t;
class Register64_t;
class Register128_t;
class FIFOQueue_t;
class FIFOQueue_t;

/*
ByteMMU_t is responsible for converting the PS2's physical memory into host memory.
It is byte-addressable, and can map up to 4GB (full 32-bit space).
The mapping method is actually just a 2 level (directory and pages) page table!

* Why is an MapperBaseObjectByteMMU_t object used instead of a raw pointer to a block of memory?
Some memory regions of the PS2 require special attributes - such as the reserved regions of the EE registers. When writing to these regions, the write is disregarded.
When a read is performed, an indeterminate value is returned (0 for some registers due to undocumented behaviour).
By using this class, we can override the read and writes performed very easily.

* Why is two levels used instead of one?
Some mapped storage such as the EE registers are separated only by 16 bytes. This means that in order to support every register, the page size would have to be 16B.
This creates a sort of wasteful memory problem, as we would need to have 4GB / 16B = 268,435,456 page table entries (pointers).
At 8 bytes a pointer (running in 64-bit mode), we would use up 2GB of memory, just for pointers! This is wasteful.
Instead, if we use a two level structure with for example a directory size of 4MB, we only allocate pointers for the directories used.
For the directory table, we require 4GB / 4MB = 1,024 directories, and 1,024 * 8B = 8KB of memory.
For a single directory, we require 4M * 8B = 32MB of memory for pointers. Still not ideal, but certainly not as bad.
However, this works well with the EE physical map, where registers are often clumped together. This means that typically only a handful of directories are created.
The advantage of keeping a page size of 16B is we have more fine grained control of memory, rather than having to allocate a big block of memory.

* Example of how constructor parameters affects address access.
By using ByteMMU_t(29, 18, 4) as an example: 
 - 29 bits for the address space. This corresponds to 512 MB total space.
 - 4 bits for the offset, ie: 16 bytes.
 - 18 bits for the page index, ie: 262,144 pages per directory, each representing 16 B.
 - (29 - 18 - 4) = 7 bits for the directory index, ie: 128 directories, each representing 4 MB.
=============================================================================================
| 31                         29 | 28            22 | 21                       4  | 3      0 |
| (undef. behaviour when set. ) | VIRTUAL DIR. NUM |     VIRTUAL PAGE NUMBER     |  OFFSET  |
=============================================================================================
*/
class ByteMMU_t
{
public:
	ByteMMU_t(const int numAddressBits, const int numPageIndexBits, const int numOffsetIndexBits);

	/*
	Maps the given object into the PS2 physical address space, provided it inherits the MapperBaseObjectByteMMU_t interface.
	Once this has been executed successfully, you will be able to use the read and write functions below to read/write to the PS2 physical addresses defined in the object.
	Once the correct object has been retrieved, a call will be made to the same function of that object.

	Note that this function simply remaps the memory in a linear fashion, meaning that for example, a PS2 physical address of 0x00000400 - 0x00000600 will map directly to 0x1234A000 - 0x1234A200.
	
	Convenience mapping functions have been provided that maps the object with the appropriate wrapper class (makes it compatible with the MapperBaseObjectByteMMU_t interface).
	*/
	void mapObject(const std::shared_ptr<MapperBaseObjectByteMMU_t> & mapperObject);
	void mapObject(const u32 physicalAddress, const std::shared_ptr<ByteMemory_t> & memory);
	void mapObject(const u32 physicalAddress, const std::shared_ptr<Register8_t> & register8);
	void mapObject(const u32 physicalAddress, const std::shared_ptr<Register16_t> & register16);
	void mapObject(const u32 physicalAddress, const std::shared_ptr<Register32_t> & register32);
	void mapObject(const u32 physicalAddress, const std::shared_ptr<Register64_t> & register64);
	void mapObject(const u32 physicalAddress, const std::shared_ptr<Register128_t> & register128);
	void mapObject(const u32 physicalAddress, const std::shared_ptr<FIFOQueue_t> & fifoQueue);

	/*
	These functions, given a PS2 physical address, will read or write a value from/to the address.
	The address is automatically translated to the allocated memory object, which passes on the read/write call to it.
	No error checking is done as these functions are performance critical. If you try to access an invalid mapping, it will probably crash.
	*/
	u8 readByte(const Context_t context, const u32 physicalAddress);
	void writeByte(const Context_t context, const u32 physicalAddress, const u8 value);
	u16 readHword(const Context_t context, const u32 physicalAddress);
	void writeHword(const Context_t context, const u32 physicalAddress, const u16 value);
	u32 readWord(const Context_t context, const u32 physicalAddress);
	void writeWord(const Context_t context, const u32 physicalAddress, const u32 value);
	u64 readDword(const Context_t context, const u32 physicalAddress);
	void writeDword(const Context_t context, const u32 physicalAddress, const u64 value);
	u128 readQword(const Context_t context, const u32 physicalAddress);
	void writeQword(const Context_t context, const u32 physicalAddress, const u128 value);

private:
	/*
	Internal parameters calculated in the constructor, related to:
	 - The number of bits the directories, pages and offsets occupy.
	 - The mask's for extracting these parts.
	 - The number of entries for each part.
	*/
	int    mNumAddressBits;
	int    mNumDirectoryIndexBits;
	int    mNumPageIndexBits;
	int    mNumOffsetIndexBits;
	u32    mDirectoryIndexMask;
	u32    mPageIndexMask;
	u32    mOffsetIndexMask;
	size_t mNumDirectories;
	size_t mNumPagesPerDirectory;
	size_t mNumOffsetsPerPage;

	/*
	Returns the VDN (virtual directory number/index), VPN (virtual page number/index) and offset properties from a given virtual address, using this MMU context.
	*/
	struct VAddressProperties_t
	{
		size_t mVDN;
		size_t mVPN;
		size_t mOffset;
	};
	VAddressProperties_t getVAddressProperties(u32 address) const;

	/*
	The page table which holds all of the page table entries, mapping the addresses.
	The directories are kept in this, which point to individual pages.
	The individual pages are only allocated on access, thereby saving memory.
	(An array of directories, each directory pointing to an mComponents of pages, each page pointing to some memory.)
	*/
	std::vector<std::vector<std::shared_ptr<MapperBaseObjectByteMMU_t>>> mPageTable;

	/*
	Given the address properties, performs a lookup in the page table and returns the mapped object.
	On a nullptr object being retrieved, a runtime_error is thrown (debug builds only).
	*/
	const std::shared_ptr<MapperBaseObjectByteMMU_t> & getMappedObject(const Context_t context, const VAddressProperties_t & properties);
};
