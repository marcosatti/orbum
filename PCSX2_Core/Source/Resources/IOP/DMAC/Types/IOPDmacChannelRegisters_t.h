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

	/*
	Saves the written BS value to be used later (see below).
	*/
	void writeHword(const Context_t& context, size_t arrayIndex, u16 value) override;
	void writeWord(const Context_t & context, u32 value) override;

	/*
	Decrements the BS counter by 1. Should be called when a data unit has been transferred.
	This will automatically update the BA (block amount) value when BS is equal to 0, 
	 and then reset BS back to the original value.
	*/
	void decrement();

private:
	/*
	Whenever the register is written to, the original BS value is stored here as a way
	 to reset the BS value whenever the end of a block has been reache (see decrement()).
	*/
	u32 mOriginalBS;
};

/*
The DMAC D_MADR register, aka transfer address register.
*/
class IOPDmacChannelRegister_MADR_t : public Register32_t
{
public:
	IOPDmacChannelRegister_MADR_t(const char * mnemonic);

	/*
	Increments or decrements the register by 0x4, which is the size of 1 DMA transfer (used when one transfer has completed).
	*/
	void increment();
	void decrement();
};

/*
The DMAC D_MADR register, aka transfer address register.
*/
class IOPDmacChannelRegister_TADR_t : public Register32_t
{
public:
	IOPDmacChannelRegister_TADR_t(const char * mnemonic);

	/*
	Increments or decrements the register by 0x4, which is the size of 1 DMA transfer (used when one transfer has completed).
	*/
	void increment();
	void decrement();
};