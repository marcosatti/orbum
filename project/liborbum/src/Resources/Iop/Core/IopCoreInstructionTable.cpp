#include "Resources/Iop/Core/IopCoreInstructionTable.hpp"

#include "Resources/Iop/Core/IopCoreInstruction.hpp"

constexpr IOPCoreInstructionTable::IOPCoreInstructionInfo_t IOPCoreInstructionTable::IOPCORE_OPCODE_TABLE[64];
constexpr IOPCoreInstructionTable::IOPCoreInstructionInfo_t IOPCoreInstructionTable::IOPCORE_SPECIAL_TABLE[64];
constexpr IOPCoreInstructionTable::IOPCoreInstructionInfo_t IOPCoreInstructionTable::IOPCORE_REGIMM_TABLE[32];
constexpr IOPCoreInstructionTable::IOPCoreInstructionInfo_t IOPCoreInstructionTable::IOPCORE_COP0_TABLE[32];
constexpr IOPCoreInstructionTable::IOPCoreInstructionInfo_t IOPCoreInstructionTable::IOPCORE_COP2_TABLE[64];
constexpr IOPCoreInstructionTable::IOPCoreInstructionInfo_t IOPCoreInstructionTable::IOPCORE_CP2BSC_TABLE[32];

const IOPCoreInstructionTable::IOPCoreInstructionInfo_t * IOPCoreInstructionTable::IOPCORE_INSTRUCTION_OPCODE_LOOKUP(const IopCoreInstruction * instruction)
{
	return &IOPCORE_OPCODE_TABLE[instruction->opcode()];
}

const IOPCoreInstructionTable::IOPCoreInstructionInfo_t * IOPCoreInstructionTable::IOPCORE_INSTRUCTION_SPECIAL_LOOKUP(const IopCoreInstruction * instruction)
{
	return &IOPCORE_SPECIAL_TABLE[instruction->funct()];
}

const IOPCoreInstructionTable::IOPCoreInstructionInfo_t * IOPCoreInstructionTable::IOPCORE_INSTRUCTION_REGIMM_LOOKUP(const IopCoreInstruction * instruction)
{
	return &IOPCORE_REGIMM_TABLE[instruction->rt()];
}

const IOPCoreInstructionTable::IOPCoreInstructionInfo_t * IOPCoreInstructionTable::IOPCORE_INSTRUCTION_COP0_LOOKUP(const IopCoreInstruction * instruction)
{
	return &IOPCORE_COP0_TABLE[instruction->rs()];
}

const IOPCoreInstructionTable::IOPCoreInstructionInfo_t * IOPCoreInstructionTable::IOPCORE_INSTRUCTION_COP2_LOOKUP(const IopCoreInstruction * instruction)
{
	return &IOPCORE_COP2_TABLE[instruction->funct()];
}

const IOPCoreInstructionTable::IOPCoreInstructionInfo_t * IOPCoreInstructionTable::IOPCORE_INSTRUCTION_CP2BSC_LOOKUP(const IopCoreInstruction * instruction)
{
	return &IOPCORE_CP2BSC_TABLE[instruction->rs()];
}

const IOPCoreInstructionTable::IOPCoreInstructionInfo_t * IOPCoreInstructionTable::getInfo(const IopCoreInstruction * instruction)
{
	// A dummy class to kickstart the search.
	const IOPCoreInstructionInfo_t rootInfo = { "root", 0, MIPSInstructionInfo_t::InstructionType::CLASS, "OPCODE", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, IOPCORE_INSTRUCTION_OPCODE_LOOKUP, 0 };
	const IOPCoreInstructionInfo_t * returnInfo = &rootInfo;

	while (returnInfo->mMIPSInstructionInfo.mInstructionType == MIPSInstructionInfo_t::InstructionType::CLASS)
	{
		returnInfo = returnInfo->mLookupFuncion(instruction);
	}

	return returnInfo;
}