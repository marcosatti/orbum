#include "stdafx.h"

#include "PS2Resources/IOP/INTC/Types/IOPIntcRegisters_t.h"

IOPIntcRegister_STAT_t::IOPIntcRegister_STAT_t()
{
	registerField(Fields::VBLNK, "VBLNK", 0, 1, 0);
	registerField(Fields::GPU, "GPU", 1, 1, 0);
	registerField(Fields::CDROM, "CDROM", 2, 1, 0);
	registerField(Fields::DMA, "DMA", 3, 1, 0);
	registerField(Fields::TMR0, "TMR0", 4, 1, 0);
	registerField(Fields::TMR1, "TMR1", 5, 1, 0);
	registerField(Fields::TMR2, "TMR2", 6, 1, 0);
	registerField(Fields::PAD_MC, "PAD_MC", 7, 1, 0);
	registerField(Fields::SIO, "SIO", 8, 1, 0);
	registerField(Fields::SPU, "SPU", 9, 1, 0);
	registerField(Fields::PIO, "PIO", 10, 1, 0);
}

IOPIntcRegister_MASK_t::IOPIntcRegister_MASK_t() 
{
	registerField(Fields::VBLNK, "VBLNK", 0, 1, 0);
	registerField(Fields::GPU, "GPU", 1, 1, 0);
	registerField(Fields::CDROM, "CDROM", 2, 1, 0);
	registerField(Fields::DMA, "DMA", 3, 1, 0);
	registerField(Fields::TMR0, "TMR0", 4, 1, 0);
	registerField(Fields::TMR1, "TMR1", 5, 1, 0);
	registerField(Fields::TMR2, "TMR2", 6, 1, 0);
	registerField(Fields::PAD_MC, "PAD_MC", 7, 1, 0);
	registerField(Fields::SIO, "SIO", 8, 1, 0);
	registerField(Fields::SPU, "SPU", 9, 1, 0);
	registerField(Fields::PIO, "PIO", 10, 1, 0);
}

IOPIntcRegister_CTRL_t::IOPIntcRegister_CTRL_t() : 
	Register32_t("IOP INTC: CTRL")
{
}

u32 IOPIntcRegister_CTRL_t::readWord()
{
	auto temp = Register32_t::readWord();
	writeWord(0);
	return temp;
}
