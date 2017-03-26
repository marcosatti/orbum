#pragma once

#include "Common/Global/Globals.h"

/*
A MIPS instruction type which is used to read specific values from it.
An instruction follows the MIPS 32-bit instruction format, see here: https://en.wikibooks.org/wiki/MIPS_Assembly/Instruction_Formats.
Convenience functions are provided for I, J and R instruction types.
*/
struct MIPSInstruction_t {
	/*
	Instruction value.
	All functions below extract information from this.
	*/
	u32 mValue;

	/*
	Returns the opcode field of the instruction.
	The opcode field is always located at bits 26-31 of the instruction.
	*/
	u8 getOpcode() const;

	/*
	Get functions for the various R instruction fields:
	- Rs					@ bits 21-25.
	- Rt					@ bits 16-20.
	- Rd					@ bits 11-15.
	- shamt (shift amount)  @ bits 6-10.
	- funct (function)		@ bits 0-5.
	*/
	u8 getRRs() const;
	u8 getRRt() const;
	u8 getRRd() const;
	u8 getRShamt() const;
	u8 getRFunct() const;
	
	/*
	Get functions for the various J instruction fields:
	- Region-address @ bits 0-25
	*/
	u32 getJRegionAddress() const;

	/*
	Get functions for the various I instruction fields:
	- Rs					 @ bits 21-25.
	- Rt					 @ bits 16-20.
	- Imm (immediate value)  @ bits 0-15.
	- Imm sign bit			 @ bits 15.
	- Trap code				 @ bits 6-15.
	*/
	u8 getIRs() const;
	u8 getIRt() const;
	u16 getIImmU() const;
	s16 getIImmS() const;
	u8 getIImmSignBit() const;
	u16 getITrapCode() const;
};
