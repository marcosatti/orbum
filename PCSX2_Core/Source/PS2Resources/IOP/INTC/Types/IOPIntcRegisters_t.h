#pragma once

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/ClrBitfieldRegister32_t.h"
#include "Common/Types/Registers/RevBitfieldRegister32_t.h"

/*
The IOP INTC I_STAT register, which holds a set of flags determining if a component caused an interrupt.
Bits are cleared by writing 1.
*/
class IOPIntcRegister_STAT_t : public ClrBitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 VBLNK = 0;
		static constexpr u8 GPU = 1;
		static constexpr u8 CDROM = 2;
		static constexpr u8 DMA = 3;
		static constexpr u8 TMR0 = 4;
		static constexpr u8 TMR1 = 5;
		static constexpr u8 TMR2 = 6;
		static constexpr u8 PAD_MC = 7;
		static constexpr u8 SIO = 8;
		static constexpr u8 SPU = 9;
		static constexpr u8 PIO = 10;
	};

	IOPIntcRegister_STAT_t();
};

/*
The IOP INTC I_MASK register, which holds a set of flags determining if the interrupt source is masked.
Bits are reversed by writing 1.
*/
class IOPIntcRegister_MASK_t : public RevBitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 VBLNK = 0;
		static constexpr u8 GPU = 1;
		static constexpr u8 CDROM = 2;
		static constexpr u8 DMA = 3;
		static constexpr u8 TMR0 = 4;
		static constexpr u8 TMR1 = 5;
		static constexpr u8 TMR2 = 6;
		static constexpr u8 PAD_MC = 7;
		static constexpr u8 SIO = 8;
		static constexpr u8 SPU = 9;
		static constexpr u8 PIO = 10;
	};

	IOPIntcRegister_MASK_t();
};

/*
The IOP INTC I_CTRL register.
Functionality is largely unknown, however upon reading, the register value is set to 0.
Seems to be the master control for masking interrupts.
See https://fossies.org/linux/audacious-plugins/src/psf/peops2/registers.h (line 249), and PCSX2's IopHwRead/Write.cpp.
*/
class IOPIntcRegister_CTRL_t : public Register32_t
{
public:
	IOPIntcRegister_CTRL_t();

	/*
	Returns the register value, and sets it to 0 after.
	*/
	u32 readWord() override;
};