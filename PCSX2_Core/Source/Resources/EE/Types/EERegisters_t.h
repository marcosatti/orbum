#pragma once

#include "Common/Global/Globals.h"
#include "Common/Types/Memory/ByteMemory_t.h"
#include "Common/Types/Registers/Register32_t.h"

/*
EERegisters_t defines SPECIAL EE registers specified in the EE Users Manual from page 21 to 25.
Special registers here mean anything that does not act as an ordinary storage such as Register32_t.
Some are implemented from the base Memory_t class, as they are not well documented.
*/

/*
The SIO (serial I/O), which is somewhat undocumented. Some information can be found in the Toshiba Tx79 architecture manual (similar to the EE), but even then information is lacking.
Some useful information can be found in the old PCSX2 under Hw.h (register names). It requires some special functionality (see below).
In a real PS2, you can communicate with the EE over this serial port.
Allocated at base PS2 physical memory address 0x1000F100.
*/
class EERegister_SIO_t : public ByteMemory_t
{
public:
	EERegister_SIO_t();

	static constexpr u32 PADDRESS_EE_REGISTER_SIO = 0x1000F100;
	static constexpr size_t SIZE_EE_REGISTER_SIO = 0x00000100;
	static constexpr size_t OFFSET_SIO_ISR = 0x30; // Actual address 0x1000F130.
	static constexpr size_t OFFSET_SIO_TXFIFO = 0x80; // Actual address 0x1000F180.

	void writeByte(const System_t context, size_t storageIndex, u8 value) override;
	u32 readWord(const System_t context, size_t storageIndex) override;
	void writeWord(const System_t context, size_t storageIndex, u32 value) override;

private:
#if DEBUG_SIO_LOG_MESSAGES
	// Varibles below needed for SIO messages output through the SIO_TXFIFO register.
	static constexpr char * SIO_BUFFER_PREFIX = "EE SIO Message";
	std::string sioBuffer;
#endif
};

/*
The MCH register class. No information available except for old PCSX2's code. Not sure what this does, but it is required by the bios.
Seems to be related to the RDRAM memory controller.
It requires some special functionality (see below).
Allocated at base PS2 physical memory address 0x1000F430 (from MCH_RICM).
*/
class EERegister_MCH_t : public ByteMemory_t
{
public:
	EERegister_MCH_t();

	static constexpr u32 PADDRESS_EE_REGISTER_MCH = 0x1000F430;
	static constexpr size_t SIZE_EE_REGISTER_MCH = 0x00000020;
	static constexpr size_t OFFSET_MCH_RICM = 0x00; // Actual address 0x1000F430.
	static constexpr size_t OFFSET_MCH_DRD = 0x10; // Actual address 0x1000F440.

	u32 readWord(const System_t context, size_t storageIndex) override;
	void writeWord(const System_t context, size_t storageIndex, u32 value) override;

private:
	// Variables below needed by logic. Used by the BIOS to initalise/test the RDRAM. See old PCSX2 code (Hw.h/HwRead.cpp/HwWrite.cpp).
	s32 rdram_sdevid = 0;
	const s32 rdram_devices = 2; // Put 8 for TOOL and 2 for PS2 and PSX.
};