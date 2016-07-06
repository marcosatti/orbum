#include "stdafx.h"

#include "Globals.h"
#include "PS2Types.h"
#include "RInstruction.h"

NAMESPACE_R5900_START

/*
Construct an R instruction. See base class Instruction constructor.
For all function documentation, see the RInstruction.h header.
*/
RInstruction::RInstruction(u32 r_instruction) : Instruction(r_instruction)
{
}

u8 RInstruction::getRs()
{
	return ((u8)(instruction >> 21) & 0x1F);
}

u8 RInstruction::getRt()
{
	return ((u8)(instruction >> 16) & 0x1F);
}

u8 RInstruction::getRd()
{
	return ((u8)(instruction >> 11) & 0x1F);
}

u8 RInstruction::getShamt()
{
	return ((u8)(instruction >> 6) & 0x1F);
}

u8 RInstruction::getFunct()
{
	return ((u8)(instruction) & 0x3F);
}


NAMESPACE_R5900_END

