#pragma once

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/BitfieldRegister32_t.h"
#include "Common/Types/Registers/DebugBitfieldRegister32_t.h"

/*
The DMAC D_CHCR register.
*/
class IOPDmacChannelRegister_CHCR_t : public DebugBitfieldRegister32_t
{
public:
	struct Fields
	{
	};

	IOPDmacChannelRegister_CHCR_t(const char * mnemonic);
};

/*
The DMAC D_MADR register.
*/
class IOPDmacChannelRegister_MADR_t : public DebugBitfieldRegister32_t
{
public:
	struct Fields
	{
	};

	IOPDmacChannelRegister_MADR_t(const char * mnemonic);
};

/*
The DMAC D_BCR register.
*/
class IOPDmacChannelRegister_BCR_t : public DebugBitfieldRegister32_t
{
public:
	struct Fields
	{
	};

	IOPDmacChannelRegister_BCR_t(const char * mnemonic);
};

/*
The DMAC D_TADR register, aka tag address register.
*/
class IOPDmacChannelRegister_TADR_t : public DebugBitfieldRegister32_t
{
public:
	struct Fields
	{
	};

	IOPDmacChannelRegister_TADR_t(const char * mnemonic);
};