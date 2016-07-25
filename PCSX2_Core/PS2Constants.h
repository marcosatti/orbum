#pragma once

#include "Globals.h"

/*
Constants used throughout the program. All of the constants will be covered somewhere in the PS2 docs.
Items are named with a prefix:
 PADDRESS = Physical base address.
 SIZE = Constant size.
*/
class PS2Constants
{
public:
	struct EE
	{
		struct EECore
		{
			// Exceptions. See EE Core Users Manual page 89 onwards.
			static constexpr u32 PADDRESS_EXCEPTION_BASE_LVL1 = 0x80000000;
			static constexpr u32 PADDRESS_EXCEPTION_BASE_LVL2 = 0xBFC00000;
		};

		// Main memory. See EE Users Manual page 20 onwards.
		static constexpr u32 PADDRESS_MAIN_MEMORY = 0x00000000;
		static constexpr u32 SIZE_MAIN_MEMORY = 0x02000000; // 32MB.. which isn't actually documented anywhere in the offical docs?
	};
};

