#include "stdafx.h"

#include "PS2Resources/EE/DMAC/Types/EEDmacRegisters_t.h"

EEDmacRegister_CTRL_t::EEDmacRegister_CTRL_t()
{
	registerField(Fields::DMAE, "DMAE", 0, 1, 0);
	registerField(Fields::RELE, "RELE", 1, 1, 0);
	registerField(Fields::MFD, "MFD", 2, 2, 0);
	registerField(Fields::STS, "STS", 4, 2, 0);
	registerField(Fields::STD, "STD", 6, 2, 0);
	registerField(Fields::RCYC, "RCYC", 8, 3, 0);
}

EEDmacRegister_STAT_t::EEDmacRegister_STAT_t() :
	BitfieldRegister32_t("EE DMAC STAT", false, true),
	mIsInterrupted(false)
{
	registerField(Fields::CIS0, "CIS0", 0, 1, 0);
	registerField(Fields::CIS1, "CIS1", 1, 1, 0);
	registerField(Fields::CIS2, "CIS2", 2, 1, 0);
	registerField(Fields::CIS3, "CIS3", 3, 1, 0);
	registerField(Fields::CIS4, "CIS4", 4, 1, 0);
	registerField(Fields::CIS5, "CIS5", 5, 1, 0);
	registerField(Fields::CIS6, "CIS6", 6, 1, 0);
	registerField(Fields::CIS7, "CIS7", 7, 1, 0);
	registerField(Fields::CIS8, "CIS8", 8, 1, 0);
	registerField(Fields::CIS9, "CIS9", 9, 1, 0);
	registerField(Fields::SIS, "SIS", 13, 1, 0);
	registerField(Fields::MEIS, "MEIS", 14, 1, 0);
	registerField(Fields::BEIS, "BEIS", 15, 1, 0);
	registerField(Fields::CIM0, "CIM0", 16, 1, 0);
	registerField(Fields::CIM1, "CIM1", 17, 1, 0);
	registerField(Fields::CIM2, "CIM2", 18, 1, 0);
	registerField(Fields::CIM3, "CIM3", 19, 1, 0);
	registerField(Fields::CIM4, "CIM4", 20, 1, 0);
	registerField(Fields::CIM5, "CIM5", 21, 1, 0);
	registerField(Fields::CIM6, "CIM6", 22, 1, 0);
	registerField(Fields::CIM7, "CIM7", 23, 1, 0);
	registerField(Fields::CIM8, "CIM8", 24, 1, 0);
	registerField(Fields::CIM9, "CIM9", 25, 1, 0);
	registerField(Fields::SIM, "SIM", 29, 1, 0);
	registerField(Fields::MEIM, "MEIM", 30, 1, 0);
}

void EEDmacRegister_STAT_t::writeWord(const Context_t & context, u32 value)
{
	if (context == Context_t::EE)
	{
		// For bits 0-15 (stat bits), they are cleared when 1 is written. For bits 16-31 (mask bits), they are reversed when 1 is written.
		u32 regValue = readWord(context);

		u32 clrBits = (regValue & 0xFFFF) & (~(value & 0xFFFF));
		u32 revBits = (regValue & 0xFFFF0000) ^ (value & 0xFFFF0000);
		value = revBits | clrBits;
	}

	BitfieldRegister32_t::writeWord(context, value);
	handleInterruptCheck();
}

void EEDmacRegister_STAT_t::raiseIRQLine(const u8& irqLine)
{
	setFieldValue(Fields::IRQ_KEYS[irqLine], 1);
	handleInterruptCheck();
}

bool EEDmacRegister_STAT_t::isInterrupted() const
{
	return mIsInterrupted;
}

void EEDmacRegister_STAT_t::handleInterruptCheck()
{
	// Check for interrupt conditions.
	// See the formula listed at the end of page 65 of the EE Users Manual.
	bool interrupt = false;
	u32 regValue = readWord(Context_t::RAW);

	// Check for STAT & MASK > 0.
	u32 statValue = regValue & 0xFFFF;
	u32 maskValue = (regValue & 0xFFFF0000) >> 16;
	if (statValue & maskValue)
		interrupt = true;

	// Check for BUSERR interrupt status.
	if (getFieldValue(Fields::BEIS))
		interrupt = true;

	// Set the internal flag.
	mIsInterrupted = interrupt;
}

EEDmacRegister_PCR_t::EEDmacRegister_PCR_t()
{
	registerField(Fields::CPC0, "CPC0", 0, 1, 0);
	registerField(Fields::CPC1, "CPC1", 1, 1, 0);
	registerField(Fields::CPC2, "CPC2", 2, 1, 0);
	registerField(Fields::CPC3, "CPC3", 3, 1, 0);
	registerField(Fields::CPC4, "CPC4", 4, 1, 0);
	registerField(Fields::CPC5, "CPC5", 5, 1, 0);
	registerField(Fields::CPC6, "CPC6", 6, 1, 0);
	registerField(Fields::CPC7, "CPC7", 7, 1, 0);
	registerField(Fields::CPC8, "CPC8", 8, 1, 0);
	registerField(Fields::CPC9, "CPC9", 9, 1, 0);
	registerField(Fields::CDE0, "CDE0", 16, 1, 0);
	registerField(Fields::CDE1, "CDE1", 17, 1, 0);
	registerField(Fields::CDE2, "CDE2", 18, 1, 0);
	registerField(Fields::CDE3, "CDE3", 19, 1, 0);
	registerField(Fields::CDE4, "CDE4", 20, 1, 0);
	registerField(Fields::CDE5, "CDE5", 21, 1, 0);
	registerField(Fields::CDE6, "CDE6", 22, 1, 0);
	registerField(Fields::CDE7, "CDE7", 23, 1, 0);
	registerField(Fields::CDE8, "CDE8", 24, 1, 0);
	registerField(Fields::CDE9, "CDE9", 25, 1, 0);
	registerField(Fields::PCE, "PCE", 31, 1, 0);
}

EEDmacRegister_SWQC_t::EEDmacRegister_SWQC_t() 
{
	registerField(Fields::SQWC, "SQWC", 0, 8, 0);
	registerField(Fields::TQWC, "TQWC", 16, 8, 0);
}

EEDmacRegister_RBOR_t::EEDmacRegister_RBOR_t() 
{
	registerField(Fields::ADDR, "ADDR", 0, 31, 0);
}

EEDmacRegister_RBSR_t::EEDmacRegister_RBSR_t() 
{
	registerField(Fields::RMSK, "RMSK", 4, 27, 0);
}

EEDmacRegister_STADR_t::EEDmacRegister_STADR_t() 
{
	registerField(Fields::ADDR, "ADDR", 0, 31, 0);
}

EEDmacRegister_ENABLEW_t::EEDmacRegister_ENABLEW_t() 
{
	registerField(Fields::CPND, "CPND", 16, 1, 0);
}

EEDmacRegister_ENABLER_t::EEDmacRegister_ENABLER_t() 
{
	registerField(Fields::CPND, "CPND", 16, 1, 0);
}