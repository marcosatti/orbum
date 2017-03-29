#pragma once

#include "Common/Global/Globals.h"

struct MIPSInstruction_t;

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

	const char *		  mBaseClassMnemonic; // Name of the base class the instruction is within.
	const int             mClassIndex;        // Index of the instruction/subclass within the class. For example in the OPCODE table, the COP0 subclass has class index = 16.
	const InstructionType mInstructionType;   // Within the class table, is it a (sub-)class or an instruction? TODO: This needs a better name (along with the enum name).
	const char *		  mMnemonic;          // A string representation of the instruction or subclass.
	const BranchDelayType mBranchDelayType;   // Some instructions have a branch delay feature, where the next instruction immediately after is executed regardless if a branch is taken or not. Most of the time it will be NONE. See the EE Core Users Manual page 44 for more information.
	const u32             mCycles;            // An approximate number of CPU cycles the instruction takes to execute, which is useful for performance tracking and timing.
};