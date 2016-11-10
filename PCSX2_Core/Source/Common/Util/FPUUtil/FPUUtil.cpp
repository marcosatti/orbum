#include "stdafx.h"

#include <cmath>
#include <stdexcept>

#include "Common/Util/FPUUtil/FPUUtil.h"
#include "PS2Constants/PS2Constants.h"

bool FPUUtil::isOverflowed(const f32& value)
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

bool FPUUtil::isUnderflowed(const f32& value)
{
	switch (std::fpclassify(value))
	{
	case FP_SUBNORMAL:
		return true;
	default:
		return false;
	}
}

f32 FPUUtil::formatIEEEToPS2Float(const f32 & value)
{
	// Intended to format incoming IEEE754 spec values into PS2 spec values.
	// In the PS2 there is no support for NaN's, +/- Inf, or denormalised (subnormal) values.
	bool isNegative = std::signbit(value);

	switch (std::fpclassify(value))
	{
	case FP_INFINITE:
	{
		// Clamp to +/- Fmax.
		return static_cast<f32>(isNegative ? PS2Constants::EE::EECore::FPU::FMAX_NEG : PS2Constants::EE::EECore::FPU::FMAX_POS);
	}
	case FP_NAN:
	{
		// Clamp to +/- Fmax.
		return static_cast<f32>(isNegative ? PS2Constants::EE::EECore::FPU::FMAX_NEG : PS2Constants::EE::EECore::FPU::FMAX_POS);
	}
	case FP_SUBNORMAL:
	{
		// Round to +/- 0.
		return static_cast<f32>(isNegative ? PS2Constants::EE::EECore::FPU::ZERO_NEG : PS2Constants::EE::EECore::FPU::ZERO_POS);
	}
	default:
	{
		throw std::runtime_error("Parsed float value was NOT abnormal to the PS2 spec. Requires debugging.");
	}
	}
}

u32 FPUUtil::getXORSign(const f32& value1, const f32& value2)
{
	u32 value1_u32 = static_cast<u32>(value1);
	u32 value2_u32 = static_cast<u32>(value2);
	return (value1_u32 ^ value2_u32) & 0x80000000;
}

bool FPUUtil::getSign(const f32& value)
{
	return std::signbit(value);
}

u8 FPUUtil::getExponent(const f32& value)
{
	s32 exp;
	std::frexp(value, &exp);
	return static_cast<u8>(exp);
}
