#pragma once

#include <string>

#include "Common/Global/Globals.h"
#include "Common/Types/Context_t.h"

/*
A simple memory object which is constructed to the (byte) size specified, and optional mnemonic which is used for debugging/logging.
It has hword (16-bit) unit granularity - each address (offset) refers to a hword.
Warning: the size constructor parameter is still defined in terms of BYTES! This is done in order to support easier debugging (windbg's .writemem). 
Make sure the byte size input is divisible by 2.
*/
class HwordMemory_t
{
public:
	explicit HwordMemory_t(const size_t byteSize);
	explicit HwordMemory_t(const size_t byteSize, const char * mnemonic);

#if defined(BUILD_DEBUG)
	explicit HwordMemory_t(const size_t byteSize, const char * mnemonic, bool debugReads, bool debugWrites); // Turn on/off debugging functionality.
	bool mDebugReads, mDebugWrites;
#endif

	virtual ~HwordMemory_t();

	/*
	Read or write a value of a given type, to the specified hword index (hwordOffset).
	*/
	virtual u16 readHword(const Context_t context, size_t hwordOffset);
	virtual void writeHword(const Context_t context, size_t hwordOffset, u16 value);
	virtual u32 readWord(const Context_t context, size_t hwordOffset);
	virtual void writeWord(const Context_t context, size_t hwordOffset, u32 value);
	virtual u64 readDword(const Context_t context, size_t hwordOffset);
	virtual void writeDword(const Context_t context, size_t hwordOffset, u64 value);
	virtual u128 readQword(const Context_t context, size_t hwordOffset);
	virtual void writeQword(const Context_t context, size_t hwordOffset, u128 value);

	/*
	Gets the storage length.
	*/
	virtual size_t getSize();

	/*
	Get the storage mnemonic, used for debug.
	*/
	virtual const char * getMnemonic() const;

private:
	size_t mMemorySize;
	u16 * mMemory;
	const std::string mMnemonic;
};

