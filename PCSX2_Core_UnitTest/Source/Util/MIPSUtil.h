#pragma once

#include <Common/Global/Globals.h>

class MIPSUtil
{
public:
	static u32 genRInstruction(int opcode, int s, int t, int d, int shamt, int funct)
	{
		return (((opcode & 0x3F) << 26) | ((s & 0x1F) << 21) | ((t & 0x1F) << 16) | ((d & 0x1F) << 11) | ((shamt & 0x1F) << 6) | ((funct & 0x3F) << 0));
	}

	static u32 genIInstruction(int opcode, int s, int t, int imm)
	{
		return (((opcode & 0x3F) << 26) | ((s & 0x1F) << 21) | ((t & 0x1F) << 16) | ((imm & 0xFFFF) << 0));
	}

	static u32 genJInstruction(int opcode, int target)
	{
		return (((opcode & 0x1F) << 26) | ((target & 0x3FFFFFF) << 0));
	}
};