#include "stdafx.h"

#include "R5900InstructionUtil.h"

const R5900InstructionUtil::R5900InstructionInfo_t & R5900InstructionUtil::getInstructionInfo(const MIPSInstruction_t & instruction)
{
	const R5900InstructionInfo_t rootInfo = { 0, R5900InstructionInfo_t::InstructionType::CLASS, "OPCODE", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, R5900_INSTRUCTION_OPCODE_LOOKUP };
	const R5900InstructionInfo_t * returnInfo = &rootInfo;
	while (returnInfo->mInstructionType == R5900InstructionInfo_t::InstructionType::CLASS)
	{
		returnInfo = &returnInfo->mLookupFuncion(instruction);
	}

	return *returnInfo;
}

const R5900InstructionUtil::R5900InstructionInfo_t & R5900InstructionUtil::R5900_INSTRUCTION_OPCODE_LOOKUP(const MIPSInstruction_t & instruction)
{
	return R5900_OPCODE_TABLE[instruction.getOpcode()];
}

const R5900InstructionUtil::R5900InstructionInfo_t& R5900InstructionUtil::R5900_INSTRUCTION_SPECIAL_LOOKUP(const MIPSInstruction_t& instruction)
{
	return R5900_SPECIAL_TABLE[instruction.getRFunct()];
}

const R5900InstructionUtil::R5900InstructionInfo_t& R5900InstructionUtil::R5900_INSTRUCTION_REGIMM_LOOKUP(const MIPSInstruction_t& instruction)
{
	return R5900_REGIMM_TABLE[instruction.getRRt()];
}

const R5900InstructionUtil::R5900InstructionInfo_t& R5900InstructionUtil::R5900_INSTRUCTION_MMI_LOOKUP(const MIPSInstruction_t& instruction)
{
	return R5900_MMI_TABLE[instruction.getRFunct()];
}

const R5900InstructionUtil::R5900InstructionInfo_t& R5900InstructionUtil::R5900_INSTRUCTION_MMI0_LOOKUP(const MIPSInstruction_t& instruction)
{
	return R5900_MMI0_TABLE[instruction.getRShamt()];
}

const R5900InstructionUtil::R5900InstructionInfo_t& R5900InstructionUtil::R5900_INSTRUCTION_MMI1_LOOKUP(const MIPSInstruction_t& instruction)
{
	return R5900_MMI1_TABLE[instruction.getRShamt()];
}

const R5900InstructionUtil::R5900InstructionInfo_t& R5900InstructionUtil::R5900_INSTRUCTION_MMI2_LOOKUP(const MIPSInstruction_t& instruction)
{
	return R5900_MMI2_TABLE[instruction.getRShamt()];
}

const R5900InstructionUtil::R5900InstructionInfo_t& R5900InstructionUtil::R5900_INSTRUCTION_MMI3_LOOKUP(const MIPSInstruction_t& instruction)
{
	return R5900_MMI3_TABLE[instruction.getRShamt()];
}

const R5900InstructionUtil::R5900InstructionInfo_t& R5900InstructionUtil::R5900_INSTRUCTION_COP0_LOOKUP(const MIPSInstruction_t& instruction)
{
	return R5900_COP0_TABLE[instruction.getRRs()];
}

const R5900InstructionUtil::R5900InstructionInfo_t& R5900InstructionUtil::R5900_INSTRUCTION_BC0_LOOKUP(const MIPSInstruction_t& instruction)
{
	return R5900_BC0_TABLE[instruction.getRRt()];
}

const R5900InstructionUtil::R5900InstructionInfo_t& R5900InstructionUtil::R5900_INSTRUCTION_C0_LOOKUP(const MIPSInstruction_t& instruction)
{
	return R5900_C0_TABLE[instruction.getRFunct()];
}

const R5900InstructionUtil::R5900InstructionInfo_t& R5900InstructionUtil::R5900_INSTRUCTION_COP1_LOOKUP(const MIPSInstruction_t& instruction)
{
	return R5900_COP1_TABLE[instruction.getRRs()];
}

const R5900InstructionUtil::R5900InstructionInfo_t& R5900InstructionUtil::R5900_INSTRUCTION_BC1_LOOKUP(const MIPSInstruction_t& instruction)
{
	return R5900_BC1_TABLE[instruction.getRRt()];
}

const R5900InstructionUtil::R5900InstructionInfo_t& R5900InstructionUtil::R5900_INSTRUCTION_S_LOOKUP(const MIPSInstruction_t& instruction)
{
	return R5900_S_TABLE[instruction.getRFunct()];
}

const R5900InstructionUtil::R5900InstructionInfo_t& R5900InstructionUtil::R5900_INSTRUCTION_W_LOOKUP(const MIPSInstruction_t& instruction)
{
	return R5900_W_TABLE[instruction.getRFunct()];
}

const R5900InstructionUtil::R5900InstructionInfo_t& R5900InstructionUtil::R5900_INSTRUCTION_COP2_LOOKUP(const MIPSInstruction_t& instruction)
{
	return R5900_INSTRUCTION_UNDEFINED;
}

const R5900InstructionUtil::R5900InstructionInfo_t R5900InstructionUtil::R5900_INSTRUCTION_UNDEFINED = { 0, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr };

const R5900InstructionUtil::R5900InstructionInfo_t R5900InstructionUtil::R5900_W_TABLE[64] =
{
	{ 0, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 1, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 2, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 3, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 4, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 5, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 6, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 7, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 8, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 9, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 10, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 11, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 12, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 13, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 14, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 15, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 16, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 17, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 18, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 19, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 20, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 21, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 22, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 23, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 24, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 25, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 26, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 27, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 28, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 29, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 30, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 31, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 32, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "CVTS", 259, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 33, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 34, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 35, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 36, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 37, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 38, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 39, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 40, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 41, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 42, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 43, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 44, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 45, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 46, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 47, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 48, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 49, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 50, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 51, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 52, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 53, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 54, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 55, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 56, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 57, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 58, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 59, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 60, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 61, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 62, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 63, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr }
};

const R5900InstructionUtil::R5900InstructionInfo_t R5900InstructionUtil::R5900_S_TABLE[64] =
{
	{ 0, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "ADD", 236, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 1, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "SUB", 237, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 2, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MUL", 238, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 3, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "DIV", 239, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 4, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "SQRT", 240, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 5, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "ABS", 241, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 6, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MOV", 242, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 7, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "NEG", 243, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 8, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 9, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 10, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 11, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 12, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 13, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 14, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 15, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 16, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 17, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 18, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 19, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 20, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 21, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RSQRT", 244, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 22, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 23, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "ADDA", 245, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 24, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "SUBA", 246, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 25, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MULA", 247, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 26, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 27, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MADD", 248, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 28, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MSUB", 249, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 29, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MADDA", 250, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 30, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MSUBA", 251, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 31, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 32, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 33, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 34, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 35, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "CVTW", 252, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 36, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 37, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 38, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 39, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MAX", 253, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 40, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MIN", 254, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 41, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 42, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 43, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 44, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 45, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 46, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 47, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "C.F", 255, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 48, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 49, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "C.EQ", 256, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 50, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 51, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "C.LT", 257, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 52, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 53, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "C.LE", 258, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 54, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 55, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 56, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 57, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 58, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 59, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 60, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 61, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 62, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 63, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr }
};

const R5900InstructionUtil::R5900InstructionInfo_t R5900InstructionUtil::R5900_BC1_TABLE[32] =
{
	{ 0, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "BC1F", 232, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 1, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "BC1T", 233, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 2, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "BC1FL", 234, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 3, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "BC1TL", 235, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 4, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 5, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 6, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 7, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 8, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 9, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 10, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 11, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 12, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 13, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 14, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 15, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 16, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 17, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 18, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 19, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 20, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 21, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 22, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 23, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 24, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 25, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 26, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 27, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 28, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 29, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 30, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 31, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr }
};

const R5900InstructionUtil::R5900InstructionInfo_t R5900InstructionUtil::R5900_COP1_TABLE[32] =
{
	{ 0, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MFC1", 228, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 1, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 2, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "CFC1", 229, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 3, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 4, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MTC1", 230, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 5, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 6, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "CTC1", 231, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 7, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 8, R5900InstructionInfo_t::InstructionType::CLASS, "BC1", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, R5900_INSTRUCTION_BC1_LOOKUP },
	{ 9, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 10, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 11, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 12, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 13, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 14, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 15, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 16, R5900InstructionInfo_t::InstructionType::CLASS, "S", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, R5900_INSTRUCTION_S_LOOKUP },
	{ 17, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 18, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 19, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 20, R5900InstructionInfo_t::InstructionType::CLASS, "W", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, R5900_INSTRUCTION_W_LOOKUP },
	{ 21, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 22, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 23, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 24, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 25, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 26, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 27, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 28, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 29, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 30, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 31, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },

};

const R5900InstructionUtil::R5900InstructionInfo_t R5900InstructionUtil::R5900_C0_TABLE[64] =
{
	{ 0, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 1, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "TLBR", 221, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 2, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "TLBWI", 222, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 3, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 4, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 5, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 6, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "TLBWR", 223, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 7, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 8, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "TLBP", 224, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 9, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 10, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 11, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 12, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 13, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 14, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 15, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 16, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 17, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 18, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 19, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 20, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 21, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 22, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 23, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 24, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "ERET", 225, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 25, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 26, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 27, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 28, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 29, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 30, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 31, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 32, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 33, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 34, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 35, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 36, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 37, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 38, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 39, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 40, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 41, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 42, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 43, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 44, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 45, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 46, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 47, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 48, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 49, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 50, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 51, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 52, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 53, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 54, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 55, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 56, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "EI", 226, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 57, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "DI", 227, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 58, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 59, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 60, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 61, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 62, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 63, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr }
};

const R5900InstructionUtil::R5900InstructionInfo_t R5900InstructionUtil::R5900_BC0_TABLE[32] =
{
	{ 0, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "BC0F", 217, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 1, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "BC0T", 218, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 2, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "BC0FL", 219, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 3, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "BC0TL", 220, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 4, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 5, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 6, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 7, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 8, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 9, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 10, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 11, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 12, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 13, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 14, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 15, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 16, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 17, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 18, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 19, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 20, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 21, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 22, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 23, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 24, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 25, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 26, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 27, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 28, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 29, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 30, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 31, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr }
};

const R5900InstructionUtil::R5900InstructionInfo_t R5900InstructionUtil::R5900_COP0_TABLE[32] =
{
	{ 0, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MF0", 215, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 1, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 2, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 3, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 4, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MT0", 216, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 5, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 6, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 7, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 8, R5900InstructionInfo_t::InstructionType::CLASS, "BC0", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, R5900_INSTRUCTION_BC0_LOOKUP },
	{ 9, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 10, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 11, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 12, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 13, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 14, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 15, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 16, R5900InstructionInfo_t::InstructionType::CLASS, "C0", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, R5900_INSTRUCTION_C0_LOOKUP },
	{ 17, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 18, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 19, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 20, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 21, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 22, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 23, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 24, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 25, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 26, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 27, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 28, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 29, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 30, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 31, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr }
};

const R5900InstructionUtil::R5900InstructionInfo_t R5900InstructionUtil::R5900_MMI3_TABLE[32] =
{
	{ 0, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PMADDUW", 202, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 1, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 2, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 3, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PSRAVW", 203, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 4, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 5, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 6, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 7, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 8, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PMTHI", 204, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 9, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PMTLO", 205, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 10, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PINTEH", 206, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 11, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 12, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PMULTUW", 207, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 13, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PDIVUW", 208, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 14, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PCPYUD", 209, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 15, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 16, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 17, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 18, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "POR", 210, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 19, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PNOR", 211, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 20, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 21, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 22, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 23, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 24, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 25, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 26, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PEXCH", 212, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 27, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PCPYH", 213, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 28, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 29, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 30, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PEXCW", 214, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 31, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr }
};

const R5900InstructionUtil::R5900InstructionInfo_t R5900InstructionUtil::R5900_MMI2_TABLE[32] =
{
	{ 0, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PMADDW", 180, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 1, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 2, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PSLLVW", 181, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 3, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PSRLVW", 182, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 4, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PMSUBW", 183, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 5, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 6, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 7, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 8, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PMFHI", 184, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 9, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PMFLO", 185, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 10, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PINTH", 186, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 11, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 12, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PMULTW", 187, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 13, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PDIVW", 188, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 14, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PCPYLD", 189, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 15, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 16, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PMADDH", 190, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 17, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PHMADH", 191, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 18, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PAND", 192, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 19, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PXOR", 193, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 20, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PMSUBH", 194, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 21, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PHMSBH", 195, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 22, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 23, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 24, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 25, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 26, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PEXEH", 196, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 27, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PREVH", 197, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 28, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PMULTH", 198, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 29, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PDIVBW", 199, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 30, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PEXEW", 200, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 31, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PROT3W", 201, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr }
};

const R5900InstructionUtil::R5900InstructionInfo_t R5900InstructionUtil::R5900_MMI1_TABLE[32] =
{
	{ 0, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 1, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PABSW", 162, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 2, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PCEQW", 163, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 3, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PMINW", 164, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 4, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PADSBH", 165, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 5, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PABSH", 166, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 6, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PCEQH", 167, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 7, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PMINH", 168, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 8, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 9, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 10, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PCEQB", 169, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 11, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 12, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 13, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 14, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 15, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 16, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PADDUW", 170, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 17, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PSUBUW", 171, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 18, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PEXTUW", 172, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 19, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 20, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PADDUH", 173, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 21, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PSUBUH", 174, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 22, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PEXTUH", 175, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 23, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 24, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PADDUB", 176, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 25, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PSUBUB", 177, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 26, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PEXTUB", 178, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 27, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "QFSRV", 179, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 28, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 29, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 30, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 31, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr }
};

const R5900InstructionUtil::R5900InstructionInfo_t R5900InstructionUtil::R5900_MMI0_TABLE[32] =
{
	{ 0, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PADDW", 137, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 1, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PSUBW", 138, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 2, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PCGTW", 139, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 3, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PMAXW", 140, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 4, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PADDH", 141, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 5, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PSUBH", 142, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 6, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PCGTH", 143, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 7, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PMAXH", 144, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 8, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PADDB", 145, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 9, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PSUBB", 146, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 10, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PCGTB", 147, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 11, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 12, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 13, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 14, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 15, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 16, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PADDSW", 148, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 17, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PSUBSW", 149, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 18, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PEXTLW", 150, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 19, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PPACW", 151, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 20, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PADDSH", 152, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 21, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PSUBSH", 153, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 22, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PEXTLH", 154, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 23, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PPACH", 155, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 24, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PADDSB", 156, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 25, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PSUBSB", 157, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 26, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PEXTLB", 158, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 27, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PPACB", 159, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 28, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 29, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 30, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PEXT5", 160, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 31, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PPAC5", 161, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr }
};

const R5900InstructionUtil::R5900InstructionInfo_t R5900InstructionUtil::R5900_MMI_TABLE[64] =
{
	{ 0, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MADD", 116, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 1, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MADDU", 117, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 2, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 3, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 4, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PLZCW", 118, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 5, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 6, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 7, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 8, R5900InstructionInfo_t::InstructionType::CLASS, "MMI0", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, R5900_INSTRUCTION_MMI0_LOOKUP },
	{ 9, R5900InstructionInfo_t::InstructionType::CLASS, "MMI2", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, R5900_INSTRUCTION_MMI2_LOOKUP },
	{ 10, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 11, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 12, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 13, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 14, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 15, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 16, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MHFI1", 119, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 17, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MTHI1", 120, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 18, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MFLO1", 121, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 19, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MTLO1", 122, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 20, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 21, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 22, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 23, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 24, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MULT1", 123, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 25, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MULTU1", 124, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 26, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "DIV1", 125, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 27, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "DIVU1", 126, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 28, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 29, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 30, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 31, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 32, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MADD1", 127, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 33, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MADDU1", 128, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 34, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 35, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 36, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 37, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 38, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 39, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 40, R5900InstructionInfo_t::InstructionType::CLASS, "MMI1", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, R5900_INSTRUCTION_MMI1_LOOKUP },
	{ 41, R5900InstructionInfo_t::InstructionType::CLASS, "MMI3", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, R5900_INSTRUCTION_MMI3_LOOKUP },
	{ 42, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 43, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 44, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 45, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 46, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 47, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 48, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PMFHL", 129, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 49, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PMTHL", 130, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 50, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 51, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 52, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PSLLH", 131, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 53, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 54, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PSRLH", 132, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 55, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PSRAH", 133, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 56, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 57, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 58, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 59, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 60, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PSLLW", 134, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 61, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 62, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PSRLW", 135, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 63, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PSRAW", 136, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },

};

const R5900InstructionUtil::R5900InstructionInfo_t R5900InstructionUtil::R5900_REGIMM_TABLE[32] =
{
	{ 0, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "BLTZ", 100, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 1, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "BGEZ", 101, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 2, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "BLTZL", 102, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 3, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "BGEZL", 103, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 4, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 5, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 6, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 7, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 8, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "TGEI", 104, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 9, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "TGEIU", 105, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 10, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "TLTI", 106, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 11, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "TLTIU", 107, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 12, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "TEQI", 108, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 13, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 14, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "TNEI", 109, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 15, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 16, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "BLTZAL", 110, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 17, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "BGEZAL", 111, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 18, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "BLTZALL", 112, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 19, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "BGEZALL", 113, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 20, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 21, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 22, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 23, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 24, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MTSAB", 114, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 25, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MTSAH", 115, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 26, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 27, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 28, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 29, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 30, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 31, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr }
};

const R5900InstructionUtil::R5900InstructionInfo_t R5900InstructionUtil::R5900_SPECIAL_TABLE[64] =
{
	{ 0, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "SLL", 48, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 1, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 2, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "SRL", 49, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 3, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "SRA", 50, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 4, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "SLLV", 51, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 5, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 6, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "SRLV", 52, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 7, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "SRAV", 53, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 8, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "JR", 54, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 9, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "JALR", 55, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 10, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MOVZ", 56, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 11, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MOVN", 57, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 12, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "SYSCALL", 58, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 13, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "BREAK", 59, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 14, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 15, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "SYNC", 60, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 16, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MFHI", 61, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 17, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MTHI", 62, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 18, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MFLO", 63, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 19, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MTLO", 64, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 20, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "DSLLV", 65, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 21, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 22, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "DSRLV", 66, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 23, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "DSRAV", 67, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 24, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MULT", 68, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 25, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MULTU", 69, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 26, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "DIV", 70, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 27, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "DIVU", 71, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 28, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 29, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 30, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 31, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 32, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "ADD", 72, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 33, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "ADDU", 73, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 34, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "SUB", 74, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 35, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "SUBU", 75, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 36, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "AND", 76, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 37, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "OR", 77, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 38, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "XOR", 78, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 39, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "NOR", 79, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 40, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MFSA", 80, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 41, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "MTSA", 81, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 42, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "SLT", 82, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 43, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "SLTU", 83, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 44, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "DADD", 84, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 45, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "DADDU", 85, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 46, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "DSUB", 86, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 47, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "DSUBU", 87, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 48, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "TGE", 88, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 49, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "TGEU", 89, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 50, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "TLT", 90, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 51, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "TLTU", 91, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 52, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "TEQ", 92, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 53, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 54, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "TNE", 93, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 55, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 56, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "DSLL", 94, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 57, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 58, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "DSRL", 95, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 59, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "DSRA", 96, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 60, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "DSLL32", 97, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 61, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 62, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "DSRL32", 98, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 63, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "DSRA32", 99, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr }
};

const R5900InstructionUtil::R5900InstructionInfo_t R5900InstructionUtil::R5900_OPCODE_TABLE[64] =
{
	{ 0, R5900InstructionInfo_t::InstructionType::CLASS, "SPECIAL", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, R5900_INSTRUCTION_SPECIAL_LOOKUP },
	{ 1, R5900InstructionInfo_t::InstructionType::CLASS, "REGIMM", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, R5900_INSTRUCTION_REGIMM_LOOKUP },
	{ 2, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "J", 1, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 3, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "JAL", 2, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 4, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "BEQ", 3, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 5, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "BNE", 4, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 6, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "BLEZ", 5, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 7, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "BGTZ", 6, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 8, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "ADDI", 7, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 9, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "ADDIU", 8, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 10, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "SLTI", 9, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 11, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "SLTIU", 10, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 12, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "ANDI", 11, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 13, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "ORI", 12, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 14, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "XORI", 13, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 15, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "LUI", 14, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 16, R5900InstructionInfo_t::InstructionType::CLASS, "COP0", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, R5900_INSTRUCTION_COP0_LOOKUP },
	{ 17, R5900InstructionInfo_t::InstructionType::CLASS, "COP1", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, R5900_INSTRUCTION_COP1_LOOKUP },
	{ 18, R5900InstructionInfo_t::InstructionType::CLASS, "COP2", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, R5900_INSTRUCTION_COP2_LOOKUP },
	{ 19, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 20, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "BEQL", 15, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 21, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "BNEL", 16, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 22, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "BLEZL", 17, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 23, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "BGTZL", 18, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 24, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "DADDI", 19, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 25, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "DADDIU", 20, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 26, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "LDL", 21, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 27, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "LDR", 22, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 28, R5900InstructionInfo_t::InstructionType::CLASS, "MMI", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, R5900_INSTRUCTION_MMI_LOOKUP },
	{ 29, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 30, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "LQ", 23, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 31, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "SQ", 24, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 32, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "LB", 25, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 33, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "LH", 26, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 34, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "LWL", 27, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 35, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "LW", 28, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 36, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "LBU", 29, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 37, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "LHU", 30, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 38, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "LWR", 31, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 39, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "LWU", 32, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 40, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "SB", 33, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 41, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "SH", 34, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 42, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "SWL", 35, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 43, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "SW", 36, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 44, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "SDL", 37, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 45, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "SDR", 38, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 46, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "SWR", 39, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 47, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "CACHE", 40, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 48, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 49, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "LWC1", 41, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 50, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 51, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "PREF", 42, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 52, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 53, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 54, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "LQC2", 43, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 55, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "LD", 44, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 56, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 57, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "SWC1", 45, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 58, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 59, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 60, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 61, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 62, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "SQC2", 46, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ 63, R5900InstructionInfo_t::InstructionType::INSTRUCTION, "SD", 47, R5900InstructionInfo_t::BranchDelayType::NONE, 0, nullptr }
};