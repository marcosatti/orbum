#pragma once

#include <string>

#include "Common/Global/Globals.h"
#include "Common/Types/System_t.h"

/*
Abstract base class for mapped storage in ByteMMU_t.
At the minimum, an implementing class needs to provide a way for read and write functions, the size, and a PS2 physical address for where it should be mapped from.
The read write functions expect the index to be a byte index (offset), not a size-specific index.
*/
class MapperBaseObjectByteMMU_t
{
public:
	explicit MapperBaseObjectByteMMU_t(const u32 physicalAddress);
	virtual ~MapperBaseObjectByteMMU_t() = default;

	/*
	Read or write a value of a given type, to the specified byte index (storageIndex).
	*/
	virtual u8 readByte(const System_t context, size_t storageIndex) = 0;
	virtual void writeByte(const System_t context, size_t storageIndex, u8 value) = 0;
	virtual u16 readHword(const System_t context, size_t storageIndex) = 0;
	virtual void writeHword(const System_t context, size_t storageIndex, u16 value) = 0;
	virtual u32 readWord(const System_t context, size_t storageIndex) = 0;
	virtual void writeWord(const System_t context, size_t storageIndex, u32 value) = 0;
	virtual u64 readDword(const System_t context, size_t storageIndex) = 0;
	virtual void writeDword(const System_t context, size_t storageIndex, u64 value) = 0;
	virtual u128 readQword(const System_t context, size_t storageIndex) = 0;
	virtual void writeQword(const System_t context, size_t storageIndex, u128 value) = 0;

	/*
	Gets the base physical address the mapping starts from.
	*/
	const u32 getMappedPhysicalAddress() const;

	/*
	Gets the length of the mapping.
	*/
	virtual size_t getSize() = 0;

	/*
	Get the map mnemonic, used for debug.
	*/
	virtual const char * getMnemonic() const = 0;

private:
	/*
	The physical address this mapping starts from.
	*/
	u32 mMappedPhysicalAddress;
};