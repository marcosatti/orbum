#pragma once

#include <string>

#include "Common/Global/Globals.h"

/*
A simple storage object which is constructed to the size specified, and optional name (mnemonic) which is used for debugging/logging.
This is directly compatible with the PhysicalMMU_t read/write functions.

The primary difference between a Memory_t and a Register_t is that storage objects are accessed by the byte index, not by the size index.
For example, a writeWordU(0, value) will write to the first 0-31 bits, while writeWordU(1, value) will write to bits 8-39 (ie: it will overwrite).
See the Register type for the counter-example.
*/
class Memory_t
{
public:
	explicit Memory_t(const size_t & size);
	explicit Memory_t(const size_t & size, const char *const mnemonic);
	virtual ~Memory_t();

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
	Gets the storage length.
	*/
	virtual size_t getSize();

	/*
	Gets the base host memory address, needed for special VM functions such as loading the BIOS (BootROM).
	Should not be used in favour of the above read/write functions unless you absolutely have to.
	*/
	void * getHostMemoryAddress() const;

	/*
	Get the storage mnemonic, used for debug.
	*/
	virtual const char * getMnemonic() const;

private:
	size_t mStorageSize;
	u8 * mStorage;
	const std::string mMnemonic;
};

