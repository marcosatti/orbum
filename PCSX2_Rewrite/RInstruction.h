#pragma once

#include "Globals.h"
#include "PS2Types.h"
#include "Instruction.h"

/*
RInstruction defines the R MIPS format instruction used by the R5900. 
Extended off the base Instruction class (Instruction.h).
See EE Core Instruction Set Manual or https://en.wikibooks.org/wiki/MIPS_Assembly/Instruction_Formats for more information.
*/

NAMESPACE_R5900_START

class RInstruction : public Instruction 
{
public:
	/*
	Initialise a RInstruction object. 
	There is no attempt to verify that an R instruction was parsed - it is up to the user.
	*/
	RInstruction(u32 r_instruction);

	/*
	Get functions for the various R instruction fields:
	 - Rs					@ bits 21-25
	 - Rt					@ bits 16-20
	 - Rd					@ bits 11-15
	 - shamt (shift amount) @ bits 6-10
	 - funct (function)		@ bits 0-5
	*/
	u8 getRs();
	u8 getRt();
	u8 getRd();
	u8 getShamt();
	u8 getFunct();
};

NAMESPACE_R5900_END