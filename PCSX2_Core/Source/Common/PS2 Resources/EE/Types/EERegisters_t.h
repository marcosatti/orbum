#pragma once

#include "Common/Global/Globals.h"

#include "Common/PS2 Constants/PS2Constants.h"
#include "Common/PS2 Resources/Types/PS2StorageObject/PS2StorageObject_t.h"

/*
EERegisters_t defines SPECIAL EE registers specified in the EE Users Manual from page 21 to 25.
Special registers here mean anything that does not act as an ordinary storage such as PS2ObjectStorage_t (used for most register regions) 
 or PS2DeadStorage_t (used in most reserved register regions).

For example, additional processing may be needed on writes, or a read may return a bit shifted value from what was written.
*/

/*
The SIO (serial I/O), which is largely undocumented. Some information can be found in the Toshiba Tx79 architecture manual (similar to the EE), but even then information is lacking.
Some useful information can be found in the old PCSX2 under Hw.h (register names). It requires some special functionality (see below).
In a real PS2, you can communicate with the EE over this serial port.
*/
class EERegisterSIO_t : public PS2StorageObject_t
{
public:
	EERegisterSIO_t() : PS2StorageObject_t(PS2Constants::EE::EE_REGISTER_SIO::SIZE_EE_REGISTER_SIO, "EE_REGISTER_SIO", PS2Constants::EE::EE_REGISTER_SIO::PADDRESS_EE_REGISTER_SIO)
	{
	}

	void writeByteU(u32 storageIndex, u8 value) override 
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

	void writeByteS(u32 storageIndex, s8 value) override
	{
		PS2StorageObject_t::writeByteS(storageIndex, static_cast<u8>(value));
	}

	u32 readWordU(u32 storageIndex) const override
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

	void writeWordU(u32 storageIndex, u32 value) override
	{
		switch (storageIndex)
		{
		case 0x80: // "SIO_TXFIFO"
		{
			// Below logic is from the old PCSX2. I guess it writes a message transmitted through the SIO_TXFIFO register..
			u8 * byteArray = reinterpret_cast<u8*>(&value);
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

	s32 readWordS(u32 storageIndex) const override 
	{ 
		return static_cast<s32>(readWordU(storageIndex)); 
	}

	void writeWordS(u32 storageIndex, s32 value) override 
	{ 
		writeWordU(storageIndex, static_cast<u32>(value)); 
	}
};

class EERegisterMCH_t : public PS2StorageObject_t
{
public:
	EERegisterMCH_t() : PS2StorageObject_t(PS2Constants::EE::EE_REGISTER_MCH::SIZE_EE_REGISTER_MCH, "EE_REGISTER_MCH", PS2Constants::EE::EE_REGISTER_MCH::PADDRESS_EE_REGISTER_MCH)
	{
	}
};