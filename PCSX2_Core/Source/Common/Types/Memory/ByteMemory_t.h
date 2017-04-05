#pragma once

#include <string>
#include <vector>

#include "Common/Global/Globals.h"
#include "Common/Types/System_t.h"

/*
A simple memory object which is constructed to the (byte) size specified, and optional mnemonic which is used for debugging/logging.
It has byte unit granularity - each address (offset) refers to a byte.
This is directly compatible with the ByteMMU_t read/write functions.
*/
class ByteMemory_t
{
public:
	explicit ByteMemory_t(const size_t byteSize);
	explicit ByteMemory_t(const size_t byteSize, const char * mnemonic);

#if defined(BUILD_DEBUG)
	explicit ByteMemory_t(const size_t byteSize, const char * mnemonic, bool debugReads, bool debugWrites); // Turn on/off debugging functionality.
	bool mDebugReads, mDebugWrites;
#endif

	virtual ~ByteMemory_t() = default;

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
	Returns a reference to the underlying vector storage.
	*/
	std::vector<u8> & getContainer();

	/*
	Get the storage mnemonic, used for debug.
	*/
	virtual const char * getMnemonic() const;

	/*
	Read in a raw file to the memory (byte copy).
	*/
	void readFile(const char * fileStr, const size_t fileByteOffset, const size_t fileByteLength, const size_t memoryByteOffset);

#if defined(BUILD_DEBUG)
	/*
	Dumps the memory contents to a file.
	*/
	void dump(const char * fileStr);
#endif

private:
	size_t mMemoryByteSize;
	std::vector<u8> mMemory;
	std::string mMnemonic;
};

