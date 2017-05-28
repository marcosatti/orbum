#pragma once

#include <string>
#include <vector>

#include "Common/Global/Globals.h"
#include "Common/Types/System/Context_t.h"
#include "Common/Types/Util/DebugBaseObject_t.h"

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
	virtual u8 readByte(const Context_t context, const size_t byteOffset);
	virtual void writeByte(const Context_t context, const size_t byteOffset, const u8 value);
	virtual u16 readHword(const Context_t context, const size_t byteOffset);
	virtual void writeHword(const Context_t context, const size_t byteOffset, const u16 value);
	virtual u32 readWord(const Context_t context, const size_t byteOffset);
	virtual void writeWord(const Context_t context, const size_t byteOffset, const u32 value);
	virtual u64 readDword(const Context_t context, const size_t byteOffset);
	virtual void writeDword(const Context_t context, const size_t byteOffset, const u64 value);
	virtual u128 readQword(const Context_t context, const size_t byteOffset);
	virtual void writeQword(const Context_t context, const size_t byteOffset, const u128 value);

	/*
	Gets the storage length.
	*/
	virtual size_t getSize();

	/*
	Reads bytes to the buffer given.
	This is a wrapper around the readByte function, and should not be treated as a separate interface (not made virtual).
	*/
	void read(const Context_t context, const size_t byteOffset, u8 * buffer, const size_t byteLength);

	/*
	Writes bytes from the buffer given.
	This is a wrapper around the writeByte function, and should not be treated as a separate interface (not made virtual).
	*/
	void write(const Context_t context, const size_t byteOffset, const u8 * buffer, const size_t byteLength);

	/*
	Read in a raw file to the memory (byte copy).
	For VM use only! Do not use within the system logic.
	*/
	void readFile(const char * fileStr, const size_t fileByteOffset, const size_t fileByteLength, const size_t memoryByteOffset);
	
	/*
	Dumps the memory contents to a file.
	For VM use only! Do not use within the system logic.
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

