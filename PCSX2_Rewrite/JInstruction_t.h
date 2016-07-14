#pragma once

#include "Globals.h"
#include "Register_t.h"
#include "Instruction_t.h"

/*
JInstruction_t defines the J MIPS format instruction used by the R5900.
Extended off the base Instruction class (Instruction.h).
See EE Core Instruction Set Manual or https://en.wikibooks.org/wiki/MIPS_Assembly/Instruction_Formats for more information.
*/

class JInstruction_t : public Instruction_t
{
public:
	/*
	Initialise a JInstruction_t object.
	There is no attempt to verify that an J instruction was parsed - it is up to the user.
	*/
	JInstruction_t(u32 j_instruction);

	/*
	Get functions for the various J instruction fields:
	- Pseudo-address @ bits 0-25

	The pseudo-address (PA) is not the jump location - rather it is calculated based on the PA, the 4 high bits of the PC of the next instruction (branch delay slot) at the most significant bits and 2 bits set to 0 at the least significant bits.
	See documentation mentioned above for a more elaborate explanation.
	- getPAddress returns the raw pseudo-address contained in the instruction.
	- getAddress returns the real address based on the pseudo-address and the other factors mentioned above.
	*/
	u32 getPAddress();
	u32 getJumpAddress(Register32_t PC);
};
