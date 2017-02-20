#pragma once

#include "Common/Types/Memory/Memory_t.h"

/*
Read-only mapped memory, used for eg: the EE BIOS.
Will not write anything when requested, and instead silently discards the data.
*/
class ROMemory_t : public Memory_t
{
public:
	ROMemory_t(const size_t & size);
	virtual ~ROMemory_t();

	/*
	All writes are discarded - this is a silent discard!
	*/
	void writeByte(const Context_t& context, size_t storageIndex, u8 value) override;
	void writeHword(const Context_t& context, size_t storageIndex, u16 value) override;
	void writeWord(const Context_t& context, size_t storageIndex, u32 value) override;
	void writeDword(const Context_t& context, size_t storageIndex, u64 value) override;
	void writeQword(const Context_t& context, size_t storageIndex, u128 value) override;
};