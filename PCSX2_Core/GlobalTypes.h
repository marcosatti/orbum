#pragma once

/*
Basic Atomic Types
These are used extensively throughout the emulator.

The PS2 and SCE manuals use this size terminology:
Byte               size is 8-bit.
Halfword (hword)   size is 16-bit.
Word               size is 32-bit.
Doubleword (dword) size is 64-bit.
Quadword (qword)   size is 128-bit.

In PCSX2, these base types are defined starting with single letter for sign status (s for signed or u for unsigned), followed by the number of bits.
For example, unsigned dword would be represented by u64, and a signed qword would be represented by s128.

As there is no 128-bit types defined in the C++ standard (ie: no uint128_t), we make our own definitions of a 128-bit type.
Do not change the ordering of the unions inside the s/u128 types as they have been crafted for little-endianess.
*/

#include <cstdint>

// Signed types
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64; // Not actually used.

// Unsigned types
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

// Single precision float (needs to be 32-bit for emulation to work, see Types_Test.cpp).
// If the test fails, you may need to add in a platform specific definition based on an #if directive.
typedef float f32;

// 128-bit type. Note that the PS2 never operates on pure 128-bit values - rather it operates on sub sections of this value, such as 4 x 32-bit (words) or 8 x 16-bit (halfwords). 
// Therefore we do not need a signed and unsigned 128-bit value, as it is meaningless to the PS2.
// Mnemonic: v64 stands for value (64-bit), v32 stands for value (32-bit), etc.
// TODO: Check alignment & endianess. Currently it is assumed that in memory, for example, hi preceedes low, and for the arrays, it is layed out [3]->[2]->[1]->[0].
struct u128
{
	union
	{
		struct {
			u64 hi;
			u64 lo;
		};

		u64 v64[2];
		u32 v32[4];
		u16 v16[8];
		u8  v8[16];
	};

	// Zero value on construction.
	u128() : hi(0), lo(0) {}

	// Below functions are convenience functions for:
	// - Returning the lower 32/16/8 bits of the 128-bit value.
	// - Comparing the 128-bit value to another.
	operator u32() const { return v32[0]; }
	operator u16() const { return v16[0]; }
	operator u8() const { return v8[0]; }

	bool operator==(const u128& right) const
	{
		return (lo == right.lo) && (hi == right.hi);
	}

	bool operator!=(const u128& right) const
	{
		return (lo != right.lo) || (hi != right.hi);
	}
};