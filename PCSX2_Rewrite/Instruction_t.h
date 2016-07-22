#pragma once

#include "Globals.h"

/*
An instruction class which is used to hold any valid MIPS instruction.
Convenience functions are provided for I, J and R instruction types.
These convenience functions are all but 1 of the get functions, which are suffixed with the instruction type after "get".
getOpcode() is common to all instruction types.
*/

class Register32_t;

class Instruction_t {
public:
	/*
	instruction holds the entire MIPS instruction, which the child class' convenience functions operate off.
	An instruction follows the MIPS format, see for example here: https://en.wikibooks.org/wiki/MIPS_Assembly/Instruction_Formats
	Also see the EE Core Instruction Set Manual.
	An instruction is always 4 bytes long (32-bit), and always has an opcode field occupying bits 26-31 throughout the types of instructions.
	*/
	u32 mInstructionValue;

	/*
	Initialise an Instruction object with the specified 32-bit MIPS instruction. Defaults to 0.
	*/
	Instruction_t(const u32 instructionValue = 0);

	/*
	Set the instruction value. Allows an object to be reused so memory allocations are not wasted.
	*/
	void setInstruction(const u32 instructionValue);

	/*
	Returns the opcode field of the instruction.
	The opcode field is always located at bits 26-31 of the instruction.
	*/
	INLINE u8 getOpcode() const;

	/*
	Get functions for the various R instruction fields:
	- Rs					@ bits 21-25
	- Rt					@ bits 16-20
	- Rd					@ bits 11-15
	- shamt (shift amount) @ bits 6-10
	- funct (function)		@ bits 0-5
	*/
	INLINE u8 getRRs() const;
	INLINE u8 getRRt() const;
	INLINE u8 getRRd() const;
	INLINE u8 getRShamt() const;
	INLINE u8 getRFunct() const;
	
	/*
	Get functions for the various J instruction fields:
	- Pseudo-address @ bits 0-25

	The pseudo-address (PA) is not the jump location - rather it is calculated based on the PA, the 4 high bits of the PC of the next instruction (branch delay slot) at the most significant bits and 2 bits set to 0 at the least significant bits.
	See documentation mentioned above for a more elaborate explanation.
	- getPAddress returns the raw pseudo-address contained in the instruction.
	- getAddress returns the real address based on the pseudo-address and the other factors mentioned above.
	*/
	INLINE u32 getJPAddress() const;
	INLINE u32 getJJumpAddress(Register32_t& PC) const;

	/*
	Get functions for the various I instruction fields:
	- Rs					 @ bits 21-25
	- Rd					 @ bits 16-20
	- IMM (immediate value)  @ bits 0-15

	There is a signed/unsigned immediate get function provided (getImmU and getImmS) as well as get the sign bit function.
	A branch address calculation function is provided based on the signed IMM value shitfted left by 2, added to the PC of the next instruction (branch delay slot).
	A convenience get trap code function (from a valid trap instruction such as TEQ) is available (from bits 6-15 of IMM).
	*/
	INLINE u8 getIRs() const;
	INLINE u8 getIRd() const;
	INLINE u16 getIImmU() const;
	INLINE s16 getIImmS() const;
	INLINE u8 getISignBit() const;
	INLINE u32 getIBranchAddress(Register32_t& PC) const;
	INLINE u16 getITrapCode() const;
};
