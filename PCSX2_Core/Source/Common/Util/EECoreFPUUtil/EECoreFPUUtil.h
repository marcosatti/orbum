#pragma once
#include "Common/Global/Globals.h"
#include "Common/PS2 Resources/PS2Resources_t.h"


class EECoreFPUUtil
{
public:
	/*
	Checks if the parsed float is overflowed (meaning equal to +/-Inf).
	*/
	static bool isOverflowed(const f32 & value);

	/*
	Checks if the parsed float is underflowed (meaning denormalised number -> exponent equal to 0 and non-zero fraction).
	*/
	static bool isUnderflowed(const f32 & value);

	/*
	Formats an IEEE 754 float into a PS2 spec float, by clamping NaN's and +/-Infinity to +/-Fmax and rounding denormalised values towards +/-0.
	A PS2 spec float can be thought of as a subset of the IEEE 754 float.
	This should NEVER be used if the value is not one of the conditions above - a runtime exception is thrown. Use the other functions (isOverflow() etc) to determine if float is abnormal to the PS2 spec.
	*/
	static f32 formatIEEEToPS2Float(const f32 & value);

	/*
	Gets the resulting sign according to the PS2 FPU spec when a instruction is carried out that has a XOR-type sign (eg: multiply or divide).
	0 = positive, 1 = negative.
	*/
	static u32 getXORSign(const f32 & value1, const f32 & value2);

	/*
	Gets the sign (bit 31).
	*/
	static bool getSign(const f32 & value);

	/*
	Gets the exponent (8 bits starting from position 23).
	*/
	static u8 getExponent(const f32 & value);

	/*
	Checks if the FPU coprocessor (COP1) is unusable.
	*/
	static bool isCOP1Unusable(std::shared_ptr<PS2Resources_t> & PS2Resources);
};

