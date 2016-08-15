#pragma once

#include "Common/Global/Globals.h"

/*
Register type and size definitions.
Register32, Register64 and Register128 define the register sizes used thoughout the EE.

These registers are implemented (at core) as a union of the signed and unsigned sums (to the register size) of these types, meaning you are able to tell the compiler
to access them as signed or unsigned, and also only a subsection of the registers.
Mnemonic: variables are accessed by signed or unsigned (S or U) then by the word size (ie: Q for quadword, D for doubleword, W for word, H for halfword, B for byte).
Normally you would access the registers by eg: Register32_t.UW

You are able to get and set individual bits using the getBit()/setBit() function.
As bitmask registers are often 32-bit, Register32_t contains an additional function setBitRange32() for setting bit masks in the register. See the function documentation.

TODO: Check byte order / endianess - it is assumed within the emulator that, for example in a 128-bit register:
Register128_t.(S or U)W[0] = bits 0-31.    Least significant bits
Register128_t.(S or U)W[1] = bits 32-63.              |
Register128_t.(S or U)W[2] = bits 64-95.              ↓
Register128_t.(S or U)W[3] = bits 96-127.  Most significant bits
*/
class Register128_t {
public:
	virtual ~Register128_t()
	{
	}

	// The PS2 never operates or manipulates values above 64-bit - but it can do parallel operations on for example 4 x 32-bit values. 
	// It is meaningless to provide a signed/unsigned combo of 128-bit variables since they can't be manipulated.
	union
	{
		u64  UD[Constants::NUMBER_DWORDS_IN_QWORD]; // Unsigned Dword.
		s64  SD[Constants::NUMBER_DWORDS_IN_QWORD]; // Signed Dword.
		u32  UW[Constants::NUMBER_WORDS_IN_QWORD];  // Unsigned Word.
		s32  SW[Constants::NUMBER_WORDS_IN_QWORD];  // Signed Word.
		u16  UH[Constants::NUMBER_HWORDS_IN_QWORD]; // Unsigned Hword.
		s16  SH[Constants::NUMBER_HWORDS_IN_QWORD]; // Signed Hword.
		u8   UB[Constants::NUMBER_BYTES_IN_QWORD];  // Unsigned Byte.
		s8   SB[Constants::NUMBER_BYTES_IN_QWORD];  // Signed Byte.
	};

	// Initialise union with 0 value. The 128-bit UQ type contains a custom initaliser to do this.
	Register128_t();

	// Functions to access the register value - you should use these functions instead of accessing them directly, as subclassed registers can contain additional check code (for specialised registers).
	virtual u8 readByteU(u32 arrayIndex);
	virtual void writeByteU(u32 arrayIndex, u8 value);
	virtual s8 readByteS(u32 arrayIndex);
	virtual void writeByteS(u32 arrayIndex, s8 value);
	virtual u16 readHwordU(u32 arrayIndex);
	virtual void writeHwordU(u32 arrayIndex, u16 value);
	virtual s16 readHwordS(u32 arrayIndex);
	virtual void writeHwordS(u32 arrayIndex, s16 value);
	virtual u32 readWordU(u32 arrayIndex);
	virtual void writeWordU(u32 arrayIndex, u32 value);
	virtual s32 readWordS(u32 arrayIndex);
	virtual void writeWordS(u32 arrayIndex, s32 value);
	virtual u64 readDwordU(u32 arrayIndex);
	virtual void writeDwordU(u32 arrayIndex, u64 value);
	virtual s64 readDwordS(u32 arrayIndex);
	virtual void writeDwordS(u32 arrayIndex, s64 value);

	// Convenience function to access individual bits. The returned u8 value will either be 1 or 0.
	// Index must be between 0 -> 127.
	u8 getBit128(u8 index) const;

	// Convenience function to set individual bits. The bit value at index will be set to bitValue.
	// Index must be between 0 -> 127.
	void setBit128(u8 index, u64 bitValue);
};