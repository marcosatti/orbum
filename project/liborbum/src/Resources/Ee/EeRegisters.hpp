#pragma once

#include "Common/Options.hpp"
#include "Common/Types/Memory/ArrayByteMemory.hpp"

/// EERegisters_t defines SPECIAL EE registers specified in the EE Users Manual from page 21 to 25.
/// Special registers here mean anything that does not act as an ordinary storage such as SizedWordRegister.
/// Some are implemented from the base Memory_t class, as they are not well documented.

/// The SIO (serial I/O), which is somewhat undocumented. Some information can be found in the Toshiba Tx79 architecture manual (similar to the EE), but even then information is lacking.
/// Some useful information can be found in the old PCSX2 under Hw.h (register names). It requires some special functionality (see below).
/// In a real PS2, you can communicate with the EE over this serial port.
/// Allocated at base PS2 physical memory address 0x1000F100.
/// This is different from the PSX / IOP SIO.
class EeRegister_Sio : public ArrayByteMemory
{
public:
	EeRegister_Sio();

	static constexpr uptr PADDRESS_EE_REGISTER_SIO = 0x1000F100;
	static constexpr size_t SIZE_EE_REGISTER_SIO = 0x00000100;
	static constexpr size_t OFFSET_SIO_ISR = 0x30; // Actual address 0x1000F130.
	static constexpr size_t OFFSET_SIO_TXFIFO = 0x80; // Actual address 0x1000F180.

	void write_ubyte(const size_t offset, const ubyte value) override;
	uword read_uword(const size_t offset) override;
	void write_uword(const size_t offset, const uword value) override;

private:
#if DEBUG_LOG_SIO_MESSAGES
	// Varibles below needed for SIO messages output through the SIO_TXFIFO register.
	static constexpr const char * SIO_BUFFER_PREFIX = "EE SIO Message";
	std::string sio_buffer;
#endif
};

/// The MCH register class. No information available except for old PCSX2's code.
/// Related to the RDRAM memory controller.
/// It requires some special functionality (see below).
/// Allocated at base PS2 physical memory address 0x1000F430 (from MCH_RICM).
class EeRegister_Mch : public ArrayByteMemory
{
public:
	EeRegister_Mch();

	static constexpr uptr PADDRESS_EE_REGISTER_MCH = 0x1000F430;
	static constexpr size_t SIZE_EE_REGISTER_MCH = 0x00000020;
	static constexpr size_t OFFSET_MCH_RICM = 0x00; // Actual address 0x1000F430.
	static constexpr size_t OFFSET_MCH_DRD = 0x10; // Actual address 0x1000F440.

	uword read_uword(const size_t offset) override;
	void write_uword(const size_t offset, const uword value) override;

private:
	// Variables below needed by logic. Used by the BIOS to initialise/test the RDRAM. See old PCSX2 code (Hw.h/HwRead.cpp/HwWrite.cpp).
	int rdram_sdevid = 0;
	static constexpr int rdram_devices = 2; // Put 8 for TOOL and 2 for PS2 and PSX.
};