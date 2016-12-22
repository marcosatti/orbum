#include "stdafx.h"

#include "PS2Resources/IOP/DMAC/Types/IOPDmacChannelRegisters_t.h"

IOPDmacChannelRegister_CHCR_t::IOPDmacChannelRegister_CHCR_t(const char * mnemonic) :
	DebugBitfieldRegister32_t(mnemonic)
{
}

IOPDmacChannelRegister_MADR_t::IOPDmacChannelRegister_MADR_t(const char * mnemonic) :
	DebugBitfieldRegister32_t(mnemonic)
{
}

IOPDmacChannelRegister_BCR_t::IOPDmacChannelRegister_BCR_t(const char * mnemonic) :
	DebugBitfieldRegister32_t(mnemonic)
{
}

IOPDmacChannelRegister_TADR_t::IOPDmacChannelRegister_TADR_t(const char * mnemonic) :
	DebugBitfieldRegister32_t(mnemonic)
{
}
