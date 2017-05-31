#include <gtest/gtest.h>

#include <Common/Global/Globals.h>
#include <Common/Types/MIPS/MIPSInstruction_t.h>

TEST(TEST_MIPSInstruction_t, RType)
{
	// SUB $7, $8, $9
	u32 rawInstruction = 0x01093822; // (8 << 21) | (9 << 16) | (7 << 11) | 34;

	MIPSInstruction_t instruction(rawInstruction);

	ASSERT_EQ(instruction.getOpcode(), 0);
	ASSERT_EQ(instruction.getRs(), 8);
	ASSERT_EQ(instruction.getRt(), 9);
	ASSERT_EQ(instruction.getRRd(), 7);
	ASSERT_EQ(instruction.getRShamt(), 0);
	ASSERT_EQ(instruction.getRFunct(), 34);
}

TEST(TEST_MIPSInstruction_t, IType)
{
	// LHU $5, +254($10)
	u32 rawInstruction = 0x954500FE; // (37 << 26) | (10 << 21) | (5 << 16) | 254;

	MIPSInstruction_t instruction(rawInstruction);

	ASSERT_EQ(instruction.getOpcode(), 37);
	ASSERT_EQ(instruction.getRs(), 10);
	ASSERT_EQ(instruction.getRt(), 5);
	ASSERT_EQ(instruction.getIImmS(), 254);
}

TEST(TEST_MIPSInstruction_t, JType)
{
	// J 4096
	u32 rawInstruction = 0x08001000;

	MIPSInstruction_t instruction(rawInstruction);

	ASSERT_EQ(instruction.getOpcode(), 2);
	ASSERT_EQ(instruction.getJRegionAddress(), 4096);
}