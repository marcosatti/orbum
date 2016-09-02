#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/EE/Types/EERegisters_t.h"

EERegisterSIO_t::EERegisterSIO_t(): PS2StorageObject_t(PS2Constants::EE::EE_REGISTER_SIO::SIZE_EE_REGISTER_SIO, "EE_REGISTER_SIO", PS2Constants::EE::EE_REGISTER_SIO::PADDRESS_EE_REGISTER_SIO)
{
}

void EERegisterSIO_t::writeByteU(u32 storageIndex, u8 value)
{
	switch (storageIndex)
	{
	case 0x80: // "SIO_TXFIFO"
		{
			// Below logic is from the old PCSX2. I guess it writes a message transmitted through the SIO_TXFIFO register..
			static bool iggy_newline = false;
			static char sio_buffer[1024];
			static int sio_count;

			if (value == '\r')
			{
				iggy_newline = true;
				sio_buffer[sio_count++] = '\n';
			}
			else if (!iggy_newline || (value != '\n'))
			{
				iggy_newline = false;
				sio_buffer[sio_count++] = value;
			}

			if ((sio_count == sizeof(sio_buffer) / sizeof((sio_buffer)[0]) - 1) || (sio_count != 0 && sio_buffer[sio_count - 1] == '\n'))
			{
				sio_buffer[sio_count] = 0;
				logDebug(sio_buffer);
				sio_count = 0;
			}
			break;
		}
	default:
		{
			PS2StorageObject_t::writeByteU(storageIndex, value);
			break;
		}
	}
}

void EERegisterSIO_t::writeByteS(u32 storageIndex, s8 value)
{
	PS2StorageObject_t::writeByteS(storageIndex, static_cast<u8>(value));
}

u32 EERegisterSIO_t::readWordU(u32 storageIndex) const
{
	switch (storageIndex)
	{
	case 0x30: // "SIO_ISR"
		// From old PCSX2: 0x..F130 returns 0. Not sure why. From my own testing, BIOS requires this.
		return 0;
	default:
		return PS2StorageObject_t::readWordU(storageIndex);
	}
}

void EERegisterSIO_t::writeWordU(u32 storageIndex, u32 value)
{
	switch (storageIndex)
	{
	case 0x80: // "SIO_TXFIFO"
		{
			// Below logic is from the old PCSX2. I guess it writes a message transmitted through the SIO_TXFIFO register..
			u8* byteArray = reinterpret_cast<u8*>(&value);
			for (auto i = 0; i < Constants::NUMBER_BYTES_IN_WORD; i++)
			{
				PS2StorageObject_t::writeByteU(storageIndex, byteArray[i]);
			}
			break;
		}
	default:
		{
			PS2StorageObject_t::writeWordU(storageIndex, value);
			break;
		}
	}
}

s32 EERegisterSIO_t::readWordS(u32 storageIndex) const
{
	return static_cast<s32>(readWordU(storageIndex));
}

void EERegisterSIO_t::writeWordS(u32 storageIndex, s32 value)
{
	writeWordU(storageIndex, static_cast<u32>(value));
}

EERegisterMCH_t::EERegisterMCH_t(): PS2StorageObject_t(PS2Constants::EE::EE_REGISTER_MCH::SIZE_EE_REGISTER_MCH, "EE_REGISTER_MCH", PS2Constants::EE::EE_REGISTER_MCH::PADDRESS_EE_REGISTER_MCH)
{
}
