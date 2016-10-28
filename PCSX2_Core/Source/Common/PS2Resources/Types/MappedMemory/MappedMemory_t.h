#pragma once

#include <string>

#include "Common/Global/Globals.h"

/*
A simple storage object which is constructed to the size specified, and optional name (mnemonic) which is used for debugging/logging.
Also defines a PS2 Physical address that it starts from - used by the Physical MMU to map for address translation.

The primary difference between a MappedMemory type and a Register type is that storage objects are accessed by the byte index, not by the size index.
For example, a writeWordU(0, value) will write to the first 0-31 bits, while writeWordU(1, value) will write to bits 8-39 (ie: it will overwrite).
See the Register type for the counter-example.
*/
class MappedMemory_t
{
public:
	explicit MappedMemory_t(const size_t & size, const char *const mnemonic, const u32 & PS2PhysicalAddress);
	virtual ~MappedMemory_t();

	/*
	Read or write a value of a given type, to the specified byte index (storageIndex).
	*/
	virtual u8 readByteU(u32 storageIndex);
	virtual void writeByteU(u32 storageIndex, u8 value);
	virtual s8 readByteS(u32 storageIndex);
	virtual void writeByteS(u32 storageIndex, s8 value);
	virtual u16 readHwordU(u32 storageIndex);
	virtual void writeHwordU(u32 storageIndex, u16 value);
	virtual s16 readHwordS(u32 storageIndex);
	virtual void writeHwordS(u32 storageIndex, s16 value);
	virtual u32 readWordU(u32 storageIndex);
	virtual void writeWordU(u32 storageIndex, u32 value);
	virtual s32 readWordS(u32 storageIndex);
	virtual void writeWordS(u32 storageIndex, s32 value);
	virtual u64 readDwordU(u32 storageIndex);
	virtual void writeDwordU(u32 storageIndex, u64 value);
	virtual s64 readDwordS(u32 storageIndex);
	virtual void writeDwordS(u32 storageIndex, s64 value);

	/*
	Gets the storage length, needed by the Physical MMU handler in order to map it.
	*/
	virtual size_t getStorageSize();

	/*
	Gets the base host memory address, needed for special VM functions such as loading the BIOS (BootROM). Not normally used, and should never
	 be used in favour of the above read/write functions unless you absolutely have to.
	*/
	virtual void * getHostMemoryAddress() const;

	/*
	Get the storage mnemonic, used for debug.
	*/
	virtual const char * getMnemonic() const;

	/*
	Gets the PS2 physical address this storage object was assigned at creation.
	*/
	virtual const u32 & getPS2PhysicalAddress() const;

	/*
	Get/set mAbsMappedPageIndex, which are used by the Physical MMU for calculating an offset.
	*/
	u32 getAbsMappedPageIndex() const;
	void setAbsMappedPageIndex(u32 absPageIndex);

private:
	/*
	mAbsMappedPageIndex is set by the Physical MMU when mapped. This provides a way for the storage object / VM TLB to determine what byte it should start accessing the array from.
	See the Physical MMU -> read/write functions to see how this is calculated. In essence, it is the base page number that it was assigned, which can be used to calulate a storage array index.
	*/
	u32 mAbsMappedPageIndex;

	size_t mStorageSize;
	u8 *const mStorage;
	const std::string mMnemonic;
	const u32 mPS2PhysicalAddress;
};

