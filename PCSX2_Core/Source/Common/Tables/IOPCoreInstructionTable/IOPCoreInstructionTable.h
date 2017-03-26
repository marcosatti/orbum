#pragma once

#include "Common/Global/Globals.h"

struct MIPSInstruction_t;
struct MIPSInstructionInfo_t;

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
class IOPCoreInstructionTable
{
public:
	/*
	The main lookup function. Use this to return a information struct with the type of instruction given.
	*/
	static const MIPSInstructionInfo_t * getInstructionInfo(const MIPSInstruction_t & instruction);

	/*
	Sub lookup functions. Contain logic for accessing any child instruction table.
	*/
	static const MIPSInstructionInfo_t & IOP_INSTRUCTION_OPCODE_LOOKUP(const MIPSInstruction_t & instruction);
	static const MIPSInstructionInfo_t & IOP_INSTRUCTION_SPECIAL_LOOKUP(const MIPSInstruction_t & instruction);
	static const MIPSInstructionInfo_t & IOP_INSTRUCTION_REGIMM_LOOKUP(const MIPSInstruction_t & instruction);
	static const MIPSInstructionInfo_t & IOP_INSTRUCTION_COP0_LOOKUP(const MIPSInstruction_t & instruction);
	static const MIPSInstructionInfo_t & IOP_INSTRUCTION_COP2_LOOKUP(const MIPSInstruction_t & instruction);
	static const MIPSInstructionInfo_t & IOP_INSTRUCTION_CP2BSC_LOOKUP(const MIPSInstruction_t & instruction);

	/*
	Instruction Tables. Each table contains either instructions or classes (sub-groups of instructions), in the form of MIPSInstructionInfo_t.
	There is a corresponding logic function which handles the access to these tables.
	*/
	static const MIPSInstructionInfo_t IOP_CP2BSC_TABLE[32];
	static const MIPSInstructionInfo_t IOP_COP2_TABLE[64];
	static const MIPSInstructionInfo_t IOP_COP0_TABLE[32];
	static const MIPSInstructionInfo_t IOP_REGIMM_TABLE[32];
	static const MIPSInstructionInfo_t IOP_SPECIAL_TABLE[64];
	static const MIPSInstructionInfo_t IOP_OPCODE_TABLE[64];

	/*
	An unknown instruction constant, used in tables not implemented.
	*/
	static const MIPSInstructionInfo_t IOP_INSTRUCTION_UNDEFINED;

	/*
	IOP CPU (R3000 & COP) cycle constants - most instructions will use one of these values for the MIPSInstructionInfo_t::mCycles field.
	These constants represent the number of cycles needed to perform an instruction by the CPU. They are approximate values.
	Most have been copied over from the old PCSX2, not sure on the accuracy.
	*/
	struct CycleConstants
	{
		// R3000 instructions.
		static constexpr u32 R3000_DEFAULT  = 9;
		static constexpr u32 R3000_BRANCH   = 11;
		static constexpr u32 R3000_MULTIPLY = 16;
		static constexpr u32 R3000_DIVIDE   = 112;
		static constexpr u32 R3000_STORE    = 14;
		static constexpr u32 R3000_LOAD     = 14;

		// COP0/1 instructions.
		static constexpr u32 COP_DEFAULT    = 11;
		static constexpr u32 COP_BRANCH     = 20; // TODO: This is a very rough guess. Needs testing.
	};
};

