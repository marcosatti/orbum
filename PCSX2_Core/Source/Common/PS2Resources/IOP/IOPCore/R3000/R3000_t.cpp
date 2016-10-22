#include "stdafx.h"

#include "Common/PS2Resources/IOP/IOPCore/R3000/R3000_t.h"
#include "Common/PS2Resources/Types/Registers/Register32_t.h"
#include "Common/PS2Resources/Types/Registers/PCRegister32_t.h"
#include "Common/PS2Resources/IOP/IOPCore/R3000/Types/ZeroRegister32_t.h"
#include "Common/PS2Resources/IOP/IOPCore/R3000/Types/LinkRegister32_t.h"

R3000_t::R3000_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),
	ZeroRegister(std::make_shared<ZeroRegister32_t>()),
	LinkRegister(std::make_shared<LinkRegister32_t>(getRootResources())),
	GPR{ ZeroRegister, std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(),
	std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(),
	std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(),
	std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), LinkRegister },
	HI(std::make_shared<Register32_t>()),
	LO(std::make_shared<Register32_t>()),
	PC(std::make_shared<PCRegister32_t>()),
	mIsInBranchDelay(false),
	mBranchDelayCycles(0),
	mBranchDelayPCTarget(0x0)
{
}

void R3000_t::setBranchDelayPCTarget(u32 pcTarget, u8 cycles)
{
	// TODO: Logic subject to change. May not work once everything is in place.
	mIsInBranchDelay = true;
	mBranchDelayCycles = cycles;
	mBranchDelayPCTarget = pcTarget;
}

void R3000_t::setBranchDelayPCJRegion(u32 JInstructionTarget, u8 cycles)
{
	// TODO: Logic subject to change. May not work once everything is in place.
	mIsInBranchDelay = true;
	mBranchDelayCycles = cycles;
	mBranchDelayPCTarget = ((PC->getPCValue() + Constants::SIZE_MIPS_INSTRUCTION) & 0xF0000000) + (JInstructionTarget << 2); // New PC = (Current PC + 4)[bits 31-28] || (JInstructionTarget << 2). See for example the instruction JAL for more info.

}

void R3000_t::setBranchDelayPCIOffset(s16 IInstructionOffset, u8 cycles)
{
	// TODO: Logic subject to change. May not work once everything is in place.
	mIsInBranchDelay = true;
	mBranchDelayCycles = cycles;
	mBranchDelayPCTarget = (PC->getPCValue() + Constants::SIZE_MIPS_INSTRUCTION) + (IInstructionOffset << 2); // New PC = Current PC + 4 + JInstructionTarget. See for example the instruction BGEZALL for more info.
}

const bool& R3000_t::isInBranchDelaySlot() const
{
	// TODO: Logic subject to change. May not work once everything is in place.
	return mIsInBranchDelay;
}
