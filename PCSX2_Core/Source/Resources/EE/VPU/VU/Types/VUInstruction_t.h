#pragma once

#include "Common/Global/Globals.h"

/*
A VU instruction type, which is used to extract information out of the parsed 32-bit value.
See VU Users Manual page 58 onwards (micro) & page 226 onwards (macro).

The micro and macro instruction types are compatible with eachother as they both use 32-bit values.
However, the field names are from the micro series of instructions.
This is very similar to a MIPS instruction type.

Parsing a full 64-bit micro instruction is not supported. 
In the system code, you must split the 64-bit value into 2 x 32-bit values, from which you can use the instructions.
*/
struct VUInstruction_t
{
	/*
	Construct the instruction with the raw value.
	Performs a lookup and stores the code info for use.
	*/
	VUInstruction_t(const u32 value) :
		mValue(value)
	{
		// mInstructionInfo = VIFcodeInstructionTable::getInstructionInfo(this);
	}

	/*
	Get functions for the VU instruction field values.
	*/
	u8 getMSB7() const
	{
		return static_cast<u8>((mValue >> 25) & 0x7F);
	}
	u8 getDest() const
	{
		return static_cast<u8>((mValue >> 21) & 0xF);
	}
	u8 getFt() const
	{
		return static_cast<u8>((mValue >> 16) & 0x1F);
	}
	u8 getFs() const
	{
		return static_cast<u8>((mValue >> 11) & 0x1F);
	}
	u8 getFd() const
	{
		return static_cast<u8>((mValue >> 6) & 0x1F);
	}
	u8 getOpcode() const
	{
		return static_cast<u8>((mValue) & 0x3F);
	}
	u8 getBc() const
	{
		return static_cast<u8>((mValue) & 0x3);
	}
	u8 getFtf() const
	{
		return static_cast<u8>((mValue >> 23) & 0x3);
	}
	u8 getFsf() const
	{
		return static_cast<u8>((mValue >> 21) & 0x3);
	}
	u16 getImm11() const
	{
		return static_cast<u8>((mValue) & 0x7FF);
	}
	u32 getImm24() const
	{
		return static_cast<u8>((mValue) & 0xFFFFFF);
	}

	/*
	Test functions for the subfields of the dest field (x, y, z, w).
	Returns if the subfield bit is set. 
	Only an index parm of 0 -> 3 is supported, otherwise a runtime error occurs (on debug builds).

	The fieldIndex/bits/subfield map is as follows:
	Index Parm. 3  ->  0.
	Bits        21 ->  24.
	Subfield    W  ->  X.

	See VU Users Manual page 61.
	*/
	bool testDestField(const int index) const
	{
#if defined(BUILD_DEBUG)
		if (index >= 4)
			throw std::runtime_error("VUInstruction_t testDestField index not valid");
#endif
		return ((mValue >> (24 - index)) & 0x1);
	}

	bool testDestX() const
	{
		return ((mValue >> 24) & 0x1);
	}

	bool testDestY() const
	{
		return ((mValue >> 23) & 0x1);
	}

	bool testDestZ() const
	{
		return ((mValue >> 22) & 0x1);
	}

	bool testDestW() const
	{
		return ((mValue >> 21) & 0x1);
	}

	/*
	Returns the constant VU instruction information.
	*/
	/*
	const VIFcodeInstructionTable::VIFcodeInstructionInfo_t * getInstructionInfo()
	{
		return mInstructionInfo;
	}
	*/

private:
	/*
	Raw instruction value.
	All functions above extract information from this.
	*/
	u32 mValue;

	/*
	Constant instruction information.
	*/
	// const VIFcodeInstructionTable::VIFcodeInstructionInfo_t * mInstructionInfo;
};
