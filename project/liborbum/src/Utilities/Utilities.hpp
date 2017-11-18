#pragma once

#include "Common/Types/FpuFlags.hpp"

/*
Formats an IEEE 754 float into a PS2 spec float, by clamping NaN's and +/-Infinity to +/-Fmax and rounding denormalised values towards +/-0.
A PS2 spec float can be thought of as a subset of the IEEE 754 float.

When converting, a set of flags will be filled in that can be used to set eg: the VU MAC flags.
*/
static f32 formatIEEEToPS2Float(const f32 value, FpuFlags & flags);

/*
Gets the resulting sign according to the PS2 FPU spec when a instruction is carried out that has a XOR-type sign (eg: multiply or divide).
0 = positive, 1 = negative.
*/
static uword getXORSign(const f32 value1, const f32 alue2);

/*
Checks if the parsed float is negative.
True = negative, false = positive.
*/
static bool isNegative(const f32 value);

/*
Gets the exponent (8 bits starting from position 23).
*/
static ubyte getExponent(const f32 value);

/*
Counts leading bits (1's) from a 32-bit value.
Example: in 0b1110001..., the answer is 3.
*/
static uword countLeadingBits(s32 value); // Adapted from the old PCSX2 code and Stackoverflow (see inside body). Thanks everyone!

/*
Constructs a mask of 1's in a uword value, starting at bit position startPos with length specified.
Thanks to: http://www.coranac.com/documents/working-with-bits-and-bitfields/ for code.
*/
static uword constructMask32(int startPos, int length);

/*
Extracts a masked value from the given, that starts at maskStartPos and has length maskLength.
The returned value is shifted right by maskStartPos (ie: becomes its own value).
*/
static uword extractMaskedValue32(uword value, int maskStartPos, int maskLength);

/*
Inserts insertValue into value by shifting it to maskStartPos with length maskLength.
It will override any bits in the position.
*/
static uword insertMaskedValue32(uword value, uword insertValue, int maskStartPos, int maskLength);

/*
Constructs a mask of 1's in a uhword value, starting at bit position startPos with length specified.
Thanks to: http://www.coranac.com/documents/working-with-bits-and-bitfields/ for code.
*/
static uhword constructMask16(int startPos, int length);

/*
Extracts a masked value from the given, that starts at maskStartPos and has length maskLength.
The returned value is shifted right by maskStartPos (ie: becomes its own value).
*/
static uhword extractMaskedValue16(uhword value, int maskStartPos, int maskLength);

/*
Inserts insertValue into value by shifting it to maskStartPos with length maskLength.
It will override any bits in the position.
*/
static uhword insertMaskedValue16(uhword value, uhword insertValue, int maskStartPos, int maskLength);

/*
Saturates/clamps values to the next smallest size, if above the maximum value allowed.
Eg: for 0x02345678 to hword, this becomes 0x7FFF;
*/
static s16 saturateWordToHword(s32 value);
static s32 saturateDwordToWord(s64 value);

/*
Finds N by log2(value), when value is known to be 2^N (only works on this condition). Used as a fast lookup instead of normal log2().
Thanks to: http://graphics.stanford.edu/~seander/bithacks.html
*/
static uword log2N(uword value);

/*
Provided x and y, returns a bool for the condition that addition it will not overflow, and for subtraction it will not underflow.
User must select the appropriate bit size (ie 32, 64).
Thanks to http://stackoverflow.com/questions/199333/how-to-detect-integer-overflow-in-c-c
*/
static bool testOverflow32(s32 x, s32 y);
static bool testUnderflow32(s32 x, s32 y);
static bool testOverOrUnderflow32(s32 x, s32 y);
static bool testOverflow64(s64 x, s64 y);
static bool testUnderflow64(s64 x, s64 y);
static bool testOverOrUnderflow64(s64 x, s64 y);

/*
Gets the high 19 bits of the 32-bit value parsed, stored at the LSB's of the returned uword.
*/
static uword getHI19(uword value);
