#include "stdafx.h"
#include <gtest/gtest.h>

#include <Common/Global/Globals.h>
#include <Common/Types/MIPSInstruction/MIPSInstruction_t.h>
#include <Common/Tables/EECoreInstructionTable/EECoreInstructionTable.h>
#include <Common/Types/MIPSInstructionInfo/MIPSInstructionInfo_t.h>

TEST(R5900Instruction_Test_Raw, RType)
{
	// SUB $7, $8, $9
	u32 rawInstruction = 0x01093822; // (8 << 21) | (9 << 16) | (7 << 11) | 34;

	MIPSInstruction_t instruction;
	instruction.setInstructionValue(rawInstruction);

	ASSERT_EQ(instruction.getOpcode(), 0);
	EXPECT_EQ(instruction.getRRs(), 8);
	EXPECT_EQ(instruction.getRRt(), 9);
	EXPECT_EQ(instruction.getRRd(), 7);
	EXPECT_EQ(instruction.getRShamt(), 0);
	EXPECT_EQ(instruction.getRFunct(), 34);
}

TEST(R5900Instruction_Test_Raw, IType)
{
	// LHU $5, +254($10)
	u32 rawInstruction = 0x954500FE; // (37 << 26) | (10 << 21) | (5 << 16) | 254;

	MIPSInstruction_t instruction;
	instruction.setInstructionValue(rawInstruction);

	ASSERT_EQ(instruction.getOpcode(), 37);
	EXPECT_EQ(instruction.getIRs(), 10);
	EXPECT_EQ(instruction.getIRt(), 5);
	EXPECT_EQ(instruction.getIImmS(), 254);
}

TEST(R5900Instruction_Test_Raw, JType)
{
	// J 4096
	u32 rawInstruction = 0x08001000;

	MIPSInstruction_t instruction;
	instruction.setInstructionValue(rawInstruction);

	ASSERT_EQ(instruction.getOpcode(), 2);
	EXPECT_EQ(instruction.getJRegionAddress(), 4096);
}

TEST(R5900Instruction_Test_Info, RType)
{
	// SUB $7, $8, $9
	u32 rawInstruction = 0x01093822; // (8 << 21) | (9 << 16) | (7 << 11) | 34;

	MIPSInstruction_t instruction;
	instruction.setInstructionValue(rawInstruction);
	auto info = EECoreInstructionTable::getInstructionInfo(instruction);

	EXPECT_STRNE(info->mMnemonic, "UNSUPPORTED");
	EXPECT_STRNE(info->mMnemonic, "RESERVED");
	EXPECT_STRNE(info->mMnemonic, "UNDEFINED") << "Mnemonic was: " << info->mMnemonic << "\n";
}

TEST(R5900Instruction_Test_Info, IType)
{
	// LHU $5, +254($10)
	u32 rawInstruction = 0x954500FE; // (37 << 26) | (10 << 21) | (5 << 16) | 254;

	MIPSInstruction_t instruction;
	instruction.setInstructionValue(rawInstruction);
	auto info = EECoreInstructionTable::getInstructionInfo(instruction);

	EXPECT_STRNE(info->mMnemonic, "UNSUPPORTED");
	EXPECT_STRNE(info->mMnemonic, "RESERVED");
	EXPECT_STRNE(info->mMnemonic, "UNDEFINED") << "Mnemonic was: " << info->mMnemonic << "\n";
}

TEST(R5900Instruction_Test_Info, JType)
{
	// J -4096
	u32 rawInstruction = 0x0BFFF000;

	MIPSInstruction_t instruction;
	instruction.setInstructionValue(rawInstruction);
	auto info = EECoreInstructionTable::getInstructionInfo(instruction);

	EXPECT_STRNE(info->mMnemonic, "UNSUPPORTED");
	EXPECT_STRNE(info->mMnemonic, "RESERVED");
	EXPECT_STRNE(info->mMnemonic, "UNDEFINED") << "Mnemonic was: " << info->mMnemonic << "\n";
}