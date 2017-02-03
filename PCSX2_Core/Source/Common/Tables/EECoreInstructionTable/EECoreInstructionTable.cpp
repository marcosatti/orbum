#include "stdafx.h"

#include "Common/Tables/EECoreInstructionTable/EECoreInstructionTable.h"
#include "Common/Types/MIPSInstructionInfo/MIPSInstructionInfo_t.h"

#include "Resources/EE/EECore/Types/EECoreInstruction_t.h"

EECoreInstructionInfo_t::EECoreInstructionInfo_t(const char* baseClass, const u8 classIndex, const MIPSInstructionInfo_t::InstructionType instructionType, const char* mnemonic, const u32 implementationIndex, const MIPSInstructionInfo_t::BranchDelayType branchDelayType, const u32 cycles, const EECoreInstructionInfo_t & (* lookupFunction)(const EECoreInstruction_t& instruction)) :
	mBaseClass(baseClass),
	mClassIndex(classIndex),
	mInstructionType(instructionType),
	mMnemonic(mnemonic),
	mImplementationIndex(implementationIndex),
	mBranchDelayType(branchDelayType),
	mCycles(cycles),
	mLookupFuncion(lookupFunction)
{
}

const EECoreInstructionInfo_t * EECoreInstructionTable::getInstructionInfo(const EECoreInstruction_t & instruction)
{
	// A dummy class to kickstart the search.
	const EECoreInstructionInfo_t rootInfo = {"root", 0, MIPSInstructionInfo_t::InstructionType::CLASS, "OPCODE", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, EECORE_INSTRUCTION_OPCODE_LOOKUP };
	const EECoreInstructionInfo_t * returnInfo = &rootInfo;

	while (returnInfo->mInstructionType == MIPSInstructionInfo_t::InstructionType::CLASS)
	{
		returnInfo = &returnInfo->mLookupFuncion(instruction);
	}

	return returnInfo;
}

const EECoreInstructionInfo_t & EECoreInstructionTable::EECORE_INSTRUCTION_OPCODE_LOOKUP(const EECoreInstruction_t & instruction)
{
	return EECORE_OPCODE_TABLE[instruction.getOpcode()];
}

const EECoreInstructionInfo_t& EECoreInstructionTable::EECORE_INSTRUCTION_SPECIAL_LOOKUP(const EECoreInstruction_t& instruction)
{
	return EECORE_SPECIAL_TABLE[instruction.getRFunct()];
}

const EECoreInstructionInfo_t& EECoreInstructionTable::EECORE_INSTRUCTION_REGIMM_LOOKUP(const EECoreInstruction_t& instruction)
{
	return EECORE_REGIMM_TABLE[instruction.getRRt()];
}

const EECoreInstructionInfo_t& EECoreInstructionTable::EECORE_INSTRUCTION_MMI_LOOKUP(const EECoreInstruction_t& instruction)
{
	return EECORE_MMI_TABLE[instruction.getRFunct()];
}

const EECoreInstructionInfo_t& EECoreInstructionTable::EECORE_INSTRUCTION_MMI0_LOOKUP(const EECoreInstruction_t& instruction)
{
	return EECORE_MMI0_TABLE[instruction.getRShamt()];
}

const EECoreInstructionInfo_t& EECoreInstructionTable::EECORE_INSTRUCTION_MMI1_LOOKUP(const EECoreInstruction_t& instruction)
{
	return EECORE_MMI1_TABLE[instruction.getRShamt()];
}

const EECoreInstructionInfo_t& EECoreInstructionTable::EECORE_INSTRUCTION_MMI2_LOOKUP(const EECoreInstruction_t& instruction)
{
	return EECORE_MMI2_TABLE[instruction.getRShamt()];
}

const EECoreInstructionInfo_t& EECoreInstructionTable::EECORE_INSTRUCTION_MMI3_LOOKUP(const EECoreInstruction_t& instruction)
{
	return EECORE_MMI3_TABLE[instruction.getRShamt()];
}

const EECoreInstructionInfo_t& EECoreInstructionTable::EECORE_INSTRUCTION_COP0_LOOKUP(const EECoreInstruction_t& instruction)
{
	return EECORE_COP0_TABLE[instruction.getRRs()];
}

const EECoreInstructionInfo_t& EECoreInstructionTable::EECORE_INSTRUCTION_BC0_LOOKUP(const EECoreInstruction_t& instruction)
{
	return EECORE_BC0_TABLE[instruction.getRRt()];
}

const EECoreInstructionInfo_t& EECoreInstructionTable::EECORE_INSTRUCTION_C0_LOOKUP(const EECoreInstruction_t& instruction)
{
	return EECORE_C0_TABLE[instruction.getRFunct()];
}

const EECoreInstructionInfo_t& EECoreInstructionTable::EECORE_INSTRUCTION_COP1_LOOKUP(const EECoreInstruction_t& instruction)
{
	return EECORE_COP1_TABLE[instruction.getRRs()];
}

const EECoreInstructionInfo_t& EECoreInstructionTable::EECORE_INSTRUCTION_BC1_LOOKUP(const EECoreInstruction_t& instruction)
{
	return EECORE_BC1_TABLE[instruction.getRRt()];
}

const EECoreInstructionInfo_t& EECoreInstructionTable::EECORE_INSTRUCTION_S_LOOKUP(const EECoreInstruction_t& instruction)
{
	return EECORE_S_TABLE[instruction.getRFunct()];
}

const EECoreInstructionInfo_t& EECoreInstructionTable::EECORE_INSTRUCTION_W_LOOKUP(const EECoreInstruction_t& instruction)
{
	return EECORE_W_TABLE[instruction.getRFunct()];
}

const EECoreInstructionInfo_t& EECoreInstructionTable::EECORE_INSTRUCTION_COP2_LOOKUP(const EECoreInstruction_t& instruction)
{
	return EECORE_COP2_TABLE[instruction.getVCO()];
}

const EECoreInstructionInfo_t& EECoreInstructionTable::EECORE_INSTRUCTION_CO0_LOOKUP(const EECoreInstruction_t& instruction)
{
	return EECORE_CO0_TABLE[instruction.getVDest()];
}

const EECoreInstructionInfo_t& EECoreInstructionTable::EECORE_INSTRUCTION_BC2_LOOKUP(const EECoreInstruction_t& instruction)
{
	return EECORE_BC2_TABLE[instruction.getRRt()];
}

const EECoreInstructionInfo_t& EECoreInstructionTable::EECORE_INSTRUCTION_CO1_LOOKUP(const EECoreInstruction_t& instruction)
{
	return EECORE_CO1_TABLE[instruction.getRFunct()];
}

const EECoreInstructionInfo_t& EECoreInstructionTable::EECORE_INSTRUCTION_VEXT0_LOOKUP(const EECoreInstruction_t& instruction)
{
	return EECORE_VEXT0_TABLE[instruction.getRShamt()];
}

const EECoreInstructionInfo_t& EECoreInstructionTable::EECORE_INSTRUCTION_VEXT1_LOOKUP(const EECoreInstruction_t& instruction)
{
	return EECORE_VEXT1_TABLE[instruction.getRShamt()];
}

const EECoreInstructionInfo_t& EECoreInstructionTable::EECORE_INSTRUCTION_VEXT2_LOOKUP(const EECoreInstruction_t& instruction)
{
	return EECORE_VEXT2_TABLE[instruction.getRShamt()];
}

const EECoreInstructionInfo_t& EECoreInstructionTable::EECORE_INSTRUCTION_VEXT3_LOOKUP(const EECoreInstruction_t& instruction)
{
	return EECORE_VEXT3_TABLE[instruction.getRShamt()];
}

const EECoreInstructionInfo_t EECoreInstructionTable::EECORE_VEXT3_TABLE[32] =
{
	{ "VEXT3", 0, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VADDAbc.3", 373, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT3", 1, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VSUBAbc.3", 374, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT3", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMADDAbc.3", 375, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT3", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMSUBAbc.3", 376, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT3", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VITOF15", 377, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT3", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VFTOI15", 378, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT3", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMULAbc.3", 379, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT3", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VCLIP", 380, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT3", 8, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMADDAi", 381, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT3", 9, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMSUBAi", 382, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT3", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT3", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VNOP", 383, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT3", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT3", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VSQD", 384, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT3", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VWAITQ", 385, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT3", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VISWR", 386, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT3", 16, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VRXOR", 387, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT3", 17, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT3", 18, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT3", 19, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT3", 20, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT3", 21, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT3", 22, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT3", 23, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT3", 24, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT3", 25, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT3", 26, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT3", 27, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT3", 28, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT3", 29, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT3", 30, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT3", 31, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr }
};

const EECoreInstructionInfo_t EECoreInstructionTable::EECORE_VEXT2_TABLE[32] =
{
	{ "VEXT2", 0, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VADDAbc.2", 357, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT2", 1, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VSUBAbc.2", 358, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT2", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMADDAbc.2", 359, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT2", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMSUBAbc.2", 360, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT2", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VITOF12", 361, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT2", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VFTOI12", 362, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT2", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMULAbc.2", 363, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT2", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMULAi", 364, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT2", 8, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VADDAi", 365, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT2", 9, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VSUBAi", 366, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT2", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMULA", 367, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT2", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VOPMULA", 368, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT2", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT2", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VLQD", 369, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT2", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VRSQRT", 370, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT2", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VILWR", 371, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT2", 16, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VRINIT", 372, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT2", 17, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT2", 18, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT2", 19, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT2", 20, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT2", 21, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT2", 22, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT2", 23, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT2", 24, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT2", 25, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT2", 26, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT2", 27, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT2", 28, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT2", 29, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT2", 30, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT2", 31, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr }
};

const EECoreInstructionInfo_t EECoreInstructionTable::EECORE_VEXT1_TABLE[32] =
{
	{ "VEXT1", 0, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VADDAbc.1", 340, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT1", 1, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VSUBAbc.1", 341, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT1", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMADDAbc.1", 342, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT1", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMSUBAbc.1", 343, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT1", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VITOF4", 344, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT1", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VFTOI4", 345, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT1", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMULAbc.1", 346, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT1", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VABS", 347, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT1", 8, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMADDAq", 348, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT1", 9, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMSUBAq", 349, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT1", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMADDA", 350, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT1", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMSUBA", 351, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT1", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMR32", 352, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT1", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VSQI", 353, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT1", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VSQRT", 354, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT1", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMFIR", 355, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT1", 16, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VRGET", 356, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT1", 17, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT1", 18, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT1", 19, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT1", 20, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT1", 21, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT1", 22, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT1", 23, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT1", 24, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT1", 25, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT1", 26, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT1", 27, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT1", 28, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT1", 29, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT1", 30, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT1", 31, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr }
};

const EECoreInstructionInfo_t EECoreInstructionTable::EECORE_VEXT0_TABLE[32] =
{
	{ "VEXT0", 0, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VADDAbc.0", 323, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT0", 1, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VSUBAbc.0", 324, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT0", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMADDAbc.0", 325, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT0", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMSUBAbc.0", 326, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT0", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VITOF0", 327, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT0", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VFTOI0", 328, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT0", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMULAbc.0", 329, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT0", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMULAq", 330, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT0", 8, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VADDAq", 331, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT0", 9, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VSUBAq", 332, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT0", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VADDA", 333, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT0", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VSUBA", 334, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT0", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMOVE", 335, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT0", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VLQI", 336, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT0", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VDIV", 337, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT0", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMTIR", 338, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT0", 16, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VRNEXT", 339, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT0", 17, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT0", 18, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT0", 19, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT0", 20, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT0", 21, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT0", 22, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT0", 23, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT0", 24, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT0", 25, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT0", 26, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT0", 27, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT0", 28, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT0", 29, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT0", 30, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "VEXT0", 31, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr }
};

const EECoreInstructionInfo_t EECoreInstructionTable::EECORE_CO1_TABLE[64] =
{
	{ "CO1", 0, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VADDbc.0", 268, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 1, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VADDbc.1", 269, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VADDbc.2", 270, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VADDbc.3", 271, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VSUBbc.0", 272, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VSUBbc.1", 273, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VSUBbc.2", 274, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VSUBbc.3", 275, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 8, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMADDbc.0", 276, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 9, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMADDbc.1", 277, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMADDbc.2", 278, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMADDbc.3", 279, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMSUBbc.0", 280, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMSUBbc.1", 281, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMSUBbc.2", 282, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMSUBbc.3", 283, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 16, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMAXbc.0", 284, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 17, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMAXbc.1", 285, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 18, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMAXbc.2", 286, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 19, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMAXbc.3", 287, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 20, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMINIbc.0", 288, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 21, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMINIbc.1", 289, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 22, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMINIbc.2", 290, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 23, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMINIbc.3", 291, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 24, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMULbc.0", 292, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 25, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMULbc.1", 293, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 26, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMULbc.2", 294, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 27, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMULbc.3", 295, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 28, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMULq", 296, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 29, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMAXi", 297, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 30, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMULi", 298, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 31, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMINIi", 299, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 32, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VADDq", 300, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 33, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMADDq", 301, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 34, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VADDi", 302, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 35, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMADDi", 303, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 36, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VSUBq", 304, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 37, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMSUBq", 305, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 38, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VSUBi", 306, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 39, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMSUBi", 307, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 40, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VADD", 308, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 41, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMADD", 309, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 42, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMUL", 310, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 43, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMAX", 311, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 44, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VSUB", 312, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 45, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMSUB", 313, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 46, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VOPMSUB", 314, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 47, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VMINI", 315, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 48, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VIADD", 316, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 49, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VISUB", 317, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 50, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VIADDI", 318, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 51, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 52, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VIAND", 319, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 53, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VIOR", 320, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 54, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 55, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 56, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VCALLMS", 321, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 57, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "VCALLMSR", 322, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 58, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 59, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO1", 60, MIPSInstructionInfo_t::InstructionType::CLASS, "VEXT0", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_VEXT0_LOOKUP },
	{ "CO1", 61, MIPSInstructionInfo_t::InstructionType::CLASS, "VEXT1", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_VEXT1_LOOKUP },
	{ "CO1", 62, MIPSInstructionInfo_t::InstructionType::CLASS, "VEXT2", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_VEXT2_LOOKUP },
	{ "CO1", 63, MIPSInstructionInfo_t::InstructionType::CLASS, "VEXT3", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_VEXT3_LOOKUP }
};

const EECoreInstructionInfo_t EECoreInstructionTable::EECORE_BC2_TABLE[32] =
{
	{ "BC2", 0, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BC2F", 264, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::COP_BRANCH, nullptr },
	{ "BC2", 1, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BC2T", 265, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::COP_BRANCH, nullptr },
	{ "BC2", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BC2FL", 266, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY_LIKELY, CycleConstants::COP_BRANCH, nullptr },
	{ "BC2", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BC2TL", 267, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY_LIKELY, CycleConstants::COP_BRANCH, nullptr },
	{ "BC2", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC2", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC2", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC2", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC2", 8, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC2", 9, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC2", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC2", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC2", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC2", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC2", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC2", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC2", 16, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC2", 17, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC2", 18, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC2", 19, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC2", 20, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC2", 21, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC2", 22, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC2", 23, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC2", 24, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC2", 25, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC2", 26, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC2", 27, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC2", 28, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC2", 29, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC2", 30, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC2", 31, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr }
};

const EECoreInstructionInfo_t EECoreInstructionTable::EECORE_CO0_TABLE[16] =
{
	{ "CO0", 0, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO0", 1, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "QMFC2", 260, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO0", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "CFC2", 261, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO0", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO0", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO0", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "QMTC2", 262, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO0", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "CTC2", 263, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO0", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO0", 8, MIPSInstructionInfo_t::InstructionType::CLASS, "BC2", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_BC2_LOOKUP },
	{ "CO0", 9, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO0", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO0", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO0", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO0", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO0", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "CO0", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr }
};

const EECoreInstructionInfo_t EECoreInstructionTable::EECORE_COP2_TABLE[2] =
{
	{ "COP2", 0, MIPSInstructionInfo_t::InstructionType::CLASS, "CO0", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_CO0_LOOKUP },
	{ "COP2", 1, MIPSInstructionInfo_t::InstructionType::CLASS, "CO1", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_CO1_LOOKUP }
};

const EECoreInstructionInfo_t EECoreInstructionTable::EECORE_W_TABLE[64] =
{
	{ "W", 0, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 1, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 8, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 9, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 16, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 17, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 18, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 19, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 20, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 21, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 22, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 23, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 24, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 25, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 26, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 27, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 28, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 29, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 30, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 31, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 32, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "CVTS", 259, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 33, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 34, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 35, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 36, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 37, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 38, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 39, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 40, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 41, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 42, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 43, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 44, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 45, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 46, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 47, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 48, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 49, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 50, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 51, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 52, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 53, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 54, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 55, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 56, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 57, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 58, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 59, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 60, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 61, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 62, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "W", 63, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr }
};

const EECoreInstructionInfo_t EECoreInstructionTable::EECORE_S_TABLE[64] =
{
	{ "S", 0, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "ADD", 236, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 1, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SUB", 237, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MUL", 238, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP1_MULTIPLY, nullptr },
	{ "S", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "DIV", 239, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP1_DIVIDE, nullptr },
	{ "S", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SQRT", 240, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP1_DIVIDE, nullptr },
	{ "S", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "ABS", 241, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MOV", 242, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "NEG", 243, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 8, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 9, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 16, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 17, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 18, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 19, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 20, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 21, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RSQRT", 244, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP1_DIVIDE, nullptr },
	{ "S", 22, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 23, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "ADDA", 245, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 24, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SUBA", 246, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 25, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MULA", 247, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP1_MULTIPLY, nullptr },
	{ "S", 26, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 27, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MADD", 248, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP1_MULTIPLY, nullptr },
	{ "S", 28, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MSUB", 249, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP1_MULTIPLY, nullptr },
	{ "S", 29, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MADDA", 250, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP1_MULTIPLY, nullptr },
	{ "S", 30, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MSUBA", 251, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP1_MULTIPLY, nullptr },
	{ "S", 31, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 32, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 33, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 34, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 35, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "CVTW", 252, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 36, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 37, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 38, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 39, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MAX", 253, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 40, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MIN", 254, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 41, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 42, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 43, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 44, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 45, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 46, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 47, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "C.F", 255, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 48, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 49, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "C.EQ", 256, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 50, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 51, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "C.LT", 257, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 52, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 53, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "C.LE", 258, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 54, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 55, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 56, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 57, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 58, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 59, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 60, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 61, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 62, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "S", 63, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr }
};

const EECoreInstructionInfo_t EECoreInstructionTable::EECORE_BC1_TABLE[32] =
{
	{ "BC1", 0, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BC1F", 232, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::COP_BRANCH, nullptr },
	{ "BC1", 1, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BC1T", 233, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::COP_BRANCH, nullptr },
	{ "BC1", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BC1FL", 234, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY_LIKELY, CycleConstants::COP_BRANCH, nullptr },
	{ "BC1", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BC1TL", 235, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY_LIKELY, CycleConstants::COP_BRANCH, nullptr },
	{ "BC1", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC1", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC1", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC1", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC1", 8, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC1", 9, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC1", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC1", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC1", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC1", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC1", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC1", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC1", 16, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC1", 17, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC1", 18, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC1", 19, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC1", 20, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC1", 21, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC1", 22, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC1", 23, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC1", 24, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC1", 25, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC1", 26, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC1", 27, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC1", 28, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC1", 29, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC1", 30, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC1", 31, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr }
};

const EECoreInstructionInfo_t EECoreInstructionTable::EECORE_COP1_TABLE[32] =
{
	{ "COP1", 0, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MFC1", 228, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP1", 1, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP1", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "CFC1", 229, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP1", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP1", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MTC1", 230, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP1", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP1", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "CTC1", 231, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP1", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP1", 8, MIPSInstructionInfo_t::InstructionType::CLASS, "BC1", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_BC1_LOOKUP },
	{ "COP1", 9, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP1", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP1", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP1", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP1", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP1", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP1", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP1", 16, MIPSInstructionInfo_t::InstructionType::CLASS, "S", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_S_LOOKUP },
	{ "COP1", 17, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP1", 18, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP1", 19, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP1", 20, MIPSInstructionInfo_t::InstructionType::CLASS, "W", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_W_LOOKUP },
	{ "COP1", 21, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP1", 22, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP1", 23, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP1", 24, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP1", 25, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP1", 26, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP1", 27, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP1", 28, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP1", 29, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP1", 30, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP1", 31, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr }
};

const EECoreInstructionInfo_t EECoreInstructionTable::EECORE_C0_TABLE[64] =
{
	{ "C0", 0, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 1, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "TLBR", 221, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "TLBWI", 222, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "TLBWR", 223, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 8, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "TLBP", 224, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 9, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 16, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 17, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 18, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 19, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 20, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 21, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 22, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 23, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 24, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "ERET", 225, MIPSInstructionInfo_t::BranchDelayType::BRANCH_NO_DELAY, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 25, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 26, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 27, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 28, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 29, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 30, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 31, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 32, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 33, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 34, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 35, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 36, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 37, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 38, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 39, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 40, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 41, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 42, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 43, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 44, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 45, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 46, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 47, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 48, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 49, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 50, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 51, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 52, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 53, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 54, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 55, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 56, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "EI", 226, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 57, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "DI", 227, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 58, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 59, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 60, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 61, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 62, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "C0", 63, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNDEFINED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr }
};

const EECoreInstructionInfo_t EECoreInstructionTable::EECORE_BC0_TABLE[32] =
{
	{ "BC0", 0, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BC0F", 217, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::COP_BRANCH, nullptr },
	{ "BC0", 1, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BC0T", 218, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::COP_BRANCH, nullptr },
	{ "BC0", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BC0FL", 219, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY_LIKELY, CycleConstants::COP_BRANCH, nullptr },
	{ "BC0", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BC0TL", 220, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY_LIKELY, CycleConstants::COP_BRANCH, nullptr },
	{ "BC0", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC0", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC0", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC0", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC0", 8, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC0", 9, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC0", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC0", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC0", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC0", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC0", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC0", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC0", 16, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC0", 17, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC0", 18, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC0", 19, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC0", 20, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC0", 21, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC0", 22, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC0", 23, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC0", 24, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC0", 25, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC0", 26, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC0", 27, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC0", 28, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC0", 29, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC0", 30, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "BC0", 31, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr }
};

const EECoreInstructionInfo_t EECoreInstructionTable::EECORE_COP0_TABLE[32] =
{
	{ "COP0", 0, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MFC0", 215, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP0_MFC0, nullptr },
	{ "COP0", 1, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MTC0", 216, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 8, MIPSInstructionInfo_t::InstructionType::CLASS, "BC0", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_BC0_LOOKUP },
	{ "COP0", 9, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr },
	{ "COP0", 16, MIPSInstructionInfo_t::InstructionType::CLASS, "C0", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_C0_LOOKUP },
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
	{ "COP0", 31, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr }
};

const EECoreInstructionInfo_t EECoreInstructionTable::EECORE_MMI3_TABLE[32] =
{
	{ "MMI3", 0, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PMADDUW", 202, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI3", 1, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI3", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI3", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PSRAVW", 203, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI3", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI3", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI3", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI3", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI3", 8, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PMTHI", 204, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI3", 9, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PMTLO", 205, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI3", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PINTEH", 206, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI3", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI3", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PMULTUW", 207, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI3", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PDIVUW", 208, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI3", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PCPYUD", 209, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI3", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI3", 16, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI3", 17, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI3", 18, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "POR", 210, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI3", 19, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PNOR", 211, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI3", 20, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI3", 21, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI3", 22, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI3", 23, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI3", 24, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI3", 25, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI3", 26, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PEXCH", 212, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI3", 27, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PCPYH", 213, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI3", 28, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI3", 29, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI3", 30, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PEXCW", 214, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI3", 31, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr }
};

const EECoreInstructionInfo_t EECoreInstructionTable::EECORE_MMI2_TABLE[32] =
{
	{ "MMI2", 0, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PMADDW", 180, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI2", 1, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI2", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PSLLVW", 181, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI2", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PSRLVW", 182, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI2", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PMSUBW", 183, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI2", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI2", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI2", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI2", 8, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PMFHI", 184, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI2", 9, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PMFLO", 185, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI2", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PINTH", 186, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI2", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI2", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PMULTW", 187, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI2", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PDIVW", 188, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI2", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PCPYLD", 189, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI2", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI2", 16, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PMADDH", 190, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI2", 17, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PHMADH", 191, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI2", 18, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PAND", 192, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI2", 19, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PXOR", 193, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI2", 20, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PMSUBH", 194, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI2", 21, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PHMSBH", 195, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI2", 22, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI2", 23, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI2", 24, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI2", 25, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI2", 26, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PEXEH", 196, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI2", 27, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PREVH", 197, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI2", 28, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PMULTH", 198, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI2", 29, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PDIVBW", 199, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI2", 30, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PEXEW", 200, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI2", 31, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PROT3W", 201, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr }
};

const EECoreInstructionInfo_t EECoreInstructionTable::EECORE_MMI1_TABLE[32] =
{
	{ "MMI1", 0, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI1", 1, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PABSW", 162, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI1", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PCEQW", 163, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI1", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PMINW", 164, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI1", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PADSBH", 165, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI1", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PABSH", 166, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI1", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PCEQH", 167, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI1", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PMINH", 168, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI1", 8, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI1", 9, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI1", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PCEQB", 169, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI1", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI1", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI1", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI1", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI1", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI1", 16, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PADDUW", 170, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI1", 17, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PSUBUW", 171, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI1", 18, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PEXTUW", 172, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI1", 19, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI1", 20, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PADDUH", 173, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI1", 21, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PSUBUH", 174, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI1", 22, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PEXTUH", 175, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI1", 23, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI1", 24, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PADDUB", 176, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI1", 25, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PSUBUB", 177, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI1", 26, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PEXTUB", 178, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI1", 27, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "QFSRV", 179, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI1", 28, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI1", 29, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI1", 30, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI1", 31, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr }
};

const EECoreInstructionInfo_t EECoreInstructionTable::EECORE_MMI0_TABLE[32] =
{
	{ "MMI0", 0, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PADDW", 137, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI0", 1, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PSUBW", 138, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI0", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PCGTW", 139, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI0", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PMAXW", 140, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI0", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PADDH", 141, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI0", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PSUBH", 142, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI0", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PCGTH", 143, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI0", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PMAXH", 144, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI0", 8, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PADDB", 145, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI0", 9, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PSUBB", 146, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI0", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PCGTB", 147, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI0", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI0", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI0", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI0", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI0", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI0", 16, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PADDSW", 148, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI0", 17, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PSUBSW", 149, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI0", 18, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PEXTLW", 150, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI0", 19, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PPACW", 151, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI0", 20, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PADDSH", 152, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI0", 21, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PSUBSH", 153, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI0", 22, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PEXTLH", 154, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI0", 23, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PPACH", 155, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI0", 24, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PADDSB", 156, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI0", 25, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PSUBSB", 157, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI0", 26, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PEXTLB", 158, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI0", 27, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PPACB", 159, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI0", 28, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI0", 29, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI0", 30, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PEXT5", 160, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI0", 31, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PPAC5", 161, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr }
};

const EECoreInstructionInfo_t EECoreInstructionTable::EECORE_MMI_TABLE[64] =
{
	{ "MMI", 0, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MADD", 116, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_MULTIPLY, nullptr },
	{ "MMI", 1, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MADDU", 117, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_MULTIPLY, nullptr },
	{ "MMI", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PLZCW", 118, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 8, MIPSInstructionInfo_t::InstructionType::CLASS, "MMI0", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_MMI0_LOOKUP },
	{ "MMI", 9, MIPSInstructionInfo_t::InstructionType::CLASS, "MMI2", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_MMI2_LOOKUP },
	{ "MMI", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 16, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MFHI1", 119, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 17, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MTHI1", 120, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 18, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MFLO1", 121, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 19, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MTLO1", 122, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 20, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 21, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 22, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 23, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 24, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MULT1", 123, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_MULTIPLY, nullptr },
	{ "MMI", 25, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MULTU1", 124, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_MULTIPLY, nullptr },
	{ "MMI", 26, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "DIV1", 125, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DIVIDE, nullptr },
	{ "MMI", 27, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "DIVU1", 126, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DIVIDE, nullptr },
	{ "MMI", 28, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 29, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 30, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 31, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 32, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MADD1", 127, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_MULTIPLY, nullptr },
	{ "MMI", 33, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MADDU1", 128, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_MULTIPLY, nullptr },
	{ "MMI", 34, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 35, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 36, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 37, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 38, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 39, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, 0, nullptr },
	{ "MMI", 40, MIPSInstructionInfo_t::InstructionType::CLASS, "MMI1", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_MMI1_LOOKUP },
	{ "MMI", 41, MIPSInstructionInfo_t::InstructionType::CLASS, "MMI3", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, EECORE_INSTRUCTION_MMI3_LOOKUP },
	{ "MMI", 42, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 43, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 44, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 45, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 46, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 47, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 48, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PMFHL", 129, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 49, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PMTHL", 130, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 50, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 51, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 52, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PSLLH", 131, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 53, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 54, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PSRLH", 132, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 55, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PSRAH", 133, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 56, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 57, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 58, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 59, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 60, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PSLLW", 134, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 61, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 62, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PSRLW", 135, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr },
	{ "MMI", 63, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PSRAW", 136, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::MMI_DEFAULT, nullptr }
};

const EECoreInstructionInfo_t EECoreInstructionTable::EECORE_REGIMM_TABLE[32] =
{
	{ "REGIMM", 0, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BLTZ", 100, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R5900_BRANCH, nullptr },
	{ "REGIMM", 1, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BGEZ", 101, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R5900_BRANCH, nullptr },
	{ "REGIMM", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BLTZL", 102, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY_LIKELY, CycleConstants::R5900_BRANCH, nullptr },
	{ "REGIMM", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BGEZL", 103, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY_LIKELY, CycleConstants::R5900_BRANCH, nullptr },
	{ "REGIMM", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "REGIMM", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "REGIMM", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "REGIMM", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "REGIMM", 8, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "TGEI", 104, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_BRANCH, nullptr },
	{ "REGIMM", 9, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "TGEIU", 105, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_BRANCH, nullptr },
	{ "REGIMM", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "TLTI", 106, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_BRANCH, nullptr },
	{ "REGIMM", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "TLTIU", 107, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_BRANCH, nullptr },
	{ "REGIMM", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "TEQI", 108, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_BRANCH, nullptr },
	{ "REGIMM", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "REGIMM", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "TNEI", 109, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_BRANCH, nullptr },
	{ "REGIMM", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "REGIMM", 16, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BLTZAL", 110, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R5900_BRANCH, nullptr },
	{ "REGIMM", 17, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BGEZAL", 111, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R5900_BRANCH, nullptr },
	{ "REGIMM", 18, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BLTZALL", 112, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY_LIKELY, CycleConstants::R5900_BRANCH, nullptr },
	{ "REGIMM", 19, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BGEZALL", 113, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY_LIKELY, CycleConstants::R5900_BRANCH, nullptr },
	{ "REGIMM", 20, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "REGIMM", 21, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "REGIMM", 22, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "REGIMM", 23, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "REGIMM", 24, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MTSAB", 114, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "REGIMM", 25, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MTSAH", 115, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "REGIMM", 26, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "REGIMM", 27, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "REGIMM", 28, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "REGIMM", 29, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "REGIMM", 30, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "REGIMM", 31, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr }
};

const EECoreInstructionInfo_t EECoreInstructionTable::EECORE_SPECIAL_TABLE[64] =
{ 
	{ "SPECIAL", 0, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SLL", 48, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 1, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SRL", 49, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SRA", 50, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SLLV", 51, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SRLV", 52, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SRAV", 53, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 8, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "JR", 54, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 9, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "JALR", 55, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MOVZ", 56, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MOVN", 57, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SYSCALL", 58, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BREAK", 59, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SYNC", 60, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 16, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MFHI", 61, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 17, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MTHI", 62, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 18, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MFLO", 63, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 19, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MTLO", 64, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 20, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "DSLLV", 65, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 21, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 22, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "DSRLV", 66, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 23, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "DSRAV", 67, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 24, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MULT", 68, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_MULTIPLY, nullptr },
	{ "SPECIAL", 25, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MULTU", 69, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_MULTIPLY, nullptr },
	{ "SPECIAL", 26, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "DIV", 70, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DIVIDE, nullptr },
	{ "SPECIAL", 27, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "DIVU", 71, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DIVIDE, nullptr },
	{ "SPECIAL", 28, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 29, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 30, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 31, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 32, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "ADD", 72, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 33, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "ADDU", 73, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 34, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SUB", 74, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 35, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SUBU", 75, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 36, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "AND", 76, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 37, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "OR", 77, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 38, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "XOR", 78, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 39, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "NOR", 79, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 40, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MFSA", 80, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 41, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MTSA", 81, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 42, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SLT", 82, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 43, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SLTU", 83, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 44, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "DADD", 84, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 45, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "DADDU", 85, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 46, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "DSUB", 86, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 47, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "DSUBU", 87, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 48, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "TGE", 88, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_BRANCH, nullptr },
	{ "SPECIAL", 49, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "TGEU", 89, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_BRANCH, nullptr },
	{ "SPECIAL", 50, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "TLT", 90, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_BRANCH, nullptr },
	{ "SPECIAL", 51, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "TLTU", 91, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_BRANCH, nullptr },
	{ "SPECIAL", 52, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "TEQ", 92, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_BRANCH, nullptr },
	{ "SPECIAL", 53, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 54, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "TNE", 93, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_BRANCH, nullptr },
	{ "SPECIAL", 55, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 56, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "DSLL", 94, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 57, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 58, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "DSRL", 95, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 59, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "DSRA", 96, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 60, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "DSLL32", 97, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 61, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 62, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "DSRL32", 98, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "SPECIAL", 63, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "DSRA32", 99, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr }
};

const EECoreInstructionInfo_t EECoreInstructionTable::EECORE_OPCODE_TABLE[64] =
{
	{ "OPCODE", 0, MIPSInstructionInfo_t::InstructionType::CLASS, "SPECIAL", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_SPECIAL_LOOKUP },
	{ "OPCODE", 1, MIPSInstructionInfo_t::InstructionType::CLASS, "REGIMM", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_REGIMM_LOOKUP },
	{ "OPCODE", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "J", 1, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R5900_DEFAULT, nullptr },
	{ "OPCODE", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "JAL", 2, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R5900_DEFAULT, nullptr },
	{ "OPCODE", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BEQ", 3, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R5900_BRANCH, nullptr },
	{ "OPCODE", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BNE", 4, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R5900_BRANCH, nullptr },
	{ "OPCODE", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BLEZ", 5, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R5900_BRANCH, nullptr },
	{ "OPCODE", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BGTZ", 6, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R5900_BRANCH, nullptr },
	{ "OPCODE", 8, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "ADDI", 7, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "OPCODE", 9, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "ADDIU", 8, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "OPCODE", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SLTI", 9, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "OPCODE", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SLTIU", 10, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "OPCODE", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "ANDI", 11, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "OPCODE", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "ORI", 12, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "OPCODE", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "XORI", 13, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "OPCODE", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "LUI", 14, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "OPCODE", 16, MIPSInstructionInfo_t::InstructionType::CLASS, "COP0", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_COP0_LOOKUP },
	{ "OPCODE", 17, MIPSInstructionInfo_t::InstructionType::CLASS, "COP1", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_COP1_LOOKUP },
	{ "OPCODE", 18, MIPSInstructionInfo_t::InstructionType::CLASS, "COP2", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_COP2_LOOKUP },
	{ "OPCODE", 19, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "OPCODE", 20, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BEQL", 15, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY_LIKELY, CycleConstants::R5900_BRANCH, nullptr },
	{ "OPCODE", 21, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BNEL", 16, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY_LIKELY, CycleConstants::R5900_BRANCH, nullptr },
	{ "OPCODE", 22, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BLEZL", 17, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY_LIKELY, CycleConstants::R5900_BRANCH, nullptr },
	{ "OPCODE", 23, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BGTZL", 18, MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY_LIKELY, CycleConstants::R5900_BRANCH, nullptr },
	{ "OPCODE", 24, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "DADDI", 19, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "OPCODE", 25, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "DADDIU", 20, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "OPCODE", 26, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "LDL", 21, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_LOAD, nullptr },
	{ "OPCODE", 27, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "LDR", 22, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_LOAD, nullptr },
	{ "OPCODE", 28, MIPSInstructionInfo_t::InstructionType::CLASS, "MMI", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, 0, EECORE_INSTRUCTION_MMI_LOOKUP },
	{ "OPCODE", 29, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "OPCODE", 30, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "LQ", 23, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_LOAD, nullptr },
	{ "OPCODE", 31, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SQ", 24, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_STORE, nullptr },
	{ "OPCODE", 32, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "LB", 25, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_LOAD, nullptr },
	{ "OPCODE", 33, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "LH", 26, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_LOAD, nullptr },
	{ "OPCODE", 34, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "LWL", 27, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_LOAD, nullptr },
	{ "OPCODE", 35, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "LW", 28, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_LOAD, nullptr },
	{ "OPCODE", 36, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "LBU", 29, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_LOAD, nullptr },
	{ "OPCODE", 37, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "LHU", 30, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_LOAD, nullptr },
	{ "OPCODE", 38, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "LWR", 31, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_LOAD, nullptr },
	{ "OPCODE", 39, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "LWU", 32, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_LOAD, nullptr },
	{ "OPCODE", 40, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SB", 33, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_STORE, nullptr },
	{ "OPCODE", 41, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SH", 34, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_STORE, nullptr },
	{ "OPCODE", 42, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SWL", 35, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_STORE, nullptr },
	{ "OPCODE", 43, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SW", 36, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_STORE, nullptr },
	{ "OPCODE", 44, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SDL", 37, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_STORE, nullptr },
	{ "OPCODE", 45, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SDR", 38, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_STORE, nullptr },
	{ "OPCODE", 46, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SWR", 39, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_STORE, nullptr },
	{ "OPCODE", 47, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "CACHE", 40, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "OPCODE", 48, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "OPCODE", 49, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "LWC1", 41, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_LOAD, nullptr },
	{ "OPCODE", 50, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "OPCODE", 51, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "PREF", 42, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "OPCODE", 52, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "OPCODE", 53, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "OPCODE", 54, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "LQC2", 43, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_LOAD, nullptr },
	{ "OPCODE", 55, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "LD", 44, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_LOAD, nullptr },
	{ "OPCODE", 56, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "OPCODE", 57, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SWC1", 45, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_STORE, nullptr },
	{ "OPCODE", 58, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "OPCODE", 59, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "OPCODE", 60, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "OPCODE", 61, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", 0, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_DEFAULT, nullptr },
	{ "OPCODE", 62, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SQC2", 46, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_STORE, nullptr },
	{ "OPCODE", 63, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SD", 47, MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R5900_STORE, nullptr }
};