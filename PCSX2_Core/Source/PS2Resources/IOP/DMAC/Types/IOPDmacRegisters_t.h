#pragma once

#include "Common/Global/Globals.h"

#include "Common/Types/Registers/BitfieldRegister32_t.h"

/*
The IOP DMAC D_PCR register.
Based off the PSX docs.
Responsible for the master enable of the DMA channels and the priority.
*/
class IOPDmacRegister_PCR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 PRI0 = 0;
		static constexpr u8 ENA0 = 1;
		static constexpr u8 PRI1 = 2;
		static constexpr u8 ENA1 = 3;
		static constexpr u8 PRI2 = 4;
		static constexpr u8 ENA2 = 5;
		static constexpr u8 PRI3 = 6;
		static constexpr u8 ENA3 = 7;
		static constexpr u8 PRI4 = 8;
		static constexpr u8 ENA4 = 9;
		static constexpr u8 PRI5 = 10;
		static constexpr u8 ENA5 = 11;
		static constexpr u8 PRI6 = 12;
		static constexpr u8 ENA6 = 13;
	};

	IOPDmacRegister_PCR_t(const char * mnemonic);
};

/*
The IOP DMAC D_ICR register.
Based off the PSX docs.
Responsible for controlling the interrupts for the DMA channels.
Whenever IRQMASTER is set to 1 is when an interrupt should be sent to the IOP's INTC.
*/
class IOPDmacRegister_ICR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 IRQFORCE = 0;
		static constexpr u8 IRQ0_EN = 1;
		static constexpr u8 IRQ1_EN = 2;
		static constexpr u8 IRQ2_EN = 3;
		static constexpr u8 IRQ3_EN = 4;
		static constexpr u8 IRQ4_EN = 5;
		static constexpr u8 IRQ5_EN = 6;
		static constexpr u8 IRQ6_EN = 7;
		static constexpr u8 IRQENABLE = 8;
		static constexpr u8 IRQ0_FL = 9;
		static constexpr u8 IRQ1_FL = 10;
		static constexpr u8 IRQ2_FL = 11;
		static constexpr u8 IRQ3_FL = 12;
		static constexpr u8 IRQ4_FL = 13;
		static constexpr u8 IRQ5_FL = 14;
		static constexpr u8 IRQ6_FL = 15;
		static constexpr u8 IRQMASTER = 16;
	};

	IOPDmacRegister_ICR_t(const char * mnemonic);
};