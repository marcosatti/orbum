#pragma once

#include "GlobalTypes.h"

/*
Constants used throughout the program. The constants used here are more generalised.
Special items are named with a prefix:
PADDRESS = Physical base address.
SIZE = Constant size (in bytes).
NUMBER = Number of elements.
*/
struct Constants
{
	static constexpr u32 SIZE_512MB = 512 * 1024 * 1024;

	static constexpr u32 SIZE_MIPS_INSTRUCTION = 4;

	static constexpr u32 NUMBER_R5900_INSTRUCTIONS = 259;
};