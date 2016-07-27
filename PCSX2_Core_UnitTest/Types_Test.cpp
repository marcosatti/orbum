#include "stdafx.h"
#include <gtest/gtest.h>

#include "Globals.h"


// Test to see if the 'float' type is actually 32-bit. This needs to be correct as the PS2 emulation relies on this.
// If it fails, you may need to add a #if directive for a platform specific solution into GlobalTypes.h.
TEST(Types_Test, IsFloat32) {
	u8 szFloatBits = sizeof(f32) * 8;
	ASSERT_EQ(32, szFloatBits);
}
