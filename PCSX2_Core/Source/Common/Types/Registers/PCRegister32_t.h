#pragma once

#include "Common/Global/Globals.h"

#include "Common/Types/Registers/Register32_t.h"

/*
Represents the program counter register of a MIPS CPU. It is defined as 32-bits long.
Extends a normal 32-bit register to provide convenience functions for manipulating the PC value.
*/
class PCRegister32_t : public Register32_t
{
public:
	/*
	Set the PC to a relative value.
	*/
	void setPCValueRelative(const s32& relativeLocation);

	/*
	Set the PC to an absolute value.
	*/
	void setPCValueAbsolute(const u32& absoluteLocation);

	/*
	Increments the PC by a default size of 4 bytes (equal to the size of a MIPS instruction).
	*/
	void setPCValueNext(const u32 instructionSize = Constants::SIZE_MIPS_INSTRUCTION);
};

