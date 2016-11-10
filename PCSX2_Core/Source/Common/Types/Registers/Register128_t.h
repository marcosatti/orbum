#pragma once

#include "Common/Global/Globals.h"

/*
Register type and size definitions.
Register16, Register32, Register64 and Register128 define the register sizes used thoughout the EE.

These registers are implemented (at core) as a union of the signed and unsigned sums (to the register size) of these types, meaning you are able to tell the compiler
 to access them as signed or unsigned, and also only a subsection of the registers.
Mnemonic: variables are accessed by signed or unsigned (S or U) then by the word size (ie: Q for quadword, D for doubleword, W for word, H for halfword, B for byte).
Normally you would access the registers by the read/write functions below, as subclasses might contain custom functionality. 

TODO: Check byte order / endianess - it is assumed within the emulator that, for example in a 128-bit register:
 Register128_t.(S or U)W[0] = bits 0-31.    Least significant bits
 Register128_t.(S or U)W[1] = bits 32-63.              |
 Register128_t.(S or U)W[2] = bits 64-95.              ↓
 Register128_t.(S or U)W[3] = bits 96-127.  Most significant bits

The primary difference between a Register type and MappedMemory type is that registers are accessed by the size index, not by the byte index.
For example, a writeWordU(0, value) will write to the first 0-31 bits, while writeWordU(1, value) will write to bits 32-63.
See the MappedMemory type for the counter-example.
*/
class Register128_t
{
public:
	// Initialise union with 0 value.
	explicit Register128_t();

	virtual ~Register128_t()
	{
	}

	// The PS2 never operates or manipulates values above 64-bit - but it can do parallel operations on for example 2 x 64-bit or 16 x 8-bit values. 
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
};