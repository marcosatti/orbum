#pragma once

#include <memory>

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/Types/MappedMemory/MappedMemory_t.h"
#include "Common/PS2Resources/Types/MappedMemory/MappedMemory32_t.h"
#include "Common/PS2Resources/Types/MappedMemory/BitfieldMMemory32_t.h"
#include "Common/PS2Resources/Types/MappedMemory/ClrBitfieldMMemory32_t.h"
#include "Common/PS2Resources/Types/MappedMemory/RevBitfieldMMemory32_t.h"
#include "Common/Interfaces/PS2ResourcesSubobject.h"

class EERegisterTimerCount_t;

/*
EERegisters_t defines SPECIAL EE registers specified in the EE Users Manual from page 21 to 25.
Special registers here mean anything that does not act as an ordinary storage such as PS2ObjectStorage_t (used for most register regions) 
 or PS2DeadStorage_t (used in most reserved register regions).

For example, additional processing may be needed on writes, or a read may return a bit shifted value from what was written.
TODO: Fill in bitfield information like COP0_BitfieldRegisters_t.
*/

/*
The Timer Mode register type. See EE Users Manual page 36.
Writing 1 to the Equal flag or Overflow flag will clear it (bits 10 and 11, behaves like a XOR write).

Needs a reference to the associated Count register as it will reset the value when CUE is set to 1.
It is assumed that although it is implemented as a 32-bit register-type, the upper 16-bits are not used.
*/
class EERegisterTimerMode_t : public BitfieldMMemory32_t, public PS2ResourcesSubobject
{
public:
	struct Fields
	{
		static constexpr u8 CLKS = 0;
		static constexpr u8 GATE = 1;
		static constexpr u8 GATS = 2;
		static constexpr u8 GATM = 3;
		static constexpr u8 ZRET = 4;
		static constexpr u8 CUE = 5;
		static constexpr u8 CMPE = 6;
		static constexpr u8 OVFE = 7;
		static constexpr u8 EQUF = 8;
		static constexpr u8 OVFF = 9;
	};

	EERegisterTimerMode_t(const char *const mnemonic, const u32 & PS2PhysicalAddress, const PS2Resources_t *const PS2Resources, const u32 & timerID);

	void writeWordU(u32 storageIndex, u32 value) override;

private:
	/*
	The timer ID that this object belongs to.
	*/
	const u32 mTimerID;
};

/*
The Timer Count register type. See EE Users Manual page 37.
Provides the increment function, which also wraps the u32 value around once overflow (> u16) happens (an internal flag is set).
Can also reset the counter.
It is assumed that although it is implemented as a 32-bit register-type, the upper 16-bits are not used (but are used to check for overflow).
*/
class EERegisterTimerCount_t : public MappedMemory32_t
{
public:
	EERegisterTimerCount_t(const char * const mnemonic, const u32 & PS2PhysicalAddress);

	void increment(u16 value);
	bool isOverflowed();
	void reset();
	
private:
	/*
	Internal overflow flag. Use isOverflowed() to get the status and to reset the flag.
	*/
	bool mIsOverflowed;
};

/*
The INTC I_STAT register, which holds a set of flags determining if a component caused an interrupt.
Bits are cleared by writing 1.
*/
class EERegisterIntcStat_t : public ClrBitfieldMMemory32_t
{
public:
	struct Fields
	{
		static constexpr u8 GS = 0;
		static constexpr u8 SBUS = 1;
		static constexpr u8 VBON = 2;
		static constexpr u8 VBOF = 3;
		static constexpr u8 VIF0 = 4;
		static constexpr u8 VIF1 = 5;
		static constexpr u8 VU0 = 6;
		static constexpr u8 VU1 = 7;
		static constexpr u8 IPU = 8;
		static constexpr u8 TIM0 = 9;
		static constexpr u8 TIM1 = 10;
		static constexpr u8 TIM2 = 11;
		static constexpr u8 TIM3 = 12;
		static constexpr u8 SFIFO = 13;
		static constexpr u8 VU0WD = 14;
	};

	EERegisterIntcStat_t(const char* const mnemonic, const u32& PS2PhysicalAddress);
};

/*
The INTC I_MASK register, which holds a set of flags determining if the interrupt source is masked.
Bits are reversed by writing 1.
*/
class EERegisterIntcMask_t : public RevBitfieldMMemory32_t
{
public:
	struct Fields
	{
		static constexpr u8 GS = 0;
		static constexpr u8 SBUS = 1;
		static constexpr u8 VBON = 2;
		static constexpr u8 VBOF = 3;
		static constexpr u8 VIF0 = 4;
		static constexpr u8 VIF1 = 5;
		static constexpr u8 VU0 = 6;
		static constexpr u8 VU1 = 7;
		static constexpr u8 IPU = 8;
		static constexpr u8 TIM0 = 9;
		static constexpr u8 TIM1 = 10;
		static constexpr u8 TIM2 = 11;
		static constexpr u8 TIM3 = 12;
		static constexpr u8 SFIFO = 13;
		static constexpr u8 VU0WD = 14;
	};

	EERegisterIntcMask_t(const char* const mnemonic, const u32& PS2PhysicalAddress);
};

/*
The DMAC D_CHCR register, aka channel control register.
Needs an channel index, which is used to reset the packed transferred count state when a 1 is written to the STR bit.
*/
class EERegisterDmacChcr_t : public BitfieldMMemory32_t, public PS2ResourcesSubobject
{
public:
	struct Fields
	{
		static constexpr u8 DIR = 0;
		static constexpr u8 MOD = 1;
		static constexpr u8 ASP = 2;
		static constexpr u8 TTE = 3;
		static constexpr u8 TIE = 4;
		static constexpr u8 STR = 5;
		static constexpr u8 TAG = 6;
	};

	EERegisterDmacChcr_t(const char* const mnemonic, const u32& PS2PhysicalAddress, const PS2Resources_t *const PS2Resources, const u32 & channelID);

	void writeWordU(u32 storageIndex, u32 value) override;

private:
	/*
	The DMAC channel ID this object belongs to.
	*/
	const u32 mChannelID;
};

/*
The DMAC D_MADR register, aka transfer address register.
*/
class EERegisterDmacMadr_t : public BitfieldMMemory32_t
{
public:
	struct Fields
	{
		static constexpr u8 ADDR = 0;
		static constexpr u8 SPR = 1;
	};

	EERegisterDmacMadr_t(const char* const mnemonic, const u32& PS2PhysicalAddress);
};

/*
The DMAC D_TADR register, aka tag address register.
*/
class EERegisterDmacTadr_t : public BitfieldMMemory32_t
{
public:
	struct Fields
	{
		static constexpr u8 ADDR = 0;
		static constexpr u8 SPR = 1;
	};

	EERegisterDmacTadr_t(const char* const mnemonic, const u32& PS2PhysicalAddress);
};

/*
The DMAC D_ASR0/1 register, aka tag address save register.
*/
class EERegisterDmacAsr_t : public BitfieldMMemory32_t
{
public:
	struct Fields
	{
		static constexpr u8 ADDR = 0;
		static constexpr u8 SPR = 1;
	};

	EERegisterDmacAsr_t(const char* const mnemonic, const u32& PS2PhysicalAddress);
};

/*
The DMAC D_SADR register, aka SPR (scratchpad ram) transfer address register.
*/
class EERegisterDmacSadr_t : public BitfieldMMemory32_t
{
public:
	struct Fields
	{
		static constexpr u8 ADDR = 0;
	};

	EERegisterDmacSadr_t(const char* const mnemonic, const u32& PS2PhysicalAddress);
};

/*
The DMAC D_QWC register, aka SPR (scratchpad ram) transfer address register.
*/
class EERegisterDmacQwc_t : public BitfieldMMemory32_t
{
public:
	struct Fields
	{
		static constexpr u8 QWC = 0;
	};

	EERegisterDmacQwc_t(const char* const mnemonic, const u32& PS2PhysicalAddress);
};

/*
The DMAC D_CTRL register, which contains various settings needed for the DMAC.
TODO: Need to implement cycle stealing? Wouldnt think so as it doesnt make sense in an emulator...
*/
class EERegisterDmacCtrl_t : public BitfieldMMemory32_t
{
public:
	struct Fields
	{
		static constexpr u8 DMAE = 0;
		static constexpr u8 RELE = 1;
		static constexpr u8 MFD = 2;
		static constexpr u8 STS = 3;
		static constexpr u8 STD = 4;
		static constexpr u8 RCYC = 5;
	};

	EERegisterDmacCtrl_t(const char* const mnemonic, const u32& PS2PhysicalAddress);
};

/*
The DMAC D_STAT register, aka interrupt status register.

The writeWordU() function is overriden:
When 1 is written to the CIS0-9, SIS, MEIS or BEIS bits, they are cleared (set to 0).
When 1 is written to the CIM0-9, SIM or MEIM bits, they are reversed.
*/
class EERegisterDmacStat_t : public BitfieldMMemory32_t
{
public:
	struct Fields
	{
		static constexpr u8 CIS0 = 0;
		static constexpr u8 CIS1 = 1;
		static constexpr u8 CIS2 = 2;
		static constexpr u8 CIS3 = 3;
		static constexpr u8 CIS4 = 4;
		static constexpr u8 CIS5 = 5;
		static constexpr u8 CIS6 = 6;
		static constexpr u8 CIS7 = 7;
		static constexpr u8 CIS8 = 8;
		static constexpr u8 CIS9 = 9;
		static constexpr u8 SIS = 10;
		static constexpr u8 MEIS = 11;
		static constexpr u8 BEIS = 12;
		static constexpr u8 CIM0 = 13;
		static constexpr u8 CIM1 = 14;
		static constexpr u8 CIM2 = 15;
		static constexpr u8 CIM3 = 16;
		static constexpr u8 CIM4 = 17;
		static constexpr u8 CIM5 = 18;
		static constexpr u8 CIM6 = 19;
		static constexpr u8 CIM7 = 20;
		static constexpr u8 CIM8 = 21;
		static constexpr u8 CIM9 = 22;
		static constexpr u8 SIM = 23;
		static constexpr u8 MEIM = 24;
	};

	EERegisterDmacStat_t(const char* const mnemonic, const u32& PS2PhysicalAddress);

	void writeWordU(u32 storageIndex, u32 value) override;
};

/*
The DMAC D_PCR register, aka priority control register.
*/
class EERegisterDmacPcr_t : public BitfieldMMemory32_t
{
public:
	struct Fields
	{
		static constexpr u8 CPC0 = 0;
		static constexpr u8 CPC1 = 1;
		static constexpr u8 CPC2 = 2;
		static constexpr u8 CPC3 = 3;
		static constexpr u8 CPC4 = 4;
		static constexpr u8 CPC5 = 5;
		static constexpr u8 CPC6 = 6;
		static constexpr u8 CPC7 = 7;
		static constexpr u8 CPC8 = 8;
		static constexpr u8 CPC9 = 9;
		static constexpr u8 CDE0 = 10;
		static constexpr u8 CDE1 = 11;
		static constexpr u8 CDE2 = 12;
		static constexpr u8 CDE3 = 13;
		static constexpr u8 CDE4 = 14;
		static constexpr u8 CDE5 = 15;
		static constexpr u8 CDE6 = 16;
		static constexpr u8 CDE7 = 17;
		static constexpr u8 CDE8 = 18;
		static constexpr u8 CDE9 = 19;
		static constexpr u8 PCE = 20;
	};

	EERegisterDmacPcr_t(const char* const mnemonic, const u32& PS2PhysicalAddress);
};

/*
The DMAC D_SQWC register, aka interleave size register.
*/
class EERegisterDmacSqwc_t : public BitfieldMMemory32_t
{
public:
	struct Fields
	{
		static constexpr u8 SQWC = 0;
		static constexpr u8 TQWC = 1;
	};

	EERegisterDmacSqwc_t(const char* const mnemonic, const u32& PS2PhysicalAddress);
};

/*
The DMAC D_RBOR register, aka ring buffer address register.
*/
class EERegisterDmacRbor_t : public BitfieldMMemory32_t
{
public:
	struct Fields
	{
		static constexpr u8 ADDR = 0;
	};

	EERegisterDmacRbor_t(const char* const mnemonic, const u32& PS2PhysicalAddress);
};

/*
The DMAC D_RBSR register, aka ring buffer address register.
*/
class EERegisterDmacRbsr_t : public BitfieldMMemory32_t
{
public:
	struct Fields
	{
		static constexpr u8 RMSK = 0;
	};

	EERegisterDmacRbsr_t(const char* const mnemonic, const u32& PS2PhysicalAddress);
};

/*
The DMAC D_STADR register, aka ring buffer address register.
*/
class EERegisterDmacStadr_t : public BitfieldMMemory32_t
{
public:
	struct Fields
	{
		static constexpr u8 ADDR = 0;
	};

	EERegisterDmacStadr_t(const char* const mnemonic, const u32& PS2PhysicalAddress);
};

/*
The DMAC D_ENABLEW register, aka DMA hold control register.
*/
class EERegisterDmacEnablew_t : public BitfieldMMemory32_t
{
public:
	struct Fields
	{
		static constexpr u8 CPND = 0;
	};

	EERegisterDmacEnablew_t(const char* const mnemonic, const u32& PS2PhysicalAddress);
};

/*
The DMAC D_ENABLEW register, aka DMA hold control register.
*/
class EERegisterDmacEnabler_t : public BitfieldMMemory32_t
{
public:
	struct Fields
	{
		static constexpr u8 CPND = 0;
	};

	EERegisterDmacEnabler_t(const char* const mnemonic, const u32& PS2PhysicalAddress);
};

/*
The SIO (serial I/O), which is somewhat undocumented. Some information can be found in the Toshiba Tx79 architecture manual (similar to the EE), but even then information is lacking.
Some useful information can be found in the old PCSX2 under Hw.h (register names). It requires some special functionality (see below).
In a real PS2, you can communicate with the EE over this serial port.
Allocated at base PS2 physical memory address 0x1000F100.
*/
class EERegisterSIO_t : public MappedMemory_t
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
class EERegisterMCH_t : public MappedMemory_t
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
