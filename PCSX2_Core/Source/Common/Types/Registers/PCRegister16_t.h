#pragma once

#include "Common/Global/Globals.h"

#include "Common/Types/Registers/Register16_t.h"

/*
Represents a 16-bit program counter register. 
Currently used as the PC register for the VU units.
*/
class PCRegister16_t : public Register16_t
{
public:

	/*
	Returns the current PC value.
	*/
	u16 getPCValue();

	/*
	Set the PC to a relative value.
	*/
	void setPCValueRelative(const s16 & relativeLocation);

	/*
	Set the PC to an absolute value.
	*/
	void setPCValueAbsolute(const u16 & absoluteLocation);

	/*
	Increments the PC by a default size of 4 bytes (equal to the size of a MIPS instruction).
	*/
	void setPCValueNext(const u16 instructionSize = Constants::SIZE_MIPS_INSTRUCTION);
};

