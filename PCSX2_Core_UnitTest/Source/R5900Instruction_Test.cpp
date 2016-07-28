#include "stdafx.h"
#include <gtest/gtest.h>

#include <Common/Global/Globals.h>
#include <Common/PS2 Types/MIPSInstructionHelper/MIPSInstructionHelper_t.h>


TEST(R5900Instruction_Test, RType)
{
	// SUB $7, $8, $9
	u32 rawInstruction = 0x01093822; // (8 << 21) | (9 << 16) | (7 << 11) | 34;

	MIPSInstructionHelper_t instruction;
	instruction.setInstruction(rawInstruction);

	ASSERT_EQ(instruction.getOpcode(), 0);
	EXPECT_EQ(instruction.getRRs(), 8);
	EXPECT_EQ(instruction.getRRt(), 9);
	EXPECT_EQ(instruction.getRRd(), 7);
	EXPECT_EQ(instruction.getRShamt(), 0);
	EXPECT_EQ(instruction.getRFunct(), 34);
}

TEST(R5900Instruction_Test, IType)
{
	// LHU $5, +254($10)
	u32 rawInstruction = 0x954500FE; // (37 << 26) | (10 << 21) | (5 << 16) | 254;

	MIPSInstructionHelper_t instruction;
	instruction.setInstruction(rawInstruction);

	ASSERT_EQ(instruction.getOpcode(), 37);
	EXPECT_EQ(instruction.getIRs(), 10);
	EXPECT_EQ(instruction.getIRd(), 5);
	EXPECT_EQ(instruction.getIImmS(), 254);
}

TEST(R5900Instruction_Test, JType)
{
	// J -4096
	u32 rawInstruction = 0x0BFFF000;

	MIPSInstructionHelper_t instruction;
	instruction.setInstruction(rawInstruction);

	ASSERT_EQ(instruction.getOpcode(), 2);
	EXPECT_EQ(instruction.getJPAddress(), (-4096));
}