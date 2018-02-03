#pragma once

#include "Common/Constants.hpp"
#include "Common/Types/Primitive.hpp"
#include "Common/Types/FpuFlags.hpp"

/// Formats an IEEE 754 float into a PS2 spec float, by clamping NaN's and +/-Infinity to +/-Fmax and rounding denormalised values towards +/-0.
/// A PS2 spec float can be thought of as a subset of the IEEE 754 float.
/// When converting, a set of flags will be filled in that can be used to set eg: the VU MAC flags.
f32 to_ps2_float(const f32 value, FpuFlags & flags);

/// Gets the exponent (8 bits starting from position 23).
ubyte get_float_exponent(const f32 value);

/// Counts leading bits (1's) from a 32-bit value.
/// Example: in 0b1110001..., the answer is 3.
int count_leading_bits(const sword value);

/// Saturates values to the next smallest size, if above the maximum value allowed.
/// Eg: for 0x02345678 to hword, this becomes 0x7FFF;
shword saturate_word_to_hword(const sword value);
sword saturate_dword_to_word(const sdword value);

/// Provided x and y, returns a bool for the condition that addition it will not overflow, and for subtraction it will not underflow.
/// User must select the appropriate bit size (ie 32, 64).
/// Thanks to http://stackoverflow.com/questions/199333/how-to-detect-integer-overflow-in-c-c
bool test_over_or_underflow_32(const sword x, const sword y);
bool test_over_or_underflow_64(const sdword x, const sdword y);
