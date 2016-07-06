#include "stdafx.h"

#include "Globals.h"
#include "PS2Types.h"
#include "JInstruction.h"

NAMESPACE_R5900_START

/*
Construct an J instruction. See base class Instruction constructor.
For all function documentation, see the JInstruction.h header.
*/
JInstruction::JInstruction(u32 j_instruction) : Instruction(j_instruction)
{
}

u32 JInstruction::getPAddress()
{
	return (instruction & 0x03ffffff);
}

u32 JInstruction::getJumpAddress(Register32 PC)
{
	u32 address = getPAddress();
	return ((address << 2) + (PC.UW & 0xf0000000));
}

NAMESPACE_R5900_END


