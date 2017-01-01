#pragma once

#include "Common/Global/Globals.h"

#if defined(BUILD_DEBUG)

#include "Common/Types/Memory/Memory_t.h"

/*
Debug mapped memory storage - logs all reads and writes.
*/

class DebugMemory_t : public Memory_t
{
public:
	DebugMemory_t(const size_t & size, const char * mnemonic);
	virtual ~DebugMemory_t();

	u8 readByte(u32 storageIndex) override;
	void writeByte(u32 storageIndex, u8 value) override;
	u16 readHword(u32 storageIndex) override;
	void writeHword(u32 storageIndex, u16 value) override;
	u32 readWord(u32 storageIndex) override;
	void writeWord(u32 storageIndex, u32 value) override;
	u64 readDword(u32 storageIndex) override;
	void writeDword(u32 storageIndex, u64 value) override;
	u128 readQword(u32 storageIndex) override;
	void writeQword(u32 storageIndex, u128 value) override;
};

#endif