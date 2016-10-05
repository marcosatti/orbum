#pragma once

#include "Common/Global/Globals.h"

/*
Constants used throughout the program. All of the constants will be covered somewhere in the PS2 docs.
Special items are named with a prefix:
 PADDRESS = Physical base address.
 VADDRESS = Virtual base address.
 OADDRESS = Offset from physical/virtual address.
 SIZE = Constant size (in bytes).
 MASK = Number which is used as a mask.
 NUMBER = Number of elements.
 VALUE = Constant value.
*/
class PS2Constants
{
public:
	struct EE
	{
		struct EECore
		{
			struct Exceptions
			{
				// Number of exceptions that can be raised, see EE Core Users Manual page 94.
				static constexpr u32 NUMBER_EXCEPTIONS = 20;

				// Common exception vector properties listed on EE Core Users Manual page 90. A0 = Address 0, A1 = Address 1.
				static constexpr u32 VADDRESS_EXCEPTION_BASE_A0 = 0x80000000;
				static constexpr u32 VADDRESS_EXCEPTION_BASE_A1 = 0xBFC00200;
				static constexpr u32 VADDRESS_EXCEPTION_BASE_V_RESET_NMI = 0xBFC00000; // This is a special value used when bootstrapping.
				static constexpr u32 OADDRESS_EXCEPTION_VECTOR_V_TLB_REFILL = 0x00000000;
				static constexpr u32 OADDRESS_EXCEPTION_VECTOR_V_COUNTER = 0x00000080;
				static constexpr u32 OADDRESS_EXCEPTION_VECTOR_V_DEBUG = 0x00000100;
				static constexpr u32 OADDRESS_EXCEPTION_VECTOR_V_COMMON = 0x00000180;
				static constexpr u32 OADDRESS_EXCEPTION_VECTOR_V_INTERRUPT = 0x00000200;

				// Exception prorities - see EE Core Users Manual page 93.
				// 0 = Highest priority, ordered ascending.
				// TODO: add in.
			};

			struct ScratchpadMemory
			{
				// Scratchpad memory - see 'Memory Mappings.xlsx' for information as this is PCSX2 specific.
				static constexpr u32 PADDRESS_SCRATCHPAD_MEMORY = 0x14000000;
				static constexpr u32 SIZE_SCRATCHPAD_MEMORY = 0x00004000; // 16KB
			};

			struct MMU {
				// Page mask sizes, used within a TLB MASK field. See EE Core Users Manual page 67.
				static constexpr u32 MASK_PAGE_SIZE_4KB = 0;
				static constexpr u32 MASK_PAGE_SIZE_16KB = 3;
				static constexpr u32 MASK_PAGE_SIZE_64KB = 15;
				static constexpr u32 MASK_PAGE_SIZE_256KB = 63;
				static constexpr u32 MASK_PAGE_SIZE_1MB = 255;
				static constexpr u32 MASK_PAGE_SIZE_4MB = 1023;
				static constexpr u32 MASK_PAGE_SIZE_16MB = 4095;

				static constexpr u32 NUMBER_TLB_ENTRIES = 48;
				static constexpr u32 MASK_VPN2_FIELD_16MB = 0x0007F000;

				static constexpr u32 VADDRESS_USER_UPPER_BOUND = 0x7FFFFFFF; // Memory segment 'useg'.
				static constexpr u32 VADDRESS_USER_LOWER_BOUND = 0x00000000; 

				static constexpr u32 VADDRESS_SUPERVISOR_UPPER_BOUND_1 = 0x7FFFFFFF; // Memory segment 'suseg'.
				static constexpr u32 VADDRESS_SUPERVISOR_LOWER_BOUND_1 = 0x00000000; 
				static constexpr u32 VADDRESS_SUPERVISOR_UPPER_BOUND_2 = 0xDFFFFFFF; // Memory segment 'sseg'.
				static constexpr u32 VADDRESS_SUPERVISOR_LOWER_BOUND_2 = 0xC0000000;

				static constexpr u32 VADDRESS_KERNEL_UPPER_BOUND_1 = 0x7FFFFFFF; // Memory segment 'kuseg'.
				static constexpr u32 VADDRESS_KERNEL_LOWER_BOUND_1 = 0x00000000; 
				static constexpr u32 VADDRESS_KERNEL_UPPER_BOUND_2 = 0x9FFFFFFF; // Memory segment 'kseg0'.
				static constexpr u32 VADDRESS_KERNEL_LOWER_BOUND_2 = 0x80000000;
				static constexpr u32 VADDRESS_KERNEL_UPPER_BOUND_3 = 0xBFFFFFFF; // Memory segment 'kseg1'.
				static constexpr u32 VADDRESS_KERNEL_LOWER_BOUND_3 = 0xA0000000; 
				static constexpr u32 VADDRESS_KERNEL_UPPER_BOUND_4 = 0xDFFFFFFF; // Memory segment 'ksseg'.
				static constexpr u32 VADDRESS_KERNEL_LOWER_BOUND_4 = 0xC0000000;
				static constexpr u32 VADDRESS_KERNEL_UPPER_BOUND_5 = 0xFFFFFFFF; // Memory segment 'kseg3'.
				static constexpr u32 VADDRESS_KERNEL_LOWER_BOUND_5 = 0xE0000000;
			};
			
			struct R5900
			{
				
			};

			struct COP0
			{
				static constexpr u32 NUMBER_REGISTERS = 32;
				static constexpr u32 NUMBER_PCR_REGISTERS = 2;
			};

			struct COP1
			{
				// COP1 is also known as the FPU.
				// COP1 Constants Fmax (positive) and Fmax (negative), used as the upper and lower bounds of a float value (instead of plus and minus infinity?).
				static constexpr u32 FMAX_POS = 0x7F7FFFFF; // Sign bit = 0 -> positive.
				static constexpr u32 FMAX_NEG = 0xFF7FFFFF; // Sign bit = 1 -> negative.

				// COP1 Constants +/- zero.
				static constexpr u32 ZERO_POS = 0x00000000; // Sign bit = 0 -> positive.
				static constexpr u32 ZERO_NEG = 0x80000000; // Sign bit = 1 -> negative.
			};

			static constexpr u32 SIZE_MIPS_INSTRUCTION = 4;
			static constexpr u32 NUMBER_EECORE_INSTRUCTIONS = 260;
		};

		struct Timers
		{
			static constexpr u32 NUMBER_TIMERS = 4;
		};

		struct DMAC
		{
			static constexpr u32 NUMBER_DMA_CHANNELS = 10;
			static constexpr u32 NUMBER_CHAIN_INSTRUCTIONS = 8;
		};

		// Ratios of PS2CLK (EE Core speed) divided by other clock source within EE. The PS2CLK runs at ~294 MHz.
		// BUSCLK runs at ~147 MHz.
		static constexpr u32 RATIO_PS2CLK_BUSCLK = 2;
		static constexpr u32 RATIO_PS2CLK_BUSCLK16 = 32;
		static constexpr u32 RATIO_PS2CLK_BUSCLK256 = 512;
	};

	struct MainMemory
	{
		// Main memory. See EE Users Manual page 20 onwards.
		static constexpr u32 PADDRESS_MAIN_MEMORY = 0x00000000;
		static constexpr u32 SIZE_MAIN_MEMORY = 0x02000000; // 32MB.. which isn't actually documented anywhere in the offical docs?
	};

	struct BootROM
	{
		// Boot Rom. See EE Users Manual page 20.
		static constexpr u32 PADDRESS_BOOT_ROM = 0x1FC00000;
		static constexpr u32 SIZE_BOOT_ROM = 0x00400000;
	};

	struct GS
	{
		// Note: Ratio of PS2CLK / HBLNK is defined at runtime (set by GS). See PS2Resources_t::Clock_t::RATIO_PS2CLK_HBLNK.
	};
};

