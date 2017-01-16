#pragma once

#include "Common/Global/Globals.h"
#include "PS2Constants/PS2Constants.h"
#include "Common/Types/Registers/BitfieldRegister32_t.h"

/*
The DMAC D_CTRL register, which contains various settings needed for the DMAC.
TODO: Need to implement cycle stealing? Wouldnt think so as it doesnt make sense in an emulator...
*/
class EEDmacRegister_CTRL_t : public BitfieldRegister32_t
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

	EEDmacRegister_CTRL_t();
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
		static constexpr u8 CIS_KEYS[PS2Constants::EE::DMAC::NUMBER_DMAC_CHANNELS]{ CIS0, CIS1, CIS2, CIS3, CIS4, CIS5, CIS6, CIS7, CIS8, CIS9 };
		static constexpr u8 CIM_KEYS[PS2Constants::EE::DMAC::NUMBER_DMAC_CHANNELS]{ CIM0, CIM1, CIM2, CIM3, CIM4, CIM5, CIM6, CIM7, CIM8, CIM9 };
	};

	EEDmacRegister_STAT_t();

	/*
	(EE context only.)
	When 1 is written to the CIS0-9, SIS, MEIS or BEIS bits, they are cleared (set to 0).
	When 1 is written to the CIM0-9, SIM or MEIM bits, they are reversed.
	Sets the internal flag after, if an interrupt should be raised (caches result).
	*/
	void writeWord(const Context_t & context, u32 value) override;

	/*
	Writes the field and sets the internal flag if there should be an interrupt raised (caches result).
	*/
	void setFieldValueInterrupt(const u8 & fieldIndex, const u32 & value);	

	/*
	Returns if there is a pending interrupt that should be raised.
	*/
	bool isInterrupted() const;

private:
	/*
	Checks for interrupt conditions and sets the mIsInterrupted flag.
	See the formula listed at the end of page 65 of the EE Users Manual.
	*/
	void handleInterruptCheck();

	/*
	See handleInterruptCheck() and isInterrupted() above.
	*/
	bool mIsInterrupted;
};

/*
The DMAC D_PCR register, aka priority control register.
*/
class EEDmacRegister_PCR_t : public BitfieldRegister32_t
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

	EEDmacRegister_PCR_t();
};

/*
The DMAC D_SQWC register, aka interleave size register.
*/
class EEDmacRegister_SWQC_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 SQWC = 0;
		static constexpr u8 TQWC = 1;
	};

	EEDmacRegister_SWQC_t();
};

/*
The DMAC D_RBOR register, aka ring buffer address register.
*/
class EEDmacRegister_RBOR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 ADDR = 0;
	};

	EEDmacRegister_RBOR_t();
};

/*
The DMAC D_RBSR register, aka ring buffer address register.
*/
class EEDmacRegister_RBSR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 RMSK = 0;
	};

	EEDmacRegister_RBSR_t();
};

/*
The DMAC D_STADR register, aka ring buffer address register.
*/
class EEDmacRegister_STADR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 ADDR = 0;
	};

	EEDmacRegister_STADR_t();
};

/*
The DMAC D_ENABLEW register, aka DMA hold control register.
*/
class EEDmacRegister_ENABLEW_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 CPND = 0;
	};

	EEDmacRegister_ENABLEW_t();
};

/*
The DMAC D_ENABLER register, aka DMA hold state register.
*/
class EEDmacRegister_ENABLER_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 CPND = 0;
	};

	EEDmacRegister_ENABLER_t();
};
