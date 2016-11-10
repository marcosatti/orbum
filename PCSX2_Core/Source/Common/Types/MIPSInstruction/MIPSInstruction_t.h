#pragma once

#include "Common/Global/Globals.h"

/*
A MIPS instruction helper class which is used to hold any valid MIPS instruction and read specific values from it.
Convenience functions are provided for I, J and R instruction types, which are prefixed with 'get'.
getOpcode() is common to all instruction types, and you can use this to determine which instruction type you have.
*/

class MIPSInstruction_t {
public:
	/*
	Initialise an Instruction object with the specified 32-bit MIPS instruction. Defaults to 0.
	*/
	MIPSInstruction_t(const u32 instructionValue = 0);

	/*
	instruction holds the entire MIPS instruction, which the child class' convenience functions operate off.
	An instruction follows the MIPS format, see for example here: https://en.wikibooks.org/wiki/MIPS_Assembly/Instruction_Formats
	Also see the EE Core Instruction Set Manual.
	An instruction is always 4 bytes long (32-bit), and always has an opcode field occupying bits 26-31 throughout the types of instructions.
	*/
	u32 mInstructionValue;

	/*
	Set the instruction value. Allows an object to be reused so memory allocations are not wasted.
	*/
	void setInstructionValue(const u32 instructionValue);

	/*
	Returns the opcode field of the instruction.
	The opcode field is always located at bits 26-31 of the instruction.
	*/
	u8 getOpcode() const;

	/*
	Get functions for the various R instruction fields:
	- Rs					@ bits 21-25
	- Rt					@ bits 16-20
	- Rd					@ bits 11-15
	- shamt (shift amount)  @ bits 6-10
	- funct (function)		@ bits 0-5
	*/
	u8 getRRs() const;
	u8 getRRt() const;
	u8 getRRd() const;
	u8 getRShamt() const;
	u8 getRFunct() const;
	
	/*
	Get functions for the various J instruction fields:
	- Region-address @ bits 0-25

	The region-address (RA) is not the jump location - rather the real jump address is calculated based on the RA, the 4 high bits of the PC of the next instruction (branch delay slot) at the most significant bits and 2 bits set to 0 at the least significant bits.
	See documentation mentioned above for a more elaborate explanation.
	- getJRegionAddress returns the raw region-address contained in the instruction.
	*/
	u32 getJRegionAddress() const;

	/*
	Get functions for the various I instruction fields:
	- Rs					 @ bits 21-25
	- Rd					 @ bits 16-20
	- IMM (immediate value)  @ bits 0-15

	There is a signed/unsigned immediate get function provided (getImmU and getImmS) as well as get the sign bit function.
	A branch address calculation function is provided based on the signed IMM value shitfted left by 2, added to the PC of the next instruction (branch delay slot).
	A convenience get trap code function (from a valid trap instruction such as TEQ) is available (from bits 6-15 of IMM).
	*/
	u8 getIRs() const;
	u8 getIRt() const;
	u16 getIImmU() const;
	s16 getIImmS() const;
	u8 getIImmSignBit() const;
	u16 getITrapCode() const;
};
