#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/EE/Types/EE_Registers_t.h"
#include "Common/PS2Resources/Types/MappedMemory/MappedMemory_t.h"
#include "Common/PS2Resources/Types/MappedMemory/BitfieldMMemory32_t.h"
#include "Common/PS2Resources/Types/MappedMemory/ClrBitfieldMMemory32_t.h"
#include "Common/PS2Resources/Types/MappedMemory/RevBitfieldMMemory32_t.h"
#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/EE/DMAC/DMAC_t.h"

EERegisterTimerMode_t::EERegisterTimerMode_t(const char *const mnemonic, const u32 & PS2PhysicalAddress, const PS2Resources_t *const PS2Resources, const u32 & timerID) :
	BitfieldMMemory32_t(mnemonic, PS2PhysicalAddress),
	PS2ResourcesSubobject(PS2Resources),
	mTimerID(timerID)
{
	registerField(Fields::CLKS, "CLKS", 0, 2, 0);
	registerField(Fields::GATE, "GATE", 2, 1, 0);
	registerField(Fields::GATS, "GATS", 3, 1, 0);
	registerField(Fields::GATM, "GATM", 4, 2, 0);
	registerField(Fields::ZRET, "ZRET", 6, 1, 0);
	registerField(Fields::CUE, "CUE", 7, 1, 0);
	registerField(Fields::CMPE, "CMPE", 8, 1, 0);
	registerField(Fields::OVFE, "OVFE", 9, 1, 0);
	registerField(Fields::EQUF, "EQUF", 10, 1, 0);
	registerField(Fields::OVFF, "OVFF", 11, 1, 0);
}

void EERegisterTimerMode_t::writeWordU(u32 storageIndex, u32 value)
{
	// Clear bits 10 and 11 (0xC00) when a 1 is written to them.
	u32 originalValue = MappedMemory32_t::readWordU(storageIndex);
	u32 newValue = ((value & 0xC00) ^ (originalValue & 0xC00)) | (value & ~0xC00);
	BitfieldMMemory32_t::writeWordU(storageIndex, newValue);

	// Test if the CUE flag is 1 - need to reset the associated Count register if set.
	if (value & 0x80)
		getRootResources()->EE->TimerRegisters[mTimerID].Count->reset();
}

EERegisterTimerCount_t::EERegisterTimerCount_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	MappedMemory32_t(mnemonic, PS2PhysicalAddress), 
	mIsOverflowed(false)
{
}

void EERegisterTimerCount_t::increment(u16 value)
{
	u32 temp = readWordU(0) + value;

	if (temp > Constants::VALUE_U16_MAX)
	{
		// Set overflow flag and wrap value around.
		mIsOverflowed = true;
		temp = temp % Constants::VALUE_U16_MAX;
	}

	writeWordU(0, temp);
}

bool EERegisterTimerCount_t::isOverflowed()
{
	bool temp = mIsOverflowed;
	mIsOverflowed = false;
	return temp;
}

void EERegisterTimerCount_t::reset()
{
	writeWordU(0, 0);
}

EERegisterIntcStat_t::EERegisterIntcStat_t(const char* const mnemonic, const u32& PS2PhysicalAddress) : 
	ClrBitfieldMMemory32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::GS, "GS", 0, 1, 0);
	registerField(Fields::SBUS, "SBUS", 1, 1, 0);
	registerField(Fields::VBON, "VBON", 2, 1, 0);
	registerField(Fields::VBOF, "VBOF", 3, 1, 0);
	registerField(Fields::VIF0, "VIF0", 4, 1, 0);
	registerField(Fields::VIF1, "VIF1", 5, 1, 0);
	registerField(Fields::VU0, "VU0", 6, 1, 0);
	registerField(Fields::VU1, "VU1", 7, 1, 0);
	registerField(Fields::IPU, "IPU", 8, 1, 0);
	registerField(Fields::TIM0, "TIM0", 9, 1, 0);
	registerField(Fields::TIM1, "TIM1", 10, 1, 0);
	registerField(Fields::TIM2, "TIM2", 11, 1, 0);
	registerField(Fields::TIM3, "TIM3", 12, 1, 0);
	registerField(Fields::SFIFO, "SFIFO", 13, 1, 0);
	registerField(Fields::VU0WD, "VU0WD", 14, 1, 0);
}

EERegisterIntcMask_t::EERegisterIntcMask_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	RevBitfieldMMemory32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::GS, "GS", 0, 1, 0);
	registerField(Fields::SBUS, "SBUS", 1, 1, 0);
	registerField(Fields::VBON, "VBON", 2, 1, 0);
	registerField(Fields::VBOF, "VBOF", 3, 1, 0);
	registerField(Fields::VIF0, "VIF0", 4, 1, 0);
	registerField(Fields::VIF1, "VIF1", 5, 1, 0);
	registerField(Fields::VU0, "VU0", 6, 1, 0);
	registerField(Fields::VU1, "VU1", 7, 1, 0);
	registerField(Fields::IPU, "IPU", 8, 1, 0);
	registerField(Fields::TIM0, "TIM0", 9, 1, 0);
	registerField(Fields::TIM1, "TIM1", 10, 1, 0);
	registerField(Fields::TIM2, "TIM2", 11, 1, 0);
	registerField(Fields::TIM3, "TIM3", 12, 1, 0);
	registerField(Fields::SFIFO, "SFIFO", 13, 1, 0);
	registerField(Fields::VU0WD, "VU0WD", 14, 1, 0);
}

EERegisterDmacChcr_t::EERegisterDmacChcr_t(const char* const mnemonic, const u32& PS2PhysicalAddress, const PS2Resources_t *const PS2Resources, const u32 & channelID) :
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

void EERegisterDmacChcr_t::writeWordU(u32 storageIndex, u32 value)
{
	// Check if the STR bit is 1. If so, reset the DMA channel state variables.
	if (value & 0x100)
	{
		getRootResources()->EE->DMAC->SliceCountState[mChannelID] = 0;
		getRootResources()->EE->DMAC->ChainExitState[mChannelID] = false;
	}

	BitfieldMMemory32_t::writeWordU(storageIndex, value);
}

EERegisterDmacMadr_t::EERegisterDmacMadr_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldMMemory32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::ADDR, "ADDR", 0, 31, 0);
	registerField(Fields::SPR, "SPR", 31, 1, 0);
}

void EERegisterDmacMadr_t::increment()
{
	BitfieldMap32_t::setFieldValue(Fields::ADDR, BitfieldMap32_t::getFieldValue(Fields::ADDR) + 0x10);
}

EERegisterDmacTadr_t::EERegisterDmacTadr_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldMMemory32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::ADDR, "ADDR", 0, 31, 0);
	registerField(Fields::SPR, "SPR", 31, 1, 0);
}

EERegisterDmacAsr_t::EERegisterDmacAsr_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldMMemory32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::ADDR, "ADDR", 0, 31, 0);
	registerField(Fields::SPR, "SPR", 31, 1, 0);
}

EERegisterDmacSadr_t::EERegisterDmacSadr_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldMMemory32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::ADDR, "ADDR", 0, 14, 0);
}

void EERegisterDmacSadr_t::increment()
{
	BitfieldMap32_t::setFieldValue(Fields::ADDR, BitfieldMap32_t::getFieldValue(Fields::ADDR) + 0x10);
}

EERegisterDmacQwc_t::EERegisterDmacQwc_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldMMemory32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::QWC, "QWC", 0, 16, 0);
}

void EERegisterDmacQwc_t::decrement()
{
	BitfieldMap32_t::setFieldValue(Fields::QWC, BitfieldMap32_t::getFieldValue(Fields::QWC) - 1);
}

EERegisterDmacCtrl_t::EERegisterDmacCtrl_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldMMemory32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::DMAE, "DMAE", 0, 1, 0);
	registerField(Fields::RELE, "RELE", 1, 1, 0);
	registerField(Fields::MFD, "MFD", 2, 2, 0);
	registerField(Fields::STS, "STS", 4, 2, 0);
	registerField(Fields::STD, "STD", 6, 2, 0);
	registerField(Fields::RCYC, "RCYC", 8, 3, 0);
}

EERegisterDmacStat_t::EERegisterDmacStat_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
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

void EERegisterDmacStat_t::writeWordU(u32 storageIndex, u32 value)
{
	// For bits 0-15, they are cleared when 1 is written. For bits 16-31, they are reversed when 1 is written.
	u32 clrBits = readWordU(storageIndex) & 0xFFFF;
	u32 clrBitsValue = value & 0xFFFF;
	u32 revBits = readWordU(storageIndex) & 0xFFFF0000;
	u32 revBitsValue = value & 0xFFFF0000;

	BitfieldMMemory32_t::writeWordU(storageIndex, clrBits & (~clrBitsValue));
	BitfieldMMemory32_t::writeWordU(storageIndex, revBits ^ revBitsValue);
}

EERegisterDmacPcr_t::EERegisterDmacPcr_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
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

EERegisterDmacSqwc_t::EERegisterDmacSqwc_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldMMemory32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::SQWC, "SQWC", 0, 8, 0);
	registerField(Fields::TQWC, "TQWC", 16, 8, 0);
}

EERegisterDmacRbor_t::EERegisterDmacRbor_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldMMemory32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::ADDR, "ADDR", 0, 31, 0);
}

EERegisterDmacRbsr_t::EERegisterDmacRbsr_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldMMemory32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::RMSK, "RMSK", 4, 27, 0);
}

EERegisterDmacStadr_t::EERegisterDmacStadr_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldMMemory32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::ADDR, "ADDR", 0, 31, 0);
}

EERegisterDmacEnablew_t::EERegisterDmacEnablew_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldMMemory32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::CPND, "CPND", 16, 1, 0);
}

EERegisterDmacEnabler_t::EERegisterDmacEnabler_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldMMemory32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::CPND, "CPND", 16, 1, 0);
}

EERegisterSIO_t::EERegisterSIO_t() :
	MappedMemory_t(SIZE_EE_REGISTER_SIO, "EE_REGISTER_SIO", PADDRESS_EE_REGISTER_SIO)
{
}

void EERegisterSIO_t::writeByteU(u32 storageIndex, u8 value)
{
	switch (storageIndex)
	{
	case OFFSET_SIO_TXFIFO: // "SIO_TXFIFO"
	{
#if DEBUG_LOG_SIO_MESSAGES
		// Below logic adapted from the old PCSX2 code (see HwWrite.cpp).
		if (value == '\r')
		{
			// '\r' and sometimes after, '\n', are the last characters before the message is ready to be output.
			// Do not bother outputting the '\r' or '\n' characters, as this is done by the logging functions of the emulator.

			// Output the message.
			logDebug("(%s, %d) %s: %s", __FILENAME__, __LINE__, SIO_BUFFER_PREFIX, sioBuffer.c_str());

			// Reset the buffer.
			sioBuffer.clear();
		}
		else if (value != '\n') // See above for why '\n' is not written to the buffer.
			sioBuffer.push_back(value);
#endif
		break;
	}
	default:
	{
		MappedMemory_t::writeByteU(storageIndex, value);
		break;
	}
	}
}

void EERegisterSIO_t::writeByteS(u32 storageIndex, s8 value)
{
	writeByteU(storageIndex, static_cast<u8>(value));
}

u32 EERegisterSIO_t::readWordU(u32 storageIndex)
{
	switch (storageIndex)
	{
	case OFFSET_SIO_ISR:
	{
		// From old PCSX2: 0x..F130 returns 0. Not sure why. From my own testing, BIOS requires this.
		return 0;
	}
	default:
	{
		return MappedMemory_t::readWordU(storageIndex);
	}
	}
}

void EERegisterSIO_t::writeWordU(u32 storageIndex, u32 value)
{
	switch (storageIndex)
	{
	case OFFSET_SIO_TXFIFO:
	{
		// Below logic is from the old PCSX2. I guess it writes a message transmitted through the SIO_TXFIFO register..
		for (auto i = 0; i < Constants::NUMBER_BYTES_IN_WORD; i++)
			writeByteU(storageIndex, reinterpret_cast<u8*>(&value)[i]);
		break;
	}
	default:
	{
		MappedMemory_t::writeWordU(storageIndex, value);
		break;
	}
	}
}

s32 EERegisterSIO_t::readWordS(u32 storageIndex)
{
	return static_cast<s32>(readWordU(storageIndex));
}

void EERegisterSIO_t::writeWordS(u32 storageIndex, s32 value)
{
	writeWordU(storageIndex, static_cast<u32>(value));
}

EERegisterMCH_t::EERegisterMCH_t() :
	MappedMemory_t(SIZE_EE_REGISTER_MCH, "EE_REGISTER_MCH", PADDRESS_EE_REGISTER_MCH)
{
}

u32 EERegisterMCH_t::readWordU(u32 storageIndex)
{
	switch (storageIndex)
	{
	case OFFSET_MCH_DRD:
	{
		// Below logic is from the old PCSX2.
		if (!((MappedMemory_t::readWordU(OFFSET_MCH_RICM) >> 6) & 0xF))
		{
			switch ((MappedMemory_t::readWordU(OFFSET_MCH_RICM) >> 16) & 0xFFF)
			{
				// MCH_RICM: x:4|SA:12|x:5|SDEV:1|SOP:4|SBC:1|SDEV:5
			case 0x21: //INIT
				if (rdram_sdevid < rdram_devices)
				{
					rdram_sdevid++;
					return 0x1F;
				}
				return 0;

			case 0x23: // CNFGA
				return 0x0D0D;	// PVER=3 | MVER=16 | DBL=1 | REFBIT=5

			case 0x24: // CNFGB
					   // 0x0110 for PSX  SVER=0 | CORG=8(5x9x7) | SPT=1 | DEVTYP=0 | BYTE=0
				return 0x0090;	// SVER=0 | CORG=4(5x9x6) | SPT=1 | DEVTYP=0 | BYTE=0

			case 0x40: // DEVID
				return MappedMemory_t::readWordU(OFFSET_MCH_RICM) & 0x1F;	// =SDEV
			}
		}
	}
	case OFFSET_MCH_RICM:
	{
		return 0;
	}
	default:
	{
		return MappedMemory_t::readWordU(storageIndex);
	}
	}
}

void EERegisterMCH_t::writeWordU(u32 storageIndex, u32 value)
{
	switch (storageIndex)
	{
	case OFFSET_MCH_RICM:
	{
		// Below logic is from the old PCSX2.
		// MCH_RICM: x:4|SA:12|x:5|SDEV:1|SOP:4|SBC:1|SDEV:5

		if ((((value >> 16) & 0xFFF) == 0x21) && (((value >> 6) & 0xF) == 1) && (((MappedMemory_t::readWordU(OFFSET_MCH_DRD) >> 7) & 1) == 0)) // INIT & SRP=0
			rdram_sdevid = 0;	// If SIO repeater is cleared, reset sdevid

		MappedMemory_t::writeWordU(OFFSET_MCH_RICM, value & ~0x80000000);	// Kill the busy bit

		break;
	}
	default:
	{
		MappedMemory_t::writeWordU(storageIndex, value);
		break;
	}
	}
}

s32 EERegisterMCH_t::readWordS(u32 storageIndex)
{
	return static_cast<s32>(readWordU(storageIndex));
}

void EERegisterMCH_t::writeWordS(u32 storageIndex, s32 value)
{
	writeWordU(storageIndex, static_cast<u32>(value));
}