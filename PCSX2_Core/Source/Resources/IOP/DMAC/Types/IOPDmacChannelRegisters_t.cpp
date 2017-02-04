#include "stdafx.h"

#include "Resources/IOP/DMAC/Types/IOPDmacChannelRegisters_t.h"

IOPDmacChannelRegister_CHCR_t::IOPDmacChannelRegister_CHCR_t(const char * mnemonic) :
	BitfieldRegister32_t(mnemonic, false, false)
{
	registerField(Fields::TD, "TD", 0, 1, 0);
	registerField(Fields::MAS, "MAS", 1, 1, 0);
	registerField(Fields::CE, "CE", 8, 1, 0);
	registerField(Fields::SM, "SM", 9, 2, 0);
	registerField(Fields::C_DWS, "C_DWS", 16, 3, 0);
	registerField(Fields::C_CWS, "C_CWS", 20, 3, 0);
	registerField(Fields::START_B, "START_B", 24, 1, 0);
	registerField(Fields::START_T, "START_T", 28, 1, 0);
}

IOPDmacChannelRegister_BCR_t::IOPDmacChannelRegister_BCR_t(const char * mnemonic) :
	BitfieldRegister32_t(mnemonic, false, false),
	mOriginalBS(0)
{
	registerField(Fields::BS, "BS", 0, 16, 0);
	registerField(Fields::BA, "BA", 16, 16, 0);
}

void IOPDmacChannelRegister_BCR_t::writeHword(const Context& context, size_t arrayIndex, u16 value)
{
	BitfieldRegister32_t::writeHword(context, arrayIndex, value);

	// Save the BS value for later.
	mOriginalBS = getFieldValue(Fields::BS);
}

void IOPDmacChannelRegister_BCR_t::writeWord(const Context& context, u32 value)
{
	BitfieldRegister32_t::writeWord(context, value);

	// Save the BS value for later.
	mOriginalBS = getFieldValue(Fields::BS);
}

void IOPDmacChannelRegister_BCR_t::decrement()
{
	u32 bsValue = getFieldValue(Fields::BS);
	u32 baValue = getFieldValue(Fields::BA);

	// Reset BS and decrement BA if end of block reached (BS == 0 and BA != 0).
	// TODO: need to check for BA underflow?
	if (((bsValue - 1) == 0)
		&& (baValue != 0))
	{
		bsValue = mOriginalBS;
		setFieldValue(Fields::BS, bsValue);
		setFieldValue(Fields::BA, baValue - 1);
	}
	else
	{
		setFieldValue(Fields::BS, bsValue - 1);
	}
}

IOPDmacChannelRegister_MADR_t::IOPDmacChannelRegister_MADR_t(const char* mnemonic) :
	Register32_t(mnemonic)
{
}

void IOPDmacChannelRegister_MADR_t::increment()
{
	writeWord(RAW, readWord(RAW) + 0x4);
}

void IOPDmacChannelRegister_MADR_t::decrement()
{
	writeWord(RAW, readWord(RAW) - 0x4);
}

IOPDmacChannelRegister_TADR_t::IOPDmacChannelRegister_TADR_t(const char* mnemonic) :
	Register32_t(mnemonic, false, false)
{
}

void IOPDmacChannelRegister_TADR_t::increment()
{
	writeWord(RAW, readWord(RAW) + 0x4);
}

void IOPDmacChannelRegister_TADR_t::decrement()
{
	writeWord(RAW, readWord(RAW) - 0x4);
}
