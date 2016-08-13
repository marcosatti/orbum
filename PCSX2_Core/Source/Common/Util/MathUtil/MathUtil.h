#pragma once
#include "Common/Global/Globals.h"

class MathUtil
{
public:
	static u32 countLeadingBits(s32 value); // Adapted from the old PCSX2 code and Stackoverflow (see inside body). Thanks everyone!

	static s16 saturateWordToHword(s32 value);
	static s32 saturateDwordToWord(s64 value);
};
