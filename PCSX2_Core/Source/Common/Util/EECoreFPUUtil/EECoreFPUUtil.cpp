#include "stdafx.h"


#include <cmath>

#include "Common/Util/EECoreFPUUtil/EECoreFPUUtil.h"
#include "Common/PS2 Constants/PS2Constants.h"

f32 EECoreFPUUtil::formatIEEEToPS2Float(const f32 & value)
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
		return value;
	}
	}
}

u32 EECoreFPUUtil::getXORSign(const f32& value1, const f32& value2)
{
	u32 value1_u32 = static_cast<u32>(value1);
	u32 value2_u32 = static_cast<u32>(value2);
	return (value1_u32 ^ value2_u32) & 0x80000000;
}
