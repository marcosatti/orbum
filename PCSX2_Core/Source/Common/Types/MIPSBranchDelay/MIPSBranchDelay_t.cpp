#include "stdafx.h"

#include "Common/Types/MIPSBranchDelay/MIPSBranchDelay_t.h"
#include "Common/Types/Registers/MIPS/PCRegister32_t.h"

MIPSBranchDelay_t::MIPSBranchDelay_t(std::shared_ptr<PCRegister32_t>& pcRegister32) :
	mPCRegister32(pcRegister32), 
	mBranchDelayCycles(0), 
	mBranchDelayPC(0)
{
}

void MIPSBranchDelay_t::handleBranchDelay()
{
	// Dont do anything if cycles is at 0 (not in a branch delay).
	if (mBranchDelayCycles != 0)
	{
		// Decrement cycles.
		mBranchDelayCycles--;

		// Now check if we should change the PC now.
		if (mBranchDelayCycles == 0)
			mPCRegister32->setPCValueAbsolute(mBranchDelayPC);
	}
}

void MIPSBranchDelay_t::executeBranchDelayNow()
{
	// Set cycles to 0 and set PC now.
	mBranchDelayCycles = 0;
	mPCRegister32->setPCValueAbsolute(mBranchDelayPC);
}

void MIPSBranchDelay_t::resetBranchDelay()
{
	mBranchDelayCycles = 0;
}

void MIPSBranchDelay_t::setBranchDelayPCAbsolute(const u32 & pc, const u8 & cycles)
{
	mBranchDelayCycles = cycles;
	mBranchDelayPC = pc;
}

void MIPSBranchDelay_t::setBranchDelayPCJRegion(const u32& JInstructionTarget, const u8& cycles)
{
	mBranchDelayCycles = cycles;

	// New PC = (Current PC)[bits 31-28] | (JInstructionTarget << 2). See for example the instruction JAL for more info.
	mBranchDelayPC = (mPCRegister32->readWord(Context_t::RAW) & 0xF0000000) | (JInstructionTarget << 2);
}

void MIPSBranchDelay_t::setBranchDelayPCIOffset(const s16& IInstructionOffset, const u8& cycles)
{
	mBranchDelayCycles = cycles;

	// New PC = Current PC + IInstructionOffset. See for example the instruction BGEZALL for more info.
	mBranchDelayPC = mPCRegister32->readWord(Context_t::RAW) + (IInstructionOffset << 2); 
}

bool MIPSBranchDelay_t::isInBranchDelay() const
{
	return (mBranchDelayCycles > 0);
}
