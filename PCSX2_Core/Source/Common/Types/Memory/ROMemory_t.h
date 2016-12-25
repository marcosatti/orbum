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
	void writeByteU(u32 storageIndex, u8 value) override;
	void writeByteS(u32 storageIndex, s8 value) override;
	void writeHwordU(u32 storageIndex, u16 value) override;
	void writeHwordS(u32 storageIndex, s16 value) override;
	void writeWordU(u32 storageIndex, u32 value) override;
	void writeWordS(u32 storageIndex, s32 value) override;
	void writeDwordU(u32 storageIndex, u64 value) override;
	void writeDwordS(u32 storageIndex, s64 value) override;
	void writeQwordU(u32 storageIndex, u128 value) override;
};