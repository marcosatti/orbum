#pragma once

#include "Common/Types/Memory/ByteMemory_t.h"

/*
Read-only mapped memory, used for eg: the EE BIOS.
Will not write anything when requested, and instead silently discards the data.
*/
class ROByteMemory_t : public ByteMemory_t
{
public:
	ROByteMemory_t(const size_t & size);
	virtual ~ROByteMemory_t();

	/*
	All writes are discarded - this is a silent discard!
	*/
	void writeByte(const Context_t context, size_t byteOffset, u8 value) override;
	void writeHword(const Context_t context, size_t byteOffset, u16 value) override;
	void writeWord(const Context_t context, size_t byteOffset, u32 value) override;
	void writeDword(const Context_t context, size_t byteOffset, u64 value) override;
	void writeQword(const Context_t context, size_t byteOffset, u128 value) override;
};