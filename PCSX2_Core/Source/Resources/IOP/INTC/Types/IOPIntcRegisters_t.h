#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/Register/BitfieldRegister32_t.h"
#include "Common/Types/Register/Register32_t.h"

/*
The IOP INTC I_CTRL register.
Functionality is largely unknown, however upon reading (through IOP), the register value is set to 0.
Seems to be the master control for masking interrupts.
See https://fossies.org/linux/audacious-plugins/src/psf/peops2/registers.h (line 249), and PCSX2's IopHwRead/Write.cpp.
*/
class IOPIntcRegister_CTRL_t : public Register32_t
{
public:
	explicit IOPIntcRegister_CTRL_t(const char * mnemonic, const bool debugReads, const bool debugWrites);

	/*
	Returns the register value, and sets it to 0 after (IOP context only).
	*/
	u32 readWord(const System_t context) override;
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
		static constexpr int VBLANK = 0;
		static constexpr int GPU = 1;
		static constexpr int CDROM = 2;
		static constexpr int DMA = 3;
		static constexpr int TMR0 = 4;
		static constexpr int TMR1 = 5;
		static constexpr int TMR2 = 6;
		static constexpr int SIO0 = 7;
		static constexpr int SIO1 = 8;
		static constexpr int SPU = 9;
		static constexpr int PIO = 10;
		static constexpr int EVBLANK = 11;
		static constexpr int DVD = 12;
		static constexpr int PCMCIA = 13;
		static constexpr int TMR3 = 14;
		static constexpr int TMR4 = 15;
		static constexpr int TMR5 = 16;
		static constexpr int SIO2 = 17;
		static constexpr int HTR0 = 18;
		static constexpr int HTR1 = 19;
		static constexpr int HTR2 = 20;
		static constexpr int HTR3 = 21;
		static constexpr int USB = 22;
		static constexpr int EXTR = 23;
		static constexpr int FWRE = 24;
		static constexpr int FDMA = 25;
	};

	explicit IOPIntcRegister_MASK_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
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
		static constexpr int VBLANK = 0;
		static constexpr int GPU = 1;
		static constexpr int CDROM = 2;
		static constexpr int DMA = 3;
		static constexpr int TMR0 = 4;
		static constexpr int TMR1 = 5;
		static constexpr int TMR2 = 6;
		static constexpr int SIO0 = 7;
		static constexpr int SIO1 = 8;
		static constexpr int SPU = 9;
		static constexpr int PIO = 10;
		static constexpr int EVBLANK = 11;
		static constexpr int DVD = 12;
		static constexpr int PCMCIA = 13;
		static constexpr int TMR3 = 14;
		static constexpr int TMR4 = 15;
		static constexpr int TMR5 = 16;
		static constexpr int SIO2 = 17;
		static constexpr int HTR0 = 18;
		static constexpr int HTR1 = 19;
		static constexpr int HTR2 = 20;
		static constexpr int HTR3 = 21;
		static constexpr int USB = 22;
		static constexpr int EXTR = 23;
		static constexpr int FWRE = 24;
		static constexpr int FDMA = 25;

		static constexpr int IRQ_KEYS[Constants::IOP::INTC::NUMBER_IRQ_LINES] = { VBLANK, GPU, CDROM, DMA, TMR0, TMR1, TMR2, SIO0, SIO1, SPU, PIO, EVBLANK, DVD, PCMCIA, TMR3, TMR4, TMR5, SIO2, HTR0, HTR1, HTR2, HTR3, USB, EXTR, FWRE, FDMA };
		static constexpr int TMR_KEYS[Constants::IOP::Timers::NUMBER_TIMERS] = { TMR0, TMR1, TMR2, TMR3, TMR4, TMR5 };
	};

	explicit IOPIntcRegister_STAT_t(const char * mnemonic, const bool debugReads, const bool debugWrites);

	/*
	AND's the new value with old value (IOP context only).
	*/
	void writeWord(const System_t context, u32 value) override;
};