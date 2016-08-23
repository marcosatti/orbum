#include "stdafx.h"
#include <gtest/gtest.h>

#include <VM/VMMMUHandler/VMMMUHandler.h>

TEST(MMUHandler_Test, AllPTEsValidNotNull_MAX_MAP_SIZE) {
	VMMMUHandler a(nullptr);

	u8 * MEMORYBLOCK = new u8[a.getTableMaxSize()];
	a.mapMemory(MEMORYBLOCK, a.getTableMaxSize(), 0x0);

	// Check if all PTE's are valid and not null.
	for (u32 i = 0; i < a.getTableMaxSize(); i++)
	{
		EXPECT_NE(nullptr, a.getclientMemoryAddress(i));
	}

	delete[] MEMORYBLOCK;
}

TEST(MMUHandler_Test, AllPTEsValidNotNull_MIN_PAGE_SIZE) {
	// Seems to require a lot of memory (3.5GB).. not sure where it is coming from though... it is not from the VMMMUHandler. Maybe because of client OS page size?
	VMMMUHandler a(nullptr);

	u8 ** MEMORYBLOCKS = new u8*[a.getTotalPageEntries()];
	for (u32 i = 0; i < a.getTotalPageEntries(); i++)
	{
		MEMORYBLOCKS[i] = new u8[a.getPageSizeBytes()];
		a.mapMemory(MEMORYBLOCKS[i], a.getPageSizeBytes(), i * a.getPageSizeBytes());
	}

	// Check if all PTE's are valid and not null.
	for (u32 i = 0; i < a.getTableMaxSize(); i++)
	{
		EXPECT_NE(nullptr, a.getclientMemoryAddress(i));
	}

	for (u32 i = 0; i < a.getTotalPageEntries(); i++)
	{
		delete[] MEMORYBLOCKS[i];
	}

	delete[] MEMORYBLOCKS;
}

TEST(MMUHandler_Test, ReadAndWrite) {
	VMMMUHandler a(nullptr);
	u32 PS2MemoryAddress = 0x00017FF4;
	u8 * MEMORYBLOCK = new u8[16];
	a.mapMemory(MEMORYBLOCK, 1, PS2MemoryAddress);

	// 8-bit test.
	u8 valueU8 = 123;
	s8 valueS8 = -51;
	a.writeByteU(PS2MemoryAddress, valueU8);
	EXPECT_EQ(valueU8, a.readByteU(PS2MemoryAddress));
	a.writeByteS(PS2MemoryAddress, valueS8);
	EXPECT_EQ(valueS8, a.readByteS(PS2MemoryAddress));

	// 16-bit test.
	u16 valueU16 = 12345;
	s16 valueS16 = -23232;
	a.writeHwordU(PS2MemoryAddress, valueU16);
	EXPECT_EQ(valueU16, a.readHwordU(PS2MemoryAddress));
	a.writeHwordS(PS2MemoryAddress, valueS16);
	EXPECT_EQ(valueS16, a.readHwordS(PS2MemoryAddress));

	// 32-bit test.
	u32 valueU32 = 2012345610;
	s32 valueS32 = -1549267813;
	a.writeWordU(PS2MemoryAddress, valueU32);
	EXPECT_EQ(valueU32, a.readWordU(PS2MemoryAddress));
	a.writeWordS(PS2MemoryAddress, valueS32);
	EXPECT_EQ(valueS32, a.readWordS(PS2MemoryAddress));

	// 64-bit test.
	u64 valueU64 = 8424978132468451571;
	s64 valueS64 = -2312456987458799565;
	a.writeDwordU(PS2MemoryAddress, valueU64);
	EXPECT_EQ(valueU64, a.readDwordU(PS2MemoryAddress));
	a.writeDwordS(PS2MemoryAddress, valueS64);
	EXPECT_EQ(valueS64, a.readDwordS(PS2MemoryAddress));
}