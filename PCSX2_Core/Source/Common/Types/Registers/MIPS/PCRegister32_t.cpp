#include "stdafx.h"

#include "Common/Types/Registers/MIPS/PCRegister32_t.h"

PCRegister32_t::PCRegister32_t():
	mBranchDelayCycles(0),                                       
	mBranchDelayPC(0)
{
}

void PCRegister32_t::next()
{
	// Check if we should execute the branch delay or increment the PC by 1 instruction.
	if (mBranchDelayCycles > 0)
	{
		mBranchDelayCycles--;
		if (mBranchDelayCycles == 0)
			setPCValueAbsolute(mBranchDelayPC);
		else
			setPCValueRelative(Constants::MIPS::SIZE_MIPS_INSTRUCTION);
	}
	else
	{
		setPCValueRelative(Constants::MIPS::SIZE_MIPS_INSTRUCTION);
	}
}

void PCRegister32_t::setPCValueRelative(const s32 relativePC)
{
	writeWord(RAW, readWord(RAW) + relativePC);
}

void PCRegister32_t::setPCValueAbsolute(const u32 absolutePC)
{
	writeWord(RAW, absolutePC);
}

void PCRegister32_t::setBranchPCAbsolute(const u32 pc, const int cycles)
{
	mBranchDelayCycles = cycles;
	mBranchDelayPC = pc;
}

void PCRegister32_t::setBranchPCJRegion(const u32 JInstructionTarget, const int cycles)
{
	mBranchDelayCycles = cycles;

	// New PC = (Current PC)[bits 31-28] | (JInstructionTarget << 2). See for example the instruction JAL for more info.
	mBranchDelayPC = ((readWord(RAW) + Constants::MIPS::SIZE_MIPS_INSTRUCTION) & 0xF0000000) | (JInstructionTarget << 2);
}

void PCRegister32_t::setBranchPCIOffset(const s16 IInstructionOffset, const int cycles)
{
	mBranchDelayCycles = cycles;

	// New PC = (Current PC + 4) + IInstructionOffset. See for example the instruction BGEZALL for more info.
	mBranchDelayPC = (readWord(RAW) + Constants::MIPS::SIZE_MIPS_INSTRUCTION) + (IInstructionOffset << 2);
}

void PCRegister32_t::doBranchNow()
{
	mBranchDelayCycles = 0;
	setPCValueAbsolute(mBranchDelayPC);
}

bool PCRegister32_t::isBranchPending() const
{
	return (mBranchDelayCycles > 0);
}

void PCRegister32_t::resetBranch()
{
	mBranchDelayCycles = 0;
}
