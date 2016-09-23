#pragma once

#include <sstream>

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/Types/StorageObject/StorageObject_t.h"
#include "Common/PS2Resources/Types/StorageObject/StorageObject32_t.h"
#include "Common/PS2Resources/Types/StorageObject/BitfieldStorageObject32_t.h"
#include <memory>

class EERegisterTimerCount_t;

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

class EERegisterSIO_t : public StorageObject_t
{
public:
	EERegisterSIO_t();

	static constexpr u32 PADDRESS_EE_REGISTER_SIO = 0x1000F100;
	static constexpr u32 SIZE_EE_REGISTER_SIO = 0x00000100;
	static constexpr u32 OFFSET_SIO_ISR = 0x30; // Actual address 0x1000F130.
	static constexpr u32 OFFSET_SIO_TXFIFO = 0x80; // Actual address 0x1000F180.

	void writeByteU(u32 storageIndex, u8 value) override;
	void writeByteS(u32 storageIndex, s8 value) override;
	u32 readWordU(u32 storageIndex) override;
	void writeWordU(u32 storageIndex, u32 value) override;
	s32 readWordS(u32 storageIndex) override;
	void writeWordS(u32 storageIndex, s32 value) override;

private:
#if DEBUG_LOG_SIO_MESSAGES
	// Varibles below needed for SIO messages output through the SIO_TXFIFO register.
	static constexpr char * SIO_BUFFER_PREFIX = "SIO Message";
	std::string sioBuffer;
#endif
};

/*
The MCH register class. No information available except for old PCSX2's code. Not sure what this does, but it is required by the bios from my own testing.
It requires some special functionality (see below).
Allocated at base PS2 physical memory address 0x1000F430 (from MCH_RICM).
*/
class EERegisterMCH_t : public StorageObject_t
{
public:
	EERegisterMCH_t();

	static constexpr u32 PADDRESS_EE_REGISTER_MCH = 0x1000F430;
	static constexpr u32 SIZE_EE_REGISTER_MCH = 0x00000020;
	static constexpr u32 OFFSET_MCH_RICM = 0x00; // Actual address 0x1000F430.
	static constexpr u32 OFFSET_MCH_DRD = 0x10; // Actual address 0x1000F440.

	u32 readWordU(u32 storageIndex) override;
	void writeWordU(u32 storageIndex, u32 value) override;
	s32 readWordS(u32 storageIndex) override;
	void writeWordS(u32 storageIndex, s32 value) override;

private:
	// Variables below needed by logic. Used by the BIOS to initalise/test the RDRAM. See old PCSX2 code (Hw.h/HwRead.cpp/HwWrite.cpp).
	s32 rdram_sdevid = 0;
	const s32 rdram_devices = 2; // Put 8 for TOOL and 2 for PS2 and PSX.
};

/*
The Timer Mode register type. See EE Users Manual page 36.
TODO: Fill in bitfield information like COP0_BitfieldRegisters_t.
Writing 1 to the Equal flag or Overflow flag will clear it (bits 10 and 11, behaves like a XOR write).

Needs a reference to the associated Count register as it will reset the value when CUE is set to 1.
It is assumed that although it is implemented as a 32-bit register-type, the upper 16-bits are not used.
*/
class EERegisterTimerMode_t : public BitfieldStorageObject32_t
{
public:
	struct Fields
	{
		static constexpr char * CLKS = "CLKS";
		static constexpr char * GATE = "GATE";
		static constexpr char * GATS = "GATS";
		static constexpr char * GATM = "GATM";
		static constexpr char * ZRET = "ZRET";
		static constexpr char * CUE = "CUE";
		static constexpr char * CMPE = "CMPE";
		static constexpr char * OVFE = "OVFE";
		static constexpr char * EQUF = "EQUF";
		static constexpr char * OVFF = "OVFF";
	};

	EERegisterTimerMode_t(const char *const mnemonic, const u32 & PS2PhysicalAddress, const std::shared_ptr<EERegisterTimerCount_t> & count);

	void writeWordU(u32 storageIndex, u32 value) override;
	void writeWordS(u32 storageIndex, s32 value) override;

private:
	/*
	The associated Count register that belongs to this timer.
	*/
	std::shared_ptr<EERegisterTimerCount_t> mCount;
};

/*
The Timer Count register type. See EE Users Manual page 37.
Provides the increment function, which also wraps the u32 value around once overflow (> u16) happens.
Can also reset the counter.
It is assumed that although it is implemented as a 32-bit register-type, the upper 16-bits are not used.
*/
class EERegisterTimerCount_t : public StorageObject32_t
{
public:
	EERegisterTimerCount_t(const char * const mnemonic, const u32 & PS2PhysicalAddress);

	void increment(u16 value);
	void reset();
};

/*
The INTC I_STAT register, which holds a set of flags determining if a component caused an interrupt.
*/
class EERegisterINTCIStat_t : public BitfieldStorageObject32_t
{
public:
	struct Fields
	{
		static constexpr char * GS = "GS";
		static constexpr char * SBUS = "SBUS";
		static constexpr char * VBON = "VBON";
		static constexpr char * VBOF = "VBOF";
		static constexpr char * VIF0 = "VIF0";
		static constexpr char * VIF1 = "VIF1";
		static constexpr char * VU0 = "VU0";
		static constexpr char * VU1 = "VU1";
		static constexpr char * IPU = "IPU";
		static constexpr char * TIM0 = "TIM0";
		static constexpr char * TIM1 = "TIM1";
		static constexpr char * TIM2 = "TIM2";
		static constexpr char * TIM3 = "TIM3";
		static constexpr char * SFIFO = "SFIFO";
		static constexpr char * VU0WD = "VU0WD";
	};

	EERegisterINTCIStat_t(const char* const mnemonic, const u32& PS2PhysicalAddress);
};

/*
The DMAC D_CTRL register, which contains various settings needed for the DMAC.
TODO: Need to implement cycle stealing? Wouldnt think so as it doesnt make sense in an emulator...
*/
class EERegisterDMACDCtrl_t : public BitfieldStorageObject32_t
{
public:
	struct Fields
	{
		static constexpr char * DMAE = "DMAE";
		static constexpr char * RELE = "RELE";
		static constexpr char * MFD = "MFD";
		static constexpr char * STS = "STS";
		static constexpr char * STD = "STD";
		static constexpr char * RCYC = "RCYC";
	};

	EERegisterDMACDCtrl_t(const char* const mnemonic, const u32& PS2PhysicalAddress);
};