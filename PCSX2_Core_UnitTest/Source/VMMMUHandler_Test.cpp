#include "stdafx.h"
#include <gtest/gtest.h>

#include <Common/Types/PhysicalMMU/PhysicalMMU_t.h>
#include <Common/Types/Memory/Memory_t.h>

TEST(MMUHandler_Test, EECore_ReadAndWrite) {
	PhysicalMMU_t a(Constants::SIZE_512MB, Constants::SIZE_4MB, Constants::SIZE_16B);
	u32 PS2MemoryAddress = 0x00017FC4;
	std::shared_ptr<Memory_t> mem = std::make_shared<Memory_t>(128, "");
	a.mapObject(PS2MemoryAddress, mem);

	// 8-bit test.
	u8 valueU8 = 123;
	s8 valueS8 = -51;
	a.writeByte(Context::RAW, PS2MemoryAddress, valueU8);
	EXPECT_EQ(valueU8, a.readByte(Context::RAW, PS2MemoryAddress));
	a.writeByte(Context::RAW, PS2MemoryAddress + 16, valueS8);
	EXPECT_EQ(valueS8, a.readByte(Context::RAW, PS2MemoryAddress + 16));

	// 16-bit test.
	u16 valueU16 = 12345;
	s16 valueS16 = -23232;
	a.writeHword(Context::RAW, PS2MemoryAddress + 32, valueU16);
	EXPECT_EQ(valueU16, a.readHword(Context::RAW, PS2MemoryAddress + 32));
	a.writeHword(Context::RAW, PS2MemoryAddress + 48, valueS16);
	EXPECT_EQ(valueS16, a.readHword(Context::RAW, PS2MemoryAddress + 48));

	// 32-bit test.
	u32 valueU32 = 2012345610;
	s32 valueS32 = -1549267813;
	a.writeWord(Context::RAW, PS2MemoryAddress + 64, valueU32);
	EXPECT_EQ(valueU32, a.readWord(Context::RAW, PS2MemoryAddress + 64));
	a.writeWord(Context::RAW, PS2MemoryAddress + 80, valueS32);
	EXPECT_EQ(valueS32, a.readWord(Context::RAW, PS2MemoryAddress + 80));

	// 64-bit test.
	u64 valueU64 = 8424978132468451571;
	s64 valueS64 = -2312456987458799565;
	a.writeDword(Context::RAW, PS2MemoryAddress + 96, valueU64);
	EXPECT_EQ(valueU64, a.readDword(Context::RAW, PS2MemoryAddress + 96));
	a.writeDword(Context::RAW, PS2MemoryAddress + 112, valueS64);
	EXPECT_EQ(valueS64, a.readDword(Context::RAW, PS2MemoryAddress + 112));
}