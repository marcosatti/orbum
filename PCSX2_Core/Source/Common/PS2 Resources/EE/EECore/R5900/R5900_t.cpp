#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/PS2 Resources/EE/EECore/R5900/R5900_t.h"

R5900_t::R5900_t(const PS2Resources_t* const PS2Resources): PS2ResourcesSubobject(PS2Resources)
{
	mIsBranchDelayPending = false;
	mBranchDelayCycles = 0;
	mBranchDelayPCTarget = 0x0;
}

void R5900_t::setBranchDelayPCTarget(u32 pcTarget, u8 cycles)
{
	mIsBranchDelayPending = true;
	mBranchDelayCycles = cycles;
	mBranchDelayPCTarget = pcTarget;
}

void R5900_t::setBranchDelayPCJOffset(s32 JInstructionTarget, u8 cycles)
{
	mIsBranchDelayPending = true;
	mBranchDelayCycles = cycles;
	mBranchDelayPCTarget = (JInstructionTarget << 2) + (PC->getPCValue() & 0xF0000000);
}

void R5900_t::setBranchDelayPCIOffset(s16 IInstructionOffset, u8 cycles)
{
	mIsBranchDelayPending = true;
	mBranchDelayCycles = cycles;
	mBranchDelayPCTarget = (IInstructionOffset << 2) + PC->getPCValue();
}

void R5900_t::checkBranchDelaySlot()
{
	if (mIsBranchDelayPending)
	{
		if (mBranchDelayCycles == 0)
		{
			PC->setPCValueAbsolute(mBranchDelayPCTarget);
			mIsBranchDelayPending = false;
			mIsInBranchDelay = true;
		}
		else
		{
			mBranchDelayCycles--;
			mIsInBranchDelay = false;
		}
	}
	else
		mIsInBranchDelay = false;
}

const bool & R5900_t::isInBranchDelaySlot() const
{
	return mIsInBranchDelay;
}
