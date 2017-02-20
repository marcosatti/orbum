#pragma once

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/FPRegister128_t.h"

/*
ConstantFPRegister128_t has the same functionality as a normal constant register except with the MSB 32-bit float value set to 1.0 (ie: VF0.w = 1.0f) as default.
This is to be used in the vector units as VF[0].
*/
class ConstantFPRegister128_t : public FPRegister128_t
{
public:
	ConstantFPRegister128_t(const f32 f0 = 0.0f, const f32 f1 = 0.0f, const f32 f2 = 0.0f, const f32 f3 = 1.0f);

	void writeWord(const Context_t& context, size_t arrayIndex, u32 value) override;
	void writeDword(const Context_t& context, size_t arrayIndex, u64 value) override;
	void writeQword(const Context_t& context, u128 value) override;
	void writeFloat(const Context_t& context, size_t arrayIndex, f32 value) override;

	/*
	Initalise register (set to do nothing).
	*/
	void initalise() override;
};