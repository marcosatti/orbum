#include "stdafx.h"

#include "Resources/IOP/DMAC/Types/IOPDmacRegisters_t.h"

IOPDmacRegister_PCR_t::IOPDmacRegister_PCR_t(const char* mnemonic) :
	BitfieldRegister32_t(mnemonic, false, false)
{
	registerField(Fields::PRI0, "PRI0", 0, 3, 0);
	registerField(Fields::ENA0, "ENA0", 3, 1, 0);
	registerField(Fields::PRI1, "PRI1", 4, 3, 0);
	registerField(Fields::ENA1, "ENA1", 7, 1, 0);
	registerField(Fields::PRI2, "PRI2", 8, 3, 0);
	registerField(Fields::ENA2, "ENA2", 11, 1, 0);
	registerField(Fields::PRI3, "PRI3", 12, 3, 0);
	registerField(Fields::ENA3, "ENA3", 15, 1, 0);
	registerField(Fields::PRI4, "PRI4", 16, 3, 0);
	registerField(Fields::ENA4, "ENA4", 19, 1, 0);
	registerField(Fields::PRI5, "PRI5", 20, 3, 0);
	registerField(Fields::ENA5, "ENA5", 23, 1, 0);
	registerField(Fields::PRI6, "PRI6", 24, 3, 0);
	registerField(Fields::ENA6, "ENA6", 27, 1, 0);
}

IOPDmacRegister_ICR_t::IOPDmacRegister_ICR_t(const char* mnemonic) :
	BitfieldRegister32_t(mnemonic, false, true),
	mIsInterrupted(false)
{
	registerField(Fields::IRQFORCE, "IRQFORCE", 15, 1, 0);
	registerField(Fields::IRQ0_EN, "IRQ0_EN", 16, 1, 0);
	registerField(Fields::IRQ1_EN, "IRQ1_EN", 17, 1, 0);
	registerField(Fields::IRQ2_EN, "IRQ2_EN", 18, 1, 0);
	registerField(Fields::IRQ3_EN, "IRQ3_EN", 19, 1, 0);
	registerField(Fields::IRQ4_EN, "IRQ4_EN", 20, 1, 0);
	registerField(Fields::IRQ5_EN, "IRQ5_EN", 21, 1, 0);
	registerField(Fields::IRQ6_EN, "IRQ6_EN", 22, 1, 0);
	registerField(Fields::IRQENABLE, "IRQENABLE", 23, 1, 0);
	registerField(Fields::IRQ0_FL, "IRQ0_FL", 24, 1, 0);
	registerField(Fields::IRQ1_FL, "IRQ1_FL", 25, 1, 0);
	registerField(Fields::IRQ2_FL, "IRQ2_FL", 26, 1, 0);
	registerField(Fields::IRQ3_FL, "IRQ3_FL", 27, 1, 0);
	registerField(Fields::IRQ4_FL, "IRQ4_FL", 28, 1, 0);
	registerField(Fields::IRQ5_FL, "IRQ5_FL", 29, 1, 0);
	registerField(Fields::IRQ6_FL, "IRQ6_FL", 30, 1, 0);
	registerField(Fields::IRQMASTER, "IRQMASTER", 31, 1, 0);
}

void IOPDmacRegister_ICR_t::writeWord(const Context_t& context, u32 value)
{
	// Preprocessing for IOP: reset (clear) the FL bits if 1 is written to them (taken from PCSX2 "IopHwWrite.cpp").
	if (context == IOP)
		value = ((readWord(RAW) & 0xFF000000) | (value & 0xFFFFFF)) & ~(value & 0x7F000000);
		
	BitfieldRegister32_t::writeWord(context, value);
	handleInterruptCheck();
}

void IOPDmacRegister_ICR_t::raiseIRQLine(const u8& irqLine)
{
	setFieldValue(Fields::IRQ_KEYS[irqLine], 1);
	handleInterruptCheck();
}

bool IOPDmacRegister_ICR_t::isInterrupted() const
{
	return mIsInterrupted;
}

void IOPDmacRegister_ICR_t::handleInterruptCheck()
{
	mIsInterrupted = false;

	// If IRQFORCE is set, then IRQ master is set.
	if (getFieldValue(Fields::IRQFORCE))
		setFieldValue(Fields::IRQMASTER, 1);

	// Check master IRQ bit.
	// TODO: check this, PCSX2 does not handle this at all.
	if (getFieldValue(Fields::IRQMASTER))
		mIsInterrupted = true;

	// Check if any channel has emitted an interrupt.
	u32 regValue = readWord(RAW);
	u32 icrEN = (regValue & 0x7F0000) >> 16;
	u32 icrFL = (regValue & 0x7F000000) >> 24;
	if (icrEN & icrFL)
	{
		// Also set IRQ master if IRQENABLE is set.
		if (getFieldValue(Fields::IRQENABLE))
			setFieldValue(Fields::IRQMASTER, 1);

		mIsInterrupted = true;
	}
}
