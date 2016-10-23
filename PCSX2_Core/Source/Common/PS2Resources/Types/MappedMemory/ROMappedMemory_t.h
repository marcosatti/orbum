#pragma once

#include "Common/PS2Resources/Types/MappedMemory/MappedMemory_t.h"

/*
Read-only mapped memory, used for eg: the EE BIOS.
Will not write anything when requested, and instead silently discards the data.
*/

class ROMappedMemory_t : public MappedMemory_t
{
public:
	ROMappedMemory_t(const size_t & size, const char *const mnemonic, const u32 & PS2PhysicalAddress);
	virtual ~ROMappedMemory_t();

	/*
	All writes are discarded - this is a silent error!
	Can optionally log when this happens.
	*/
	void writeByteU(u32 storageIndex, u8 value) override;
	void writeByteS(u32 storageIndex, s8 value) override;
	void writeHwordU(u32 storageIndex, u16 value) override;
	void writeHwordS(u32 storageIndex, s16 value) override;
	void writeWordU(u32 storageIndex, u32 value) override;
	void writeWordS(u32 storageIndex, s32 value) override;
	void writeDwordU(u32 storageIndex, u64 value) override;
	void writeDwordS(u32 storageIndex, s64 value) override;
};