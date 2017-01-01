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
	*/
	virtual u8 readByte(u32 storageIndex) = 0;
	virtual void writeByte(u32 storageIndex, u8 value) = 0;
	virtual u16 readHword(u32 storageIndex) = 0;
	virtual void writeHword(u32 storageIndex, u16 value) = 0;
	virtual u32 readWord(u32 storageIndex) = 0;
	virtual void writeWord(u32 storageIndex, u32 value) = 0;
	virtual u64 readDword(u32 storageIndex) = 0;
	virtual void writeDword(u32 storageIndex, u64 value) = 0;
	virtual u128 readQword(u32 storageIndex) = 0;
	virtual void writeQword(u32 storageIndex, u128 value) = 0;

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