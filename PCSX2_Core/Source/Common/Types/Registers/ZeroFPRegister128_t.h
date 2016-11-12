#pragma once

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/FPRegister128_t.h"

/*
ZeroFPRegister128_t has the same functionality as a normal zero register except with the MSB 32-bit float value set to 1.0 (VF0.w = 1.0f).
This is to be used in the vector units as VF[0].
*/
class ZeroFPRegister128_t : public FPRegister128_t
{
public:
	ZeroFPRegister128_t();

	void writeWordU(u32 arrayIndex, u32 value) override;
	void writeWordS(u32 arrayIndex, s32 value) override;
	void writeDwordU(u32 arrayIndex, u64 value) override;
	void writeDwordS(u32 arrayIndex, s64 value) override;
	void writeFloat(u32 arrayIndex, f32 value) override;
};