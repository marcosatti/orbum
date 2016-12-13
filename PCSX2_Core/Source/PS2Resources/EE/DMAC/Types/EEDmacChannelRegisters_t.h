#pragma once

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/BitfieldRegister32_t.h"

/*
The DMAC D_CHCR register, aka channel control register.
Needs a reference to a slice count variable that is reset when the STR bit is set to 1.
*/
class EEDmacChannelRegister_CHCR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 DIR = 0;
		static constexpr u8 MOD = 1;
		static constexpr u8 ASP = 2;
		static constexpr u8 TTE = 3;
		static constexpr u8 TIE = 4;
		static constexpr u8 STR = 5;
		static constexpr u8 TAG = 6;
	};

	EEDmacChannelRegister_CHCR_t(u32 & sliceCountState);

	void writeWordU(u32 value) override;

private:
	/*
	A pointer to the DMAC channel slice count state, used to determine if a transfer should stop after 8 qwords (a "slice").
	*/
	u32 & mSliceCountState;
};

/*
The DMAC D_MADR register, aka transfer address register.
*/
class EEDmacChannelRegister_MADR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 ADDR = 0;
		static constexpr u8 SPR = 1;
	};

	EEDmacChannelRegister_MADR_t();

	/*
	Increments ADDR by 0x10, which is the size of 1 DMA transfer (used when one transfer has completed).
	*/
	void increment();
};

/*
The DMAC D_QWC register, aka quadword count register (holds remaining transfer qword count).
*/
class EEDmacChannelRegister_QWC_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 QWC = 0;
	};

	EEDmacChannelRegister_QWC_t();

	/*
	Decrements the QWC counter by 1. Should be called when a data unit has been transferred.
	*/
	void decrement();
};

/*
The DMAC D_TADR register, aka tag address register.
*/
class EEDmacChannelRegister_TADR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 ADDR = 0;
		static constexpr u8 SPR = 1;
	};

	EEDmacChannelRegister_TADR_t();
};

/*
The DMAC D_ASR0/1 register, aka tag address save register.
*/
class EEDmacChannelRegister_ASR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 ADDR = 0;
		static constexpr u8 SPR = 1;
	};

	EEDmacChannelRegister_ASR_t();
};

/*
The DMAC D_SADR register, aka SPR (scratchpad ram) transfer address register.
*/
class EEDmacChannelRegister_SADR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 ADDR = 0;
	};

	EEDmacChannelRegister_SADR_t();

	/*
	Increments ADDR by 0x10, which is the size of 1 DMA transfer (used when one transfer has completed).
	*/
	void increment();
};

