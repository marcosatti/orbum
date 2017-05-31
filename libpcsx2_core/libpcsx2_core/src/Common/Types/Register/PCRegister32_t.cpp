#include "Common/Types/Register/PCRegister32_t.h"

PCRegister32_t::PCRegister32_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	Register32_t(mnemonic, debugReads, debugWrites),
	mBranchDelayCycles(0),
	mBranchDelayPC(0)
{
}

void PCRegister32_t::next(const Context_t context)
{
	// Check if we should execute the branch delay or increment the PC by 1 instruction.
	if (mBranchDelayCycles > 0)
	{
		mBranchDelayCycles--;
		if (mBranchDelayCycles == 0)
			setPCValueAbsolute(context, mBranchDelayPC);
		else
			setPCValueRelative(context, Constants::MIPS::SIZE_MIPS_INSTRUCTION);
	}
	else
	{
		setPCValueRelative(context, Constants::MIPS::SIZE_MIPS_INSTRUCTION);
	}
}

void PCRegister32_t::setPCValueRelative(const Context_t context, const s32 relativePC)
{
	writeWord(context, readWord(context) + relativePC);
}

void PCRegister32_t::setPCValueAbsolute(const Context_t context, const u32 absolutePC)
{
	writeWord(context, absolutePC);
}

void PCRegister32_t::setBranchPCAbsolute(const u32 pc, const int cycles)
{
	mBranchDelayCycles = cycles;
	mBranchDelayPC = pc;
}

void PCRegister32_t::setBranchPCJRegion(const Context_t context, const u32 JInstructionTarget, const int cycles)
{
	mBranchDelayCycles = cycles;

	// New PC = (Current PC)[bits 31-28] | (JInstructionTarget << 2). See for example the instruction JAL for more info.
	mBranchDelayPC = ((readWord(context) + Constants::MIPS::SIZE_MIPS_INSTRUCTION) & 0xF0000000) | (JInstructionTarget << 2);
}

void PCRegister32_t::setBranchPCIOffset(const Context_t context, const s16 IInstructionOffset, const int cycles)
{
	mBranchDelayCycles = cycles;

	// New PC = (Current PC + 4) + IInstructionOffset. See for example the instruction BGEZALL for more info.
	mBranchDelayPC = (readWord(context) + Constants::MIPS::SIZE_MIPS_INSTRUCTION) + (IInstructionOffset << 2);
}

void PCRegister32_t::doBranchNow(const Context_t context)
{
	mBranchDelayCycles = 0;
	setPCValueAbsolute(context, mBranchDelayPC);
}

bool PCRegister32_t::isBranchPending() const
{
	return (mBranchDelayCycles > 0);
}

void PCRegister32_t::resetBranch()
{
	mBranchDelayCycles = 0;
}
