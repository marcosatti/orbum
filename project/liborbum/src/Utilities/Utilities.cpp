#include <climits>
#include <cmath>
#include <stdexcept>

#include "Utilities/Utilities.hpp"

int count_leading_bits(const sword value)
{
	// If the value is 0, return 32 automatically.
	if (value == 0)
		return 32;

	// If the sign bit is 1, we invert the bits to 0 for count-leading-zero.    
    sword conditioned = value < 0 ? ~value : value;

	// Perform our count leading zero.
	int num_leading_bits = 0;
	for (int i = CHAR_BIT * sizeof(conditioned); i > 0; i--)
	{
		if ((conditioned & (1 << (i - 1))) == 0)
			num_leading_bits++;
		else
			break;
	}

	return num_leading_bits;
}

int count_trailing_zeros(const uword value)
{
	// If the value is 0, return 32 automatically.
	if (value == 0)
		return 32;

	// Perform our count trailing zero.
	int num_trailing_zeros = 0;
	for (int i = 0; i < CHAR_BIT * sizeof(value); i++)
	{
		if ((value & (1 << i)) == 0)
			num_trailing_zeros++;
		else
			break;
	}

	return num_trailing_zeros;
}

shword saturate_word_to_hword(const sword value)
{
	if (value > static_cast<sword>(VALUE_SHWORD_MAX))
		return VALUE_SHWORD_MAX;
	else if (value < static_cast<sword>(VALUE_SHWORD_MIN))
		return VALUE_SHWORD_MIN;
	else 
		return static_cast<shword>(value);
}

sword saturate_dword_to_word(const sdword value)
{
	if (value > VALUE_SWORD_MAX)
		return VALUE_SWORD_MAX;
	else if (value < VALUE_SWORD_MIN)
		return VALUE_SWORD_MIN;
	else
		return static_cast<sword>(value);
}

bool test_over_or_underflow_32(sword x, sword y)
{
	if (((x > 0) && (y > VALUE_SWORD_MAX - x))
		|| ((x < 0) && (y < VALUE_SWORD_MIN - x)))
	{
		return true;
	}
	
	return false;
}

bool test_over_or_underflow_64(sdword x, sdword y)
{
	if (((x > 0) && (y > VALUE_SDWORD_MAX - x))
		|| ((x < 0) && (y < VALUE_SDWORD_MIN - x)))
	{
		return true;
	}

	return false;
}

f32 to_ps2_float(const f32 value, FpuFlags & flags)
{
	// Intended to format incoming IEEE754 spec values into PS2 spec values.
	// In the PS2 there is no support for NaN's, +/- Inf, or denormalised (subnormal) values.

	// Reset all of the flags.
	flags.ZF = false;
	flags.SF = false;
	flags.UF = false;
	flags.OF = false;

	// Set the sign flag (always checked no matter the float type).
	// A negative value means true.
	flags.SF = value < 0.0f;

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

ubyte get_float_exponent(const f32 value)
{
	sword exp;
	std::frexp(value, &exp);
	return static_cast<ubyte>(exp);
}
