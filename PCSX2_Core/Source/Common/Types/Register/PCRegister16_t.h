#pragma once

#include "Common/Global/Globals.h"

#include "Common/Types/Register/Register16_t.h"

/*
Represents a 16-bit program counter register. 
Currently used as the PC register for the VU units.
*/
class PCRegister16_t : public Register16_t
{
public:
	explicit PCRegister16_t(const char * mnemonic, const bool debugReads, const bool debugWrites);

	/*
	Set the PC to a relative value.
	*/
	void setPCValueRelative(const System_t context, const s16 relativeLocation);

	/*
	Set the PC to an absolute value.
	*/
	void setPCValueAbsolute(const System_t context, const u16 absoluteLocation);

	/*
	Increments the PC by a default size of 4 bytes (equal to the size of a MIPS instruction).
	*/
	void setPCValueNext(const System_t context, const u16 instructionSize = Constants::MIPS::SIZE_MIPS_INSTRUCTION);
};

