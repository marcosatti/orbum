#pragma once

#include "Common/Global/Globals.h"
#include "Common/PS2Constants/PS2Constants.h"
#include "Common/PS2Resources/Types/MappedMemory/BitfieldMMemory32_t.h"
#include "Common/Interfaces/PS2ResourcesSubobject.h"

/*
The DMAC D_CHCR register, aka channel control register.
Needs an channel index, which is used to reset the EE->DMAC state variables when a 1 is written to the STR bit.
*/
class DmacRegisterChcr_t : public BitfieldMMemory32_t, public PS2ResourcesSubobject
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

	DmacRegisterChcr_t(const char* const mnemonic, const u32& PS2PhysicalAddress, const PS2Resources_t *const PS2Resources, const u32 & channelID);

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
class DmacRegisterMadr_t : public BitfieldMMemory32_t
{
public:
	struct Fields
	{
		static constexpr u8 ADDR = 0;
		static constexpr u8 SPR = 1;
	};

	DmacRegisterMadr_t(const char* const mnemonic, const u32& PS2PhysicalAddress);

	/*
	Increments ADDR by 0x10, which is the size of 1 DMA transfer (used when one transfer has completed).
	*/
	void increment();
};

/*
The DMAC D_TADR register, aka tag address register.
*/
class DmacRegisterTadr_t : public BitfieldMMemory32_t
{
public:
	struct Fields
	{
		static constexpr u8 ADDR = 0;
		static constexpr u8 SPR = 1;
	};

	DmacRegisterTadr_t(const char* const mnemonic, const u32& PS2PhysicalAddress);
};

/*
The DMAC D_ASR0/1 register, aka tag address save register.
*/
class DmacRegisterAsr_t : public BitfieldMMemory32_t
{
public:
	struct Fields
	{
		static constexpr u8 ADDR = 0;
		static constexpr u8 SPR = 1;
	};

	DmacRegisterAsr_t(const char* const mnemonic, const u32& PS2PhysicalAddress);
};

/*
The DMAC D_SADR register, aka SPR (scratchpad ram) transfer address register.
*/
class DmacRegisterSadr_t : public BitfieldMMemory32_t
{
public:
	struct Fields
	{
		static constexpr u8 ADDR = 0;
	};

	DmacRegisterSadr_t(const char* const mnemonic, const u32& PS2PhysicalAddress);

	/*
	Increments ADDR by 0x10, which is the size of 1 DMA transfer (used when one transfer has completed).
	*/
	void increment();
};

/*
The DMAC D_QWC register, aka SPR (scratchpad ram) transfer address register.
*/
class DmacRegisterQwc_t : public BitfieldMMemory32_t
{
public:
	struct Fields
	{
		static constexpr u8 QWC = 0;
	};

	DmacRegisterQwc_t(const char* const mnemonic, const u32& PS2PhysicalAddress);

	/*
	Decrements the QWC counter by 1. Should be called when a data unit has been transferred.
	*/
	void decrement();
};

/*
The DMAC D_CTRL register, which contains various settings needed for the DMAC.
TODO: Need to implement cycle stealing? Wouldnt think so as it doesnt make sense in an emulator...
*/
class DmacRegisterCtrl_t : public BitfieldMMemory32_t
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

	DmacRegisterCtrl_t(const char* const mnemonic, const u32& PS2PhysicalAddress);
};

/*
The DMAC D_STAT register, aka interrupt status register.

The writeWordU() function is overriden:
When 1 is written to the CIS0-9, SIS, MEIS or BEIS bits, they are cleared (set to 0).
When 1 is written to the CIM0-9, SIM or MEIM bits, they are reversed.
*/
class DmacRegisterStat_t : public BitfieldMMemory32_t
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

		// Array of CIS and CIM keys needed for iterations.
		static constexpr u8 CIS_KEYS[PS2Constants::EE::DMAC::NUMBER_DMA_CHANNELS]{ CIS0, CIS1, CIS2, CIS3, CIS4, CIS5, CIS6, CIS7, CIS8, CIS9 };
		static constexpr u8 CIM_KEYS[PS2Constants::EE::DMAC::NUMBER_DMA_CHANNELS]{ CIM0, CIM1, CIM2, CIM3, CIM4, CIM5, CIM6, CIM7, CIM8, CIM9 };
	};

	DmacRegisterStat_t(const char* const mnemonic, const u32& PS2PhysicalAddress);

	void writeWordU(u32 storageIndex, u32 value) override;
};

/*
The DMAC D_PCR register, aka priority control register.
*/
class DmacRegisterPcr_t : public BitfieldMMemory32_t
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

	DmacRegisterPcr_t(const char* const mnemonic, const u32& PS2PhysicalAddress);
};

/*
The DMAC D_SQWC register, aka interleave size register.
*/
class DmacRegisterSqwc_t : public BitfieldMMemory32_t
{
public:
	struct Fields
	{
		static constexpr u8 SQWC = 0;
		static constexpr u8 TQWC = 1;
	};

	DmacRegisterSqwc_t(const char* const mnemonic, const u32& PS2PhysicalAddress);
};

/*
The DMAC D_RBOR register, aka ring buffer address register.
*/
class DmacRegisterRbor_t : public BitfieldMMemory32_t
{
public:
	struct Fields
	{
		static constexpr u8 ADDR = 0;
	};

	DmacRegisterRbor_t(const char* const mnemonic, const u32& PS2PhysicalAddress);
};

/*
The DMAC D_RBSR register, aka ring buffer address register.
*/
class DmacRegisterRbsr_t : public BitfieldMMemory32_t
{
public:
	struct Fields
	{
		static constexpr u8 RMSK = 0;
	};

	DmacRegisterRbsr_t(const char* const mnemonic, const u32& PS2PhysicalAddress);
};

/*
The DMAC D_STADR register, aka ring buffer address register.
*/
class DmacRegisterStadr_t : public BitfieldMMemory32_t
{
public:
	struct Fields
	{
		static constexpr u8 ADDR = 0;
	};

	DmacRegisterStadr_t(const char* const mnemonic, const u32& PS2PhysicalAddress);
};

/*
The DMAC D_ENABLEW register, aka DMA hold control register.
*/
class DmacRegisterEnablew_t : public BitfieldMMemory32_t
{
public:
	struct Fields
	{
		static constexpr u8 CPND = 0;
	};

	DmacRegisterEnablew_t(const char* const mnemonic, const u32& PS2PhysicalAddress);
};

/*
The DMAC D_ENABLEW register, aka DMA hold control register.
*/
class DmacRegisterEnabler_t : public BitfieldMMemory32_t
{
public:
	struct Fields
	{
		static constexpr u8 CPND = 0;
	};

	DmacRegisterEnabler_t(const char* const mnemonic, const u32& PS2PhysicalAddress);
};
