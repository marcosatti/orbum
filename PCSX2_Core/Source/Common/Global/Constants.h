#pragma once

#include "Common/Global/PrimativeTypes.h"

/*
Constants used throughout the PS2 core.

Some prefix definitions (others are self-explanatory):
PADDRESS = Physical base address.
VADDRESS = Virtual base address.
OADDRESS = Offset from physical/virtual address.
SIZE = Size in bytes.
CLK_SPEED = Speed in Hz;
REFRESH_RATE = Speed in Hz.
*/
struct Constants
{
	// From Microsoft: https://msdn.microsoft.com/en-AU/library/296az74e.aspx.
	static constexpr u8  VALUE_U8_MAX = 255;
	static constexpr s8  VALUE_S8_MAX = 127;
	static constexpr s8  VALUE_S8_MIN = -128;
	static constexpr u16 VALUE_U16_MAX = 65535;
	static constexpr s16 VALUE_S16_MAX = 32767;
	static constexpr s16 VALUE_S16_MIN = -32768;
	static constexpr u32 VALUE_U32_MAX = 4294967295;
	static constexpr s32 VALUE_S32_MAX = 2147483647;
	static constexpr s32 VALUE_S32_MIN = -2147483647 - 1; // Can't use -2147483648, as it results in compiler error C4146 (too big) on VS, so use this workaround. Thanks: http://stackoverflow.com/questions/29355956/how-can-i-fix-error-code-c4146-unary-minus-operator-applied-to-unsigned-type-re.
	static constexpr u64 VALUE_U64_MAX = 18446744073709551615;
	static constexpr s64 VALUE_S64_MAX = 9223372036854775807;
	static constexpr s64 VALUE_S64_MIN = -9223372036854775807 - 1; // Same reason as above.

	static constexpr size_t SIZE_4GB   = 0x100000000;
	static constexpr size_t SIZE_512MB = 0x20000000;
	static constexpr size_t SIZE_32MB  = 0x2000000;
	static constexpr size_t SIZE_4MB   = 0x400000;
	static constexpr size_t SIZE_2MB   = 0x200000;
	static constexpr size_t SIZE_512KB = 0x80000;
	static constexpr size_t SIZE_256KB = 0x40000;
	static constexpr size_t SIZE_64KB  = 0x10000;
	static constexpr size_t SIZE_32KB  = 0x8000;
	static constexpr size_t SIZE_16KB  = 0x4000;
	static constexpr size_t SIZE_8KB   = 0x2000;
	static constexpr size_t SIZE_4KB   = 0x1000;
	static constexpr size_t SIZE_1KB   = 0x400;
	static constexpr size_t SIZE_16B   = 0x10;
	static constexpr size_t SIZE_4B    = 0x4;

	static constexpr u32 MASK_16KB = 0x00003FFF;

	static constexpr int NUMBER_BYTES_IN_QWORD = 16;
	static constexpr int NUMBER_HWORDS_IN_QWORD = 8;
	static constexpr int NUMBER_WORDS_IN_QWORD = 4;
	static constexpr int NUMBER_DWORDS_IN_QWORD = 2;
	static constexpr int NUMBER_BYTES_IN_DWORD = 8;
	static constexpr int NUMBER_HWORDS_IN_DWORD = 4;
	static constexpr int NUMBER_WORDS_IN_DWORD = 2;
	static constexpr int NUMBER_BYTES_IN_WORD = 4;
	static constexpr int NUMBER_HWORDS_IN_WORD = 2;
	static constexpr int NUMBER_BYTES_IN_HWORD = 2;

	struct MIPS
	{
		static constexpr size_t SIZE_MIPS_INSTRUCTION = 0x4;

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
			// Split into the MIPS COP0.PRId.Imp values. These values are set according to the MIPS ISA, not Sony (REV is for vendors, such as Sony, to set).
			struct Imp0
			{
				// Used by the IOP (R3000).
				// Taken from PSX docs, plus PCSX2 source code (R3000A.cpp).
				static constexpr u32 VADDRESS_EXCEPTION_BASE_A0 = 0x80000000;
				static constexpr u32 VADDRESS_EXCEPTION_BASE_A1 = 0xBFC00100;
				static constexpr u32 VADDRESS_EXCEPTION_BASE_V_RESET_NMI = 0xBFC00000;
				static constexpr u32 OADDRESS_EXCEPTION_VECTOR_V_TLB_REFILL = 0x00000000;
				static constexpr u32 OADDRESS_EXCEPTION_VECTOR_V_COMMON = 0x00000080;
			};

			struct Imp46
			{
				// Used by the EE Core (R5900).
				// See EE Core Users Manual page 90. A0 = Address 0, A1 = Address 1.
				static constexpr u32 VADDRESS_EXCEPTION_BASE_A0 = 0x80000000;
				static constexpr u32 VADDRESS_EXCEPTION_BASE_A1 = 0xBFC00200;
				static constexpr u32 VADDRESS_EXCEPTION_BASE_V_RESET_NMI = 0xBFC00000;
				static constexpr u32 OADDRESS_EXCEPTION_VECTOR_V_TLB_REFILL = 0x00000000;
				static constexpr u32 OADDRESS_EXCEPTION_VECTOR_V_COUNTER = 0x00000080;
				static constexpr u32 OADDRESS_EXCEPTION_VECTOR_V_DEBUG = 0x00000100;
				static constexpr u32 OADDRESS_EXCEPTION_VECTOR_V_COMMON = 0x00000180;
				static constexpr u32 OADDRESS_EXCEPTION_VECTOR_V_INTERRUPT = 0x00000200;
			};
		};
	};

	struct EE
	{
		struct EECore
		{
			struct ScratchpadMemory
			{
				static constexpr size_t SIZE_SCRATCHPAD_MEMORY = SIZE_16KB;
			};

			struct R5900
			{
				static constexpr int NUMBER_GP_REGISTERS = 32;
				static constexpr int NUMBER_SYSCALLS = 256; // TODO: get real value.
				static constexpr int NUMBER_EXCEPTIONS = 20;
			};

			struct COP0
			{
				static constexpr int NUMBER_REGISTERS = 32;
				static constexpr int NUMBER_PCR_REGISTERS = 2;
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

				static constexpr int NUMBER_TLB_ENTRIES = 48;
				static constexpr u32 MASK_VPN2_FIELD_16MB = 0x0007F000;
			};

			static constexpr int NUMBER_INSTRUCTIONS = 388;
			static constexpr double EECORE_CLK_SPEED = 294912000.0; // 294.912 MHz.
		};

		struct Timers
		{
			static constexpr int NUMBER_TIMERS = 4;
		};

		struct DMAC
		{
			static constexpr int NUMBER_DMAC_CHANNELS = 10;
			static constexpr int NUMBER_CHAIN_INSTRUCTIONS = 8;
		};

		struct INTC
		{
			static constexpr int NUMBER_IRQ_LINES = 15;
		};

		struct MainMemory
		{
			static constexpr size_t SIZE_MAIN_MEMORY = SIZE_32MB;
		};

		struct ROM
		{
			// BootROM. See EE Users Manual page 20.
			static constexpr size_t SIZE_BOOT_ROM = SIZE_4MB;

			// ROM1. See PCSX2's source code ("MemoryTypes.h", "Memory.cpp", "IopMem.cpp").
			static constexpr size_t SIZE_ROM1 = SIZE_256KB;

			// EROM. See PCSX2's source code ("MemoryTypes.h", "Memory.cpp", "IopMem.cpp").
			static constexpr size_t SIZE_EROM = 0x001C0000; // 1792 kB.

			// ROM2. See PCSX2's source code ("MemoryTypes.h", "Memory.cpp", "IopMem.cpp").
			static constexpr size_t SIZE_ROM2 = SIZE_512KB;
		};

		struct VPU
		{
			struct VIF
			{
				// Number of instructions is based off the CMD field in the VIFcode, without the leading interrupt bit and the m bit in the UNPACK instructions. See EE Users Manual page 87.
				static constexpr int NUMBER_INSTRUCTIONS = 34;
				static constexpr int NUMBER_VIF_CORES = 2;
			};

			struct VU
			{
				static constexpr int NUMBER_VF_REGISTERS = 32;
				static constexpr int NUMBER_VI_REGISTERS = 16;
				static constexpr int NUMBER_VU_CORES = 2;
				static constexpr int NUMBER_VU0_CCR_REGISTERS = 32;
				static constexpr int NUMBER_VU_INSTRUCTIONS = 164;
				static constexpr double VU_CLK_SPEED = 147456000.0; // 147.456 MHz.
			};
		};

		static constexpr double EEBUS_CLK_SPEED = 150000000.0; // 150 MHz.
	};

	struct IOP
	{
		struct IOPCore
		{
			struct R3000
			{
				static constexpr int NUMBER_GP_REGISTERS = 32;
				static constexpr int NUMBER_SYSCALLS = 256; // TODO: get real value.
				static constexpr int NUMBER_EXCEPTIONS = 14;
			};

			struct COP0
			{
				static constexpr int NUMBER_REGISTERS = 32;
			};

			struct ScratchpadMemory
			{
				// IOP scratchpad memory - see http://www.psxdev.net/forum/viewtopic.php?f=49&t=147
				static constexpr size_t SIZE_SCRATCHPAD_MEMORY = SIZE_1KB;
			};

			struct MMU
			{
				static constexpr u32 VADDRESS_SPECIAL_1_LOWER_BOUND = 0x00000000;
				static constexpr u32 VADDRESS_SPECIAL_1_UPPER_BOUND = 0x001FFFFF;

				static constexpr u32 VADDRESS_SPECIAL_2_LOWER_BOUND = 0xFFC00000;
				static constexpr u32 VADDRESS_SPECIAL_2_UPPER_BOUND = 0xFFFFFFFF;
			};

			static constexpr int NUMBER_IOP_INSTRUCTIONS = 91;
			static constexpr double IOPCORE_CLK_SPEED = 37500000.0; // 37.5 MHz in PS2 mode, PS1 mode not supported for now (runs at original PSX speed of ~33 MHz).
		};

		struct DMAC
		{
			static constexpr int NUMBER_DMAC_CHANNELS = 14;
			static constexpr int NUMBER_PCR_REGISTERS = 2;
			static constexpr int NUMBER_ICR_REGISTERS = 2;
			static constexpr int NUMBER_ICR_IRQ_LINES = 7;
		};

		struct SPU2
		{
			static constexpr size_t SIZE_MAIN_MEMORY = SIZE_2MB;
			static constexpr int NUMBER_CORES = 2;
			static constexpr int NUMBER_CORE_VOICES = 24;
		};

		struct Timers
		{
			static constexpr int NUMBER_TIMERS = 6;
		};

		struct INTC
		{
			static constexpr int NUMBER_IRQ_LINES = 26;
		};

		struct IOPMemory
		{
			// IOP Memory. No official documentation - from PCSX2. 
			static constexpr size_t SIZE_IOP_MEMORY = SIZE_2MB;
		};

		struct ParallelPort
		{
			// IOP Parallel Port. No official documentation - from online PSX docs.
			static constexpr size_t SIZE_PARALLEL_PORT = SIZE_64KB;
		};

		static constexpr double IOPBUS_CLK_SPEED = 37500000.0; // 37.5 MHz (same as IOPCore speed).
	};

	struct GS
	{
		struct GSCore
		{
			static constexpr double GSCORE_CLK_SPEED = 150000000.0; // 150 MHz.
		};

		struct CRTC
		{
			struct NTSC
			{
				static constexpr double INTERLACED_FIELD_REFRESH_RATE = 59.94; // Vertical refresh rate (interlaced).
				static constexpr double PROGRESSIVE_FRAME_REFRESH_RATE = 59.82; // Vertical refresh rate (progressive).
				static constexpr double SCANLINE_REFRESH_RATE = 15734.0; // Horizontal refresh rate.
			};

			struct PAL
			{
				static constexpr double INTERLACED_FIELD_REFRESH_RATE = 50.00; // Vertical refresh rate (interlaced).
				static constexpr double PROGRESSIVE_FRAME_REFRESH_RATE = 49.76; // Vertical refresh rate (progressive).
				static constexpr double SCANLINE_REFRESH_RATE = 16625.0; // Horizontal refresh rate.
			};

			struct VESA
			{
			};

			struct DTV
			{
			};

			static constexpr double PCRTC_CLK_SPEED_DEFAULT = 1 / ((1/15734.0) / 2 / 640); // ~20 MHz, guess based on NTSC defaults of resX = 640 @ 15.734 kHz. Working: period of 1 cycle, divided by half (actual render vs. hblank), divided by number of resX pixels, all inversed for Hz.
		};

	};

	
};