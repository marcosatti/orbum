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

				// Exception prorities - see EE Core Users Manual page 93.
				// 0 = Highest priority, ordered ascending.
				// TODO: add in.
			};

			struct ScratchpadMemory
			{
				// Scratchpad memory.
				static constexpr u32 PADDRESS_SCRATCHPAD_MEMORY = 0x70000000;
				static constexpr size_t SIZE_SCRATCHPAD_MEMORY = 0x00004000; // 16KB
			};
			
			struct R5900
			{
				static constexpr u32 NUMBER_GP_REGISTERS = 32;
				static constexpr u32 NUMBER_SYSCALLS = 256; // TODO: get real value.
			};

			struct COP0
			{
				static constexpr u32 NUMBER_REGISTERS = 32;
				static constexpr u32 NUMBER_PCR_REGISTERS = 2;
			};

			struct FPU
			{
				// FPU Constants Fmax (positive) and Fmax (negative), used as the upper and lower bounds of a float value (instead of plus and minus infinity?).
				static constexpr u32 FMAX_POS = 0x7F7FFFFF; // Sign bit = 0 -> positive.
				static constexpr u32 FMAX_NEG = 0xFF7FFFFF; // Sign bit = 1 -> negative.

				// FPU Constants +/- zero.
				static constexpr u32 ZERO_POS = 0x00000000; // Sign bit = 0 -> positive.
				static constexpr u32 ZERO_NEG = 0x80000000; // Sign bit = 1 -> negative.
			};

			struct MMU 
			{
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
			};

			static constexpr u32 NUMBER_EECORE_INSTRUCTIONS = 388;
		};

		struct Timers
		{
			static constexpr u32 NUMBER_TIMERS = 4;
		};

		struct DMAC
		{
			static constexpr u32 NUMBER_DMAC_CHANNELS = 10;
			static constexpr u32 NUMBER_CHAIN_INSTRUCTIONS = 8;
			static constexpr u32 NUMBER_IRQ_LINES = 13;
		};

		struct INTC
		{
			static constexpr u32 NUMBER_IRQ_LINES = 15;
		};

		struct MainMemory
		{
			// Main memory. See EE Users Manual page 20 onwards.
			static constexpr u32 PADDRESS_MAIN_MEMORY = 0x00000000;
			static constexpr size_t SIZE_MAIN_MEMORY = 0x02000000; // 32MB.. which isn't actually documented anywhere in the offical docs?
		};

		struct ROM
		{
			// BootROM. See EE Users Manual page 20.
			static constexpr u32 PADDRESS_BOOT_ROM = 0x1FC00000;
			static constexpr size_t SIZE_BOOT_ROM = 0x00400000;

			// ROM1. See PCSX2's source code ("MemoryTypes.h", "Memory.cpp", "IopMem.cpp").
			static constexpr u32 PADDRESS_ROM1 = 0x1E000000;
			static constexpr size_t SIZE_ROM1 = 0x00040000;

			// EROM. See PCSX2's source code ("MemoryTypes.h", "Memory.cpp", "IopMem.cpp").
			static constexpr u32 PADDRESS_EROM = 0x1E040000;
			static constexpr size_t SIZE_EROM = 0x001C0000;

			// ROM2. See PCSX2's source code ("MemoryTypes.h", "Memory.cpp", "IopMem.cpp").
			static constexpr u32 PADDRESS_ROM2 = 0x1E400000;
			static constexpr size_t SIZE_ROM2 = 0x00080000;
		};

		struct VPU
		{
			struct VIF
			{
				// Number of instructions is based off the CMD field in the VIFcode, without the leading interrupt bit and the m bit in the UNPACK instructions.
				// See EE Users Manual page 87.
				static constexpr u32 NUMBER_INSTRUCTIONS = 34;
				static constexpr u32 NUMBER_VIF_UNITS = 2;
				// VIF units run at 150 MHz, aka the BUSCLK.
			};

			struct VU
			{
				static constexpr u32 NUMBER_VF_REGISTERS = 32;
				static constexpr u32 NUMBER_VI_REGISTERS = 16;
				static constexpr u32 NUMBER_VU_UNITS = 2;
				static constexpr u32 NUMBER_VU0_CCR_REGISTERS = 32;
				static constexpr u32 NUMBER_VU_INSTRUCTIONS = 164;
				// VU units run at 150 MHz, aka the BUSCLK.
			};
		};

		// Ratios of PS2CLK (EE Core speed) divided by other clock source within EE. The PS2CLK runs at ~294 MHz.
		static constexpr u32 RATIO_PS2CLK_BUSCLK = 2;      // BUSCLK runs at ~147 MHz.
		static constexpr u32 RATIO_PS2CLK_BUSCLK16 = 32;   // BUSCLK16 = BUSCLK / 16.
		static constexpr u32 RATIO_PS2CLK_BUSCLK256 = 512; // BUSCLK256 = BUSCLK / 256
	};

	struct IOP
	{
		struct IOPCore
		{
			struct R3000
			{
				static constexpr u32 NUMBER_GP_REGISTERS = 32;
				static constexpr u32 NUMBER_SYSCALLS = 256; // TODO: get real value.
			};

			struct COP0
			{
				static constexpr u32 NUMBER_REGISTERS = 32;
			};

			struct Exceptions
			{
				static constexpr u32 NUMBER_EXCEPTIONS = 14;
			};

			struct ScratchpadMemory
			{
				// Scratchpad memory - see http://www.psxdev.net/forum/viewtopic.php?f=49&t=147
				static constexpr u32 PADDRESS_SCRATCHPAD_MEMORY = 0x1F800000;
				static constexpr size_t SIZE_SCRATCHPAD_MEMORY = 0x00000400; // 1KB
			};

			struct MMU
			{
				static constexpr u32 VADDRESS_SPECIAL_1_LOWER_BOUND = 0x00000000;
				static constexpr u32 VADDRESS_SPECIAL_1_UPPER_BOUND = 0x001FFFFF;

				static constexpr u32 VADDRESS_SPECIAL_2_LOWER_BOUND = 0xFFC00000;
				static constexpr u32 VADDRESS_SPECIAL_2_UPPER_BOUND = 0xFFFFFFFF;
			};

			static constexpr u32 NUMBER_IOP_INSTRUCTIONS = 91;
		};

		struct DMAC
		{
			static constexpr u32 NUMBER_DMAC_CHANNELS = 14;
			static constexpr u32 NUMBER_PCR_REGISTERS = 2;
			static constexpr u32 NUMBER_ICR_REGISTERS = 2;
			static constexpr u32 NUMBER_ICR_IRQ_LINES = 7;
		};

		struct Timers
		{
			static constexpr u32 NUMBER_TIMERS = 6;
		};

		struct INTC
		{
			static constexpr u32 NUMBER_IRQ_LINES = 26;
		};

		struct IOPMemory
		{
			// IOP Memory. No official documentation - from PCSX2. 
			static constexpr u32 PADDRESS_IOP_MEMORY = 0x00000000;
			static constexpr size_t SIZE_IOP_MEMORY = 0x00200000;
		};

		struct ParallelPort
		{
			// IOP Parallel Port. No official documentation - from online PSX docs.
			static constexpr u32 PADDRESS_PARALLEL_PORT = 0x1F000000;
			static constexpr size_t SIZE_PARALLEL_PORT = 0x00010000;
		};

		static constexpr u32 RATIO_PS2CLK_IOP = 8; // IOP (R3000) runs at ~36 MHz.
	};

	struct GS
	{
		// Note: Ratio of PS2CLK / HBLNK is defined at runtime (set by GS). See PS2Resources_t::Clock_t::RATIO_PS2CLK_HBLNK.
	};

	struct MIPS
	{
		// Used to define MIPS CPU constants (ie: common for the EE Core and IOP).

		struct MMU
		{
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

		struct Exceptions
		{
			// Split into the MIPS COP0.PRId.Imp values. These values are set according to the MIPS ISA, not Sony (REV is for vendors to set).
			struct Imp0
			{
				// Used by the IOP (R3000).
				// Taken from PSX docs, plus PCSX2 source code (R3000A.cpp).
				static constexpr u32 VADDRESS_EXCEPTION_BASE_A0 = 0x80000000;
				static constexpr u32 VADDRESS_EXCEPTION_BASE_A1 = 0xBFC00100;
				static constexpr u32 VADDRESS_EXCEPTION_BASE_V_RESET_NMI = 0xBFC00000; // This is a special value used when bootstrapping.
				static constexpr u32 OADDRESS_EXCEPTION_VECTOR_V_TLB_REFILL = 0x00000000;
				static constexpr u32 OADDRESS_EXCEPTION_VECTOR_V_COMMON = 0x00000080;
			};
			
			struct Imp46
			{
				// Used by the EE Core (R5900).
				// See EE Core Users Manual page 90. A0 = Address 0, A1 = Address 1.
				static constexpr u32 VADDRESS_EXCEPTION_BASE_A0 = 0x80000000;
				static constexpr u32 VADDRESS_EXCEPTION_BASE_A1 = 0xBFC00200;
				static constexpr u32 VADDRESS_EXCEPTION_BASE_V_RESET_NMI = 0xBFC00000; // This is a special value used when bootstrapping.
				static constexpr u32 OADDRESS_EXCEPTION_VECTOR_V_TLB_REFILL = 0x00000000;
				static constexpr u32 OADDRESS_EXCEPTION_VECTOR_V_COUNTER = 0x00000080;
				static constexpr u32 OADDRESS_EXCEPTION_VECTOR_V_DEBUG = 0x00000100;
				static constexpr u32 OADDRESS_EXCEPTION_VECTOR_V_COMMON = 0x00000180;
				static constexpr u32 OADDRESS_EXCEPTION_VECTOR_V_INTERRUPT = 0x00000200;
			};
		};
	};
};

