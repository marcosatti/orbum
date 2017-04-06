#include "stdafx.h"

#include <gtest/gtest.h>
#include <memory>

#include <Common/Types/ByteMMU/ByteMMU_t.h>
#include <Common/Types/Memory/ByteMemory_t.h>

class TEST_ByteMMU_t : public testing::Test 
{
public:
	ByteMMU_t mmu = ByteMMU_t(32, 12, 4);
	u32 address = 0x00017FC4;

	virtual void SetUp() 
	{
		std::shared_ptr<ByteMemory_t> mem = std::make_shared<ByteMemory_t>(1024, "Test of ByteMMU_t");
		mmu.mapObject(address, mem);
	}

	virtual void TearDown() {}
};

TEST_F(TEST_ByteMMU_t, READ_WRITE_8BIT) 
{
	// 8-bit test.
	u8 valueU8 = 123;
	s8 valueS8 = -51;
	mmu.writeByte(System_t::EECore, address, valueU8);
	ASSERT_EQ(valueU8, mmu.readByte(System_t::EECore, address));
	mmu.writeByte(System_t::EECore, address, valueS8);
	ASSERT_EQ(valueS8, static_cast<s8>(mmu.readByte(System_t::EECore, address)));
}

TEST_F(TEST_ByteMMU_t, READ_WRITE_16BIT)
{
	// 16-bit test.
	u16 valueU16 = 12345;
	s16 valueS16 = -23232;
	mmu.writeHword(System_t::EECore, address, valueU16);
	ASSERT_EQ(valueU16, mmu.readHword(System_t::EECore, address));
	mmu.writeHword(System_t::EECore, address, valueS16);
	ASSERT_EQ(valueS16, static_cast<s16>(mmu.readHword(System_t::EECore, address)));
}

TEST_F(TEST_ByteMMU_t, READ_WRITE_32BIT)
{
	// 32-bit test.
	u32 valueU32 = 2012345610;
	s32 valueS32 = -1549267813;
	mmu.writeWord(System_t::EECore, address, valueU32);
	ASSERT_EQ(valueU32, mmu.readWord(System_t::EECore, address));
	mmu.writeWord(System_t::EECore, address, valueS32);
	ASSERT_EQ(valueS32, static_cast<s32>(mmu.readWord(System_t::EECore, address)));
}

TEST_F(TEST_ByteMMU_t, READ_WRITE_64BIT)
{
	// 64-bit test.
	u64 valueU64 = 8424978132468451571;
	s64 valueS64 = -2312456987458799565;
	mmu.writeDword(System_t::EECore, address, valueU64);
	ASSERT_EQ(valueU64, mmu.readDword(System_t::EECore, address));
	mmu.writeDword(System_t::EECore, address, valueS64);
	ASSERT_EQ(valueS64, static_cast<s64>(mmu.readDword(System_t::EECore, address)));
}

TEST_F(TEST_ByteMMU_t, READ_WRITE_128BIT)
{
	// 128-bit test. There is no signed test, only unsigned.
	u64 val0 = 9384;
	u64 val1 = 6545;
	u128 valueU128 = u128(val0, val1);
	mmu.writeQword(System_t::EECore, address, valueU128);
	u128 val2 = mmu.readQword(System_t::EECore, address);
	ASSERT_EQ(val0, val2.lo);
	ASSERT_EQ(val1, val2.hi);
}