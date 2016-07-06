#include "stdafx.h"

#include "Globals.h"
#include "PS2Types.h"
#include "IInstruction.h"

NAMESPACE_R5900_START

/*
Construct an I instruction. See base class Instruction constructor.
For all function documentation, see the IInstruction.h header.
*/
IInstruction::IInstruction(u32 i_instruction) : Instruction(i_instruction)
{
}

u8 IInstruction::getRs()
{
	return ((u8)(instruction >> 21) & 0x1F);
}

u8 IInstruction::getRd()
{
	return ((u8)(instruction >> 16) & 0x1F);
}

u16 IInstruction::getImmU()
{
	return ((u16)(instruction) & 0xFFFF);
}

s16 IInstruction::getImmS()
{
	return ((s16)(instruction) & 0xFFFF);
}

u8 IInstruction::getSignBit()
{
	return ((u8)(instruction >> 15) & 0x1);
}

u32 IInstruction::getBranchAddress(Register32 PC)
{
	s32 IMM32 = (s32)getImmS();
	return (u32)((IMM32 << 2) + PC.UW);
}

u16 IInstruction::getTrapCode()
{
	return (u16)((getImmU() >> 6) & 0x3FF);
}

NAMESPACE_R5900_END

