#pragma once

#include "GlobalTypes.h"

/*
Constants used throughout the program. The constants used here are more generalised.
Special items are named with a prefix:
PADDRESS = Physical base address.
SIZE = Constant size (in bytes).
NUMBER = Number of elements.
VALUE = Constant value.
*/
struct Constants
{
	static constexpr u32 SIZE_512MB = 512 * 1024 * 1024;

	static constexpr u32 SIZE_MIPS_INSTRUCTION = 4;

	static constexpr u32 NUMBER_R5900_INSTRUCTIONS = 259;

	static constexpr u32 NUMBER_BYTES_IN_QWORD = 16;
	static constexpr u32 NUMBER_HWORDS_IN_QWORD = 8;
	static constexpr u32 NUMBER_WORDS_IN_QWORD = 4;
	static constexpr u32 NUMBER_DWORDS_IN_QWORD = 2;

	// Thanks Microsoft! https://msdn.microsoft.com/en-AU/library/296az74e.aspx
	static constexpr u8   VALUE_U8_MAX = 255;
	static constexpr s8   VALUE_S8_MAX = 127;
	static constexpr s8   VALUE_S8_MIN = -128;
	static constexpr u16  VALUE_U16_MAX = 65535;
	static constexpr s16  VALUE_S16_MAX = 32767;
	static constexpr s16  VALUE_S16_MIN = -32768;
	static constexpr u32  VALUE_U32_MAX = 4294967295;
	static constexpr s32  VALUE_S32_MAX = 2147483647;
	static constexpr s32  VALUE_S32_MIN = -2147483647 - 1; // Hmm... interesting. Can't use -2147483648, as it results in compiler error C4146 (too big) on VS, so use this workaround. Thanks: http://stackoverflow.com/questions/29355956/how-can-i-fix-error-code-c4146-unary-minus-operator-applied-to-unsigned-type-re
};