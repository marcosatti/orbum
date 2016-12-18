#pragma once

#include <string>

#include "Common/Global/Globals.h"

/*
Abstract base class for mapped storage in PhysicalMMU_t.
At the minimum, an implementing class needs to provide a way for read and write functions, the size, and a PS2 physical address for where it should be mapped from.
See MappedRegister32_t and MappedMemory_t for examples of implementing classes.

The read write functions expect the index to be a byte index (offset), not a size-specific index.
*/

class PhysicalMapped
{
public:
	explicit PhysicalMapped(const u32 & physicalAddress);
	virtual ~PhysicalMapped();

	/*
	Read or write a value of a given type, to the specified byte index (storageIndex).
	Only the unsigned type is provided for the Qword read/write. 
	The PS2 never operates directly on 128-bit values, so a signed version is meaningless.
	*/
	virtual u8 readByteU(u32 storageIndex) = 0;
	virtual void writeByteU(u32 storageIndex, u8 value) = 0;
	virtual s8 readByteS(u32 storageIndex) = 0;
	virtual void writeByteS(u32 storageIndex, s8 value) = 0;
	virtual u16 readHwordU(u32 storageIndex) = 0;
	virtual void writeHwordU(u32 storageIndex, u16 value) = 0;
	virtual s16 readHwordS(u32 storageIndex) = 0;
	virtual void writeHwordS(u32 storageIndex, s16 value) = 0;
	virtual u32 readWordU(u32 storageIndex) = 0;
	virtual void writeWordU(u32 storageIndex, u32 value) = 0;
	virtual s32 readWordS(u32 storageIndex) = 0;
	virtual void writeWordS(u32 storageIndex, s32 value) = 0;
	virtual u64 readDwordU(u32 storageIndex) = 0;
	virtual void writeDwordU(u32 storageIndex, u64 value) = 0;
	virtual s64 readDwordS(u32 storageIndex) = 0;
	virtual void writeDwordS(u32 storageIndex, s64 value) = 0;
	virtual u128 readQwordU(u32 storageIndex) = 0;
	virtual void writeQwordU(u32 storageIndex, u128 value) = 0;

	/*
	Gets the base PS2 physical address the mapping starts from.
	*/
	const u32 & getMappedPhysicalAddress() const;

	/*
	Gets the length of the mapping.
	*/
	virtual size_t getSize() = 0;

	/*
	Get the map mnemonic, used for debug.
	*/
	virtual const char * getMnemonic() const = 0;

	/*
	Get/set mAbsMappedPageIndex, which are used by the Physical MMU for calculating an offset.
	*/
	u32 getAbsMappedPageIndex() const;
	void setAbsMappedPageIndex(u32 absPageIndex);

private:
	/*
	The physical address this mapping starts from.
	*/
	u32 mPhysicalAddress;

	/*
	mAbsMappedPageIndex is set by the Physical MMU when mapped. This provides a way for the storage object / VM TLB to determine what byte it should start accessing the array from.
	See the Physical MMU -> read/write functions to see how this is calculated. In essence, it is the base page number that it was assigned, which can be used to calulate a storage array index.
	*/
	u32 mAbsMappedPageIndex;
};