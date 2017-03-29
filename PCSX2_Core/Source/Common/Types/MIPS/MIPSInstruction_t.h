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
	explicit MIPSInstruction_t(const u32 value) : 
		mValue(value) 
	{
	}

	/*
	Returns the instruction value.
	*/
	u32 getValue() const
	{
		return mValue;
	}

	/*
	Get functions for common instruction fields:
	- Opcode				@ bits 26-31.
	- Rs					@ bits 21-25.
	- Rt					@ bits 16-20.
	*/
	u8 getOpcode() const
	{
		return static_cast<u8>((mValue >> 26) & 0x3F);
	}
	u8 getRs() const
	{
		return static_cast<u8>((mValue >> 21) & 0x1F);
	}
	u8 getRt() const
	{
		return static_cast<u8>((mValue >> 16) & 0x1F);
	}

	/*
	Get functions for the various R instruction fields:
	- Rd					@ bits 11-15.
	- shamt (shift amount)  @ bits 6-10.
	- funct (function)		@ bits 0-5.
	*/
	u8 getRRd() const
	{
		return static_cast<u8>((mValue >> 11) & 0x1F);
	}
	u8 getRShamt() const
	{
		return static_cast<u8>((mValue >> 6) & 0x1F);
	}
	u8 getRFunct() const
	{
		return static_cast<u8>((mValue) & 0x3F);
	}
	
	/*
	Get functions for the various J instruction fields:
	- Region-address	    @ bits 0-25.
	*/
	u32 MIPSInstruction_t::getJRegionAddress() const
	{
		return (mValue & 0x03ffffff);
	}

	/*
	Get functions for the various I instruction fields:
	- Imm sign bit			 @ bits 15.
	- Trap code				 @ bits 6-15.
	- Imm (immediate value)  @ bits 0-15.
	*/
	u16 getITrapCode() const
	{
		return static_cast<u16>((getIImmU() >> 6) & 0x3FF);
	}
	u8 getIImmSignBit() const
	{
		return static_cast<u8>((mValue >> 15) & 0x1);
	}
	u16 getIImmU() const
	{
		return static_cast<u16>(mValue & 0xFFFF);
	}
	s16 getIImmS() const
	{
		return (static_cast<s16>(mValue) & 0xFFFF);
	}

protected:
	/*
	Raw instruction value.
	All functions above extract information from this.
	*/
	u32 mValue;
};
