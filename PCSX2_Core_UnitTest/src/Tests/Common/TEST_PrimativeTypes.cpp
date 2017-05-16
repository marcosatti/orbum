#include <gtest/gtest.h>
#include <limits>

#include <Common/Global/Globals.h>

TEST(Test_PrimativeTypes, IS_F32_32BIT) 
{
	// Test to see if the f32 (typedef'd from 'float') type is actually an IEEE 754 32-bit float type. This needs to be correct as the PS2 emulation relies on this.
	// If it fails, you may need to add a #if directive for a platform specific solution into PrimativeTypes.h.
	size_t sz = sizeof(f32) * 8;
	ASSERT_EQ(32, sz);
}

TEST(Test_PrimativeTypes, IS_F32_IEEE754)
{
	// IEEE 754 also known as IEC 559.
	ASSERT_EQ(true, std::numeric_limits<f32>::is_iec559); 
}

TEST(Test_PrimativeTypes, U128_ORDERING)
{
	// Test the struct memory ordering of the u128 'primative' type (against words).
	u128 value = u128(0x1122334455667788, 0x99AABBCCDDEEFF00);

	ASSERT_EQ(0x55667788, value.UW[0]);
	ASSERT_EQ(0x11223344, value.UW[1]);
	ASSERT_EQ(0xDDEEFF00, value.UW[2]);
	ASSERT_EQ(0x99AABBCC, value.UW[3]);
}
