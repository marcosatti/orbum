#pragma once

#include "Globals.h"
#include "PS2Types.h"
#include "Instruction.h"

/*
IInstruction defines the I MIPS format instruction used by the R5900.
Extended off the base Instruction class (Instruction.h).
See EE Core Instruction Set Manual or https://en.wikibooks.org/wiki/MIPS_Assembly/Instruction_Formats for more information.
*/

NAMESPACE_R5900_START

class IInstruction : public Instruction
{
public:
	/*
	Initialise a IInstruction object.
	There is no attempt to verify that an I instruction was parsed - it is up to the user.
	*/
	IInstruction(u32 i_instruction);

	/*
	Get functions for the various I instruction fields:
	- Rs					 @ bits 21-25
	- Rd					 @ bits 16-20
	- IMM (immediate value)  @ bits 0-15

	There is a signed/unsigned immediate get function provided (getImmU and getImmS) as well as get the sign bit function.
	A branch address calculation function is provided based on the signed IMM value shitfted left by 2, added to the PC of the next instruction (branch delay slot).
	A convenience get trap code function (from a valid trap instruction such as TEQ) is available (from bits 6-15 of IMM).
	*/
	u8 getRs();
	u8 getRd();
	u16 getImmU();
	s16 getImmS();
	u8 getSignBit();
	u32 getBranchAddress(Register32 PC);
	u16 getTrapCode();
};

NAMESPACE_R5900_END