#include <memory>

#include <Common/Types/ByteMMU/ByteMMU_t.h>
#include <Common/Types/Memory/ByteMemory_t.h>

#include <boost/test/unit_test.hpp>

struct R_TEST_ByteMMU_t
{
	R_TEST_ByteMMU_t() 
	{
		std::shared_ptr<ByteMemory_t> mem = std::make_shared<ByteMemory_t>("", false, false, 1024);
		mmu.mapObject(address, mem);
		BOOST_TEST_MESSAGE("Setup ByteMMU_t");
	}

	~R_TEST_ByteMMU_t() 
	{
		BOOST_TEST_MESSAGE("TearDown ByteMMU_t");
	}

	ByteMMU_t mmu = ByteMMU_t(32, 16, 2);
	u32 address = 0x00017FC4;
};

BOOST_FIXTURE_TEST_SUITE(TEST_ByteMMU_t, R_TEST_ByteMMU_t)

BOOST_AUTO_TEST_CASE(READ_WRITE_8BIT)
{
	// 8-bit test.
	u8 valueU8 = 123;
	s8 valueS8 = -51;
	mmu.writeByte(Context_t::EECore, address, valueU8);
	BOOST_TEST(valueU8 == mmu.readByte(Context_t::EECore, address));
	mmu.writeByte(Context_t::EECore, address, valueS8);
	BOOST_TEST(valueS8 == static_cast<s8>(mmu.readByte(Context_t::EECore, address)));
}

BOOST_AUTO_TEST_CASE(READ_WRITE_16BIT)
{
	// 16-bit test.
	u16 valueU16 = 12345;
	s16 valueS16 = -23232;
	mmu.writeHword(Context_t::EECore, address, valueU16);
	BOOST_TEST(valueU16 == mmu.readHword(Context_t::EECore, address));
	mmu.writeHword(Context_t::EECore, address, valueS16);
	BOOST_TEST(valueS16 == static_cast<s16>(mmu.readHword(Context_t::EECore, address)));
}

BOOST_AUTO_TEST_CASE(READ_WRITE_32BIT)
{
	// 32-bit test.
	u32 valueU32 = 2012345610;
	s32 valueS32 = -1549267813;
	mmu.writeWord(Context_t::EECore, address, valueU32);
	BOOST_TEST(valueU32 == mmu.readWord(Context_t::EECore, address));
	mmu.writeWord(Context_t::EECore, address, valueS32);
	BOOST_TEST(valueS32 == static_cast<s32>(mmu.readWord(Context_t::EECore, address)));
}

BOOST_AUTO_TEST_CASE(READ_WRITE_64BIT)
{
	// 64-bit test.
	u64 valueU64 = 8424978132468451571;
	s64 valueS64 = -2312456987458799565;
	mmu.writeDword(Context_t::EECore, address, valueU64);
	BOOST_TEST(valueU64 == mmu.readDword(Context_t::EECore, address));
	mmu.writeDword(Context_t::EECore, address, valueS64);
	BOOST_TEST(valueS64 == static_cast<s64>(mmu.readDword(Context_t::EECore, address)));
}

BOOST_AUTO_TEST_CASE(READ_WRITE_128BIT)
{
	// 128-bit test. There is no signed test, only unsigned.
	u64 val0 = 9384;
	u64 val1 = 6545;
	u128 valueU128 = u128(val0, val1);
	mmu.writeQword(Context_t::EECore, address, valueU128);
	u128 val2 = mmu.readQword(Context_t::EECore, address);
	BOOST_TEST(val0 == val2.lo);
	BOOST_TEST(val1 == val2.hi);
}

BOOST_AUTO_TEST_SUITE_END()