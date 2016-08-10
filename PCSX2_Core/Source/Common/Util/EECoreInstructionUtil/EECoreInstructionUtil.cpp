#include "stdafx.h"

#include "EECoreInstructionUtil.h"

const EECoreInstructionUtil::EECoreInstructionInfo_t & EECoreInstructionUtil::getInstructionInfo(const MIPSInstruction_t & instruction)
{
	const EECoreInstructionInfo_t rootInfo = { 0, EECoreInstructionInfo_t::InstructionType::CLASS, "OPCODE", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_OPCODE_LOOKUP };
	const EECoreInstructionInfo_t * returnInfo = &rootInfo;
	while (returnInfo->mInstructionType == EECoreInstructionInfo_t::InstructionType::CLASS)
	{
		returnInfo = &returnInfo->mLookupFuncion(instruction);
	}

	return *returnInfo;
}

const EECoreInstructionUtil::EECoreInstructionInfo_t & EECoreInstructionUtil::EECORE_INSTRUCTION_OPCODE_LOOKUP(const MIPSInstruction_t & instruction)
{
	return EECORE_OPCODE_TABLE[instruction.getOpcode()];
}

const EECoreInstructionUtil::EECoreInstructionInfo_t& EECoreInstructionUtil::EECORE_INSTRUCTION_SPECIAL_LOOKUP(const MIPSInstruction_t& instruction)
{
	return EECORE_SPECIAL_TABLE[instruction.getRFunct()];
}

const EECoreInstructionUtil::EECoreInstructionInfo_t& EECoreInstructionUtil::EECORE_INSTRUCTION_REGIMM_LOOKUP(const MIPSInstruction_t& instruction)
{
	return EECORE_REGIMM_TABLE[instruction.getRRt()];
}

const EECoreInstructionUtil::EECoreInstructionInfo_t& EECoreInstructionUtil::EECORE_INSTRUCTION_MMI_LOOKUP(const MIPSInstruction_t& instruction)
{
	return EECORE_MMI_TABLE[instruction.getRFunct()];
}

const EECoreInstructionUtil::EECoreInstructionInfo_t& EECoreInstructionUtil::EECORE_INSTRUCTION_MMI0_LOOKUP(const MIPSInstruction_t& instruction)
{
	return EECORE_MMI0_TABLE[instruction.getRShamt()];
}

const EECoreInstructionUtil::EECoreInstructionInfo_t& EECoreInstructionUtil::EECORE_INSTRUCTION_MMI1_LOOKUP(const MIPSInstruction_t& instruction)
{
	return EECORE_MMI1_TABLE[instruction.getRShamt()];
}

const EECoreInstructionUtil::EECoreInstructionInfo_t& EECoreInstructionUtil::EECORE_INSTRUCTION_MMI2_LOOKUP(const MIPSInstruction_t& instruction)
{
	return EECORE_MMI2_TABLE[instruction.getRShamt()];
}

const EECoreInstructionUtil::EECoreInstructionInfo_t& EECoreInstructionUtil::EECORE_INSTRUCTION_MMI3_LOOKUP(const MIPSInstruction_t& instruction)
{
	return EECORE_MMI3_TABLE[instruction.getRShamt()];
}

const EECoreInstructionUtil::EECoreInstructionInfo_t& EECoreInstructionUtil::EECORE_INSTRUCTION_COP0_LOOKUP(const MIPSInstruction_t& instruction)
{
	return EECORE_COP0_TABLE[instruction.getRRs()];
}

const EECoreInstructionUtil::EECoreInstructionInfo_t& EECoreInstructionUtil::EECORE_INSTRUCTION_BC0_LOOKUP(const MIPSInstruction_t& instruction)
{
	return EECORE_BC0_TABLE[instruction.getRRt()];
}

const EECoreInstructionUtil::EECoreInstructionInfo_t& EECoreInstructionUtil::EECORE_INSTRUCTION_C0_LOOKUP(const MIPSInstruction_t& instruction)
{
	return EECORE_C0_TABLE[instruction.getRFunct()];
}

const EECoreInstructionUtil::EECoreInstructionInfo_t& EECoreInstructionUtil::EECORE_INSTRUCTION_COP1_LOOKUP(const MIPSInstruction_t& instruction)
{
	return EECORE_COP1_TABLE[instruction.getRRs()];
}

const EECoreInstructionUtil::EECoreInstructionInfo_t& EECoreInstructionUtil::EECORE_INSTRUCTION_BC1_LOOKUP(const MIPSInstruction_t& instruction)
{
	return EECORE_BC1_TABLE[instruction.getRRt()];
}

const EECoreInstructionUtil::EECoreInstructionInfo_t& EECoreInstructionUtil::EECORE_INSTRUCTION_S_LOOKUP(const MIPSInstruction_t& instruction)
{
	return EECORE_S_TABLE[instruction.getRFunct()];
}

const EECoreInstructionUtil::EECoreInstructionInfo_t& EECoreInstructionUtil::EECORE_INSTRUCTION_W_LOOKUP(const MIPSInstruction_t& instruction)
{
	return EECORE_W_TABLE[instruction.getRFunct()];
}

const EECoreInstructionUtil::EECoreInstructionInfo_t& EECoreInstructionUtil::EECORE_INSTRUCTION_COP2_LOOKUP(const MIPSInstruction_t& instruction)
{
	return EECORE_INSTRUCTION_UNDEFINED;
}

const EECoreInstructionUtil::EECoreInstructionInfo_t EECoreInstructionUtil::EECORE_INSTRUCTION_UNDEFINED = { 0, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr };

const EECoreInstructionUtil::EECoreInstructionInfo_t EECoreInstructionUtil::EECORE_W_TABLE[64] =
{
	{ 0, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 1, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 2, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 3, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 4, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 5, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 6, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 7, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 8, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 9, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 10, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 11, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 12, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 13, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 14, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 15, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 16, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 17, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 18, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 19, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 20, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 21, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 22, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 23, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 24, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 25, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 26, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 27, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 28, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 29, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 30, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 31, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 32, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "CVTS", 259, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 33, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 34, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 35, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 36, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 37, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 38, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 39, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 40, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 41, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 42, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 43, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 44, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 45, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 46, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 47, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 48, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 49, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 50, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 51, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 52, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 53, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 54, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 55, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 56, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 57, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 58, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 59, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 60, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 61, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 62, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 63, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr }
};

const EECoreInstructionUtil::EECoreInstructionInfo_t EECoreInstructionUtil::EECORE_S_TABLE[64] =
{
	{ 0, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "ADD", 236, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 1, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "SUB", 237, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 2, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MUL", 238, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 3, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "DIV", 239, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 4, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "SQRT", 240, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 5, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "ABS", 241, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 6, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MOV", 242, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 7, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "NEG", 243, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 8, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 9, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 10, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 11, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 12, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 13, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 14, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 15, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 16, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 17, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 18, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 19, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 20, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 21, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RSQRT", 244, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 22, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 23, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "ADDA", 245, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 24, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "SUBA", 246, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 25, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MULA", 247, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 26, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 27, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MADD", 248, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 28, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MSUB", 249, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 29, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MADDA", 250, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 30, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MSUBA", 251, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 31, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 32, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 33, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 34, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 35, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "CVTW", 252, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 36, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 37, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 38, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 39, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MAX", 253, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 40, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MIN", 254, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 41, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 42, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 43, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 44, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 45, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 46, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 47, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "C.F", 255, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 48, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 49, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "C.EQ", 256, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 50, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 51, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "C.LT", 257, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 52, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 53, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "C.LE", 258, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 54, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 55, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 56, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 57, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 58, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 59, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 60, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 61, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 62, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 63, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr }
};

const EECoreInstructionUtil::EECoreInstructionInfo_t EECoreInstructionUtil::EECORE_BC1_TABLE[32] =
{
	{ 0, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "BC1F", 232, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 1, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "BC1T", 233, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 2, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "BC1FL", 234, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 3, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "BC1TL", 235, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 4, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 5, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 6, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 7, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 8, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 9, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 10, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 11, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 12, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 13, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 14, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 15, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 16, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 17, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 18, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 19, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 20, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 21, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 22, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 23, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 24, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 25, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 26, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 27, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 28, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 29, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 30, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 31, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr }
};

const EECoreInstructionUtil::EECoreInstructionInfo_t EECoreInstructionUtil::EECORE_COP1_TABLE[32] =
{
	{ 0, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MFC1", 228, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 1, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 2, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "CFC1", 229, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 3, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 4, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MTC1", 230, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 5, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 6, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "CTC1", 231, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 7, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 8, EECoreInstructionInfo_t::InstructionType::CLASS, "BC1", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_BC1_LOOKUP },
	{ 9, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 10, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 11, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 12, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 13, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 14, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 15, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 16, EECoreInstructionInfo_t::InstructionType::CLASS, "S", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_S_LOOKUP },
	{ 17, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 18, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 19, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 20, EECoreInstructionInfo_t::InstructionType::CLASS, "W", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_W_LOOKUP },
	{ 21, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 22, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 23, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 24, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 25, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 26, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 27, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 28, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 29, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 30, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 31, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },

};

const EECoreInstructionUtil::EECoreInstructionInfo_t EECoreInstructionUtil::EECORE_C0_TABLE[64] =
{
	{ 0, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 1, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "TLBR", 221, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 2, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "TLBWI", 222, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 3, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 4, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 5, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 6, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "TLBWR", 223, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 7, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 8, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "TLBP", 224, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 9, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 10, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 11, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 12, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 13, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 14, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 15, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 16, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 17, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 18, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 19, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 20, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 21, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 22, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 23, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 24, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "ERET", 225, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 25, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 26, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 27, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 28, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 29, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 30, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 31, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 32, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 33, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 34, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 35, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 36, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 37, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 38, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 39, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 40, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 41, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 42, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 43, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 44, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 45, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 46, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 47, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 48, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 49, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 50, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 51, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 52, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 53, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 54, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 55, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 56, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "EI", 226, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 57, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "DI", 227, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 58, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 59, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 60, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 61, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 62, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 63, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr }
};

const EECoreInstructionUtil::EECoreInstructionInfo_t EECoreInstructionUtil::EECORE_BC0_TABLE[32] =
{
	{ 0, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "BC0F", 217, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 1, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "BC0T", 218, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 2, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "BC0FL", 219, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 3, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "BC0TL", 220, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 4, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 5, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 6, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 7, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 8, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 9, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 10, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 11, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 12, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 13, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 14, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 15, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 16, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 17, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 18, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 19, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 20, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 21, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 22, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 23, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 24, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 25, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 26, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 27, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 28, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 29, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 30, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 31, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr }
};

const EECoreInstructionUtil::EECoreInstructionInfo_t EECoreInstructionUtil::EECORE_COP0_TABLE[32] =
{
	{ 0, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MF0", 215, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 1, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 2, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 3, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 4, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MT0", 216, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 5, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 6, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 7, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 8, EECoreInstructionInfo_t::InstructionType::CLASS, "BC0", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_BC0_LOOKUP },
	{ 9, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 10, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 11, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 12, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 13, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 14, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 15, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 16, EECoreInstructionInfo_t::InstructionType::CLASS, "C0", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_C0_LOOKUP },
	{ 17, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 18, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 19, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 20, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 21, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 22, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 23, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 24, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 25, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 26, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 27, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 28, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 29, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 30, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 31, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr }
};

const EECoreInstructionUtil::EECoreInstructionInfo_t EECoreInstructionUtil::EECORE_MMI3_TABLE[32] =
{
	{ 0, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PMADDUW", 202, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 1, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 2, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 3, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PSRAVW", 203, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 4, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 5, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 6, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 7, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 8, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PMTHI", 204, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 9, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PMTLO", 205, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 10, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PINTEH", 206, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 11, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 12, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PMULTUW", 207, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 13, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PDIVUW", 208, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 14, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PCPYUD", 209, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 15, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 16, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 17, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 18, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "POR", 210, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 19, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PNOR", 211, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 20, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 21, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 22, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 23, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 24, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 25, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 26, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PEXCH", 212, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 27, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PCPYH", 213, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 28, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 29, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 30, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PEXCW", 214, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 31, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr }
};

const EECoreInstructionUtil::EECoreInstructionInfo_t EECoreInstructionUtil::EECORE_MMI2_TABLE[32] =
{
	{ 0, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PMADDW", 180, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 1, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 2, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PSLLVW", 181, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 3, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PSRLVW", 182, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 4, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PMSUBW", 183, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 5, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 6, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 7, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 8, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PMFHI", 184, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 9, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PMFLO", 185, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 10, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PINTH", 186, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 11, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 12, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PMULTW", 187, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 13, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PDIVW", 188, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 14, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PCPYLD", 189, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 15, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 16, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PMADDH", 190, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 17, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PHMADH", 191, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 18, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PAND", 192, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 19, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PXOR", 193, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 20, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PMSUBH", 194, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 21, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PHMSBH", 195, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 22, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 23, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 24, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 25, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 26, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PEXEH", 196, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 27, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PREVH", 197, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 28, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PMULTH", 198, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 29, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PDIVBW", 199, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 30, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PEXEW", 200, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 31, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PROT3W", 201, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr }
};

const EECoreInstructionUtil::EECoreInstructionInfo_t EECoreInstructionUtil::EECORE_MMI1_TABLE[32] =
{
	{ 0, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 1, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PABSW", 162, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 2, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PCEQW", 163, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 3, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PMINW", 164, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 4, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PADSBH", 165, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 5, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PABSH", 166, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 6, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PCEQH", 167, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 7, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PMINH", 168, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 8, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 9, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 10, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PCEQB", 169, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 11, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 12, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 13, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 14, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 15, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 16, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PADDUW", 170, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 17, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PSUBUW", 171, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 18, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PEXTUW", 172, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 19, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 20, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PADDUH", 173, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 21, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PSUBUH", 174, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 22, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PEXTUH", 175, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 23, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 24, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PADDUB", 176, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 25, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PSUBUB", 177, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 26, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PEXTUB", 178, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 27, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "QFSRV", 179, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 28, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 29, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 30, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 31, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr }
};

const EECoreInstructionUtil::EECoreInstructionInfo_t EECoreInstructionUtil::EECORE_MMI0_TABLE[32] =
{
	{ 0, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PADDW", 137, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 1, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PSUBW", 138, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 2, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PCGTW", 139, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 3, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PMAXW", 140, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 4, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PADDH", 141, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 5, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PSUBH", 142, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 6, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PCGTH", 143, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 7, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PMAXH", 144, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 8, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PADDB", 145, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 9, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PSUBB", 146, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 10, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PCGTB", 147, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 11, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 12, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 13, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 14, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 15, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 16, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PADDSW", 148, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 17, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PSUBSW", 149, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 18, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PEXTLW", 150, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 19, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PPACW", 151, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 20, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PADDSH", 152, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 21, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PSUBSH", 153, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 22, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PEXTLH", 154, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 23, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PPACH", 155, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 24, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PADDSB", 156, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 25, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PSUBSB", 157, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 26, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PEXTLB", 158, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 27, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PPACB", 159, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 28, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 29, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 30, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PEXT5", 160, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 31, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PPAC5", 161, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr }
};

const EECoreInstructionUtil::EECoreInstructionInfo_t EECoreInstructionUtil::EECORE_MMI_TABLE[64] =
{
	{ 0, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MADD", 116, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 1, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MADDU", 117, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 2, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 3, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 4, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PLZCW", 118, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 5, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 6, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 7, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 8, EECoreInstructionInfo_t::InstructionType::CLASS, "MMI0", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_MMI0_LOOKUP },
	{ 9, EECoreInstructionInfo_t::InstructionType::CLASS, "MMI2", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_MMI2_LOOKUP },
	{ 10, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 11, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 12, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 13, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 14, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 15, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 16, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MHFI1", 119, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 17, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MTHI1", 120, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 18, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MFLO1", 121, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 19, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MTLO1", 122, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 20, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 21, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 22, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 23, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 24, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MULT1", 123, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 25, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MULTU1", 124, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 26, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "DIV1", 125, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 27, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "DIVU1", 126, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 28, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 29, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 30, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 31, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 32, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MADD1", 127, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 33, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MADDU1", 128, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 34, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 35, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 36, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 37, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 38, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 39, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 40, EECoreInstructionInfo_t::InstructionType::CLASS, "MMI1", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_MMI1_LOOKUP },
	{ 41, EECoreInstructionInfo_t::InstructionType::CLASS, "MMI3", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_MMI3_LOOKUP },
	{ 42, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 43, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 44, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 45, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 46, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 47, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 48, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PMFHL", 129, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 49, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PMTHL", 130, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 50, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 51, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 52, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PSLLH", 131, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 53, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 54, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PSRLH", 132, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 55, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PSRAH", 133, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 56, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 57, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 58, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 59, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 60, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PSLLW", 134, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 61, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 62, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PSRLW", 135, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 63, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PSRAW", 136, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },

};

const EECoreInstructionUtil::EECoreInstructionInfo_t EECoreInstructionUtil::EECORE_REGIMM_TABLE[32] =
{
	{ 0, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "BLTZ", 100, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 1, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "BGEZ", 101, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 2, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "BLTZL", 102, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 3, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "BGEZL", 103, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 4, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 5, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 6, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 7, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 8, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "TGEI", 104, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 9, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "TGEIU", 105, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 10, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "TLTI", 106, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 11, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "TLTIU", 107, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 12, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "TEQI", 108, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 13, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 14, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "TNEI", 109, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 15, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 16, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "BLTZAL", 110, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 17, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "BGEZAL", 111, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 18, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "BLTZALL", 112, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 19, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "BGEZALL", 113, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 20, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 21, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 22, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 23, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 24, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MTSAB", 114, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 25, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MTSAH", 115, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 26, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 27, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 28, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 29, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 30, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 31, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr }
};

const EECoreInstructionUtil::EECoreInstructionInfo_t EECoreInstructionUtil::EECORE_SPECIAL_TABLE[64] =
{
	{ 0, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "SLL", 48, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 1, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 2, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "SRL", 49, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 3, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "SRA", 50, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 4, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "SLLV", 51, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 5, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 6, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "SRLV", 52, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 7, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "SRAV", 53, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 8, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "JR", 54, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 9, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "JALR", 55, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 10, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MOVZ", 56, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 11, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MOVN", 57, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 12, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "SYSCALL", 58, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 13, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "BREAK", 59, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 14, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 15, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "SYNC", 60, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 16, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MFHI", 61, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 17, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MTHI", 62, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 18, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MFLO", 63, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 19, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MTLO", 64, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 20, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "DSLLV", 65, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 21, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 22, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "DSRLV", 66, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 23, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "DSRAV", 67, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 24, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MULT", 68, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 25, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MULTU", 69, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 26, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "DIV", 70, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 27, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "DIVU", 71, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 28, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 29, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 30, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 31, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 32, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "ADD", 72, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 33, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "ADDU", 73, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 34, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "SUB", 74, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 35, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "SUBU", 75, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 36, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "AND", 76, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 37, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "OR", 77, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 38, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "XOR", 78, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 39, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "NOR", 79, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 40, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MFSA", 80, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 41, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "MTSA", 81, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 42, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "SLT", 82, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 43, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "SLTU", 83, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 44, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "DADD", 84, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 45, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "DADDU", 85, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 46, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "DSUB", 86, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 47, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "DSUBU", 87, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 48, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "TGE", 88, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 49, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "TGEU", 89, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 50, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "TLT", 90, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 51, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "TLTU", 91, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 52, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "TEQ", 92, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 53, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 54, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "TNE", 93, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 55, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 56, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "DSLL", 94, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 57, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 58, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "DSRL", 95, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 59, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "DSRA", 96, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 60, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "DSLL32", 97, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 61, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 62, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "DSRL32", 98, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 63, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "DSRA32", 99, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr }
};

const EECoreInstructionUtil::EECoreInstructionInfo_t EECoreInstructionUtil::EECORE_OPCODE_TABLE[64] =
{
	{ 0, EECoreInstructionInfo_t::InstructionType::CLASS, "SPECIAL", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_SPECIAL_LOOKUP },
	{ 1, EECoreInstructionInfo_t::InstructionType::CLASS, "REGIMM", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_REGIMM_LOOKUP },
	{ 2, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "J", 1, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 3, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "JAL", 2, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 4, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "BEQ", 3, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 5, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "BNE", 4, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 6, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "BLEZ", 5, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 7, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "BGTZ", 6, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 8, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "ADDI", 7, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 9, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "ADDIU", 8, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 10, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "SLTI", 9, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 11, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "SLTIU", 10, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 12, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "ANDI", 11, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 13, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "ORI", 12, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 14, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "XORI", 13, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 15, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "LUI", 14, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 16, EECoreInstructionInfo_t::InstructionType::CLASS, "COP0", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_COP0_LOOKUP },
	{ 17, EECoreInstructionInfo_t::InstructionType::CLASS, "COP1", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_COP1_LOOKUP },
	{ 18, EECoreInstructionInfo_t::InstructionType::CLASS, "COP2", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_COP2_LOOKUP },
	{ 19, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 20, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "BEQL", 15, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 21, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "BNEL", 16, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 22, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "BLEZL", 17, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 23, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "BGTZL", 18, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 24, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "DADDI", 19, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 25, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "DADDIU", 20, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 26, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "LDL", 21, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 27, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "LDR", 22, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 28, EECoreInstructionInfo_t::InstructionType::CLASS, "MMI", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_MMI_LOOKUP },
	{ 29, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 30, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "LQ", 23, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 31, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "SQ", 24, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 32, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "LB", 25, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 33, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "LH", 26, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 34, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "LWL", 27, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 35, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "LW", 28, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 36, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "LBU", 29, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 37, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "LHU", 30, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 38, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "LWR", 31, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 39, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "LWU", 32, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 40, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "SB", 33, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 41, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "SH", 34, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 42, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "SWL", 35, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 43, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "SW", 36, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 44, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "SDL", 37, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 45, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "SDR", 38, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 46, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "SWR", 39, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 47, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "CACHE", 40, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 48, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 49, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "LWC1", 41, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 50, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 51, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "PREF", 42, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 52, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 53, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 54, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "LQC2", 43, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 55, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "LD", 44, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 56, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 57, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "SWC1", 45, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 58, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 59, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 60, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 61, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 62, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "SQC2", 46, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 63, EECoreInstructionInfo_t::InstructionType::INSTRUCTION, "SD", 47, EECoreInstructionInfo_t::BranchDelayType::NONE, 0, nullptr }
};