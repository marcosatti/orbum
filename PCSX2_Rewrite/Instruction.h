#pragma once

#include "Globals.h"
#include "PS2Types.h"

/*
A base instruction class which is extended by other instruction classes.
*/

NAMESPACE_R5900_START

// TODO: make immutable as the instruction shouldn't be changed after creation.
class Instruction {
public:
	/*
	instruction holds the entire MIPS instruction, which the child class' convenience functions operate off.
	An instruction follows the MIPS format, see for example here: https://en.wikibooks.org/wiki/MIPS_Assembly/Instruction_Formats
	Also see the EE Core Instruction Set Manual.
	An instruction is always 4 bytes long (32-bit), and always has an opcode field occupying bits 26-31 throughout the types of instructions.
	*/
	u32 instruction;

	/*
	Initialise an Instruction object with the specified 32-bit MIPS instruction.
	*/
	Instruction(u32 instruction);

	/*
	Returns the opcode field of the instruction.
	The opcode field is always located at bits 26-31 of the instruction.
	*/
	INLINE u8 getOpcode();
};

NAMESPACE_R5900_END