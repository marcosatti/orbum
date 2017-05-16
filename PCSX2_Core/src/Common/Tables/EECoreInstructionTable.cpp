#include "Common/Tables/EECoreInstructionTable.h"

#include "Resources/EE/EECore/Types/EECoreInstruction_t.h"

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_OPCODE_LOOKUP(const EECoreInstruction_t * instruction)
{
	return &EECORE_OPCODE_TABLE[instruction->getOpcode()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_SPECIAL_LOOKUP(const EECoreInstruction_t * instruction)
{
	return &EECORE_SPECIAL_TABLE[instruction->getRFunct()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_REGIMM_LOOKUP(const EECoreInstruction_t * instruction)
{
	return &EECORE_REGIMM_TABLE[instruction->getRt()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_MMI_LOOKUP(const EECoreInstruction_t * instruction)
{
	return &EECORE_MMI_TABLE[instruction->getRFunct()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_MMI0_LOOKUP(const EECoreInstruction_t * instruction)
{
	return &EECORE_MMI0_TABLE[instruction->getRShamt()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_MMI1_LOOKUP(const EECoreInstruction_t * instruction)
{
	return &EECORE_MMI1_TABLE[instruction->getRShamt()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_MMI2_LOOKUP(const EECoreInstruction_t * instruction)
{
	return &EECORE_MMI2_TABLE[instruction->getRShamt()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_MMI3_LOOKUP(const EECoreInstruction_t * instruction)
{
	return &EECORE_MMI3_TABLE[instruction->getRShamt()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_COP0_LOOKUP(const EECoreInstruction_t * instruction)
{
	return &EECORE_COP0_TABLE[instruction->getRs()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_BC0_LOOKUP(const EECoreInstruction_t * instruction)
{
	return &EECORE_BC0_TABLE[instruction->getRt()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_C0_LOOKUP(const EECoreInstruction_t * instruction)
{
	return &EECORE_C0_TABLE[instruction->getRFunct()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_COP1_LOOKUP(const EECoreInstruction_t * instruction)
{
	return &EECORE_COP1_TABLE[instruction->getRs()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_BC1_LOOKUP(const EECoreInstruction_t * instruction)
{
	return &EECORE_BC1_TABLE[instruction->getRt()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_S_LOOKUP(const EECoreInstruction_t * instruction)
{
	return &EECORE_S_TABLE[instruction->getRFunct()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_W_LOOKUP(const EECoreInstruction_t * instruction)
{
	return &EECORE_W_TABLE[instruction->getRFunct()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_COP2_LOOKUP(const EECoreInstruction_t * instruction)
{
	return &EECORE_COP2_TABLE[instruction->getVCO()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_CO0_LOOKUP(const EECoreInstruction_t * instruction)
{
	return &EECORE_CO0_TABLE[instruction->getVDest()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_BC2_LOOKUP(const EECoreInstruction_t * instruction)
{
	return &EECORE_BC2_TABLE[instruction->getRt()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_CO1_LOOKUP(const EECoreInstruction_t * instruction)
{
	return &EECORE_CO1_TABLE[instruction->getRFunct()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_VEXT0_LOOKUP(const EECoreInstruction_t * instruction)
{
	return &EECORE_VEXT0_TABLE[instruction->getRShamt()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_VEXT1_LOOKUP(const EECoreInstruction_t * instruction)
{
	return &EECORE_VEXT1_TABLE[instruction->getRShamt()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_VEXT2_LOOKUP(const EECoreInstruction_t * instruction)
{
	return &EECORE_VEXT2_TABLE[instruction->getRShamt()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::EECORE_INSTRUCTION_VEXT3_LOOKUP(const EECoreInstruction_t * instruction)
{
	return &EECORE_VEXT3_TABLE[instruction->getRShamt()];
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstructionTable::getInfo(const EECoreInstruction_t * instruction)
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