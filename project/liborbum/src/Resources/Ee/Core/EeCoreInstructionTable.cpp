#include "Resources/Ee/Core/EeCoreInstructionTable.hpp"

#include "Resources/Ee/Core/EeCoreInstruction.hpp"

constexpr EECoreInstructionTable::EECoreInstructionInfo_t EECoreInstructionTable::EECORE_OPCODE_TABLE[64];
constexpr EECoreInstructionTable::EECoreInstructionInfo_t EECoreInstructionTable::EECORE_SPECIAL_TABLE[64];
constexpr EECoreInstructionTable::EECoreInstructionInfo_t EECoreInstructionTable::EECORE_REGIMM_TABLE[32];
constexpr EECoreInstructionTable::EECoreInstructionInfo_t EECoreInstructionTable::EECORE_MMI_TABLE[64];
constexpr EECoreInstructionTable::EECoreInstructionInfo_t EECoreInstructionTable::EECORE_MMI0_TABLE[32];
constexpr EECoreInstructionTable::EECoreInstructionInfo_t EECoreInstructionTable::EECORE_MMI1_TABLE[32];
constexpr EECoreInstructionTable::EECoreInstructionInfo_t EECoreInstructionTable::EECORE_MMI2_TABLE[32];
constexpr EECoreInstructionTable::EECoreInstructionInfo_t EECoreInstructionTable::EECORE_MMI3_TABLE[32];
constexpr EECoreInstructionTable::EECoreInstructionInfo_t EECoreInstructionTable::EECORE_COP0_TABLE[32];
constexpr EECoreInstructionTable::EECoreInstructionInfo_t EECoreInstructionTable::EECORE_BC0_TABLE[32];
constexpr EECoreInstructionTable::EECoreInstructionInfo_t EECoreInstructionTable::EECORE_C0_TABLE[64];
constexpr EECoreInstructionTable::EECoreInstructionInfo_t EECoreInstructionTable::EECORE_COP1_TABLE[32];
constexpr EECoreInstructionTable::EECoreInstructionInfo_t EECoreInstructionTable::EECORE_BC1_TABLE[32];
constexpr EECoreInstructionTable::EECoreInstructionInfo_t EECoreInstructionTable::EECORE_S_TABLE[64];
constexpr EECoreInstructionTable::EECoreInstructionInfo_t EECoreInstructionTable::EECORE_W_TABLE[64];
constexpr EECoreInstructionTable::EECoreInstructionInfo_t EECoreInstructionTable::EECORE_COP2_TABLE[2];
constexpr EECoreInstructionTable::EECoreInstructionInfo_t EECoreInstructionTable::EECORE_CO0_TABLE[16];
constexpr EECoreInstructionTable::EECoreInstructionInfo_t EECoreInstructionTable::EECORE_BC2_TABLE[32];
constexpr EECoreInstructionTable::EECoreInstructionInfo_t EECoreInstructionTable::EECORE_CO1_TABLE[64];
constexpr EECoreInstructionTable::EECoreInstructionInfo_t EECoreInstructionTable::EECORE_VEXT0_TABLE[32];
constexpr EECoreInstructionTable::EECoreInstructionInfo_t EECoreInstructionTable::EECORE_VEXT1_TABLE[32];
constexpr EECoreInstructionTable::EECoreInstructionInfo_t EECoreInstructionTable::EECORE_VEXT2_TABLE[32];
constexpr EECoreInstructionTable::EECoreInstructionInfo_t EECoreInstructionTable::EECORE_VEXT3_TABLE[32];

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_OPCODE_LOOKUP(const EeCoreInstruction * instruction)
{
	return &EECORE_OPCODE_TABLE[instruction->opcode()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_SPECIAL_LOOKUP(const EeCoreInstruction * instruction)
{
	return &EECORE_SPECIAL_TABLE[instruction->funct()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_REGIMM_LOOKUP(const EeCoreInstruction * instruction)
{
	return &EECORE_REGIMM_TABLE[instruction->rt()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_MMI_LOOKUP(const EeCoreInstruction * instruction)
{
	return &EECORE_MMI_TABLE[instruction->funct()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_MMI0_LOOKUP(const EeCoreInstruction * instruction)
{
	return &EECORE_MMI0_TABLE[instruction->shamt()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_MMI1_LOOKUP(const EeCoreInstruction * instruction)
{
	return &EECORE_MMI1_TABLE[instruction->shamt()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_MMI2_LOOKUP(const EeCoreInstruction * instruction)
{
	return &EECORE_MMI2_TABLE[instruction->shamt()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_MMI3_LOOKUP(const EeCoreInstruction * instruction)
{
	return &EECORE_MMI3_TABLE[instruction->shamt()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_COP0_LOOKUP(const EeCoreInstruction * instruction)
{
	return &EECORE_COP0_TABLE[instruction->rs()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_BC0_LOOKUP(const EeCoreInstruction * instruction)
{
	return &EECORE_BC0_TABLE[instruction->rt()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_C0_LOOKUP(const EeCoreInstruction * instruction)
{
	return &EECORE_C0_TABLE[instruction->funct()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_COP1_LOOKUP(const EeCoreInstruction * instruction)
{
	return &EECORE_COP1_TABLE[instruction->rs()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_BC1_LOOKUP(const EeCoreInstruction * instruction)
{
	return &EECORE_BC1_TABLE[instruction->rt()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_S_LOOKUP(const EeCoreInstruction * instruction)
{
	return &EECORE_S_TABLE[instruction->funct()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_W_LOOKUP(const EeCoreInstruction * instruction)
{
	return &EECORE_W_TABLE[instruction->funct()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_COP2_LOOKUP(const EeCoreInstruction * instruction)
{
	return &EECORE_COP2_TABLE[instruction->co()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_CO0_LOOKUP(const EeCoreInstruction * instruction)
{
	return &EECORE_CO0_TABLE[instruction->dest()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_BC2_LOOKUP(const EeCoreInstruction * instruction)
{
	return &EECORE_BC2_TABLE[instruction->rt()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_CO1_LOOKUP(const EeCoreInstruction * instruction)
{
	return &EECORE_CO1_TABLE[instruction->funct()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_VEXT0_LOOKUP(const EeCoreInstruction * instruction)
{
	return &EECORE_VEXT0_TABLE[instruction->shamt()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_VEXT1_LOOKUP(const EeCoreInstruction * instruction)
{
	return &EECORE_VEXT1_TABLE[instruction->shamt()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_VEXT2_LOOKUP(const EeCoreInstruction * instruction)
{
	return &EECORE_VEXT2_TABLE[instruction->shamt()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_VEXT3_LOOKUP(const EeCoreInstruction * instruction)
{
	return &EECORE_VEXT3_TABLE[instruction->shamt()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::getInfo(const EeCoreInstruction * instruction)
{
	// A dummy class to kickstart the search.
	const EECoreInstructionInfo_t rootInfo = { "root", 0, MIPSInstructionInfo_t::InstructionType::CLASS, "OPCODE", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, EECORE_INSTRUCTION_OPCODE_LOOKUP, 0 };
	const EECoreInstructionInfo_t * returnInfo = &rootInfo;

	while (returnInfo->mMIPSInstructionInfo.mInstructionType == MIPSInstructionInfo_t::InstructionType::CLASS)
	{
		returnInfo = returnInfo->mLookupFuncion(instruction);
	}

	return returnInfo;
}