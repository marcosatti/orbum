#pragma once

#include "Common/Types/Memory/Memory_t.h"

/*
Read-only mapped memory, used for eg: the EE BIOS.
Will not write anything when requested, and instead silently discards the data.
*/

class ROMemory_t : public Memory_t
{
public:
	ROMemory_t(const size_t & size, const char * mnemonic);
	virtual ~ROMemory_t();

	/*
	All writes are discarded - this is a silent discard!
	Can optionally debug log when this happens.
	*/
	void writeByte(u32 storageIndex, u8 value) override;
	void writeHword(u32 storageIndex, u16 value) override;
	void writeWord(u32 storageIndex, u32 value) override;
	void writeDword(u32 storageIndex, u64 value) override;
	void writeQword(u32 storageIndex, u128 value) override;
};