#pragma once

#include "Common/Global/Globals.h"

/*
Constants used throughout the program. All of the constants will be covered somewhere in the PS2 docs.
Special items are named with a prefix:
 PADDRESS = Physical base address.
 OADDRESS = Offset from physical address.
 SIZE = Constant size (in bytes).
*/
class PS2Constants
{
public:
	struct EE
	{
		struct EECore
		{
			// Exceptions. See EE Core Users Manual page 89 onwards. A0 = Address 0, A1 = Address 1.
			static constexpr u32 PADDRESS_EXCEPTION_BASE_A0 = 0x80000000;
			static constexpr u32 PADDRESS_EXCEPTION_BASE_A1 = 0xBFC00200;
			static constexpr u32 PADDRESS_EXCEPTION_BASE_V_RESET_NMI = 0xBFC00000; // This is a special value used when bootstrapping.
			static constexpr u32 OADDRESS_EXCEPTION_VECTOR_V_TLB_REFILL = 0x00000000;
			static constexpr u32 OADDRESS_EXCEPTION_VECTOR_V_COUNTER = 0x00000080;
			static constexpr u32 OADDRESS_EXCEPTION_VECTOR_V_DEBUG = 0x00000100;
			static constexpr u32 OADDRESS_EXCEPTION_VECTOR_V_COMMON = 0x00000180;
			static constexpr u32 OADDRESS_EXCEPTION_VECTOR_V_INTERRUPT = 0x00000200;
			
			struct R5900
			{
				
			};

			struct FPU
			{
				// FPU Constants Fmax (positive) and Fmax (negative), used as the upper and lower bounds of a float value (instead of plus and minus infinity?).
				static constexpr u32 FMAX_POS = 0x7FFFFFFF; // Sign bit = 0 -> positive.
				static constexpr u32 FMAX_NEG = 0xFFFFFFFF; // Sign bit = 1 -> negative.
			};

		};

		// Main memory. See EE Users Manual page 20 onwards.
		static constexpr u32 PADDRESS_MAIN_MEMORY = 0x00000000;
		static constexpr u32 SIZE_MAIN_MEMORY = 0x02000000; // 32MB.. which isn't actually documented anywhere in the offical docs?
	};
};

