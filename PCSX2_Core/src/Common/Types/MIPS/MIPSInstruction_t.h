#pragma once

#include "Common/Global/Globals.h"

/*
A MIPS instruction type which is used to read specific values from it.
An instruction follows the MIPS 32-bit instruction format, see here: https://en.wikibooks.org/wiki/MIPS_Assembly/Instruction_Formats.
Convenience functions are provided for I, J and R instruction types.
*/
struct MIPSInstruction_t {
	/*
	Construct the instruction with the raw value.
	*/
	MIPSInstruction_t(const u32 value);

	/*
	Returns the instruction value.
	*/
	u32 getValue() const;

	/*
	Get functions for common instruction fields:
	- Opcode				@ bits 26-31.
	- Rs					@ bits 21-25.
	- Rt					@ bits 16-20.
	*/
	u8 getOpcode() const;
	u8 getRs() const;
	u8 getRt() const;

	/*
	Get functions for the various R instruction fields:
	- Rd					@ bits 11-15.
	- shamt (shift amount)  @ bits 6-10.
	- funct (function)		@ bits 0-5.
	*/
	u8 getRRd() const;
	u8 getRShamt() const;
	u8 getRFunct() const;
	
	/*
	Get functions for the various J instruction fields:
	- Region-address	    @ bits 0-25.
	*/
	u32 MIPSInstruction_t::getJRegionAddress() const;

	/*
	Get functions for the various I instruction fields:
	- Imm sign bit			 @ bits 15.
	- Trap code				 @ bits 6-15.
	- Imm (immediate value)  @ bits 0-15.
	*/
	u16 getITrapCode() const;
	u8  getIImmSignBit() const;
	u16 getIImmU() const;
	s16 getIImmS() const;

protected:
	/*
	Raw instruction value.
	All functions above extract information from this.
	*/
	u32 mValue;
};
