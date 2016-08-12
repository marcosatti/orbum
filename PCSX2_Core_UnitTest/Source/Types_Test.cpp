#include "stdafx.h"
#include <gtest/gtest.h>

#include <limits>

#include <Common/Global/Globals.h>

// Test to see if the 'float' type is actually an IEEE 754 32-bit float type. This needs to be correct as the PS2 emulation relies on this.
// If it fails, you may need to add a #if directive for a platform specific solution into GlobalTypes.h.
TEST(Types_Test, IsFloatIEEE754_32) {
	u8 szFloatBits = sizeof(f32) * 8;
	ASSERT_EQ(32, szFloatBits);
	ASSERT_EQ(true, std::numeric_limits<float>::is_iec559);
}
