#pragma once
#include "Common/Global/Globals.h"

class EECoreFPUUtil
{
public:
	/*
	Formats an IEEE 754 float into a PS2 spec float, by clamping NaN's and +/-Infinity to +/-Fmax and rounding denormalised values towards +/-0.
	A PS2 spec float can be thought of as a subset of the IEEE 754 float.
	*/
	static f32 formatIEEEToPS2Float(const f32 & value);

	/*
	Gets the resulting sign according to the PS2 FPU spec when a XOR-type instruction is carried out (eg: multiply or divide).
	0 = positive, 1 = negative.
	*/
	static u32 getXORSign(const f32 & value1, const f32 & value2);
};

