#pragma once

#include "Common/Types/Memory/ByteMemory_t.h"

/*
Read-only mapped memory, used for eg: the EE BIOS.
Will not write anything when requested, and instead silently discards the data.
*/
class ROByteMemory_t : public ByteMemory_t
{
public:
	ROByteMemory_t(const char * mnemonic, bool debugReads, bool debugWrites, const size_t byteSize);

	/*
	All writes are discarded - this is a silent discard!
	*/
	void writeByte(const System_t context, size_t byteOffset, u8 value) override;
	void writeHword(const System_t context, size_t byteOffset, u16 value) override;
	void writeWord(const System_t context, size_t byteOffset, u32 value) override;
	void writeDword(const System_t context, size_t byteOffset, u64 value) override;
	void writeQword(const System_t context, size_t byteOffset, u128 value) override;
};