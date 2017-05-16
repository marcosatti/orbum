#pragma once

#include "Common/Global/Globals.h"
#include "Common/Types/MIPS/MIPSInstructionInfo_t.h"

struct IOPCoreInstruction_t;

/*
Static class used as the IOP instruction information lookup.
There is no official documentation, but the R3000 uses the MIPS I instruction set which this is based off. You can find various PSX info on the internet about this.
See also the original PCSX2 file "R3000AOpcodeTables.cpp".
The instruction tables are defined in IOP Instruction Implementation Register.xlsx. You can copy and paste any changes made to that file in here, but make sure the spreadsheet is the master copy.
It is a lot easier to read the spreadsheet than looking at the source code.

The purpose of this class is to decode the given instruction, so that an execution core knows which instruction implementation to use.
For example (pseduo-code): 
 MIPSInstruction = 0xABCD1234
 Info = IOPCoreInstructionTable::getInstructionInfo(MIPSInstruction)
 ExecutionCore.ExecuteInstruction(Info.mImplementationIndex)

The mImplementationIndex is a linear UNIQUE index of all of the instructions for the IOP - there should be no two instructions with the same index.
Therefore in an execution core, a simple function pointer array of size = MAX(Implementation Indexes) will be enough, which is simply used as in the example above.
*/
struct IOPCoreInstructionTable
{
	/*
	IOP CPU (R3000 & COP) cycle constants - most instructions will use one of these values for the MIPSInstructionInfo_t::mCycles field.
	These constants represent the number of cycles needed to perform an instruction by the CPU. They are approximate values.
	Most have been copied over from the old PCSX2, not sure on the accuracy.
	*/
	struct CycleConstants
	{
		// R3000 instructions.
		static constexpr int R3000_DEFAULT = 9;
		static constexpr int R3000_BRANCH = 11;
		static constexpr int R3000_MULTIPLY = 16;
		static constexpr int R3000_DIVIDE = 112;
		static constexpr int R3000_STORE = 14;
		static constexpr int R3000_LOAD = 14;

		// COP0/1 instructions.
		static constexpr int COP_DEFAULT = 11;
		static constexpr int COP_BRANCH = 20; // TODO: This is a very rough guess. Needs testing.
	};

	struct IOPCoreInstructionInfo_t
	{
		const MIPSInstructionInfo_t      mMIPSInstructionInfo;
		const IOPCoreInstructionInfo_t * (*mLookupFuncion)(const IOPCoreInstruction_t * instruction);
		const u32                        mImplementationIndex;
	};

	/*
	Sub lookup functions. Contain logic for accessing any child instruction table.
	*/
	static const IOPCoreInstructionInfo_t * IOPCORE_INSTRUCTION_OPCODE_LOOKUP(const IOPCoreInstruction_t * instruction);
	static const IOPCoreInstructionInfo_t * IOPCORE_INSTRUCTION_SPECIAL_LOOKUP(const IOPCoreInstruction_t * instruction);
	static const IOPCoreInstructionInfo_t * IOPCORE_INSTRUCTION_REGIMM_LOOKUP(const IOPCoreInstruction_t * instruction);
	static const IOPCoreInstructionInfo_t * IOPCORE_INSTRUCTION_COP0_LOOKUP(const IOPCoreInstruction_t * instruction);
	static const IOPCoreInstructionInfo_t * IOPCORE_INSTRUCTION_COP2_LOOKUP(const IOPCoreInstruction_t * instruction);
	static const IOPCoreInstructionInfo_t * IOPCORE_INSTRUCTION_CP2BSC_LOOKUP(const IOPCoreInstruction_t * instruction);

	static constexpr IOPCoreInstructionInfo_t IOPCORE_OPCODE_TABLE[64] =
	{
		{ "OPCODE", 0, MIPSInstructionInfo_t::InstructionType::CLASS, "SPECIAL", MIPSInstructionInfo_t::BranchDelayType::NONE, 0, IOPCORE_INSTRUCTION_SPECIAL_LOOKUP, 0 },
		{ "OPCODE", 1, MIPSInstructionInfo_t::InstructionType::CLASS, "REGIMM", MIPSInstructionInfo_t::BranchDelayType::NONE, 0, IOPCORE_INSTRUCTION_REGIMM_LOOKUP, 0 },
		{ "OPCODE", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "J", MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R3000_DEFAULT, nullptr, 1 },
		{ "OPCODE", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "JAL", MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R3000_DEFAULT, nullptr, 2 },
		{ "OPCODE", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BEQ", MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R3000_BRANCH, nullptr, 3 },
		{ "OPCODE", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BNE", MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R3000_BRANCH, nullptr, 4 },
		{ "OPCODE", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BLEZ", MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R3000_BRANCH, nullptr, 5 },
		{ "OPCODE", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BGTZ", MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R3000_BRANCH, nullptr, 6 },
		{ "OPCODE", 8, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "ADDI", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 7 },
		{ "OPCODE", 9, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "ADDIU", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 8 },
		{ "OPCODE", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SLTI", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 9 },
		{ "OPCODE", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SLTIU", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 10 },
		{ "OPCODE", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "ANDI", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 11 },
		{ "OPCODE", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "ORI", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 12 },
		{ "OPCODE", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "XORI", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 13 },
		{ "OPCODE", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "LUI", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 14 },
		{ "OPCODE", 16, MIPSInstructionInfo_t::InstructionType::CLASS, "COP0", MIPSInstructionInfo_t::BranchDelayType::NONE, 0, IOPCORE_INSTRUCTION_COP0_LOOKUP, 0 },
		{ "OPCODE", 17, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "OPCODE", 18, MIPSInstructionInfo_t::InstructionType::CLASS, "COP2", MIPSInstructionInfo_t::BranchDelayType::NONE, 0, IOPCORE_INSTRUCTION_COP2_LOOKUP, 0 },
		{ "OPCODE", 19, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "OPCODE", 20, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "OPCODE", 21, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "OPCODE", 22, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "OPCODE", 23, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "OPCODE", 24, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "OPCODE", 25, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "OPCODE", 26, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "OPCODE", 27, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "OPCODE", 28, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "OPCODE", 29, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "OPCODE", 30, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "OPCODE", 31, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "OPCODE", 32, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "LB", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_LOAD, nullptr, 15 },
		{ "OPCODE", 33, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "LH", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_LOAD, nullptr, 16 },
		{ "OPCODE", 34, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "LWL", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_LOAD, nullptr, 17 },
		{ "OPCODE", 35, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "LW", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_LOAD, nullptr, 18 },
		{ "OPCODE", 36, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "LBU", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_LOAD, nullptr, 19 },
		{ "OPCODE", 37, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "LHU", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_LOAD, nullptr, 20 },
		{ "OPCODE", 38, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "LWR", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_LOAD, nullptr, 21 },
		{ "OPCODE", 39, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "OPCODE", 40, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SB", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_STORE, nullptr, 22 },
		{ "OPCODE", 41, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SH", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_STORE, nullptr, 23 },
		{ "OPCODE", 42, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SWL", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_STORE, nullptr, 24 },
		{ "OPCODE", 43, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SW", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_STORE, nullptr, 25 },
		{ "OPCODE", 44, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "OPCODE", 45, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "OPCODE", 46, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SWR", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_STORE, nullptr, 26 },
		{ "OPCODE", 47, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "OPCODE", 48, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "OPCODE", 49, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "OPCODE", 50, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "LWC2", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_LOAD, nullptr, 27 },
		{ "OPCODE", 51, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "OPCODE", 52, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "OPCODE", 53, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "OPCODE", 54, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "OPCODE", 55, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "OPCODE", 56, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "OPCODE", 57, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "OPCODE", 58, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SWC2", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_STORE, nullptr, 28 },
		{ "OPCODE", 59, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "OPCODE", 60, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "OPCODE", 61, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "OPCODE", 62, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "OPCODE", 63, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
	};
	static constexpr IOPCoreInstructionInfo_t IOPCORE_SPECIAL_TABLE[64] =
	{
		{ "SPECIAL", 0, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SLL", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 29 },
		{ "SPECIAL", 1, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SRL", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 30 },
		{ "SPECIAL", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SRA", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 31 },
		{ "SPECIAL", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SLLV", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 32 },
		{ "SPECIAL", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SRLV", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 33 },
		{ "SPECIAL", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SRAV", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 34 },
		{ "SPECIAL", 8, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "JR", MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R3000_DEFAULT, nullptr, 35 },
		{ "SPECIAL", 9, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "JALR", MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R3000_DEFAULT, nullptr, 36 },
		{ "SPECIAL", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SYSCALL", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 37 },
		{ "SPECIAL", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BREAK", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 38 },
		{ "SPECIAL", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 16, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MFHI", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 39 },
		{ "SPECIAL", 17, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MTHI", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 40 },
		{ "SPECIAL", 18, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MFLO", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 41 },
		{ "SPECIAL", 19, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MTLO", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 42 },
		{ "SPECIAL", 20, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 21, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 22, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 23, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 24, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MULT", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_MULTIPLY, nullptr, 43 },
		{ "SPECIAL", 25, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MULTU", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_MULTIPLY, nullptr, 44 },
		{ "SPECIAL", 26, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "DIV", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DIVIDE, nullptr, 45 },
		{ "SPECIAL", 27, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "DIVU", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DIVIDE, nullptr, 46 },
		{ "SPECIAL", 28, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 29, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 30, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 31, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "UNSUPPORTED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 32, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "ADD", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 47 },
		{ "SPECIAL", 33, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "ADDU", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 48 },
		{ "SPECIAL", 34, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SUB", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 49 },
		{ "SPECIAL", 35, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SUBU", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 50 },
		{ "SPECIAL", 36, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "AND", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 51 },
		{ "SPECIAL", 37, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "OR", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 52 },
		{ "SPECIAL", 38, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "XOR", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 53 },
		{ "SPECIAL", 39, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "NOR", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 54 },
		{ "SPECIAL", 40, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 41, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 42, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SLT", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 55 },
		{ "SPECIAL", 43, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SLTU", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 56 },
		{ "SPECIAL", 44, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 45, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 46, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 47, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 48, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 49, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 50, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 51, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 52, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 53, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 54, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 55, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 56, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 57, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 58, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 59, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 60, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 61, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 62, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "SPECIAL", 63, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
	};
	static constexpr IOPCoreInstructionInfo_t IOPCORE_REGIMM_TABLE[32] = 
	{
		{ "REGIMM", 0, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BLTZ", MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R3000_BRANCH, nullptr, 57 },
		{ "REGIMM", 1, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BGEZ", MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R3000_BRANCH, nullptr, 58 },
		{ "REGIMM", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "REGIMM", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "REGIMM", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "REGIMM", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "REGIMM", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "REGIMM", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "REGIMM", 8, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "REGIMM", 9, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "REGIMM", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "REGIMM", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "REGIMM", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "REGIMM", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "REGIMM", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "REGIMM", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "REGIMM", 16, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BLTZAL", MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R3000_BRANCH, nullptr, 59 },
		{ "REGIMM", 17, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "BGEZAL", MIPSInstructionInfo_t::BranchDelayType::BRANCH_DELAY, CycleConstants::R3000_BRANCH, nullptr, 60 },
		{ "REGIMM", 18, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "REGIMM", 19, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "REGIMM", 20, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "REGIMM", 21, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "REGIMM", 22, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "REGIMM", 23, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "REGIMM", 24, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "REGIMM", 25, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "REGIMM", 26, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "REGIMM", 27, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "REGIMM", 28, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "REGIMM", 29, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "REGIMM", 30, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
		{ "REGIMM", 31, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::R3000_DEFAULT, nullptr, 0 },
	};
	static constexpr IOPCoreInstructionInfo_t IOPCORE_COP0_TABLE[32] = 
	{
		{ "COP0", 0, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MFC0", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 61 },
		{ "COP0", 1, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP0", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "CFC0", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 62 },
		{ "COP0", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP0", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MTC0", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 63 },
		{ "COP0", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP0", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "CTC0", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 64 },
		{ "COP0", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP0", 8, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP0", 9, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP0", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP0", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP0", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP0", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP0", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP0", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP0", 16, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RFE", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 65 },
		{ "COP0", 17, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP0", 18, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP0", 19, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP0", 20, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP0", 21, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP0", 22, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP0", 23, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP0", 24, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP0", 25, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP0", 26, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP0", 27, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP0", 28, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP0", 29, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP0", 30, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP0", 31, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
	};
	static constexpr IOPCoreInstructionInfo_t IOPCORE_COP2_TABLE[64] = 
	{
		{ "COP2", 0, MIPSInstructionInfo_t::InstructionType::CLASS, "CP2BSC", MIPSInstructionInfo_t::BranchDelayType::NONE, 0, IOPCORE_INSTRUCTION_CP2BSC_LOOKUP, 0 },
		{ "COP2", 1, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RTPS", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 66 },
		{ "COP2", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "NCLIP", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 67 },
		{ "COP2", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 8, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 9, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "OP", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 68 },
		{ "COP2", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 16, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "DPCS", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 69 },
		{ "COP2", 17, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "INTPL", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 70 },
		{ "COP2", 18, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MVMVA", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 71 },
		{ "COP2", 19, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "NCDS", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 72 },
		{ "COP2", 20, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "CDP", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 73 },
		{ "COP2", 21, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 22, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "NCDT", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 74 },
		{ "COP2", 23, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 24, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 25, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 26, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 27, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "NCCS", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 75 },
		{ "COP2", 28, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "CC", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 76 },
		{ "COP2", 29, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 30, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "NCS", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 77 },
		{ "COP2", 31, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 32, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "NCT", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 78 },
		{ "COP2", 33, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 34, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 35, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 36, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 37, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 38, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 39, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 40, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "SQR", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 79 },
		{ "COP2", 41, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "DCPL", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 80 },
		{ "COP2", 42, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "DPCT", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 81 },
		{ "COP2", 43, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 44, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 45, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "AVSZ3", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 82 },
		{ "COP2", 46, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "AVSZ4", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 83 },
		{ "COP2", 47, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 48, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RTPT", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 84 },
		{ "COP2", 49, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 50, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 51, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 52, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 53, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 54, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 55, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 56, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 57, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 58, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 59, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 60, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "COP2", 61, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "GPF", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 85 },
		{ "COP2", 62, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "GPL", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 86 },
		{ "COP2", 63, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
	};
	static constexpr IOPCoreInstructionInfo_t IOPCORE_CP2BSC_TABLE[32] =
	{
		{ "CP2BSC", 0, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MFC2", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 87 },
		{ "CP2BSC", 1, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "CP2BSC", 2, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "CFC2", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 88 },
		{ "CP2BSC", 3, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "CP2BSC", 4, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "MTC2", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 89 },
		{ "CP2BSC", 5, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "CP2BSC", 6, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "CTC2", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 90 },
		{ "CP2BSC", 7, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "CP2BSC", 8, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "CP2BSC", 9, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "CP2BSC", 10, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "CP2BSC", 11, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "CP2BSC", 12, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "CP2BSC", 13, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "CP2BSC", 14, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "CP2BSC", 15, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "CP2BSC", 16, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "CP2BSC", 17, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "CP2BSC", 18, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "CP2BSC", 19, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "CP2BSC", 20, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "CP2BSC", 21, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "CP2BSC", 22, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "CP2BSC", 23, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "CP2BSC", 24, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "CP2BSC", 25, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "CP2BSC", 26, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "CP2BSC", 27, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "CP2BSC", 28, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "CP2BSC", 29, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "CP2BSC", 30, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
		{ "CP2BSC", 31, MIPSInstructionInfo_t::InstructionType::INSTRUCTION, "RESERVED", MIPSInstructionInfo_t::BranchDelayType::NONE, CycleConstants::COP_DEFAULT, nullptr, 0 },
	};
	
	/*
	The main lookup function. Use this to return information on the instruction given.
	*/
	static const IOPCoreInstructionInfo_t * getInfo(const IOPCoreInstruction_t * instruction);	
};

