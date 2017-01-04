#pragma once

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/BitfieldRegister32_t.h"

/*
The IOP DMAC D_CHCR register.
Based off the PSX docs.
*/
class IOPDmacChannelRegister_CHCR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 TD = 0;
		static constexpr u8 MAS = 1;
		static constexpr u8 CE = 2;
		static constexpr u8 SM = 3;
		static constexpr u8 C_DWS = 4;
		static constexpr u8 C_CWS = 5;
		static constexpr u8 START_B = 6;
		static constexpr u8 START_T = 7;
	};

	IOPDmacChannelRegister_CHCR_t(const char * mnemonic);
};

/*
The IOP DMAC D_BCR register.
Based of the PSX docs.
*/
class IOPDmacChannelRegister_BCR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 BS = 0;
		static constexpr u8 BA = 1;
	};

	IOPDmacChannelRegister_BCR_t(const char * mnemonic);
};