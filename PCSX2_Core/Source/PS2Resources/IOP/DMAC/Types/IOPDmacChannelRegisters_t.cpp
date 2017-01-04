#include "stdafx.h"

#include "PS2Resources/IOP/DMAC/Types/IOPDmacChannelRegisters_t.h"

IOPDmacChannelRegister_CHCR_t::IOPDmacChannelRegister_CHCR_t(const char * mnemonic) :
	BitfieldRegister32_t(mnemonic, true)
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
	BitfieldRegister32_t(mnemonic, true)
{
	registerField(Fields::BS, "BS", 0, 16, 0);
	registerField(Fields::BA, "BA", 16, 16, 0);
}
