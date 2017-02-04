#pragma once

#include "Common/Global/Globals.h"

/*
Represents a VU instruction, which is used to extract information out of the parsed 32-bit value.
See VU Users Manual page 58 onwards (micro) & page 226 onwards (macro).

The Micro and Macro instruction types are compatible with eachother as they both use 32-bit values.
However, the field names are from the micro series of instructions.

Parsing a full 64-bit micro instruction is not supported. In the system code, you must split the 64-bit value into 2 x 32-bit values, 
 from which you can use the upper and lower instructions.
*/
class VUInstruction_t
{
public:
	/*
	Initalise a VUInstruction object optionally with the code value.
	*/
	VUInstruction_t(const u32 & vuCodeValue = 0);

	/*
	Holder for the VU instruction value.
	*/
	u32 mInstructionValue;

	/*
	Set the VU instruction value.
	*/
	void setValue(const u32 & vuCodeValue);

	/*
	Get functions for the VU instruction field values.
	*/
	u8 getMSB7() const;
	u8 getDest() const;
	u8 getFt() const;
	u8 getFs() const;
	u8 getFd() const;
	u8 getOpcode() const;
	u8 getBc() const;
	u8 getFtf() const;
	u8 getFsf() const;;
	u16 getImm11() const;
	u32 getImm24() const;

	/*
	Test functions for the subfields of the dest field (x, y, z, w).
	Checks if the subfield bit is set. 
	Only an index parm of 0 -> 3 is supported, otherwise a runtime error occurs (on debug builds).
	Index Parm. 3  ->  0.
	Bits        21 ->  24.
	Subfield    W  ->  X.

	See VU Users Manual page 61.
	*/
	bool testDestField(const u8 & fieldIndex) const;
	bool testDestX() const;
	bool testDestY() const;
	bool testDestZ() const;
	bool testDestW() const;
};
