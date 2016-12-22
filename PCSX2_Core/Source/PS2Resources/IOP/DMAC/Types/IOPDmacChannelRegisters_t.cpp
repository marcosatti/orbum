#include "stdafx.h"

#include "PS2Resources/IOP/DMAC/Types/IOPDmacChannelRegisters_t.h"

IOPDmacChannelRegister_CHCR_t::IOPDmacChannelRegister_CHCR_t(const char * mnemonic) :
	DebugBitfieldRegister32_t(mnemonic)
{
	registerField(Fields::DR, "DR", 0, 1, 0);
	registerField(Fields::CO, "CO", 9, 1, 0);
	registerField(Fields::LI, "LI", 10, 1, 0);
	registerField(Fields::TR, "TR", 24, 1, 0);
}

IOPDmacChannelRegister_BCR_t::IOPDmacChannelRegister_BCR_t(const char * mnemonic) :
	DebugBitfieldRegister32_t(mnemonic)
{
	registerField(Fields::BS, "BS", 0, 16, 0);
	registerField(Fields::BA, "BA", 16, 16, 0);
}
