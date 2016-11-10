#include "stdafx.h"

#include "Common/Types/MIPSInstructionInfo/MIPSInstructionInfo_t.h"

MIPSInstructionInfo_t::MIPSInstructionInfo_t(const char* const baseClass, const u8 classIndex, const InstructionType instructionType, const char* const mnemonic, const u32 implementationIndex, const BranchDelayType branchDelayType, const u32 cycles, const MIPSInstructionInfo_t & (*const lookupFunction)(const MIPSInstruction_t& instruction)) :
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