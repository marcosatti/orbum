#pragma once

#include "Common/Global/Globals.h"
#include "Common/Types/MIPSInstruction/MIPSInstruction_t.h"

/*
Encapsulates information about any MIPS instruction defined.
See comments below, next to each field.
*/
struct MIPSInstructionInfo_t
{
	enum class InstructionType
	{
		CLASS,
		INSTRUCTION
	};

	enum class BranchDelayType
	{
		NONE,
		BRANCH_DELAY,
		BRANCH_DELAY_LIKELY,
		BRANCH_NO_DELAY
	};

	// Constructor.
	MIPSInstructionInfo_t(
		const char * const            baseClass, 
		const u8                      classIndex, 
		const InstructionType         instructionType, 
		const char* const             mnemonic, 
		const u32                     implementationIndex, 
		const BranchDelayType         branchDelayType, 
		const u32                     cycles, 
		const MIPSInstructionInfo_t & (*const lookupFunction)(const MIPSInstruction_t& instruction)
	);

	const char *const               mBaseClass;                                                     // Name of the base class the instruction is within.
	const u8                        mClassIndex;                                                    // Index of the instruction/subclass within the class. For example in the OPCODE table, the COP0 subclass has class index = 16.
	const InstructionType           mInstructionType;                                               // Within the class table, is it a (sub-)class or an instruction? TODO: This needs a better name (along with the enum name).
	const char *const               mMnemonic;                                                      // A string representation of the instruction or subclass.
	const u32                       mImplementationIndex;                                           // A unique index which is used by an execution core to define and run an instruction. See the example in the header of this file.
	const BranchDelayType           mBranchDelayType;                                               // Some instructions have a branch delay feature, where the next instruction immediately after is executed regardless if a branch is taken or not. Most of the time it will be NONE. See the EE Core Users Manual page 44 for more information.
	const u32                       mCycles;                                                        // An approximate number of CPU cycles the instruction takes to execute, which is useful for performance tracking and timing.
	const MIPSInstructionInfo_t & (*const mLookupFuncion)(const MIPSInstruction_t & instruction); // When a sub-class is encountered, this variable points to a lookup function containing the logic needed for accessing the sub-class table properly.
};