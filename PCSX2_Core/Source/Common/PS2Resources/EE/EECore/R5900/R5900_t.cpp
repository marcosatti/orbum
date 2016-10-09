#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/EE/EECore/R5900/R5900_t.h"
#include "Common/PS2Constants/PS2Constants.h"
#include "Common/PS2Resources/Types/Registers/Register32_t.h"
#include "Common/PS2Resources/Types/Registers/Register128_t.h"
#include "Common/PS2Resources/EE/EECore/R5900/Types/ZeroRegister128_t.h"
#include "Common/PS2Resources/EE/EECore/R5900/Types/PCRegister32_t.h"
#include "Common/PS2Resources/EE/EECore/R5900/Types/LinkRegister128_t.h"

R5900_t::R5900_t(const PS2Resources_t* const PS2Resources) : 
	PS2ResourcesSubobject(PS2Resources),
	ZeroRegister(std::make_shared<ZeroRegister128_t>()),
	LinkRegister(std::make_shared<LinkRegister128_t>(getRootResources())),
	GPR{ ZeroRegister, std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(),
		 std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(),
		 std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(),
		 std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), LinkRegister },
	HI(std::make_shared<Register128_t>()),
	LO(std::make_shared<Register128_t>()),
	SA(std::make_shared<Register32_t>()),
	PC(std::make_shared<PCRegister32_t>()),
	mIsInBranchDelay(false),
	mBranchDelayCycles(0),
	mBranchDelayPCTarget(0x0)
{
}

void R5900_t::setBranchDelayPCTarget(u32 pcTarget, u8 cycles)
{
	// TODO: Logic subject to change. May not work once everything is in place.
	mIsInBranchDelay = true;
	mBranchDelayCycles = cycles;
	mBranchDelayPCTarget = pcTarget;
}

void R5900_t::setBranchDelayPCJRegion(u32 JInstructionTarget, u8 cycles)
{
	// TODO: Logic subject to change. May not work once everything is in place.
	mIsInBranchDelay = true;
	mBranchDelayCycles = cycles;
	mBranchDelayPCTarget = ((PC->getPCValue() + Constants::SIZE_MIPS_INSTRUCTION) & 0xF0000000) + (JInstructionTarget << 2); // New PC = (Current PC + 4)[bits 31-28] || (JInstructionTarget << 2). See for example the instruction JAL for more info.
}

void R5900_t::setBranchDelayPCIOffset(s16 IInstructionOffset, u8 cycles)
{
	// TODO: Logic subject to change. May not work once everything is in place.
	mIsInBranchDelay = true;
	mBranchDelayCycles = cycles;
	mBranchDelayPCTarget = (PC->getPCValue() + Constants::SIZE_MIPS_INSTRUCTION) + (IInstructionOffset << 2); // New PC = Current PC + 4 + JInstructionTarget. See for example the instruction BGEZALL for more info.
}

const bool & R5900_t::isInBranchDelaySlot() const
{
	// TODO: Logic subject to change. May not work once everything is in place.
	return mIsInBranchDelay;
}
