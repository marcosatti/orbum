#pragma once

#include "Common/Global/Globals.h"

#include "Common/Types/Registers/BitfieldRegister32_t.h"
#include <PS2Constants/PS2Constants.h>

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

		static constexpr u8 PRI_KEYS[PS2Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2] = { PRI0, PRI1, PRI2, PRI3, PRI4, PRI5, PRI6 };
		static constexpr u8 ENA_KEYS[PS2Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2] = { ENA0, ENA1, ENA2, ENA3, ENA4, ENA5, ENA6 };
	};

	IOPDmacRegister_PCR_t(const char * mnemonic);
};

/*
The IOP DMAC D_ICR register.
Based off the PSX docs (http://problemkaputt.de/psx-spx.htm).
Responsible for controlling the interrupts for the DMA channels.
Whenever IRQMASTER is set to 1 is when an interrupt should be sent to the IOP's INTC.

The IRQx_FL bits are reset (acknowledged) when 1 is written to them.
On the condition that an DMA channel irq is enabled, the IRQENABLE bit is set, and the corresponding flag is set, the IRQMASTER bit is set.

Although the PSX docs mention that the IRQENABLE bit has to be set for an interrupt to occur, PCSX2 interrupts on only the EN and FL bit being set.
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

		static constexpr u8 FL_KEYS[PS2Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2] = { IRQ0_FL, IRQ1_FL, IRQ2_FL, IRQ3_FL, IRQ4_FL, IRQ5_FL, IRQ6_FL };
	};

	IOPDmacRegister_ICR_t(const char * mnemonic);

	/*
	Firstly, reset any FL bits written to.
	If (EN AND FL) is set and IRQENABLE is set, or IRQFORCE is set, then IRQMASTER is set.
	*/
	void setFieldValue(const u8& fieldIndex, const u32& value) override;
	void writeWord(const Context_t& context, u32 value) override;
};