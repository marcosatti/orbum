#include "stdafx.h"

#include "Globals.h"

#include "Instruction_t.h"
#include "Register_t.h"

Instruction_t::Instruction_t(u32 instructionValue)
{
	this->mInstructionValue = instructionValue;
}

void Instruction_t::setInstruction(const u32 instructionValue)
{
	mInstructionValue = instructionValue;
}

INLINE u8 Instruction_t::getOpcode() const
{
	return (static_cast<u8>(mInstructionValue >> 26) & 0x3F);
}

// R instruction functions

INLINE u8 Instruction_t::getRRs() const
{
	return (static_cast<u8>(mInstructionValue >> 21) & 0x1F);
}

INLINE u8 Instruction_t::getRRt() const
{
	return (static_cast<u8>(mInstructionValue >> 16) & 0x1F);
}

INLINE u8 Instruction_t::getRRd() const
{
	return (static_cast<u8>(mInstructionValue >> 11) & 0x1F);
}

INLINE u8 Instruction_t::getRShamt() const
{
	return (static_cast<u8>(mInstructionValue >> 6) & 0x1F);
}

INLINE u8 Instruction_t::getRFunct() const
{
	return (static_cast<u8>(mInstructionValue) & 0x3F);
}

// J instruction functions

INLINE s32 Instruction_t::getJPAddress() const
{
	// A sign-extension is needed. Done by testing if the 25th bit is eq to 1. If so, OR's the original result with the value that contains 1's in the upper bits. Else OR's with 0.
	return (mInstructionValue & 0x03ffffff) | ((mInstructionValue & 0x02000000) ? 0xFC000000 : 0x00);
}

INLINE u32 Instruction_t::getJJumpAddress(Register32_t& PC) const
{
	u32 address = getJPAddress();
	return ((address << 2) + (PC.UW & 0xf0000000));
}

// I instruction functions

INLINE u8 Instruction_t::getIRs() const
{
	return (static_cast<u8>(mInstructionValue >> 21) & 0x1F);
}

INLINE u8 Instruction_t::getIRd() const
{
	return (static_cast<u8>(mInstructionValue >> 16) & 0x1F);
}

INLINE u16 Instruction_t::getIImmU() const
{
	return static_cast<u16>(mInstructionValue & 0xFFFF);
}

INLINE s16 Instruction_t::getIImmS() const
{
	return (static_cast<s16>(mInstructionValue) & 0xFFFF);
}

INLINE u8 Instruction_t::getISignBit() const
{
	return (static_cast<u8>(mInstructionValue >> 15) & 0x1);
}

INLINE u32 Instruction_t::getIBranchAddress(Register32_t& PC) const
{
	s32 IMM32 = static_cast<s32>(getIImmS());
	return static_cast<u32>((IMM32 << 2) + PC.UW);
}

INLINE u16 Instruction_t::getITrapCode() const
{
	return static_cast<u16>((getIImmU() >> 6) & 0x3FF);
}