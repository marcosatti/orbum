#include "stdafx.h"

#include "Common/Tables/IOPInstructionTable/IOPInstructionTable.h"
#include "Common/PS2Resources/Types/MIPSInstructionInfo/MIPSInstructionInfo_t.h"
#include "Common/PS2Resources/Types/MIPSInstruction/MIPSInstruction_t.h"

const MIPSInstructionInfo_t * IOPInstructionTable::getInstructionInfo(const MIPSInstruction_t & instruction)
{
	// A dummy class to kickstart the search.
	const MIPSInstructionInfo_t rootInfo = {"root", 0, MIPSInstructionInfo_t::InstructionType::CLASS, "OPCODE", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, IOP_INSTRUCTION_OPCODE_LOOKUP };
	const MIPSInstructionInfo_t * returnInfo = &rootInfo;

	while (returnInfo->mInstructionType == MIPSInstructionInfo_t::InstructionType::CLASS)
	{
		returnInfo = &returnInfo->mLookupFuncion(instruction);
	}

	return returnInfo;
}

const MIPSInstructionInfo_t & IOPInstructionTable::IOP_INSTRUCTION_OPCODE_LOOKUP(const MIPSInstruction_t & instruction)
{
	return IOP_OPCODE_TABLE[instruction.getOpcode()];
}

const MIPSInstructionInfo_t& IOPInstructionTable::IOP_INSTRUCTION_SPECIAL_LOOKUP(const MIPSInstruction_t& instruction)
{
	return IOP_SPECIAL_TABLE[instruction.getRFunct()];
}

const MIPSInstructionInfo_t& IOPInstructionTable::IOP_INSTRUCTION_REGIMM_LOOKUP(const MIPSInstruction_t& instruction)
{
	return IOP_REGIMM_TABLE[instruction.getRRt()];
}

const MIPSInstructionInfo_t& IOPInstructionTable::IOP_INSTRUCTION_COP0_LOOKUP(const MIPSInstruction_t& instruction)
{
	return IOP_COP0_TABLE[instruction.getRRs()];
}

const MIPSInstructionInfo_t& IOPInstructionTable::IOP_INSTRUCTION_COP2_LOOKUP(const MIPSInstruction_t& instruction)
{
	return IOP_COP2_TABLE[instruction.getRFunct()];
}

const MIPSInstructionInfo_t& IOPInstructionTable::IOP_INSTRUCTION_CP2BSC_LOOKUP(const MIPSInstruction_t& instruction)
{
	return IOP_CP2BSC_TABLE[instruction.getRRs()];
}

const MIPSInstructionInfo_t IOPInstructionTable::IOP_INSTRUCTION_UNDEFINED = {"undefined", 0, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, 0, nullptr };

const MIPSInstructionInfo_t IOPInstructionTable::IOP_CP2BSC_TABLE[32] =
{
	{ "CP2BSC", 0, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MFC2", 87, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CP2BSC", 1, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CP2BSC", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "CFC2", 88, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CP2BSC", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CP2BSC", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MTC2", 89, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CP2BSC", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CP2BSC", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "CTC2", 90, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CP2BSC", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CP2BSC", 8, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CP2BSC", 9, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CP2BSC", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CP2BSC", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CP2BSC", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CP2BSC", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CP2BSC", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CP2BSC", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CP2BSC", 16, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CP2BSC", 17, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CP2BSC", 18, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CP2BSC", 19, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CP2BSC", 20, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CP2BSC", 21, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CP2BSC", 22, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CP2BSC", 23, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CP2BSC", 24, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CP2BSC", 25, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CP2BSC", 26, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CP2BSC", 27, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CP2BSC", 28, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CP2BSC", 29, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CP2BSC", 30, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CP2BSC", 31, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
};

const MIPSInstructionInfo_t IOPInstructionTable::IOP_COP2_TABLE[64] =
{
	{ "COP2", 0, MIPSInstructionInfo_t::InstructionType::CLASS, "CP2BSC", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, 0, IOP_INSTRUCTION_CP2BSC_LOOKUP },
	{ "COP2", 1, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RTPS", 66, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "NCLIP", 67, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 8, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 9, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "OP", 68, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 16, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "DPCS", 69, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 17, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "INTPL", 70, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 18, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MVMVA", 71, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 19, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "NCDS", 72, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 20, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "CDP", 73, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 21, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 22, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "NCDT", 74, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 23, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 24, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 25, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 26, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 27, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "NCCS", 75, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 28, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "CC", 76, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 29, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 30, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "NCS", 77, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 31, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 32, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "NCT", 78, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 33, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 34, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 35, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 36, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 37, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 38, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 39, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 40, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SQR", 79, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 41, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "DCPL", 80, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 42, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "DPCT", 81, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 43, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 44, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 45, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "AVSZ3", 82, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 46, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "AVSZ4", 83, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 47, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 48, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RTPT", 84, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 49, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 50, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 51, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 52, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 53, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 54, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 55, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 56, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 57, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 58, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 59, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 60, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 61, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "GPF", 85, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 62, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "GPL", 86, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP2", 63, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
};

const MIPSInstructionInfo_t IOPInstructionTable::IOP_COP0_TABLE[32] =
{
	{ "COP0", 0, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MFC0", 61, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 1, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "CFC0", 62, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MTC0", 63, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "CTC0", 64, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 8, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 9, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 16, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RFE", 65, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 17, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 18, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 19, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 20, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 21, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 22, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 23, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 24, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 25, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 26, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 27, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 28, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 29, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 30, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 31, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
};

const MIPSInstructionInfo_t IOPInstructionTable::IOP_REGIMM_TABLE[32] =
{ 
	{ "REGIMM", 0, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BLTZ", 57, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R3000_BRANCH, nullptr },
	{ "REGIMM", 1, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BGEZ", 58, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R3000_BRANCH, nullptr },
	{ "REGIMM", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "REGIMM", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "REGIMM", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "REGIMM", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "REGIMM", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "REGIMM", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "REGIMM", 8, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "REGIMM", 9, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "REGIMM", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "REGIMM", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "REGIMM", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "REGIMM", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "REGIMM", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "REGIMM", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "REGIMM", 16, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BLTZAL", 59, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R3000_BRANCH, nullptr },
	{ "REGIMM", 17, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BGEZAL", 60, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R3000_BRANCH, nullptr },
	{ "REGIMM", 18, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "REGIMM", 19, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "REGIMM", 20, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "REGIMM", 21, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "REGIMM", 22, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "REGIMM", 23, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "REGIMM", 24, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "REGIMM", 25, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "REGIMM", 26, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "REGIMM", 27, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "REGIMM", 28, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "REGIMM", 29, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "REGIMM", 30, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "REGIMM", 31, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
};

const MIPSInstructionInfo_t IOPInstructionTable::IOP_SPECIAL_TABLE[64] =
{ 
	{ "SPECIAL", 0, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SLL", 29, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 1, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SRL", 30, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SRA", 31, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SLLV", 32, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SRLV", 33, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SRAV", 34, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 8, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "JR", 35, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 9, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "JALR", 36, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SYSCALL", 37, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BREAK", 38, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 16, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MFHI", 39, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 17, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MTHI", 40, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 18, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MFLO", 41, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 19, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MTLO", 42, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 20, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 21, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 22, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 23, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 24, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MULT", 43, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_MULTIPLY, nullptr },
	{ "SPECIAL", 25, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MULTU", 44, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_MULTIPLY, nullptr },
	{ "SPECIAL", 26, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "DIV", 45, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DIVIDE, nullptr },
	{ "SPECIAL", 27, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "DIVU", 46, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DIVIDE, nullptr },
	{ "SPECIAL", 28, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 29, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 30, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 31, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 32, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "ADD", 47, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 33, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "ADDU", 48, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 34, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SUB", 49, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 35, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SUBU", 50, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 36, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "AND", 51, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 37, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "OR", 52, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 38, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "XOR", 53, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 39, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "NOR", 54, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 40, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 41, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 42, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SLT", 55, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 43, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SLTU", 56, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 44, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 45, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 46, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 47, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 48, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 49, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 50, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 51, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 52, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 53, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 54, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 55, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 56, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 57, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 58, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 59, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 60, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 61, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 62, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "SPECIAL", 63, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
};

const MIPSInstructionInfo_t IOPInstructionTable::IOP_OPCODE_TABLE[64] =
{
	{ "OPCODE", 0, MIPSInstructionInfo_t::InstructionType::CLASS, "SPECIAL", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, 0, IOP_INSTRUCTION_SPECIAL_LOOKUP },
	{ "OPCODE", 1, MIPSInstructionInfo_t::InstructionType::CLASS, "REGIMM", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, 0, IOP_INSTRUCTION_REGIMM_LOOKUP },
	{ "OPCODE", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "J", 1, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "JAL", 2, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BEQ", 3, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R3000_BRANCH, nullptr },
	{ "OPCODE", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BNE", 4, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R3000_BRANCH, nullptr },
	{ "OPCODE", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BLEZ", 5, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R3000_BRANCH, nullptr },
	{ "OPCODE", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BGTZ", 6, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R3000_BRANCH, nullptr },
	{ "OPCODE", 8, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "ADDI", 7, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 9, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "ADDIU", 8, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SLTI", 9, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SLTIU", 10, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "ANDI", 11, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "ORI", 12, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "XORI", 13, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "LUI", 14, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 16, MIPSInstructionInfo_t::InstructionType::CLASS, "COP0", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, 0, IOP_INSTRUCTION_COP0_LOOKUP },
	{ "OPCODE", 17, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 18, MIPSInstructionInfo_t::InstructionType::CLASS, "COP2", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, 0, IOP_INSTRUCTION_COP2_LOOKUP },
	{ "OPCODE", 19, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 20, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 21, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 22, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 23, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 24, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 25, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 26, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 27, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 28, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 29, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 30, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 31, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 32, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "LB", 15, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_LOAD, nullptr },
	{ "OPCODE", 33, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "LH", 16, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_LOAD, nullptr },
	{ "OPCODE", 34, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "LWL", 17, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_LOAD, nullptr },
	{ "OPCODE", 35, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "LW", 18, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_LOAD, nullptr },
	{ "OPCODE", 36, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "LBU", 19, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_LOAD, nullptr },
	{ "OPCODE", 37, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "LHU", 20, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_LOAD, nullptr },
	{ "OPCODE", 38, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "LWR", 21, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_LOAD, nullptr },
	{ "OPCODE", 39, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 40, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SB", 22, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_STORE, nullptr },
	{ "OPCODE", 41, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SH", 23, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_STORE, nullptr },
	{ "OPCODE", 42, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SWL", 24, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_STORE, nullptr },
	{ "OPCODE", 43, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SW", 25, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_STORE, nullptr },
	{ "OPCODE", 44, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 45, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 46, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SWR", 26, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_STORE, nullptr },
	{ "OPCODE", 47, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 48, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 49, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 50, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "LWC2", 27, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_LOAD, nullptr },
	{ "OPCODE", 51, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 52, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 53, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 54, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 55, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 56, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 57, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 58, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SWC2", 28, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_STORE, nullptr },
	{ "OPCODE", 59, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 60, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 61, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 62, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
	{ "OPCODE", 63, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr },
};