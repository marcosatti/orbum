#include "stdafx.h"
#include <gtest/gtest.h>

#include <Common/PS2Resources/Types/PhysicalMMU/PhysicalMMU_t.h>
#include <Common/PS2Resources/Types/MappedMemory/MappedMemory_t.h>

TEST(MMUHandler_Test, EECore_ReadAndWrite) {
	PhysicalMMU_t a(Constants::SIZE_512MB, Constants::SIZE_4MB, Constants::SIZE_16B);
	u32 PS2MemoryAddress = 0x00017FC4;
	std::shared_ptr<MappedMemory_t> mem = std::make_shared<MappedMemory_t>(128, "", PS2MemoryAddress);
	a.mapMemory(mem);

	// 8-bit test.
	u8 valueU8 = 123;
	s8 valueS8 = -51;
	a.writeByteU(PS2MemoryAddress, valueU8);
	EXPECT_EQ(valueU8, a.readByteU(PS2MemoryAddress));
	a.writeByteS(PS2MemoryAddress + 16, valueS8);
	EXPECT_EQ(valueS8, a.readByteS(PS2MemoryAddress + 16));

	// 16-bit test.
	u16 valueU16 = 12345;
	s16 valueS16 = -23232;
	a.writeHwordU(PS2MemoryAddress + 32, valueU16);
	EXPECT_EQ(valueU16, a.readHwordU(PS2MemoryAddress + 32));
	a.writeHwordS(PS2MemoryAddress + 48, valueS16);
	EXPECT_EQ(valueS16, a.readHwordS(PS2MemoryAddress + 48));

	// 32-bit test.
	u32 valueU32 = 2012345610;
	s32 valueS32 = -1549267813;
	a.writeWordU(PS2MemoryAddress + 64, valueU32);
	EXPECT_EQ(valueU32, a.readWordU(PS2MemoryAddress + 64));
	a.writeWordS(PS2MemoryAddress + 80, valueS32);
	EXPECT_EQ(valueS32, a.readWordS(PS2MemoryAddress + 80));

	// 64-bit test.
	u64 valueU64 = 8424978132468451571;
	s64 valueS64 = -2312456987458799565;
	a.writeDwordU(PS2MemoryAddress + 96, valueU64);
	EXPECT_EQ(valueU64, a.readDwordU(PS2MemoryAddress + 96));
	a.writeDwordS(PS2MemoryAddress + 112, valueS64);
	EXPECT_EQ(valueS64, a.readDwordS(PS2MemoryAddress + 112));
}