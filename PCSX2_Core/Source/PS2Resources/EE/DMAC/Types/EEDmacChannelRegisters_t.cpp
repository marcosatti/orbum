#include "stdafx.h"

#include "PS2Resources/EE/DMAC/Types/EEDmacChannelRegisters_t.h"

EEDmacChannelRegister_CHCR_t::EEDmacChannelRegister_CHCR_t(const char * mnemonic) :
	BitfieldRegister32_t(mnemonic, true)
{
	registerField(Fields::DIR, "DIR", 0, 1, 0);
	registerField(Fields::MOD, "MOD", 2, 2, 0);
	registerField(Fields::ASP, "ASP", 4, 2, 0);
	registerField(Fields::TTE, "TTE", 6, 1, 0);
	registerField(Fields::TIE, "TIE", 7, 1, 0);
	registerField(Fields::STR, "STR", 8, 1, 0);
	registerField(Fields::TAG, "TAG", 16, 16, 0);
}

EEDmacChannelRegister_MADR_t::EEDmacChannelRegister_MADR_t(const char * mnemonic) :
	BitfieldRegister32_t(mnemonic, true)
{
	registerField(Fields::ADDR, "ADDR", 0, 31, 0);
	registerField(Fields::SPR, "SPR", 31, 1, 0);
}

void EEDmacChannelRegister_MADR_t::increment()
{
	BitfieldMap32_t::setFieldValue(Fields::ADDR, BitfieldMap32_t::getFieldValue(Fields::ADDR) + 0x10);
}

EEDmacChannelRegister_QWC_t::EEDmacChannelRegister_QWC_t(const char * mnemonic) :
	Register32_t(mnemonic, false)
{
}

void EEDmacChannelRegister_QWC_t::decrement()
{
	writeWord(Context_t::RAW, readWord(Context_t::RAW) - 1);
}

EEDmacChannelRegister_TADR_t::EEDmacChannelRegister_TADR_t(const char * mnemonic) :
	BitfieldRegister32_t(mnemonic, true)
{
	registerField(Fields::ADDR, "ADDR", 0, 31, 0);
	registerField(Fields::SPR, "SPR", 31, 1, 0);
}

void EEDmacChannelRegister_TADR_t::increment()
{
	BitfieldMap32_t::setFieldValue(Fields::ADDR, BitfieldMap32_t::getFieldValue(Fields::ADDR) + 0x10);
}

EEDmacChannelRegister_ASR_t::EEDmacChannelRegister_ASR_t(const char * mnemonic) :
	BitfieldRegister32_t(mnemonic, true)
{
	registerField(Fields::ADDR, "ADDR", 0, 31, 0);
	registerField(Fields::SPR, "SPR", 31, 1, 0);
}

EEDmacChannelRegister_SADR_t::EEDmacChannelRegister_SADR_t(const char * mnemonic) :
	Register32_t(mnemonic, true)
{
}

void EEDmacChannelRegister_SADR_t::increment()
{
	writeWord(Context_t::RAW, readWord(Context_t::RAW) + 0x10);
}
