#pragma once

#include "Common/Global/Globals.h"

#include "Common/PS2 Types/MIPSInstruction/MIPSInstruction_t.h"

/*
Static class used as the R5900 instruction lookup.
This uses the Instruction/Class hierarchy structure as defined in the EE Core Instruction Manual Appendix section.
The instruction tables are defined in R5900 Instruction Implementation Register.xlsx. You can copy and paste any changes made to that file in here, but make sure the spreadsheet is the master copy.
 It is a lot easier to read the spreadsheet than looking at the source code.

The purpose of this class is to decode the given instruction, so that an execution core knows which instruction implementation to use.
For example (pseduo-code): 
 MIPSInstruction = 0xABCD1234
 Info = R5900InstructionUtil::getInstructionInfo(MIPSInstruction)
 ExecutionCore.ExecuteInstruction(Info.mImplementationIndex)

The mImplementationIndex is a linear UNIQUE index of all of the instructions for the R5900 - there should be no two instructions with the same index.
Therefore in an execution core, a simple function pointer array of size = MAX(Implementation Indexes) will be enough, which is simply used as in the example above.
*/
class R5900InstructionUtil
{
public:
	/*
	Encapsulates information about any R5900 instruction defined.
	See comments below, next to each field.
	*/
	struct R5900InstructionInfo_t
	{
		enum InstructionType
		{
			CLASS,
			INSTRUCTION
		};

		enum BranchDelayType
		{
			NONE,
			BRANCH_DELAY,
			BRANCH_DELAY_LIKELY
		};

		// Constructor.
		R5900InstructionInfo_t(const u8 classIndex, const InstructionType instructionType, const char* const mnemonic, const u32 implementationIndex, const BranchDelayType branchDelayType, const u8 cycles, const R5900InstructionInfo_t&(*const lookupFunction)(const MIPSInstruction_t& instruction))
			: mClassIndex(classIndex),
			mInstructionType(instructionType),
			mMnemonic(mnemonic),
			mImplementationIndex(implementationIndex),
			mBranchDelayType(branchDelayType),
			mCycles(cycles),
			mLookupFuncion(lookupFunction)
		{
		}

		const u8                       mClassIndex;                                                    // Index of the instruction/subclass within the class. For example in the OPCODE table, the COP0 subclass has class index = 16.
		const InstructionType          mInstructionType;                                               // Within the class table, is it a (sub-)class or an instruction? TODO: This needs a better name (along with the enum name).
		const char *                   mMnemonic;                                                      // A string representation of the instruction or subclass.
		const u32                      mImplementationIndex;                                           // A unique index which is used by an execution core to define and run an instruction. See the example in the header of this file.
		const BranchDelayType          mBranchDelayType;                                               // Some instructions have a branch delay feature, where the next instruction immediately after is executed regardless if a branch is taken or not. Most of the time it will be NONE. See the EE Core Users Manual page 44 for more information.
		const u8                       mCycles;                                                        // An approximate number of CPU cycles the instruction takes to execute, which is useful for performance tracking and timing.
		const R5900InstructionInfo_t & (*const mLookupFuncion)(const MIPSInstruction_t & instruction); // When a sub-class is encountered, this variable points to a lookup function containing the logic needed for accessing the sub-class table properly.
	};

	/*
	The main lookup function. Use this to return a information struct with the type of instruction given.
	*/
	static const R5900InstructionInfo_t & getInstructionInfo(const MIPSInstruction_t & instruction);

	/*
	Sub lookup functions. Contain logic for accessing any child instruction table.
	*/
	static const R5900InstructionInfo_t & R5900_INSTRUCTION_OPCODE_LOOKUP(const MIPSInstruction_t & instruction);
	static const R5900InstructionInfo_t & R5900_INSTRUCTION_SPECIAL_LOOKUP(const MIPSInstruction_t & instruction);
	static const R5900InstructionInfo_t & R5900_INSTRUCTION_REGIMM_LOOKUP(const MIPSInstruction_t & instruction);
	static const R5900InstructionInfo_t & R5900_INSTRUCTION_MMI_LOOKUP(const MIPSInstruction_t & instruction);
	static const R5900InstructionInfo_t & R5900_INSTRUCTION_MMI0_LOOKUP(const MIPSInstruction_t & instruction);
	static const R5900InstructionInfo_t & R5900_INSTRUCTION_MMI1_LOOKUP(const MIPSInstruction_t & instruction);
	static const R5900InstructionInfo_t & R5900_INSTRUCTION_MMI2_LOOKUP(const MIPSInstruction_t & instruction);
	static const R5900InstructionInfo_t & R5900_INSTRUCTION_MMI3_LOOKUP(const MIPSInstruction_t & instruction);
	static const R5900InstructionInfo_t & R5900_INSTRUCTION_COP0_LOOKUP(const MIPSInstruction_t & instruction);
	static const R5900InstructionInfo_t & R5900_INSTRUCTION_BC0_LOOKUP(const MIPSInstruction_t & instruction);
	static const R5900InstructionInfo_t & R5900_INSTRUCTION_C0_LOOKUP(const MIPSInstruction_t & instruction);
	static const R5900InstructionInfo_t & R5900_INSTRUCTION_COP1_LOOKUP(const MIPSInstruction_t & instruction);
	static const R5900InstructionInfo_t & R5900_INSTRUCTION_BC1_LOOKUP(const MIPSInstruction_t & instruction);
	static const R5900InstructionInfo_t & R5900_INSTRUCTION_S_LOOKUP(const MIPSInstruction_t & instruction);
	static const R5900InstructionInfo_t & R5900_INSTRUCTION_W_LOOKUP(const MIPSInstruction_t & instruction);
	static const R5900InstructionInfo_t & R5900_INSTRUCTION_COP2_LOOKUP(const MIPSInstruction_t & instruction);

	/*
	Instruction Tables. Each table contains either instructions or classes (sub-groups of instructions), in the form of R5900InstructionInfo_t.
	There is a corresponding logic function which handles the access to these tables.
	*/
	static const R5900InstructionInfo_t R5900_W_TABLE[64];
	static const R5900InstructionInfo_t R5900_S_TABLE[64];
	static const R5900InstructionInfo_t R5900_BC1_TABLE[32];
	static const R5900InstructionInfo_t R5900_COP1_TABLE[32];
	static const R5900InstructionInfo_t R5900_C0_TABLE[64];
	static const R5900InstructionInfo_t R5900_BC0_TABLE[32];
	static const R5900InstructionInfo_t R5900_COP0_TABLE[32];
	static const R5900InstructionInfo_t R5900_MMI3_TABLE[32];
	static const R5900InstructionInfo_t R5900_MMI2_TABLE[32];
	static const R5900InstructionInfo_t R5900_MMI1_TABLE[32];
	static const R5900InstructionInfo_t R5900_MMI0_TABLE[32];
	static const R5900InstructionInfo_t R5900_MMI_TABLE[64];
	static const R5900InstructionInfo_t R5900_REGIMM_TABLE[32];
	static const R5900InstructionInfo_t R5900_SPECIAL_TABLE[64];
	static const R5900InstructionInfo_t R5900_OPCODE_TABLE[64];

	/*
	An unknown instruction constant, used in tables not implemented.
	*/
	static const R5900InstructionInfo_t R5900_INSTRUCTION_UNDEFINED;
};

