// PCSX2_Core_UnitTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <gtest/gtest.h>


int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(InstructionTest, getOpcode)
{
	EXPECT_EQ(1, 1);
}

TEST(InstructionTest, getOpcode2)
{
	EXPECT_EQ(2, 2);
}