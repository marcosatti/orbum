#include "stdafx.h"

#include "Globals.h"
#include "Instruction.h"

NAMESPACE_R5900_START

Instruction::Instruction(u32 instruction)
{
	this->instruction = instruction;
}

u8 Instruction::getOpcode()
{
	return ((u8)(instruction >> 26) & 0x3F);
}

NAMESPACE_R5900_END