#pragma once

#include <string>
#include <vector>

#include "Common/Global/Globals.h"
#include "Common/Types/System_t.h"
#include "Common/Types/DebugBaseObject_t.h"

/*
A simple memory object which is constructed to the (byte) size specified, and optional mnemonic which is used for debugging/logging.
It has hword (16-bit) unit granularity - each address (offset) refers to a hword.
Warning: the size constructor parameter is still defined in terms of BYTES!
Make sure the byte size input is divisible by 2 (throws runtime_error otherwise).
*/
class HwordMemory_t : public DebugBaseObject_t
{
public:
	HwordMemory_t(const char * mnemonic, bool debugReads, bool debugWrites, const size_t byteSize);
	virtual ~HwordMemory_t() = default;

	/*
	Initalise byte memory (set to 0's).
	*/
	virtual void initalise();

	/*
	Read or write a value of a given type, to the specified hword index (hwordOffset).
	*/
	virtual u16 readHword(const System_t context, size_t hwordOffset);
	virtual void writeHword(const System_t context, size_t hwordOffset, u16 value);
	virtual u32 readWord(const System_t context, size_t hwordOffset);
	virtual void writeWord(const System_t context, size_t hwordOffset, u32 value);
	virtual u64 readDword(const System_t context, size_t hwordOffset);
	virtual void writeDword(const System_t context, size_t hwordOffset, u64 value);
	virtual u128 readQword(const System_t context, size_t hwordOffset);
	virtual void writeQword(const System_t context, size_t hwordOffset, u128 value);

	/*
	Gets the storage length.
	*/
	virtual size_t getSize();

	/*
	Returns a reference to the underlying vector storage.
	*/
	std::vector<u16> & getContainer();

	/*
	Read in a raw file to the memory (byte copy).
	*/
	void readFile(const char * fileStr, const size_t fileHwordOffset, const size_t fileHwordLength, const size_t memoryHwordOffset);

	/*
	Dumps the memory contents to a file.
	*/
	void dump(const char * fileStr);

private:
	/*
	Total size of the hword memory, used for mapping (size in bytes).
	*/
	size_t mMemoryByteSize;

	/*
	The backend for the hword memory.
	*/
	std::vector<u16> mMemory;
};

