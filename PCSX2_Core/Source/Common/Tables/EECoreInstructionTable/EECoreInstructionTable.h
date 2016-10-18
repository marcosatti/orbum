#pragma once

#include "Common/Global/Globals.h"

class MIPSInstruction_t;
struct MIPSInstructionInfo_t;

/*
Static class used as the EECore instruction information lookup.
This uses the Instruction/Class hierarchy structure as defined in the EE Core Instruction Manual Appendix section.
The instruction tables are defined in EECore Instruction Implementation Register.xlsx. You can copy and paste any changes made to that file in here, but make sure the spreadsheet is the master copy.
 It is a lot easier to read the spreadsheet than looking at the source code.

The purpose of this class is to decode the given instruction, so that an execution core knows which instruction implementation to use.
For example (pseduo-code): 
 MIPSInstruction = 0xABCD1234
 Info = EECoreInstructionTable::getInstructionInfo(MIPSInstruction)
 ExecutionCore.ExecuteInstruction(Info.mImplementationIndex)

The mImplementationIndex is a linear UNIQUE index of all of the instructions for the EECore - there should be no two instructions with the same index.
Therefore in an execution core, a simple function pointer array of size = MAX(Implementation Indexes) will be enough, which is simply used as in the example above.
*/
class EECoreInstructionTable
{
public:
	/*
	The main lookup function. Use this to return a information struct with the type of instruction given.
	*/
	static const MIPSInstructionInfo_t * getInstructionInfo(const MIPSInstruction_t & instruction);

	/*
	Sub lookup functions. Contain logic for accessing any child instruction table.
	*/
	static const MIPSInstructionInfo_t & EECORE_INSTRUCTION_OPCODE_LOOKUP(const MIPSInstruction_t & instruction);
	static const MIPSInstructionInfo_t & EECORE_INSTRUCTION_SPECIAL_LOOKUP(const MIPSInstruction_t & instruction);
	static const MIPSInstructionInfo_t & EECORE_INSTRUCTION_REGIMM_LOOKUP(const MIPSInstruction_t & instruction);
	static const MIPSInstructionInfo_t & EECORE_INSTRUCTION_MMI_LOOKUP(const MIPSInstruction_t & instruction);
	static const MIPSInstructionInfo_t & EECORE_INSTRUCTION_MMI0_LOOKUP(const MIPSInstruction_t & instruction);
	static const MIPSInstructionInfo_t & EECORE_INSTRUCTION_MMI1_LOOKUP(const MIPSInstruction_t & instruction);
	static const MIPSInstructionInfo_t & EECORE_INSTRUCTION_MMI2_LOOKUP(const MIPSInstruction_t & instruction);
	static const MIPSInstructionInfo_t & EECORE_INSTRUCTION_MMI3_LOOKUP(const MIPSInstruction_t & instruction);
	static const MIPSInstructionInfo_t & EECORE_INSTRUCTION_COP0_LOOKUP(const MIPSInstruction_t & instruction);
	static const MIPSInstructionInfo_t & EECORE_INSTRUCTION_BC0_LOOKUP(const MIPSInstruction_t & instruction);
	static const MIPSInstructionInfo_t & EECORE_INSTRUCTION_C0_LOOKUP(const MIPSInstruction_t & instruction);
	static const MIPSInstructionInfo_t & EECORE_INSTRUCTION_COP1_LOOKUP(const MIPSInstruction_t & instruction);
	static const MIPSInstructionInfo_t & EECORE_INSTRUCTION_BC1_LOOKUP(const MIPSInstruction_t & instruction);
	static const MIPSInstructionInfo_t & EECORE_INSTRUCTION_S_LOOKUP(const MIPSInstruction_t & instruction);
	static const MIPSInstructionInfo_t & EECORE_INSTRUCTION_W_LOOKUP(const MIPSInstruction_t & instruction);
	static const MIPSInstructionInfo_t & EECORE_INSTRUCTION_COP2_LOOKUP(const MIPSInstruction_t & instruction);

	/*
	Instruction Tables. Each table contains either instructions or classes (sub-groups of instructions), in the form of MIPSInstructionInfo_t.
	There is a corresponding logic function which handles the access to these tables.
	*/
	static const MIPSInstructionInfo_t EECORE_W_TABLE[64];
	static const MIPSInstructionInfo_t EECORE_S_TABLE[64];
	static const MIPSInstructionInfo_t EECORE_BC1_TABLE[32];
	static const MIPSInstructionInfo_t EECORE_COP1_TABLE[32];
	static const MIPSInstructionInfo_t EECORE_C0_TABLE[64];
	static const MIPSInstructionInfo_t EECORE_BC0_TABLE[32];
	static const MIPSInstructionInfo_t EECORE_COP0_TABLE[32];
	static const MIPSInstructionInfo_t EECORE_MMI3_TABLE[32];
	static const MIPSInstructionInfo_t EECORE_MMI2_TABLE[32];
	static const MIPSInstructionInfo_t EECORE_MMI1_TABLE[32];
	static const MIPSInstructionInfo_t EECORE_MMI0_TABLE[32];
	static const MIPSInstructionInfo_t EECORE_MMI_TABLE[64];
	static const MIPSInstructionInfo_t EECORE_REGIMM_TABLE[32];
	static const MIPSInstructionInfo_t EECORE_SPECIAL_TABLE[64];
	static const MIPSInstructionInfo_t EECORE_OPCODE_TABLE[64];

	/*
	An unknown instruction constant, used in tables not implemented.
	*/
	static const MIPSInstructionInfo_t EECORE_INSTRUCTION_UNDEFINED;

	/*
	EE Core CPU (R5900 & COP) cycle constants - most instructions will use one of these values for the MIPSInstructionInfo_t::mCycles field.
	These constants represent the number of cycles needed to perform an instruction by the CPU. They are approximate values.
	Most have been copied over from the old PCSX2, not sure on the accuracy.
	*/
	struct CycleConstants
	{
		// R5900 instructions.
		static constexpr u32 R5900_DEFAULT  = 9;
		static constexpr u32 R5900_BRANCH   = 11;
		static constexpr u32 R5900_MULTIPLY = 16;
		static constexpr u32 R5900_DIVIDE   = 112;
		static constexpr u32 R5900_STORE    = 14;
		static constexpr u32 R5900_LOAD     = 14;

		// MMI instructions.
		static constexpr u32 MMI_DEFAULT    = 14;
		static constexpr u32 MMI_MULTIPLY   = 16;
		static constexpr u32 MMI_DIVIDE     = 112;

		// COP0/1 instructions.
		static constexpr u32 COP_DEFAULT    = 11;
		static constexpr u32 COP_BRANCH     = 20; // TODO: This is a very rough guess. Needs testing.
		static constexpr u32 COP0_MFC0      = 10;
		static constexpr u32 COP1_MULTIPLY  = 32;
		static constexpr u32 COP1_DIVIDE    = 200; // TODO: This is a very rough guess. Needs testing.
	};
};

