#pragma once

#include "Common/Global/Globals.h"
#include "Common/Util/FPUUtil/FPUFlags_t.h"

class FPUUtil
{
public:
	/*
	Formats an IEEE 754 float into a PS2 spec float, by clamping NaN's and +/-Infinity to +/-Fmax and rounding denormalised values towards +/-0.
	A PS2 spec float can be thought of as a subset of the IEEE 754 float.
	
	When converting, a set of flags will be filled in that can be used to set eg: the VU MAC flags.
	*/
	static f32 formatIEEEToPS2Float(const f32 & value, FPUFlags_t & flags);

	/*
	Gets the resulting sign according to the PS2 FPU spec when a instruction is carried out that has a XOR-type sign (eg: multiply or divide).
	0 = positive, 1 = negative.
	*/
	static u32 getXORSign(const f32 & value1, const f32 & value2);

	/*
	Checks if the parsed float is negative.
	True = negative, false = positive.
	*/
	static bool isNegative(const f32 & value);

	/*
	Gets the exponent (8 bits starting from position 23).
	*/
	static u8 getExponent(const f32 & value);
};

