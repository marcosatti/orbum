#pragma once

#include "Common/Global/Globals.h"

/*
Interface class used for exposing storage, so it can be used in mapping (through the VM MMU).
This object and any subobjects are to be idealised as an array of bytes, which can be accessed by array[getStorageIndex()].
*/

class VMMMUMappedStorageObject
{
public:
	explicit VMMMUMappedStorageObject();

	virtual ~VMMMUMappedStorageObject();

	/*
	Read or write to an arbitrary storage object (memory, disk storage etc), as an array of bytes. Each access can be thought of as storage[storageIndex] (of type u8).
	Unfortunately C++ does not allow templated virtual functions... So we have to implement each possible case.
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

	/*
	Gets the client storage size.
	*/
	virtual size_t getStorageSize() = 0;

	/*
	Get/set mAbsMappedPageIndex, which are used by the VM MMU for calculating an offset.
	*/
	u32 getAbsMappedPageIndex() const;
	void setAbsMappedPageIndex(u32 absPageIndex);

private:
	/*
	mAbsMappedPageIndex is set by the VM MMU when mapped. This provides a way for the storage object / VM MMU to determine what byte it should start accessing the array from.
	See the VM MMU -> read/write functions to see how this is calculated. In essence, it is the base page number that it was assigned, which can be used to calulate a storage array index.
	*/
	u32 mAbsMappedPageIndex;
};