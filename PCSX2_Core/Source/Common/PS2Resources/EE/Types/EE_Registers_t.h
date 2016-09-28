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
*/

/*
The Timer Mode register type. See EE Users Manual page 36.
TODO: Fill in bitfield information like COP0_BitfieldRegisters_t.
Writing 1 to the Equal flag or Overflow flag will clear it (bits 10 and 11, behaves like a XOR write).

Needs a reference to the associated Count register as it will reset the value when CUE is set to 1.
It is assumed that although it is implemented as a 32-bit register-type, the upper 16-bits are not used.
*/
class EERegisterTimerMode_t : public BitfieldMMemory32_t, public PS2ResourcesSubobject
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
		static constexpr char * DIR = "DIR";
		static constexpr char * MOD = "MOD";
		static constexpr char * ASP = "ASP";
		static constexpr char * TTE = "TTE";
		static constexpr char * TIE = "TIE";
		static constexpr char * STR = "STR";
		static constexpr char * TAG = "TAG";
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
		static constexpr char * ADDR = "ADDR";
		static constexpr char * SPR = "SPR";
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
		static constexpr char * ADDR = "ADDR";
		static constexpr char * SPR = "SPR";
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
		static constexpr char * ADDR = "ADDR";
		static constexpr char * SPR = "SPR";
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
		static constexpr char * ADDR = "ADDR";
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
		static constexpr char * QWC = "QWC";
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
		static constexpr char * DMAE = "DMAE";
		static constexpr char * RELE = "RELE";
		static constexpr char * MFD = "MFD";
		static constexpr char * STS = "STS";
		static constexpr char * STD = "STD";
		static constexpr char * RCYC = "RCYC";
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
		static constexpr char * CIS0 = "CIS0";
		static constexpr char * CIS1 = "CIS1";
		static constexpr char * CIS2 = "CIS2";
		static constexpr char * CIS3 = "CIS3";
		static constexpr char * CIS4 = "CIS4";
		static constexpr char * CIS5 = "CIS5";
		static constexpr char * CIS6 = "CIS6";
		static constexpr char * CIS7 = "CIS7";
		static constexpr char * CIS8 = "CIS8";
		static constexpr char * CIS9 = "CIS9";
		static constexpr char * SIS = "SIS";
		static constexpr char * MEIS = "MEIS";
		static constexpr char * BEIS = "BEIS";
		static constexpr char * CIM0 = "CIM0";
		static constexpr char * CIM1 = "CIM1";
		static constexpr char * CIM2 = "CIM2";
		static constexpr char * CIM3 = "CIM3";
		static constexpr char * CIM4 = "CIM4";
		static constexpr char * CIM5 = "CIM5";
		static constexpr char * CIM6 = "CIM6";
		static constexpr char * CIM7 = "CIM7";
		static constexpr char * CIM8 = "CIM8";
		static constexpr char * CIM9 = "CIM9";
		static constexpr char * SIM = "SIM";
		static constexpr char * MEIM = "MEIM";
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
		static constexpr char * CPC0 = "CPC0";
		static constexpr char * CPC1 = "CPC1";
		static constexpr char * CPC2 = "CPC2";
		static constexpr char * CPC3 = "CPC3";
		static constexpr char * CPC4 = "CPC4";
		static constexpr char * CPC5 = "CPC5";
		static constexpr char * CPC6 = "CPC6";
		static constexpr char * CPC7 = "CPC7";
		static constexpr char * CPC8 = "CPC8";
		static constexpr char * CPC9 = "CPC9";
		static constexpr char * CDE0 = "CDE0";
		static constexpr char * CDE1 = "CDE1";
		static constexpr char * CDE2 = "CDE2";
		static constexpr char * CDE3 = "CDE3";
		static constexpr char * CDE4 = "CDE4";
		static constexpr char * CDE5 = "CDE5";
		static constexpr char * CDE6 = "CDE6";
		static constexpr char * CDE7 = "CDE7";
		static constexpr char * CDE8 = "CDE8";
		static constexpr char * CDE9 = "CDE9";
		static constexpr char * PCE = "PCE";
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
		static constexpr char * SQWC = "SQWC";
		static constexpr char * TQWC = "TQWC";
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
		static constexpr char * ADDR = "ADDR";
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
		static constexpr char * RMSK = "RMSK";
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
		static constexpr char * ADDR = "ADDR";
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
		static constexpr char * CPND = "CPND";
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
		static constexpr char * CPND = "CPND";
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
