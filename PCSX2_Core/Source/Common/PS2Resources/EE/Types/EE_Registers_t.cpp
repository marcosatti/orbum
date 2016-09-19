#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/EE/Types/EE_Registers_t.h"
#include "Common/PS2Resources/Types/StorageObject/StorageObject_t.h"
#include "Common/PS2Resources/Types/StorageObject/BitfieldStorageObject32_t.h"

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
	BitfieldStorageObject32_t(mnemonic, PS2PhysicalAddress)
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
