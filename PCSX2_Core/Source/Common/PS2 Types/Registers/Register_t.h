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

TODO: Check byte order / endianess - it is assumed within the emulator that for example in a 128-bit register:
 Register128_t.(S or U)W[0] = bits 0-31.    Least significant bits
 Register128_t.(S or U)W[1] = bits 32-63.              |
 Register128_t.(S or U)W[2] = bits 64-95.              ↓
 Register128_t.(S or U)W[3] = bits 96-127.  Most significant bits
*/
class Register128_t {
public:
	// The PS2 never operates or manipulates values above 64-bit - but it can do parallel operations on for example 4 x 32-bit values. 
	// It is meaningless to provide a signed/unsigned combo of 128-bit variables since they can't be manipulated.
	union
	{
		u128 UQ;     // Unsigned Qword.
		u64  UD[2];  // Unsigned Dword.
		s64  SD[2];  // Signed Dword.
		u32  UW[4];  // Unsigned Word.
		s32  SW[4];  // Signed Word.
		u16  UH[8];  // Unsigned Hword.
		s16  SH[8];  // Signed Hword.
		u8   UB[16]; // Unsigned Byte.
		s8   SB[16]; // Signed Byte.
	};

	// Initialise union with 0 value. The 128-bit UQ type contains a custom initaliser to do this.
	Register128_t();

	// Convenience function to access individual bits. The returned u8 value will either be 1 or 0.
	// Index must be between 0 -> 127.
	u8 getBit128(u8 index) const;

	// Convenience function to set individual bits. The bit value at index will be set to bitValue.
	// Index must be between 0 -> 127.
	void setBit128(u8 index, u64 bitValue);
};

class Register64_t {
public:
	union 
	{
		u64  UD;    // Unsigned Dword.
		s64  SD; // Signed Dword.
		u32  UW[2]; // Unsigned Word.
		s32  SW[2]; // Signed Word.
		u16  UH[4]; // Unsigned Hword.
		s16  SH[4]; // Signed Hword.
		u8   UB[8]; // Unsigned Byte.
		s8   SB[8]; // Signed Byte.
	};

	// Initialise union with 0 value.
	Register64_t();

	// Convenience function to access individual bits. The returned u8 value will either be 1 or 0.
	// Index must be between 0 -> 63.
	u8 getBit64(u8 index) const;

	// Convenience function to set individual bits. The bit value at index will be set to bitValue.
	// Index must be between 0 -> 63.
	void setBit64(u8 index, u64 bitValue);
};

class Register32_t {
public:
	union 
	{
		u32  UW;    // Unsigned Word.
		s32  SW;    // Signed Word.
		u16  UH[2]; // Unsigned Hword.
		s16  SH[2]; // Signed Hword.
		u8   UB[4]; // Unsigned Byte.
		s8   SB[4]; // Signed Byte.
	};

	// Initialise union with 0 value.
	Register32_t();

	// Convenience function to access individual bits. The returned u8 value will either be 1 or 0.
	// Index must be between 0 -> 31.
	u8 getBit32(u8 index) const;

	// Convenience function to set individual bits. The bit value at index will be set to bitValue.
	// Index must be between 0 -> 31.
	void setBit32(u8 index, u32 bitValue);

	// Convenience function to get a value (bit array) with a specified length at startPos in the register.
	// This function is primarily used for getting a bitmask field in a register.
	u32 getBitRange32(u8 startPosition, u8 bitLength) const;

	// Convenience function to insert a value (bit array) with a specified length at startPos in the register.
	// This will overwrite the bits currently set at the startPos to (startPos + length).
	// This function is primarily used for setting bit masks in a register.
	// Note: If there are more bits set in value than bitLength allows for, the extra bits will not be written.
	void setBitRange32(u8 startPosition, u8 bitLength, u32 value);
};