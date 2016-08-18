#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/Types/MIPSInstruction/MIPSInstruction_t.h"
#include "Common/Types/Registers/Register32_t.h"

MIPSInstruction_t::MIPSInstruction_t(u32 instructionValue)
{
	this->mInstructionValue = instructionValue;
}

void MIPSInstruction_t::setInstruction(const u32 instructionValue)
{
	mInstructionValue = instructionValue;
}

INLINE u8 MIPSInstruction_t::getOpcode() const
{
	return (static_cast<u8>(mInstructionValue >> 26) & 0x3F);
}

// R instruction functions

INLINE u8 MIPSInstruction_t::getRRs() const
{
	return (static_cast<u8>(mInstructionValue >> 21) & 0x1F);
}

INLINE u8 MIPSInstruction_t::getRRt() const
{
	return (static_cast<u8>(mInstructionValue >> 16) & 0x1F);
}

INLINE u8 MIPSInstruction_t::getRRd() const
{
	return (static_cast<u8>(mInstructionValue >> 11) & 0x1F);
}

INLINE u8 MIPSInstruction_t::getRShamt() const
{
	return (static_cast<u8>(mInstructionValue >> 6) & 0x1F);
}

INLINE u8 MIPSInstruction_t::getRFunct() const
{
	return (static_cast<u8>(mInstructionValue) & 0x3F);
}

// J instruction functions

INLINE s32 MIPSInstruction_t::getJOffsetAddress() const
{
	// A sign-extension is needed. Done by testing if the 25th bit is eq to 1. If so, OR's the original result with the value that contains 1's in the upper bits. Else OR's with 0.
	return (mInstructionValue & 0x03ffffff) | ((mInstructionValue & 0x02000000) ? 0xFC000000 : 0x00);
}

INLINE u32 MIPSInstruction_t::getJJumpAddress(Register32_t& PC) const
{
	u32 address = getJOffsetAddress();
	return ((address << 2) + (PC.UW & 0xf0000000));
}

// I instruction functions

INLINE u8 MIPSInstruction_t::getIRs() const
{
	return (static_cast<u8>(mInstructionValue >> 21) & 0x1F);
}

INLINE u8 MIPSInstruction_t::getIRt() const
{
	return (static_cast<u8>(mInstructionValue >> 16) & 0x1F);
}

INLINE u16 MIPSInstruction_t::getIImmU() const
{
	return static_cast<u16>(mInstructionValue & 0xFFFF);
}

INLINE s16 MIPSInstruction_t::getIImmS() const
{
	return (static_cast<s16>(mInstructionValue) & 0xFFFF);
}

INLINE u8 MIPSInstruction_t::getIImmSignBit() const
{
	return (static_cast<u8>(mInstructionValue >> 15) & 0x1);
}

INLINE u32 MIPSInstruction_t::getIBranchAddress(Register32_t& PC) const
{
	s32 IMM32 = static_cast<s32>(getIImmS());
	return static_cast<u32>((IMM32 << 2) + PC.UW);
}

INLINE u16 MIPSInstruction_t::getITrapCode() const
{
	return static_cast<u16>((getIImmU() >> 6) & 0x3FF);
}