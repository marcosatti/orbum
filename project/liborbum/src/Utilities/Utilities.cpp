#include <climits>
#include <cmath>
#include <stdexcept>

#include "Utilities/Utilities.hpp"

uword countLeadingBits(s32 value)
{
	// If the value is 0, return 32 automatically.
	if (value == 0)
		return 32;

	// If the sign bit is 1, we invert the bits to 0 for count-leading-zero.
	if (value < 0)
		value = ~value;

	// Perform our count leading zero.
	uword num_leading_bits = 0;
	for (int i = CHAR_BIT * sizeof value; i > 0; i--)
	{
		if ((value & (1 << (i - 1))) == 0)
			num_leading_bits++;
		else
			break;
	}

	return num_leading_bits;
}

uword constructMask32(int startPos, int length)
{
	// Due to how x86 (and possibly other arch's) shift, we need a solution for the case when length == 32, as it generates a bad mask.
	// Old method: mask = (1 << param) - 1;
	// Algorithm from here (thanks to Siu Ching Pong): http://stackoverflow.com/questions/1392059/algorithm-to-generate-bit-mask
	return (static_cast<uword>(-(length != 0)) & (static_cast<uword>(-1) >> (32 - length))) << startPos;
}

uword extractMaskedValue32(uword value, int maskStartPos, int maskLength)
{
	const uword mask = constructMask32(maskStartPos, maskLength);
	return ((value & mask) >> maskStartPos);
}

uword insertMaskedValue32(uword value, uword insertValue, int maskStartPos, int maskLength)
{
	const uword mask = constructMask32(maskStartPos, maskLength);
	const uword insertValueShifted = (insertValue << maskStartPos) & mask;
	return ((value & ~mask) | insertValueShifted);
}

uhword constructMask16(int startPos, int length)
{
	// Due to how x86 (and possibly other arch's) shift, we need a solution for the case when length == 16, as it generates a bad mask.
	// Old method: mask = (1 << param) - 1;
	// Algorithm from here (thanks to Siu Ching Pong): http://stackoverflow.com/questions/1392059/algorithm-to-generate-bit-mask
	return (static_cast<uhword>(-(length != 0)) & (static_cast<uhword>(-1) >> (16 - length))) << startPos;
}

uhword extractMaskedValue16(uhword value, int maskStartPos, int maskLength)
{
	const uhword mask = constructMask16(maskStartPos, maskLength);
	return ((value & mask) >> maskStartPos);
}

uhword insertMaskedValue16(uhword value, uhword insertValue, int maskStartPos, int maskLength)
{
	const uhword mask = constructMask16(maskStartPos, maskLength);
	const uhword insertValueShifted = (insertValue << maskStartPos) & mask;
	return ((value & ~mask) | insertValueShifted);
}

s16 saturateWordToHword(s32 value)
{
	if (value > Constants::VALUE_S16_MAX)
		return Constants::VALUE_S16_MAX;
	else if (value < Constants::VALUE_S16_MIN)
		return Constants::VALUE_S16_MIN;
	else 
		return static_cast<s16>(value);
}

s32 saturateDwordToWord(s64 value)
{
	if (value > Constants::VALUE_S32_MAX)
		return Constants::VALUE_S32_MAX;
	else if (value < Constants::VALUE_S32_MIN)
		return Constants::VALUE_S32_MIN;
	else
		return static_cast<s32>(value);
}

uword log2N(uword value)
{
	static const uword b[] = { 0xAAAAAAAA, 0xCCCCCCCC, 0xF0F0F0F0, 0xFF00FF00, 0xFFFF0000 };

	uword r = (value & b[0]) != 0;

	for (uword i = 4; i > 0; i--) // unroll for speed...
		r |= ((value & b[i]) != 0) << i;

	return r;
}

bool testOverflow32(s32 x, s32 y)
{
	if (((x > 0) && (y > Constants::VALUE_S32_MAX - x)))
	{
		return true;
	}

	return false;
}

bool testUnderflow32(s32 x, s32 y)
{
	if (((x < 0) && (y < Constants::VALUE_S32_MIN - x)))
	{
		return true;
	}

	return false;
}

bool testOverOrUnderflow32(s32 x, s32 y)
{
	if (((x > 0) && (y > Constants::VALUE_S32_MAX - x))
		|| ((x < 0) && (y < Constants::VALUE_S32_MIN - x)))
	{
		return true;
	}
	
	return false;
}

bool testOverflow64(s64 x, s64 y)
{
	if (((x > 0) && (y > Constants::VALUE_S64_MAX - x)))
	{
		return true;
	}

	return false;
}

bool testUnderflow64(s64 x, s64 y)
{
	if (((x < 0) && (y < Constants::VALUE_S64_MIN - x)))
	{
		return true;
	}

	return false;
}

bool testOverOrUnderflow64(s64 x, s64 y)
{
	if (((x > 0) && (y > Constants::VALUE_S64_MAX - x))
		|| ((x < 0) && (y < Constants::VALUE_S64_MIN - x)))
	{
		return true;
	}

	return false;
}

uword getHI19(uword value)
{
	return (value & 0xFFFFE000) >> 19;
}

f32 formatIEEEToPS2Float(const f32 value, FpuFlags & flags)
{
	// Intended to format incoming IEEE754 spec values into PS2 spec values.
	// In the PS2 there is no support for NaN's, +/- Inf, or denormalised (subnormal) values.

	// Reset all of the flags.
	flags.ZF = false;
	flags.SF = false;
	flags.UF = false;
	flags.OF = false;

	// Set the sign flag (always checked no matter the float type).
	flags.SF = isNegative(value);

	switch (std::fpclassify(value))
	{
	case FP_INFINITE:
	{
		// Set OF flag, clamp to +/- Fmax.
		flags.OF = true;
		return static_cast<f32>(flags.SF ? Constants::EE::EECore::FPU::FMAX_NEG : Constants::EE::EECore::FPU::FMAX_POS);
	}
	case FP_NAN:
	{
		// Set OF flag, clamp to +/- Fmax.
		flags.OF = true;
		return static_cast<f32>(flags.SF ? Constants::EE::EECore::FPU::FMAX_NEG : Constants::EE::EECore::FPU::FMAX_POS);
	}
	case FP_SUBNORMAL:
	{
		// Set UF flag, round to +/- 0.
		flags.UF = true;
		return static_cast<f32>(flags.SF ? Constants::EE::EECore::FPU::ZERO_NEG : Constants::EE::EECore::FPU::ZERO_POS);
	}
	case FP_ZERO:
	{
		// Set ZF flag, return parsed value (no change).
		flags.ZF = true;
		return value;
	}
	default:
	{
		// Parsed value was within the PS2 spec, no need to change or set any other flags.
		return value;
	}
	}
}

uword getXORSign(const f32 value1, const f32 value2)
{
	uword value1_uword = static_cast<uword>(value1);
	uword value2_uword = static_cast<uword>(value2);
	return (value1_uword ^ value2_uword) & 0x80000000;
}

bool isNegative(const f32 value)
{
	return std::signbit(value);
}

ubyte getExponent(const f32 value)
{
	s32 exp;
	std::frexp(value, &exp);
	return static_cast<ubyte>(exp);
}

