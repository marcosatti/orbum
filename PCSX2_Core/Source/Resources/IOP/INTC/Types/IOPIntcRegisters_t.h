#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/BitfieldRegister32_t.h"
#include "Common/Types/Registers/Register32_t.h"

/*
The IOP INTC I_CTRL register.
Functionality is largely unknown, however upon reading (through IOP), the register value is set to 0.
Seems to be the master control for masking interrupts.
See https://fossies.org/linux/audacious-plugins/src/psf/peops2/registers.h (line 249), and PCSX2's IopHwRead/Write.cpp.
*/
class IOPIntcRegister_CTRL_t : public Register32_t
{
public:
	IOPIntcRegister_CTRL_t();

	/*
	Returns the register value, and sets it to 0 after (IOP context only).
	*/
	u32 readWord(const Context_t context) override;
};

/*
The IOP INTC I_MASK register, which holds a set of flags determining if the interrupt source is masked.
Names from here, not sure if accurate: https://github.com/kode54/Highly_Experimental/blob/master/Core/iop.c.
*/
class IOPIntcRegister_MASK_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 VBLANK = 0;
		static constexpr u8 GPU = 1;
		static constexpr u8 CDROM = 2;
		static constexpr u8 DMA = 3;
		static constexpr u8 TMR0 = 4;
		static constexpr u8 TMR1 = 5;
		static constexpr u8 TMR2 = 6;
		static constexpr u8 SIO0 = 7;
		static constexpr u8 SIO1 = 8;
		static constexpr u8 SPU = 9;
		static constexpr u8 PIO = 10;
		static constexpr u8 EVBLANK = 11;
		static constexpr u8 DVD = 12;
		static constexpr u8 PCMCIA = 13;
		static constexpr u8 TMR3 = 14;
		static constexpr u8 TMR4 = 15;
		static constexpr u8 TMR5 = 16;
		static constexpr u8 SIO2 = 17;
		static constexpr u8 HTR0 = 18;
		static constexpr u8 HTR1 = 19;
		static constexpr u8 HTR2 = 20;
		static constexpr u8 HTR3 = 21;
		static constexpr u8 USB = 22;
		static constexpr u8 EXTR = 23;
		static constexpr u8 FWRE = 24;
		static constexpr u8 FDMA = 25;
	};

	IOPIntcRegister_MASK_t();
};

/*
The IOP INTC I_STAT register, which holds a set of flags determining if a component caused an interrupt.
When written to, AND's the previous value with the new value (see IopHwWrite.cpp in PCSX2).
Names from here, not sure if accurate: https://github.com/kode54/Highly_Experimental/blob/master/Core/iop.c.
*/
class IOPIntcRegister_STAT_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 VBLANK = 0;
		static constexpr u8 GPU = 1;
		static constexpr u8 CDROM = 2;
		static constexpr u8 DMA = 3;
		static constexpr u8 TMR0 = 4;
		static constexpr u8 TMR1 = 5;
		static constexpr u8 TMR2 = 6;
		static constexpr u8 SIO0 = 7;
		static constexpr u8 SIO1 = 8;
		static constexpr u8 SPU = 9;
		static constexpr u8 PIO = 10;
		static constexpr u8 EVBLANK = 11;
		static constexpr u8 DVD = 12;
		static constexpr u8 PCMCIA = 13;
		static constexpr u8 TMR3 = 14;
		static constexpr u8 TMR4 = 15;
		static constexpr u8 TMR5 = 16;
		static constexpr u8 SIO2 = 17;
		static constexpr u8 HTR0 = 18;
		static constexpr u8 HTR1 = 19;
		static constexpr u8 HTR2 = 20;
		static constexpr u8 HTR3 = 21;
		static constexpr u8 USB = 22;
		static constexpr u8 EXTR = 23;
		static constexpr u8 FWRE = 24;
		static constexpr u8 FDMA = 25;

		static constexpr u8 IRQ_KEYS[Constants::IOP::INTC::NUMBER_IRQ_LINES] = { VBLANK, GPU, CDROM, DMA, TMR0, TMR1, TMR2, SIO0, SIO1, SPU, PIO, EVBLANK, DVD, PCMCIA, TMR3, TMR4, TMR5, SIO2, HTR0, HTR1, HTR2, HTR3, USB, EXTR, FWRE, FDMA };
		static constexpr u8 TMR_KEYS[Constants::IOP::Timers::NUMBER_TIMERS] = { TMR0, TMR1, TMR2, TMR3, TMR4, TMR5 };
	};

	explicit IOPIntcRegister_STAT_t();

	/*
	AND's the new value with old value (IOP context only).
	*/
	void writeWord(const Context_t context, u32 value) override;
};