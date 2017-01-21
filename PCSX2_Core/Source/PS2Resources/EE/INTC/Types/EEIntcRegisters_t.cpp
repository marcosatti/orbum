#include "stdafx.h"

#include "PS2Resources/EE/INTC/Types/EEIntcRegisters_t.h"

EEIntcRegister_STAT_t::EEIntcRegister_STAT_t(const std::shared_ptr<EEIntcRegister_MASK_t> & mask) :
	BitfieldRegister32_t("EE INTC STAT", false, false)
{
	registerField(Fields::GS, "GS", 0, 1, 0);
	registerField(Fields::SBUS, "SBUS", 1, 1, 0);
	registerField(Fields::VBON, "VBON", 2, 1, 0);
	registerField(Fields::VBOF, "VBOF", 3, 1, 0);
	registerField(Fields::VIF0, "VIF0", 4, 1, 0);
	registerField(Fields::VIF1, "VIF1", 5, 1, 0);
	registerField(Fields::VU0, "VU0", 6, 1, 0);
	registerField(Fields::VU1, "VU1", 7, 1, 0);
	registerField(Fields::IPU, "IPU", 8, 1, 0);
	registerField(Fields::TIM0, "TIM0", 9, 1, 0);
	registerField(Fields::TIM1, "TIM1", 10, 1, 0);
	registerField(Fields::TIM2, "TIM2", 11, 1, 0);
	registerField(Fields::TIM3, "TIM3", 12, 1, 0);
	registerField(Fields::SFIFO, "SFIFO", 13, 1, 0);
	registerField(Fields::VU0WD, "VU0WD", 14, 1, 0);
}

void EEIntcRegister_STAT_t::writeWord(const Context_t& context, u32 value)
{
	if (context == Context_t::EE)
		value = readWord(Context_t::RAW) & (~value);
		
	BitfieldRegister32_t::writeWord(context, value);
}

EEIntcRegister_MASK_t::EEIntcRegister_MASK_t() 
{
	registerField(Fields::GS, "GS", 0, 1, 0);
	registerField(Fields::SBUS, "SBUS", 1, 1, 0);
	registerField(Fields::VBON, "VBON", 2, 1, 0);
	registerField(Fields::VBOF, "VBOF", 3, 1, 0);
	registerField(Fields::VIF0, "VIF0", 4, 1, 0);
	registerField(Fields::VIF1, "VIF1", 5, 1, 0);
	registerField(Fields::VU0, "VU0", 6, 1, 0);
	registerField(Fields::VU1, "VU1", 7, 1, 0);
	registerField(Fields::IPU, "IPU", 8, 1, 0);
	registerField(Fields::TIM0, "TIM0", 9, 1, 0);
	registerField(Fields::TIM1, "TIM1", 10, 1, 0);
	registerField(Fields::TIM2, "TIM2", 11, 1, 0);
	registerField(Fields::TIM3, "TIM3", 12, 1, 0);
	registerField(Fields::SFIFO, "SFIFO", 13, 1, 0);
	registerField(Fields::VU0WD, "VU0WD", 14, 1, 0);
}

void EEIntcRegister_MASK_t::writeWord(const Context_t& context, u32 value)
{
	if (context == Context_t::EE)
		BitfieldRegister32_t::writeWord(Context_t::RAW, readWord(Context_t::RAW) ^ value);
	else
		BitfieldRegister32_t::writeWord(context, value);
}
