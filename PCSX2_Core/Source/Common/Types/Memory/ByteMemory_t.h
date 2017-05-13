#pragma once

#include <string>
#include <vector>

#include "Common/Global/Globals.h"
#include "Common/Types/System_t.h"
#include "Common/Types/DebugBaseObject_t.h"

/*
A simple memory object which is constructed to the (byte) size specified, and optional mnemonic which is used for debugging/logging.
It has byte unit granularity - each address (offset) refers to a byte.
This is directly compatible with the ByteMMU_t read/write functions.
*/
class ByteMemory_t : public DebugBaseObject_t
{
public:
	ByteMemory_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const size_t byteSize);
	virtual ~ByteMemory_t() = default;

	/*
	Initialise byte memory (set to 0's).
	*/
	virtual void initialise();

	/*
	Read or write a value of a given type, to the specified byte index (byteOffset).
	*/
	virtual u8 readByte(const System_t context, size_t byteOffset);
	virtual void writeByte(const System_t context, size_t byteOffset, u8 value);
	virtual u16 readHword(const System_t context, size_t byteOffset);
	virtual void writeHword(const System_t context, size_t byteOffset, u16 value);
	virtual u32 readWord(const System_t context, size_t byteOffset);
	virtual void writeWord(const System_t context, size_t byteOffset, u32 value);
	virtual u64 readDword(const System_t context, size_t byteOffset);
	virtual void writeDword(const System_t context, size_t byteOffset, u64 value);
	virtual u128 readQword(const System_t context, size_t byteOffset);
	virtual void writeQword(const System_t context, size_t byteOffset, u128 value);

	/*
	Gets the storage length.
	*/
	virtual size_t getSize();

	/*
	Reads bytes to the buffer given.
	*/
	virtual void read(const System_t context, u8 * buffer, const size_t byteLength, const size_t byteOffset) const;

	/*
	Writes bytes from the buffer given.
	*/
	virtual void write(const System_t context, const u8 * buffer, const size_t byteLength, const size_t byteOffset);

	/*
	Read in a raw file to the memory (byte copy).
	*/
	void readFile(const char * fileStr, const size_t fileByteOffset, const size_t fileByteLength, const size_t memoryByteOffset);
	
	/*
	Dumps the memory contents to a file.
	*/
	void dump(const char * fileStr);

private:
	/*
	Total size of the byte memory, used for mapping.
	*/
	size_t mMemoryByteSize;

	/*
	The backend for the byte memory.
	*/
	std::vector<u8> mMemory;
};

