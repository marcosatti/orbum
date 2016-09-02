#pragma once

#include "Common/Global/Globals.h"

#include "Common/PS2Constants/PS2Constants.h"
#include "Common/PS2Resources/Types/PS2StorageObject/PS2StorageObject_t.h"

/*
EERegisters_t defines SPECIAL EE registers specified in the EE Users Manual from page 21 to 25.
Special registers here mean anything that does not act as an ordinary storage such as PS2ObjectStorage_t (used for most register regions) 
 or PS2DeadStorage_t (used in most reserved register regions).

For example, additional processing may be needed on writes, or a read may return a bit shifted value from what was written.
*/

/*
The SIO (serial I/O), which is somewhat undocumented. Some information can be found in the Toshiba Tx79 architecture manual (similar to the EE), but even then information is lacking.
Some useful information can be found in the old PCSX2 under Hw.h (register names). It requires some special functionality (see below).
In a real PS2, you can communicate with the EE over this serial port.
Allocated at base PS2 physical memory address 0x1000F100.
*/
class EERegisterSIO_t : public PS2StorageObject_t
{
public:
	EERegisterSIO_t();

	static constexpr u32 OFFSET_SIO_ISR = 0x30; // Actual address 0x1000F130.
	static constexpr u32 OFFSET_SIO_TXFIFO = 0x80; // Actual address 0x1000F180.

	void writeByteU(u32 storageIndex, u8 value) override;
	void writeByteS(u32 storageIndex, s8 value) override;
	u32 readWordU(u32 storageIndex) override;
	void writeWordU(u32 storageIndex, u32 value) override;
	s32 readWordS(u32 storageIndex) override;
	void writeWordS(u32 storageIndex, s32 value) override;
};

/*
The MCH register class. No information available except for old PCSX2's code. Not sure what this does, but it is required by the bios from my own testing.
It requires some special functionality (see below).
Allocated at base PS2 physical memory address 0x1000F400.
*/
class EERegisterMCH_t : public PS2StorageObject_t
{
public:
	EERegisterMCH_t();

	static constexpr u32 OFFSET_MCH_RICM = 0x30;
	static constexpr u32 OFFSET_MCH_DRD = 0x40;

	u32 readWordU(u32 storageIndex) override;
	void writeWordU(u32 storageIndex, u32 value) override;
	s32 readWordS(u32 storageIndex) override;
	void writeWordS(u32 storageIndex, s32 value) override;

private:
	// Variables below needed by logic. Not sure what they are for. See old PCSX2 code (Hw.h/HwRead.cpp/HwWrite.cpp).
	int rdram_sdevid = 0;
	const int rdram_devices = 2; // Put 8 for TOOL and 2 for PS2 and PSX.
};