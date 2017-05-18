#include "Resources/IOP/INTC/Types/IOPIntcRegisters_t.h"

constexpr int IOPIntcRegister_STAT_t::Fields::IRQ_KEYS[Constants::IOP::INTC::NUMBER_IRQ_LINES];
constexpr int IOPIntcRegister_STAT_t::Fields::TMR_KEYS[Constants::IOP::Timers::NUMBER_TIMERS];

IOPIntcRegister_STAT_t::IOPIntcRegister_STAT_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister32_t(mnemonic, debugReads, debugWrites)
{
	registerField(Fields::VBLANK, "VBLANK", 0, 1, 0);
	registerField(Fields::GPU, "GPU", 1, 1, 0);
	registerField(Fields::CDROM, "CDROM", 2, 1, 0);
	registerField(Fields::DMAC, "DMAC", 3, 1, 0);
	registerField(Fields::TMR0, "TMR0", 4, 1, 0);
	registerField(Fields::TMR1, "TMR1", 5, 1, 0);
	registerField(Fields::TMR2, "TMR2", 6, 1, 0);
	registerField(Fields::SIO0, "SIO0", 7, 1, 0);
	registerField(Fields::SIO1, "SIO1", 8, 1, 0);
	registerField(Fields::SPU, "SPU", 9, 1, 0);
	registerField(Fields::PIO, "PIO", 10, 1, 0);
	registerField(Fields::EVBLANK, "EVBLANK", 11, 1, 0); // End of VBLANK?
	registerField(Fields::DVD, "DVD", 12, 1, 0);
	registerField(Fields::PCMCIA, "PCMCIA", 13, 1, 0);
	registerField(Fields::TMR3, "TMR3", 14, 1, 0);
	registerField(Fields::TMR4, "TMR4", 15, 1, 0);
	registerField(Fields::TMR5, "TMR5", 16, 1, 0);
	registerField(Fields::SIO2, "SIO2", 17, 1, 0);
	registerField(Fields::HTR0, "HTR0", 18, 1, 0);
	registerField(Fields::HTR1, "HTR1", 19, 1, 0);
	registerField(Fields::HTR2, "HTR2", 20, 1, 0);
	registerField(Fields::HTR3, "HTR3", 21, 1, 0);
	registerField(Fields::USB, "USB", 22, 1, 0);
	registerField(Fields::EXTR, "EXTR", 23, 1, 0);
	registerField(Fields::FWRE, "FWRE", 24, 1, 0);
	registerField(Fields::FDMA, "FDMA", 25, 1, 0);
}

void IOPIntcRegister_STAT_t::writeWord(const System_t context, const u32 value)
{
	// Preprocessing for IOP: AND with old value (acknowledge bits).
	u32 temp = value;
	if (context == System_t::IOPCore)
		temp = readWord(context) & value;

	BitfieldRegister32_t::writeWord(context, temp);
}

IOPIntcRegister_MASK_t::IOPIntcRegister_MASK_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister32_t(mnemonic, debugReads, debugWrites)
{
	registerField(Fields::VBLANK, "VBLANK", 0, 1, 0);
	registerField(Fields::GPU, "GPU", 1, 1, 0);
	registerField(Fields::CDROM, "CDROM", 2, 1, 0);
	registerField(Fields::DMAC, "DMAC", 3, 1, 0);
	registerField(Fields::TMR0, "TMR0", 4, 1, 0);
	registerField(Fields::TMR1, "TMR1", 5, 1, 0);
	registerField(Fields::TMR2, "TMR2", 6, 1, 0);
	registerField(Fields::SIO0, "SIO0", 7, 1, 0);
	registerField(Fields::SIO1, "SIO1", 8, 1, 0);
	registerField(Fields::SPU, "SPU", 9, 1, 0);
	registerField(Fields::PIO, "PIO", 10, 1, 0);
	registerField(Fields::EVBLANK, "EVBLANK", 11, 1, 0); // End of VBLANK?
	registerField(Fields::DVD, "DVD", 12, 1, 0);
	registerField(Fields::PCMCIA, "PCMCIA", 13, 1, 0);
	registerField(Fields::TMR3, "TMR3", 14, 1, 0);
	registerField(Fields::TMR4, "TMR4", 15, 1, 0);
	registerField(Fields::TMR5, "TMR5", 16, 1, 0);
	registerField(Fields::SIO2, "SIO2", 17, 1, 0);
	registerField(Fields::HTR0, "HTR0", 18, 1, 0);
	registerField(Fields::HTR1, "HTR1", 19, 1, 0);
	registerField(Fields::HTR2, "HTR2", 20, 1, 0);
	registerField(Fields::HTR3, "HTR3", 21, 1, 0);
	registerField(Fields::USB, "USB", 22, 1, 0);
	registerField(Fields::EXTR, "EXTR", 23, 1, 0);
	registerField(Fields::FWRE, "FWRE", 24, 1, 0);
	registerField(Fields::FDMA, "FDMA", 25, 1, 0);
}

IOPIntcRegister_CTRL_t::IOPIntcRegister_CTRL_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	Register32_t(mnemonic, debugReads, debugWrites)
{
}

u32 IOPIntcRegister_CTRL_t::readWord(const System_t context)
{
	auto temp = Register32_t::readWord(context);

	if (context == System_t::IOPCore)
		writeWord(context, 0);

	return temp;
}
