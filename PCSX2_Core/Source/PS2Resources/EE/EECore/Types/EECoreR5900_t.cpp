#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "PS2Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "Common/Types/Registers/Register32_t.h"
#include "Common/Types/Registers/Register128_t.h"
#include "Common/Types/Registers/Constant/ConstantRegister128_t.h"
#include "Common/Types/Registers/PCRegister32_t.h"
#include "Common/Types/Registers/LinkRegister128_t.h"

EECoreR5900_t::EECoreR5900_t() : 
	mIsInBranchDelay(false),
	mBranchDelayCycles(0),
	mBranchDelayPCTarget(0x0),
	PC(std::make_shared<PCRegister32_t>()),
	ZeroRegister(std::make_shared<ConstantRegister128_t>()),
	LinkRegister(std::make_shared<LinkRegister128_t>(PC)),
	GPR{ ZeroRegister, std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(),
		std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(),
		std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(),
		std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), LinkRegister },
	HI(std::make_shared<Register128_t>()),
	LO(std::make_shared<Register128_t>()),
	SA(std::make_shared<Register32_t>())
{
}

void EECoreR5900_t::setBranchDelayPCTarget(u32 pcTarget, u8 cycles)
{
	// TODO: Logic subject to change. May not work once everything is in place.
	mIsInBranchDelay = true;
	mBranchDelayCycles = cycles;
	mBranchDelayPCTarget = pcTarget;
}

void EECoreR5900_t::setBranchDelayPCJRegion(u32 JInstructionTarget, u8 cycles)
{
	// TODO: Logic subject to change. May not work once everything is in place.
	mIsInBranchDelay = true;
	mBranchDelayCycles = cycles;
	mBranchDelayPCTarget = ((PC->readWord(Context_t::EE) + Constants::SIZE_MIPS_INSTRUCTION) & 0xF0000000) + (JInstructionTarget << 2); // New PC = (Current PC + 4)[bits 31-28] || (JInstructionTarget << 2). See for example the instruction JAL for more info.
}

void EECoreR5900_t::setBranchDelayPCIOffset(s16 IInstructionOffset, u8 cycles)
{
	// TODO: Logic subject to change. May not work once everything is in place.
	mIsInBranchDelay = true;
	mBranchDelayCycles = cycles;
	mBranchDelayPCTarget = (PC->readWord(Context_t::EE) + Constants::SIZE_MIPS_INSTRUCTION) + (IInstructionOffset << 2); // New PC = Current PC + 4 + JInstructionTarget. See for example the instruction BGEZALL for more info.
}

const bool & EECoreR5900_t::isInBranchDelaySlot() const
{
	// TODO: Logic subject to change. May not work once everything is in place.
	return mIsInBranchDelay;
}
