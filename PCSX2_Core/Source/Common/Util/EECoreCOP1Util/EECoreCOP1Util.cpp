#include "stdafx.h"

#include <cmath>

#include "Common/Util/EECoreCOP1Util/EECoreCOP1Util.h"
#include "Common/PS2 Constants/PS2Constants.h"

bool EECoreCOP1Util::isOverflowed(const f32& value)
{
	switch (std::fpclassify(value))
	{
	case FP_INFINITE:
		return true;
	case FP_NAN:
		return true;
	default: 
		return false;
	}
}

bool EECoreCOP1Util::isUnderflowed(const f32& value)
{
	switch (std::fpclassify(value))
	{
	case FP_SUBNORMAL:
		return true;
	default:
		return false;
	}
}

f32 EECoreCOP1Util::formatIEEEToPS2Float(const f32 & value)
{
	// Intended to format incoming IEEE754 spec values into PS2 spec values.
	// In the PS2 there is no support for NaN's, +/- Inf, or denormalised (subnormal) values.
	bool isNegative = std::signbit(value);

	switch (std::fpclassify(value))
	{
	case FP_INFINITE:
	{
		// Clamp to +/- Fmax.
		return static_cast<f32>(isNegative ? PS2Constants::EE::EECore::COP1::FMAX_NEG : PS2Constants::EE::EECore::COP1::FMAX_POS);
	}
	case FP_NAN:
	{
		// Clamp to +/- Fmax.
		return static_cast<f32>(isNegative ? PS2Constants::EE::EECore::COP1::FMAX_NEG : PS2Constants::EE::EECore::COP1::FMAX_POS);
	}
	case FP_SUBNORMAL:
	{
		// Round to +/- 0.
		return static_cast<f32>(isNegative ? PS2Constants::EE::EECore::COP1::ZERO_NEG : PS2Constants::EE::EECore::COP1::ZERO_POS);
	}
	default:
	{
		throw std::runtime_error("Parsed float value was NOT abnormal to the PS2 spec. Requires debugging.");
	}
	}
}

u32 EECoreCOP1Util::getXORSign(const f32& value1, const f32& value2)
{
	u32 value1_u32 = static_cast<u32>(value1);
	u32 value2_u32 = static_cast<u32>(value2);
	return (value1_u32 ^ value2_u32) & 0x80000000;
}

bool EECoreCOP1Util::getSign(const f32& value)
{
	return std::signbit(value);
}

u8 EECoreCOP1Util::getExponent(const f32& value)
{
	s32 exp;
	std::frexp(value, &exp);
	return static_cast<u8>(exp);
}
