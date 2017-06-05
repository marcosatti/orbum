#include <cmath>
#include <stdexcept>

#include "Common/Util/FPUUtil/FPUUtil.h"
#include "Common/Global/Globals.h"

f32 FPUUtil::formatIEEEToPS2Float(const f32 value, FPUFlags_t & flags)
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

u32 FPUUtil::getXORSign(const f32 value1, const f32 value2)
{
	u32 value1_u32 = static_cast<u32>(value1);
	u32 value2_u32 = static_cast<u32>(value2);
	return (value1_u32 ^ value2_u32) & 0x80000000;
}

bool FPUUtil::isNegative(const f32 value)
{
	return std::signbit(value);
}

u8 FPUUtil::getExponent(const f32 value)
{
	s32 exp;
	std::frexp(value, &exp);
	return static_cast<u8>(exp);
}
