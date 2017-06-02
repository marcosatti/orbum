#pragma once

#include "Common/Global/Globals.h"
#include "Common/Types/Register/BitfieldRegister32_t.h"

/*
The DMAC D_CTRL register, which contains various settings needed for the DMAC.
TODO: Need to implement cycle stealing? Wouldnt think so as it doesnt make sense in an emulator...
*/
class EEDmacRegister_CTRL_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr int DMAE = 0;
		static constexpr int RELE = 1;
		static constexpr int MFD = 2;
		static constexpr int STS = 3;
		static constexpr int STD = 4;
		static constexpr int RCYC = 5;
	};

	EEDmacRegister_CTRL_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
};

/*
The DMAC D_STAT register, aka interrupt status register.

The writeWordU() function is overriden:
When 1 is written to the CIS0-9, SIS, MEIS or BEIS bits, they are cleared (set to 0).
When 1 is written to the CIM0-9, SIM or MEIM bits, they are reversed.
*/
class EEDmacRegister_STAT_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr int CIS0 = 0;
		static constexpr int CIS1 = 1;
		static constexpr int CIS2 = 2;
		static constexpr int CIS3 = 3;
		static constexpr int CIS4 = 4;
		static constexpr int CIS5 = 5;
		static constexpr int CIS6 = 6;
		static constexpr int CIS7 = 7;
		static constexpr int CIS8 = 8;
		static constexpr int CIS9 = 9;
		static constexpr int SIS = 10;
		static constexpr int MEIS = 11;
		static constexpr int BEIS = 12;
		static constexpr int CIM0 = 13;
		static constexpr int CIM1 = 14;
		static constexpr int CIM2 = 15;
		static constexpr int CIM3 = 16;
		static constexpr int CIM4 = 17;
		static constexpr int CIM5 = 18;
		static constexpr int CIM6 = 19;
		static constexpr int CIM7 = 20;
		static constexpr int CIM8 = 21;
		static constexpr int CIM9 = 22;
		static constexpr int SIM = 23;
		static constexpr int MEIM = 24;

		static constexpr int CHANNEL_CIS_KEYS[Constants::EE::DMAC::NUMBER_DMAC_CHANNELS] = { CIS0, CIS1, CIS2, CIS3, CIS4, CIS5, CIS6, CIS7, CIS8, CIS9 };
		static constexpr int CHANNEL_CIM_KEYS[Constants::EE::DMAC::NUMBER_DMAC_CHANNELS] = { CIM0, CIM1, CIM2, CIM3, CIM4, CIM5, CIM6, CIM7, CIM8, CIM9 };
	};

	EEDmacRegister_STAT_t(const char * mnemonic, const bool debugReads, const bool debugWrites);

	/*
	(EE context only.)
	When 1 is written to the CIS0-9, SIS, MEIS or BEIS bits, they are cleared (set to 0).
	When 1 is written to the CIM0-9, SIM or MEIM bits, they are reversed.
	*/
	void writeWord(const Context_t context, const u32 value) override;

	/*
	Returns if there is a pending interrupt that should be raised.
	*/
	bool isInterruptPending(const Context_t context);
};

/*
The DMAC D_PCR register, aka priority control register.
*/
class EEDmacRegister_PCR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr int CPC0 = 0;
		static constexpr int CPC1 = 1;
		static constexpr int CPC2 = 2;
		static constexpr int CPC3 = 3;
		static constexpr int CPC4 = 4;
		static constexpr int CPC5 = 5;
		static constexpr int CPC6 = 6;
		static constexpr int CPC7 = 7;
		static constexpr int CPC8 = 8;
		static constexpr int CPC9 = 9;
		static constexpr int CDE0 = 10;
		static constexpr int CDE1 = 11;
		static constexpr int CDE2 = 12;
		static constexpr int CDE3 = 13;
		static constexpr int CDE4 = 14;
		static constexpr int CDE5 = 15;
		static constexpr int CDE6 = 16;
		static constexpr int CDE7 = 17;
		static constexpr int CDE8 = 18;
		static constexpr int CDE9 = 19;
		static constexpr int PCE = 20;
	};

	EEDmacRegister_PCR_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
};

/*
The DMAC D_SQWC register, aka interleave size register.
*/
class EEDmacRegister_SWQC_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr int SQWC = 0;
		static constexpr int TQWC = 1;
	};

	EEDmacRegister_SWQC_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
};

/*
The DMAC D_RBOR register, aka ring buffer address register.
*/
class EEDmacRegister_RBOR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr int ADDR = 0;
	};

	EEDmacRegister_RBOR_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
};

/*
The DMAC D_RBSR register, aka ring buffer address register.
*/
class EEDmacRegister_RBSR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr int RMSK = 0;
	};

	EEDmacRegister_RBSR_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
};

/*
The DMAC D_STADR register, aka ring buffer address register.
*/
class EEDmacRegister_STADR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr int ADDR = 0;
	};

	EEDmacRegister_STADR_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
};

/*
The DMAC D_ENABLEW register, aka DMA hold control register.
*/
class EEDmacRegister_ENABLEW_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr int CPND = 0;
	};

	EEDmacRegister_ENABLEW_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
};

/*
The DMAC D_ENABLER register, aka DMA hold state register.
*/
class EEDmacRegister_ENABLER_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr int CPND = 0;
	};

	EEDmacRegister_ENABLER_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
};
