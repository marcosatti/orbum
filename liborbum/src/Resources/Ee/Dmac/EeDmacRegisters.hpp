#pragma once

#include "Common/Constants.hpp"
#include "Common/Types/ScopeLock.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"

// The DMAC D_CTRL register, which contains various settings needed for the DMAC.
// TODO: Need to implement cycle stealing? Wouldn't think so...
class EeDmacRegister_Ctrl : public SizedWordRegister
{
public:
	static constexpr Bitfield DMAE = Bitfield(0, 1);
	static constexpr Bitfield RELE = Bitfield(1, 1);
	static constexpr Bitfield MFD = Bitfield(2, 2);
	static constexpr Bitfield STS = Bitfield(4, 2);
	static constexpr Bitfield STD = Bitfield(6, 2);
	static constexpr Bitfield RCYC = Bitfield(8, 3);
};

// The DMAC D_STAT register, aka interrupt status register.
class EeDmacRegister_Stat : public SizedWordRegister, public ScopeLock
{
public:
	static constexpr Bitfield CIS0 = Bitfield(0, 1);
	static constexpr Bitfield CIS1 = Bitfield(1, 1);
	static constexpr Bitfield CIS2 = Bitfield(2, 1);
	static constexpr Bitfield CIS3 = Bitfield(3, 1);
	static constexpr Bitfield CIS4 = Bitfield(4, 1);
	static constexpr Bitfield CIS5 = Bitfield(5, 1);
	static constexpr Bitfield CIS6 = Bitfield(6, 1);
	static constexpr Bitfield CIS7 = Bitfield(7, 1);
	static constexpr Bitfield CIS8 = Bitfield(8, 1);
	static constexpr Bitfield CIS9 = Bitfield(9, 1);
	static constexpr Bitfield SIS  = Bitfield(13, 1);
	static constexpr Bitfield MEIS = Bitfield(14, 1);
	static constexpr Bitfield BEIS = Bitfield(15, 1);
	static constexpr Bitfield CIM0 = Bitfield(16, 1);
	static constexpr Bitfield CIM1 = Bitfield(17, 1);
	static constexpr Bitfield CIM2 = Bitfield(18, 1);
	static constexpr Bitfield CIM3 = Bitfield(19, 1);
	static constexpr Bitfield CIM4 = Bitfield(20, 1);
	static constexpr Bitfield CIM5 = Bitfield(21, 1);
	static constexpr Bitfield CIM6 = Bitfield(22, 1);
	static constexpr Bitfield CIM7 = Bitfield(23, 1);
	static constexpr Bitfield CIM8 = Bitfield(24, 1);
	static constexpr Bitfield CIM9 = Bitfield(25, 1);
	static constexpr Bitfield SIM  = Bitfield(29, 1);
	static constexpr Bitfield MEIM = Bitfield(30, 1);

	static constexpr Bitfield CHANNEL_CIS_KEYS[Constants::EE::DMAC::NUMBER_DMAC_CHANNELS] = { CIS0, CIS1, CIS2, CIS3, CIS4, CIS5, CIS6, CIS7, CIS8, CIS9 };
	static constexpr Bitfield CHANNEL_CIM_KEYS[Constants::EE::DMAC::NUMBER_DMAC_CHANNELS] = { CIM0, CIM1, CIM2, CIM3, CIM4, CIM5, CIM6, CIM7, CIM8, CIM9 };

	/// (EE context only.)
	/// When 1 is written to the CIS0-9, SIS, MEIS or BEIS bits, they are cleared (set to 0).
	/// When 1 is written to the CIM0-9, SIM or MEIM bits, they are reversed.
	/// Scope locked for entire duration.
	void byte_bus_write_uword(const BusContext context, const usize offset, const uword value) override;

	/// Returns the current interrupt condition state.
	/// If either the same STAT and MASK bits are set, or there is a bus error, an interrupt occurs.
	/// See the algorithm listed at the end of page 65 of the EE Users Manual.
	bool is_interrupt_pending();
};

// The DMAC D_PCR register, aka priority control register.
class EeDmacRegister_Pcr : public SizedWordRegister
{
public:
	static constexpr Bitfield CPC0 = Bitfield(0, 1);
	static constexpr Bitfield CPC1 = Bitfield(1, 1);
	static constexpr Bitfield CPC2 = Bitfield(2, 1);
	static constexpr Bitfield CPC3 = Bitfield(3, 1);
	static constexpr Bitfield CPC4 = Bitfield(4, 1);
	static constexpr Bitfield CPC5 = Bitfield(5, 1);
	static constexpr Bitfield CPC6 = Bitfield(6, 1);
	static constexpr Bitfield CPC7 = Bitfield(7, 1);
	static constexpr Bitfield CPC8 = Bitfield(8, 1);
	static constexpr Bitfield CPC9 = Bitfield(9, 1);
	static constexpr Bitfield CDE0 = Bitfield(16, 1);
	static constexpr Bitfield CDE1 = Bitfield(17, 1);
	static constexpr Bitfield CDE2 = Bitfield(18, 1);
	static constexpr Bitfield CDE3 = Bitfield(19, 1);
	static constexpr Bitfield CDE4 = Bitfield(20, 1);
	static constexpr Bitfield CDE5 = Bitfield(21, 1);
	static constexpr Bitfield CDE6 = Bitfield(22, 1);
	static constexpr Bitfield CDE7 = Bitfield(23, 1);
	static constexpr Bitfield CDE8 = Bitfield(24, 1);
	static constexpr Bitfield CDE9 = Bitfield(25, 1);
	static constexpr Bitfield PCE  = Bitfield(31, 1);
};

// The DMAC D_SQWC register, aka interleave size register.
class EeDmacRegister_Swqc : public SizedWordRegister
{
public:
	static constexpr Bitfield SQWC = Bitfield(0, 8);
	static constexpr Bitfield TQWC = Bitfield(16, 8);
};

// The DMAC D_RBSR register, aka ring buffer address register.
class EeDmacRegister_Rbsr : public SizedWordRegister
{
public:
	static constexpr Bitfield RMSK = Bitfield(4, 27);
};

// The DMAC D_ENABLEW register, aka DMA hold control register.
class EeDmacRegister_EnableW : public SizedWordRegister
{
public:
	static constexpr Bitfield CPND = Bitfield(16, 1);
};

// The DMAC D_ENABLER register, aka DMA hold state register.
class EeDmacRegister_EnableR : public SizedWordRegister
{
public:	
	static constexpr Bitfield CPND = Bitfield(16, 1);
};
