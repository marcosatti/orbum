#pragma once

#include "Globals.h"
#include "Register_t.h"

/*
A base instruction class which is extended by other instruction classes.
*/

// TODO: make immutable as the instruction shouldn't be changed after creation.
class Instruction_t {
public:
	/*
	instruction holds the entire MIPS instruction, which the child class' convenience functions operate off.
	An instruction follows the MIPS format, see for example here: https://en.wikibooks.org/wiki/MIPS_Assembly/Instruction_Formats
	Also see the EE Core Instruction Set Manual.
	An instruction is always 4 bytes long (32-bit), and always has an opcode field occupying bits 26-31 throughout the types of instructions.
	*/
	u32 instruction;

	/*
	Initialise an Instruction object with the specified 32-bit MIPS instruction. Defaults to 0.
	*/
	Instruction_t(u32 instruction = 0);

	/*
	Returns the opcode field of the instruction.
	The opcode field is always located at bits 26-31 of the instruction.
	*/
	INLINE u8 getOpcode();
};