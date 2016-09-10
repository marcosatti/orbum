#pragma once

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/Types/MIPSInstruction/MIPSInstruction_t.h"

/*
Static class used as the EECore instruction lookup.
This uses the Instruction/Class hierarchy structure as defined in the EE Core Instruction Manual Appendix section.
The instruction tables are defined in EECore Instruction Implementation Register.xlsx. You can copy and paste any changes made to that file in here, but make sure the spreadsheet is the master copy.
 It is a lot easier to read the spreadsheet than looking at the source code.

The purpose of this class is to decode the given instruction, so that an execution core knows which instruction implementation to use.
For example (pseduo-code): 
 MIPSInstruction = 0xABCD1234
 Info = EECoreInstructionUtil::getInstructionInfo(MIPSInstruction)
 ExecutionCore.ExecuteInstruction(Info.mImplementationIndex)

The mImplementationIndex is a linear UNIQUE index of all of the instructions for the EECore - there should be no two instructions with the same index.
Therefore in an execution core, a simple function pointer array of size = MAX(Implementation Indexes) will be enough, which is simply used as in the example above.
*/
class EECoreInstructionUtil
{
public:
	/*
	Encapsulates information about any EECore instruction defined.
	See comments below, next to each field.
	*/
	struct EECoreInstructionInfo_t
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
		EECoreInstructionInfo_t(const char *const baseClass, const u8 classIndex, const InstructionType instructionType, const char* const mnemonic, const u32 implementationIndex, const BranchDelayType branchDelayType, const u32 cycles, const EECoreInstructionInfo_t&(*const lookupFunction)(const MIPSInstruction_t& instruction))
			: mBaseClass(baseClass),
			mClassIndex(classIndex),
			mInstructionType(instructionType),
			mMnemonic(mnemonic),
			mImplementationIndex(implementationIndex),
			mBranchDelayType(branchDelayType),
			mCycles(cycles),
			mLookupFuncion(lookupFunction)
		{
		}

		const char *const               mBaseClass;                                                     // Name of the base class the instruction is within.
		const u8                        mClassIndex;                                                    // Index of the instruction/subclass within the class. For example in the OPCODE table, the COP0 subclass has class index = 16.
		const InstructionType           mInstructionType;                                               // Within the class table, is it a (sub-)class or an instruction? TODO: This needs a better name (along with the enum name).
		const char *const               mMnemonic;                                                      // A string representation of the instruction or subclass.
		const u32                       mImplementationIndex;                                           // A unique index which is used by an execution core to define and run an instruction. See the example in the header of this file.
		const BranchDelayType           mBranchDelayType;                                               // Some instructions have a branch delay feature, where the next instruction immediately after is executed regardless if a branch is taken or not. Most of the time it will be NONE. See the EE Core Users Manual page 44 for more information.
		const u32                       mCycles;                                                        // An approximate number of CPU cycles the instruction takes to execute, which is useful for performance tracking and timing.
		const EECoreInstructionInfo_t & (*const mLookupFuncion)(const MIPSInstruction_t & instruction); // When a sub-class is encountered, this variable points to a lookup function containing the logic needed for accessing the sub-class table properly.
	};

	/*
	The main lookup function. Use this to return a information struct with the type of instruction given.
	*/
	static const EECoreInstructionInfo_t * getInstructionInfo(const MIPSInstruction_t & instruction);

	/*
	Sub lookup functions. Contain logic for accessing any child instruction table.
	*/
	static const EECoreInstructionInfo_t & EECORE_INSTRUCTION_OPCODE_LOOKUP(const MIPSInstruction_t & instruction);
	static const EECoreInstructionInfo_t & EECORE_INSTRUCTION_SPECIAL_LOOKUP(const MIPSInstruction_t & instruction);
	static const EECoreInstructionInfo_t & EECORE_INSTRUCTION_REGIMM_LOOKUP(const MIPSInstruction_t & instruction);
	static const EECoreInstructionInfo_t & EECORE_INSTRUCTION_MMI_LOOKUP(const MIPSInstruction_t & instruction);
	static const EECoreInstructionInfo_t & EECORE_INSTRUCTION_MMI0_LOOKUP(const MIPSInstruction_t & instruction);
	static const EECoreInstructionInfo_t & EECORE_INSTRUCTION_MMI1_LOOKUP(const MIPSInstruction_t & instruction);
	static const EECoreInstructionInfo_t & EECORE_INSTRUCTION_MMI2_LOOKUP(const MIPSInstruction_t & instruction);
	static const EECoreInstructionInfo_t & EECORE_INSTRUCTION_MMI3_LOOKUP(const MIPSInstruction_t & instruction);
	static const EECoreInstructionInfo_t & EECORE_INSTRUCTION_COP0_LOOKUP(const MIPSInstruction_t & instruction);
	static const EECoreInstructionInfo_t & EECORE_INSTRUCTION_BC0_LOOKUP(const MIPSInstruction_t & instruction);
	static const EECoreInstructionInfo_t & EECORE_INSTRUCTION_C0_LOOKUP(const MIPSInstruction_t & instruction);
	static const EECoreInstructionInfo_t & EECORE_INSTRUCTION_COP1_LOOKUP(const MIPSInstruction_t & instruction);
	static const EECoreInstructionInfo_t & EECORE_INSTRUCTION_BC1_LOOKUP(const MIPSInstruction_t & instruction);
	static const EECoreInstructionInfo_t & EECORE_INSTRUCTION_S_LOOKUP(const MIPSInstruction_t & instruction);
	static const EECoreInstructionInfo_t & EECORE_INSTRUCTION_W_LOOKUP(const MIPSInstruction_t & instruction);
	static const EECoreInstructionInfo_t & EECORE_INSTRUCTION_COP2_LOOKUP(const MIPSInstruction_t & instruction);

	/*
	Instruction Tables. Each table contains either instructions or classes (sub-groups of instructions), in the form of EECoreInstructionInfo_t.
	There is a corresponding logic function which handles the access to these tables.
	*/
	static const EECoreInstructionInfo_t EECORE_W_TABLE[64];
	static const EECoreInstructionInfo_t EECORE_S_TABLE[64];
	static const EECoreInstructionInfo_t EECORE_BC1_TABLE[32];
	static const EECoreInstructionInfo_t EECORE_COP1_TABLE[32];
	static const EECoreInstructionInfo_t EECORE_C0_TABLE[64];
	static const EECoreInstructionInfo_t EECORE_BC0_TABLE[32];
	static const EECoreInstructionInfo_t EECORE_COP0_TABLE[32];
	static const EECoreInstructionInfo_t EECORE_MMI3_TABLE[32];
	static const EECoreInstructionInfo_t EECORE_MMI2_TABLE[32];
	static const EECoreInstructionInfo_t EECORE_MMI1_TABLE[32];
	static const EECoreInstructionInfo_t EECORE_MMI0_TABLE[32];
	static const EECoreInstructionInfo_t EECORE_MMI_TABLE[64];
	static const EECoreInstructionInfo_t EECORE_REGIMM_TABLE[32];
	static const EECoreInstructionInfo_t EECORE_SPECIAL_TABLE[64];
	static const EECoreInstructionInfo_t EECORE_OPCODE_TABLE[64];

	/*
	An unknown instruction constant, used in tables not implemented.
	*/
	static const EECoreInstructionInfo_t EECORE_INSTRUCTION_UNDEFINED;

	/*
	EE Core CPU (R5900 & COP) cycle constants - most instructions will use one of these values for the EECoreInstructionInfo_t::mCycles field.
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
		static constexpr u32 COP0_MFC0      = 10000;
		static constexpr u32 COP1_MULTIPLY  = 32;
		static constexpr u32 COP1_DIVIDE    = 200; // TODO: This is a very rough guess. Needs testing.
	};
};

