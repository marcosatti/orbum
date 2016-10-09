#include "stdafx.h"

#include "Common/PS2Resources/EE/DMAC/Types/DMAC_Registers_t.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/EE/DMAC/DMAC_t.h"

DmacRegisterChcr_t::DmacRegisterChcr_t(const char* const mnemonic, const u32& PS2PhysicalAddress, const PS2Resources_t *const PS2Resources, const u32 & channelID) :
	BitfieldMMemory32_t(mnemonic, PS2PhysicalAddress),
	PS2ResourcesSubobject(PS2Resources),
	mChannelID(channelID)
{
	registerField(Fields::DIR, "DIR", 0, 1, 0);
	registerField(Fields::MOD, "MOD", 2, 2, 0);
	registerField(Fields::ASP, "ASP", 4, 2, 0);
	registerField(Fields::TTE, "TTE", 6, 1, 0);
	registerField(Fields::TIE, "TIE", 7, 1, 0);
	registerField(Fields::STR, "STR", 8, 1, 0);
	registerField(Fields::TAG, "TAG", 16, 16, 0);
}

void DmacRegisterChcr_t::writeWordU(u32 storageIndex, u32 value)
{
	// Check if the STR bit is 1. If so, reset the DMA channel state variables.
	if (value & 0x100)
	{
		getRootResources()->EE->DMAC->SliceCountState[mChannelID] = 0;
	}

	BitfieldMMemory32_t::writeWordU(storageIndex, value);
}

DmacRegisterMadr_t::DmacRegisterMadr_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldMMemory32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::ADDR, "ADDR", 0, 31, 0);
	registerField(Fields::SPR, "SPR", 31, 1, 0);
}

void DmacRegisterMadr_t::increment()
{
	BitfieldMap32_t::setFieldValue(Fields::ADDR, BitfieldMap32_t::getFieldValue(Fields::ADDR) + 0x10);
}

DmacRegisterTadr_t::DmacRegisterTadr_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldMMemory32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::ADDR, "ADDR", 0, 31, 0);
	registerField(Fields::SPR, "SPR", 31, 1, 0);
}

DmacRegisterAsr_t::DmacRegisterAsr_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldMMemory32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::ADDR, "ADDR", 0, 31, 0);
	registerField(Fields::SPR, "SPR", 31, 1, 0);
}

DmacRegisterSadr_t::DmacRegisterSadr_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldMMemory32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::ADDR, "ADDR", 0, 14, 0);
}

void DmacRegisterSadr_t::increment()
{
	BitfieldMap32_t::setFieldValue(Fields::ADDR, BitfieldMap32_t::getFieldValue(Fields::ADDR) + 0x10);
}

DmacRegisterQwc_t::DmacRegisterQwc_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldMMemory32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::QWC, "QWC", 0, 16, 0);
}

void DmacRegisterQwc_t::decrement()
{
	BitfieldMap32_t::setFieldValue(Fields::QWC, BitfieldMap32_t::getFieldValue(Fields::QWC) - 1);
}

DmacRegisterCtrl_t::DmacRegisterCtrl_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldMMemory32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::DMAE, "DMAE", 0, 1, 0);
	registerField(Fields::RELE, "RELE", 1, 1, 0);
	registerField(Fields::MFD, "MFD", 2, 2, 0);
	registerField(Fields::STS, "STS", 4, 2, 0);
	registerField(Fields::STD, "STD", 6, 2, 0);
	registerField(Fields::RCYC, "RCYC", 8, 3, 0);
}

DmacRegisterStat_t::DmacRegisterStat_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldMMemory32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::CIS0, "CIS0""CIS0", 0, 1, 0);
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

void DmacRegisterStat_t::writeWordU(u32 storageIndex, u32 value)
{
	// For bits 0-15, they are cleared when 1 is written. For bits 16-31, they are reversed when 1 is written.
	u32 clrBits = readWordU(storageIndex) & 0xFFFF;
	u32 clrBitsValue = value & 0xFFFF;
	u32 revBits = readWordU(storageIndex) & 0xFFFF0000;
	u32 revBitsValue = value & 0xFFFF0000;

	BitfieldMMemory32_t::writeWordU(storageIndex, clrBits & (~clrBitsValue));
	BitfieldMMemory32_t::writeWordU(storageIndex, revBits ^ revBitsValue);
}

DmacRegisterPcr_t::DmacRegisterPcr_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldMMemory32_t(mnemonic, PS2PhysicalAddress)
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

DmacRegisterSqwc_t::DmacRegisterSqwc_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldMMemory32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::SQWC, "SQWC", 0, 8, 0);
	registerField(Fields::TQWC, "TQWC", 16, 8, 0);
}

DmacRegisterRbor_t::DmacRegisterRbor_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldMMemory32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::ADDR, "ADDR", 0, 31, 0);
}

DmacRegisterRbsr_t::DmacRegisterRbsr_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldMMemory32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::RMSK, "RMSK", 4, 27, 0);
}

DmacRegisterStadr_t::DmacRegisterStadr_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldMMemory32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::ADDR, "ADDR", 0, 31, 0);
}

DmacRegisterEnablew_t::DmacRegisterEnablew_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldMMemory32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::CPND, "CPND", 16, 1, 0);
}

DmacRegisterEnabler_t::DmacRegisterEnabler_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldMMemory32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::CPND, "CPND", 16, 1, 0);
}