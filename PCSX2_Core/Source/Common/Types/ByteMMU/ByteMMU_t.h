#pragma once

#include <memory>
#include <vector>

#include "Common/Global/Globals.h"
#include "Common/Types/System_t.h"

class MapperBaseObjectByteMMU_t;
class ByteMemory_t;
class Register8_t;
class Register16_t;
class Register32_t;
class Register64_t;
class Register128_t;
class FIFOQueue32_t;

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
class ByteMMU_t
{
public:
	explicit ByteMMU_t(const int numAddressBits, const int numPageIndexBits, const int numOffsetIndexBits);

	/*
	Maps the given object into the PS2 physical address space, provided it inherits the MapperBaseObjectByteMMU_t interface.
	Once this has been executed sucesfully, you will be able to use the read and write functions below to read/write to the PS2 physical addresses defined in the object.
	Once the correct object has been retreived, a call will be made to the same function of that object.

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
	void mapObject(const u32 physicalAddress, const std::shared_ptr<FIFOQueue32_t> & fifoQueue32);

	/*
	These functions, given a PS2 physical address, will read or write a value from/to the address.
	The address is automatically translated to the allocated memory object, which passes on the read/write call to it.
	You cannot use these functions before an object has been mapped to the parsed address - a runtime_error will be thrown otherwise.
	*/
	u8 readByte(const System_t context, u32 physicalAddress);
	void writeByte(const System_t context, u32 physicalAddress, u8 value);
	u16 readHword(const System_t context, u32 physicalAddress);
	void writeHword(const System_t context, u32 physicalAddress, u16 value);
	u32 readWord(const System_t context, u32 physicalAddress);
	void writeWord(const System_t context, u32 physicalAddress, u32 value);
	u64 readDword(const System_t context, u32 physicalAddress);
	void writeDword(const System_t context, u32 physicalAddress, u64 value);
	u128 readQword(const System_t context, u32 physicalAddress);
	void writeQword(const System_t context, u32 physicalAddress, u128 value);

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
	The page table which holds all of the page table entries, mapping the addresses.
	The directories are kept in this, which point to individual pages.
	The individual pages are only allocated on access, thereby saving memory.
	(An array of directories, each directory pointing to an mComponents of pages, each page pointing to some memory.)
	*/
	std::vector<std::vector<std::shared_ptr<MapperBaseObjectByteMMU_t>>> mPageTable;

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
};
