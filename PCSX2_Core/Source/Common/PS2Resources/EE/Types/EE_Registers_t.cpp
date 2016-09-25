#include "stdafx.h"

#include <ctime>

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/EE/Types/EE_Registers_t.h"
#include "Common/PS2Resources/Types/StorageObject/StorageObject_t.h"
#include "Common/PS2Resources/Types/StorageObject/BitfieldStorageObject32_t.h"
#include "Common/PS2Resources/Types/StorageObject/ClrBitfieldStorageObject32_t.h"
#include "Common/PS2Resources/Types/StorageObject/RevBitfieldStorageObject32_t.h"

EERegisterTimerMode_t::EERegisterTimerMode_t(const char *const mnemonic, const u32 & PS2PhysicalAddress, const std::shared_ptr<EERegisterTimerCount_t> & count) :
	BitfieldStorageObject32_t(mnemonic, PS2PhysicalAddress),
	mCount(count)
{
	registerField(Fields::CLKS, 0, 2, 0);
	registerField(Fields::GATE, 2, 1, 0);
	registerField(Fields::GATS, 3, 1, 0);
	registerField(Fields::GATM, 4, 2, 0);
	registerField(Fields::ZRET, 6, 1, 0);
	registerField(Fields::CUE, 7, 1, 0);
	registerField(Fields::CMPE, 8, 1, 0);
	registerField(Fields::OVFE, 9, 1, 0);
	registerField(Fields::EQUF, 10, 1, 0);
	registerField(Fields::OVFF, 11, 1, 0);
}

void EERegisterTimerMode_t::writeWordU(u32 storageIndex, u32 value)
{
	// XOR bits 10 and 11 (0xC00) with the original value, remaining bits OR'd with the new value.
	u32 originalValue = StorageObject32_t::readWordU(storageIndex);
	u32 newValue = (value & 0xC00) ^ (originalValue & 0xC00) | (value & ~0xC00);
	BitfieldStorageObject32_t::writeWordU(storageIndex, newValue);

	// Test if the CUE flag is 1 - need to reset the associated Count register if set.
	if (getFieldValue(Fields::CUE))
		mCount->reset();
}

void EERegisterTimerMode_t::writeWordS(u32 storageIndex, s32 value)
{
	writeWordU(storageIndex, static_cast<u32>(value));
}

EERegisterTimerCount_t::EERegisterTimerCount_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	StorageObject32_t(mnemonic, PS2PhysicalAddress)
{
}

void EERegisterTimerCount_t::increment(u16 value)
{
	writeWordU(0, readWordU(0) + value);
}

void EERegisterTimerCount_t::reset()
{
	writeWordU(0, 0);
}

EERegisterINTCIStat_t::EERegisterINTCIStat_t(const char* const mnemonic, const u32& PS2PhysicalAddress) : 
	ClrBitfieldStorageObject32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::GS, 0, 1, 0);
	registerField(Fields::SBUS, 1, 1, 0);
	registerField(Fields::VBON, 2, 1, 0);
	registerField(Fields::VBOF, 3, 1, 0);
	registerField(Fields::VIF0, 4, 1, 0);
	registerField(Fields::VIF1, 5, 1, 0);
	registerField(Fields::VU0, 6, 1, 0);
	registerField(Fields::VU1, 7, 1, 0);
	registerField(Fields::IPU, 8, 1, 0);
	registerField(Fields::TIM0, 9, 1, 0);
	registerField(Fields::TIM1, 10, 1, 0);
	registerField(Fields::TIM2, 11, 1, 0);
	registerField(Fields::TIM3, 12, 1, 0);
	registerField(Fields::SFIFO, 13, 1, 0);
	registerField(Fields::VU0WD, 14, 1, 0);
}

EERegisterINTCIMask_t::EERegisterINTCIMask_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	RevBitfieldStorageObject32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::GS, 0, 1, 0);
	registerField(Fields::SBUS, 1, 1, 0);
	registerField(Fields::VBON, 2, 1, 0);
	registerField(Fields::VBOF, 3, 1, 0);
	registerField(Fields::VIF0, 4, 1, 0);
	registerField(Fields::VIF1, 5, 1, 0);
	registerField(Fields::VU0, 6, 1, 0);
	registerField(Fields::VU1, 7, 1, 0);
	registerField(Fields::IPU, 8, 1, 0);
	registerField(Fields::TIM0, 9, 1, 0);
	registerField(Fields::TIM1, 10, 1, 0);
	registerField(Fields::TIM2, 11, 1, 0);
	registerField(Fields::TIM3, 12, 1, 0);
	registerField(Fields::SFIFO, 13, 1, 0);
	registerField(Fields::VU0WD, 14, 1, 0);
}

EERegisterDMACDChcr_t::EERegisterDMACDChcr_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldStorageObject32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::DIR, 0, 1, 0);
	registerField(Fields::MOD, 2, 2, 0);
	registerField(Fields::ASP, 4, 2, 0);
	registerField(Fields::TTE, 6, 1, 0);
	registerField(Fields::TIE, 7, 1, 0);
	registerField(Fields::STR, 8, 1, 0);
	registerField(Fields::TAG, 16, 16, 0);
}

EERegisterDMACDMadr_t::EERegisterDMACDMadr_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldStorageObject32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::ADDR, 0, 31, 0);
	registerField(Fields::SPR, 31, 1, 0);
}

EERegisterDMACDTadr_t::EERegisterDMACDTadr_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldStorageObject32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::ADDR, 0, 31, 0);
	registerField(Fields::SPR, 31, 1, 0);
}

EERegisterDMACDAsr_t::EERegisterDMACDAsr_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldStorageObject32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::ADDR, 0, 31, 0);
	registerField(Fields::SPR, 31, 1, 0);
}

EERegisterDMACDSadr_t::EERegisterDMACDSadr_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldStorageObject32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::ADDR, 0, 14, 0);
}

EERegisterDMACDQwc_t::EERegisterDMACDQwc_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldStorageObject32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::QWC, 0, 16, 0);
}

EERegisterDMACDCtrl_t::EERegisterDMACDCtrl_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldStorageObject32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::DMAE, 0, 1, 0);
	registerField(Fields::RELE, 1, 1, 0);
	registerField(Fields::MFD, 2, 2, 0);
	registerField(Fields::STS, 4, 2, 0);
	registerField(Fields::STD, 6, 2, 0);
	registerField(Fields::RCYC, 8, 3, 0);
}

EERegisterDMACDStat_t::EERegisterDMACDStat_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldStorageObject32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::CIS0, 0, 1, 0);
	registerField(Fields::CIS1, 1, 1, 0);
	registerField(Fields::CIS2, 2, 1, 0);
	registerField(Fields::CIS3, 3, 1, 0);
	registerField(Fields::CIS4, 4, 1, 0);
	registerField(Fields::CIS5, 5, 1, 0);
	registerField(Fields::CIS6, 6, 1, 0);
	registerField(Fields::CIS7, 7, 1, 0);
	registerField(Fields::CIS8, 8, 1, 0);
	registerField(Fields::CIS9, 9, 1, 0);
	registerField(Fields::SIS, 13, 1, 0);
	registerField(Fields::MEIS, 14, 1, 0);
	registerField(Fields::BEIS, 15, 1, 0);
	registerField(Fields::CIM0, 16, 1, 0);
	registerField(Fields::CIM1, 17, 1, 0);
	registerField(Fields::CIM2, 18, 1, 0);
	registerField(Fields::CIM3, 19, 1, 0);
	registerField(Fields::CIM4, 20, 1, 0);
	registerField(Fields::CIM5, 21, 1, 0);
	registerField(Fields::CIM6, 22, 1, 0);
	registerField(Fields::CIM7, 23, 1, 0);
	registerField(Fields::CIM8, 24, 1, 0);
	registerField(Fields::CIM9, 25, 1, 0);
	registerField(Fields::SIM, 29, 1, 0);
	registerField(Fields::MEIM, 30, 1, 0);
}

void EERegisterDMACDStat_t::writeWordU(u32 storageIndex, u32 value)
{
	// For bits 0-15, they are cleared when 1 is written. For bits 16-31, they are reversed when 1 is written.
	u32 clrBits = readWordU(storageIndex) & 0xFFFF;
	u32 clrBitsValue = value & 0xFFFF;
	u32 revBits = readWordU(storageIndex) & 0xFFFF0000;
	u32 revBitsValue = value & 0xFFFF0000;

	BitfieldStorageObject32_t::writeWordU(storageIndex, clrBits & (~clrBitsValue));
	BitfieldStorageObject32_t::writeWordU(storageIndex, revBits ^ revBitsValue);
}

EERegisterDMACDPcr_t::EERegisterDMACDPcr_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldStorageObject32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::CPC0, 0, 1, 0);
	registerField(Fields::CPC1, 1, 1, 0);
	registerField(Fields::CPC2, 2, 1, 0);
	registerField(Fields::CPC3, 3, 1, 0);
	registerField(Fields::CPC4, 4, 1, 0);
	registerField(Fields::CPC5, 5, 1, 0);
	registerField(Fields::CPC6, 6, 1, 0);
	registerField(Fields::CPC7, 7, 1, 0);
	registerField(Fields::CPC8, 8, 1, 0);
	registerField(Fields::CPC9, 9, 1, 0);
	registerField(Fields::CDE0, 16, 1, 0);
	registerField(Fields::CDE1, 17, 1, 0);
	registerField(Fields::CDE2, 18, 1, 0);
	registerField(Fields::CDE3, 19, 1, 0);
	registerField(Fields::CDE4, 20, 1, 0);
	registerField(Fields::CDE5, 21, 1, 0);
	registerField(Fields::CDE6, 22, 1, 0);
	registerField(Fields::CDE7, 23, 1, 0);
	registerField(Fields::CDE8, 24, 1, 0);
	registerField(Fields::CDE9, 25, 1, 0);
	registerField(Fields::PCE, 31, 1, 0);
}

EERegisterDMACDSqwc_t::EERegisterDMACDSqwc_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldStorageObject32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::SQWC, 0, 8, 0);
	registerField(Fields::TQWC, 16, 8, 0);
}

EERegisterDMACDRbor_t::EERegisterDMACDRbor_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldStorageObject32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::ADDR, 0, 31, 0);
}

EERegisterDMACDRbsr_t::EERegisterDMACDRbsr_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldStorageObject32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::RMSK, 4, 27, 0);
}

EERegisterDMACDStadr_t::EERegisterDMACDStadr_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldStorageObject32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::ADDR, 0, 31, 0);
}

EERegisterDMACDEnablew_t::EERegisterDMACDEnablew_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldStorageObject32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::CPND, 16, 1, 0);
}

EERegisterDMACDEnabler_t::EERegisterDMACDEnabler_t(const char* const mnemonic, const u32& PS2PhysicalAddress) :
	BitfieldStorageObject32_t(mnemonic, PS2PhysicalAddress)
{
	registerField(Fields::CPND, 16, 1, 0);
}

EERegisterSIO_t::EERegisterSIO_t() :
	StorageObject_t(SIZE_EE_REGISTER_SIO, "EE_REGISTER_SIO", PADDRESS_EE_REGISTER_SIO)
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
		StorageObject_t::writeByteU(storageIndex, value);
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
		return StorageObject_t::readWordU(storageIndex);
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
		StorageObject_t::writeWordU(storageIndex, value);
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
	StorageObject_t(SIZE_EE_REGISTER_MCH, "EE_REGISTER_MCH", PADDRESS_EE_REGISTER_MCH)
{
}

u32 EERegisterMCH_t::readWordU(u32 storageIndex)
{
	switch (storageIndex)
	{
	case OFFSET_MCH_DRD:
	{
		// Below logic is from the old PCSX2.
		if (!((StorageObject_t::readWordU(OFFSET_MCH_RICM) >> 6) & 0xF))
		{
			switch ((StorageObject_t::readWordU(OFFSET_MCH_RICM) >> 16) & 0xFFF)
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
				return StorageObject_t::readWordU(OFFSET_MCH_RICM) & 0x1F;	// =SDEV
			}
		}
	}
	case OFFSET_MCH_RICM:
	{
		return 0;
	}
	default:
	{
		return StorageObject_t::readWordU(storageIndex);
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

		if ((((value >> 16) & 0xFFF) == 0x21) && (((value >> 6) & 0xF) == 1) && (((StorageObject_t::readWordU(OFFSET_MCH_DRD) >> 7) & 1) == 0)) // INIT & SRP=0
			rdram_sdevid = 0;	// If SIO repeater is cleared, reset sdevid

		StorageObject_t::writeWordU(OFFSET_MCH_RICM, value & ~0x80000000);	// Kill the busy bit

		break;
	}
	default:
	{
		StorageObject_t::writeWordU(storageIndex, value);
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