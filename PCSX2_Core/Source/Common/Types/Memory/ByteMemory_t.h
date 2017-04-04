#pragma once

#include <string>

#include "Common/Global/Globals.h"
#include "Common/Types/System_t.h"

/*
A simple memory object which is constructed to the (byte) size specified, and optional mnemonic which is used for debugging/logging.
It has byte unit granularity - each address (offset) refers to a byte.
This is directly compatible with the PhysicalMMU_t read/write functions.
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

	virtual ~ByteMemory_t();

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
	Gets the base host memory address, needed for special VM functions such as loading the BIOS (BootROM).
	Should not be used in favour of the above read/write functions unless you absolutely have to.
	*/
	void * getHostMemoryAddress() const;

	/*
	Get the storage mnemonic, used for debug.
	*/
	virtual const char * getMnemonic() const;

	/*
	Read in a raw file to the memory (byte copy).
	*/
	void readFile(const std::string & fileStr, const size_t fileByteOffset, const size_t fileByteLength, const size_t memoryByteOffset) const;

private:
	size_t mMemorySize;
	u8 * mMemory;
	std::string mMnemonic;
};

