#pragma once

#include <memory>

#include "Globals.h"

class MainMemory_t
{
public:
	static constexpr auto MAIN_MEMORY_SIZE = 0x02000000; // Equal to 32 MB.
	u8 *const mainMemory;

	MainMemory_t() : mainMemory(new u8[MAIN_MEMORY_SIZE])
	{
	}

	~MainMemory_t()
	{
		delete mainMemory;
	}

	/*
	Convenience functions. Get/Set for each primitive type.
	No get/set provided for 128-bit types.
	*/
	INLINE u8 readByte(const size_t & address) const
	{
		// 8-bit
		return *(mainMemory + address);
	}
	INLINE void writeByte(const size_t & address, const u8 & value) const
	{
		// 8-bit
		*(mainMemory + address) = value;
	}
	INLINE u16 readHword(const size_t & address) const
	{
		// 16-bit
		return *((u16*)(mainMemory + address));
	}
	INLINE void writeHword(const size_t & address, const u16 & value) const
	{
		// 16-bit
		*((u16*)(mainMemory + address)) = value;
	}
	INLINE u32 readWord(const size_t & address) const
	{
		// 32-bit
		return *((u32*)(mainMemory + address));
	}
	INLINE void writeWord(const size_t & address, const u32 & value) const
	{
		// 32-bit
		*((u32*)(mainMemory + address)) = value;
	}
	INLINE u64 readDword(const size_t & address) const
	{
		// 64-bit
		return *((u64*)(mainMemory + address));
	}
	INLINE void writeDword(const size_t & address, const u64 & value) const
	{
		// 64-bit
		*((u64*)(mainMemory + address)) = value;
	}
};