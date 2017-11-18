#pragma once

#include "Common/Types/Register/SizedWordRegister.hpp"

/// EE COP0 registers.
/// See EE Core Users Manual page 62 onwards for more information.

class EeCoreCop0Register_Index : public SizedWordRegister
{
public:
	static constexpr Bitfield INDEX = Bitfield(0, 6);
	static constexpr Bitfield P     = Bitfield(31, 1);
};

class EeCoreCop0Register_Random : public SizedWordRegister
{
public:
	static constexpr Bitfield RANDOM = Bitfield(0, 6);
};

class EeCoreCop0Register_EntryLo0 : public SizedWordRegister
{
public:
	static constexpr Bitfield G   = Bitfield(0, 1);
	static constexpr Bitfield V   = Bitfield(1, 1);
	static constexpr Bitfield D   = Bitfield(2, 1);
	static constexpr Bitfield C   = Bitfield(3, 3);
	static constexpr Bitfield PFN = Bitfield(6, 20);
	static constexpr Bitfield S   = Bitfield(31, 1);
};

class EeCoreCop0Register_EntryLo1 : public SizedWordRegister
{
public:
	static constexpr Bitfield G   = Bitfield(0, 1);
	static constexpr Bitfield V   = Bitfield(1, 1);
	static constexpr Bitfield D   = Bitfield(2, 1);
	static constexpr Bitfield C   = Bitfield(3, 3);
	static constexpr Bitfield PFN = Bitfield(6, 20);
};

class EeCoreCop0Register_System : public SizedWordRegister
{
public:
	static constexpr Bitfield BADVPN2 = Bitfield(4, 19);
	static constexpr Bitfield PTEBASE = Bitfield(23, 9);
};

class EeCoreCop0Register_PageMask : public SizedWordRegister
{
public:
	static constexpr Bitfield MASK = Bitfield(13, 12);
};

class EeCoreCop0Register_Wired : public SizedWordRegister
{
public:
	static constexpr Bitfield Wired = Bitfield(0, 6);
};

class EeCoreCop0Register_EntryHi : public SizedWordRegister
{
public:
	static constexpr Bitfield ASID = Bitfield(0, 8);
	static constexpr Bitfield VPN2 = Bitfield(13, 19);
};

class EeCoreCop0Register_Status : public SizedWordRegister
{
public:
	static constexpr Bitfield IE  = Bitfield(0, 1);
	static constexpr Bitfield EXL = Bitfield(1, 1);
	static constexpr Bitfield ERL = Bitfield(2, 1);
	static constexpr Bitfield KSU = Bitfield(3, 2);
	static constexpr Bitfield IM  = Bitfield(8, 8);
	static constexpr Bitfield EIE = Bitfield(16, 1);
	static constexpr Bitfield EDI = Bitfield(17, 1);
	static constexpr Bitfield CH  = Bitfield(18, 1);
	static constexpr Bitfield BEV = Bitfield(22, 1);
	static constexpr Bitfield DEV = Bitfield(23, 1);
	static constexpr Bitfield CU  = Bitfield(28, 4);

	/// Returns if all interrupts are currently masked ( = NOT ENABLED).
	/// Does so by checking the master EIE and IE bit.
	bool is_interrupts_masked();
};

class EeCoreCop0Register_Cause : public SizedWordRegister
{
public:
	static constexpr Bitfield EXCCODE = Bitfield(2, 5);
	static constexpr Bitfield IP      = Bitfield(8, 8);
	static constexpr Bitfield EXC2    = Bitfield(16, 3);
	static constexpr Bitfield CE      = Bitfield(28, 2);
	static constexpr Bitfield BD2     = Bitfield(30, 1);
	static constexpr Bitfield BD      = Bitfield(31, 1);

	/// Clears the Cause.IP bits (from bits 8 -> 15).
	void clear_ip();

	/// Sets the given IP[irq] bit given.
	/// The other IP bits are left unchanged (uses OR).
	void set_irq_line(const int irq);

	/// Clears the given IP[irq] bit given.
	/// The other IP bits are left unchanged (uses ~AND).
	void clear_irq_line(const int irq);
};

class EeCoreCop0Register_Prid : public SizedWordRegister
{
public:
	static constexpr Bitfield REV = Bitfield(0, 8);
	static constexpr Bitfield IMP = Bitfield(8, 8);

	static constexpr uword INITIAL_VALUE = 0x00002E20;

	EeCoreCop0Register_Prid();
};

class EeCoreCop0Register_Config : public SizedWordRegister
{
public:
	static constexpr Bitfield K0  = Bitfield(0, 3);
	static constexpr Bitfield DC  = Bitfield(6, 3);
	static constexpr Bitfield IC  = Bitfield(9, 3);
	static constexpr Bitfield BPE = Bitfield(12, 1);
	static constexpr Bitfield NBE = Bitfield(13, 1);
	static constexpr Bitfield DCE = Bitfield(16, 1);
	static constexpr Bitfield ICE = Bitfield(17, 1);
	static constexpr Bitfield DIE = Bitfield(18, 1);
	static constexpr Bitfield EC  = Bitfield(28, 3);
};

class EeCoreCop0Register_BadPAddr : public SizedWordRegister
{
public:
	static constexpr Bitfield BadPAddr = Bitfield(4, 28);
};

class EeCoreCop0Register_Bpc : public SizedWordRegister
{
public:
	static constexpr Bitfield IAB = Bitfield(0, 1);
	static constexpr Bitfield DRB = Bitfield(1, 1);
	static constexpr Bitfield DWB = Bitfield(2, 1);
	static constexpr Bitfield BED = Bitfield(15, 1);
	static constexpr Bitfield DTE = Bitfield(16, 1);
	static constexpr Bitfield ITE = Bitfield(17, 1);
	static constexpr Bitfield DXE = Bitfield(18, 1);
	static constexpr Bitfield DKE = Bitfield(19, 1);
	static constexpr Bitfield DSE = Bitfield(20, 1);
	static constexpr Bitfield DUE = Bitfield(21, 1);
	static constexpr Bitfield IXE = Bitfield(23, 1);
	static constexpr Bitfield IKE = Bitfield(24, 1);
	static constexpr Bitfield ISE = Bitfield(25, 1);
	static constexpr Bitfield IUE = Bitfield(26, 1);
	static constexpr Bitfield DVE = Bitfield(28, 1);
	static constexpr Bitfield DWE = Bitfield(29, 1);
	static constexpr Bitfield DRE = Bitfield(30, 1);
	static constexpr Bitfield IAE = Bitfield(31, 1);
};

class EeCoreCop0Register_Pccr : public SizedWordRegister
{
public:
	static constexpr Bitfield EXL0   = Bitfield(1, 1);
	static constexpr Bitfield K0     = Bitfield(2, 1);
	static constexpr Bitfield S0     = Bitfield(3, 1);
	static constexpr Bitfield U0     = Bitfield(4, 1);
	static constexpr Bitfield EVENT0 = Bitfield(5, 5);
	static constexpr Bitfield EXL1   = Bitfield(11, 1);
	static constexpr Bitfield K1     = Bitfield(12, 1);
	static constexpr Bitfield S1     = Bitfield(13, 1);
	static constexpr Bitfield U1     = Bitfield(14, 1);
	static constexpr Bitfield EVENT1 = Bitfield(15, 5);
	static constexpr Bitfield CTE    = Bitfield(31, 1);
};

class EeCoreCop0Register_Pcr0 : public SizedWordRegister
{
public:
	static constexpr Bitfield VALUE = Bitfield(0, 31);
	static constexpr Bitfield OVFL  = Bitfield(31, 1);
};

class EeCoreCop0Register_Pcr1 : public SizedWordRegister
{
public:
	static constexpr Bitfield VALUE = Bitfield(0, 31);
	static constexpr Bitfield OVFL  = Bitfield(31, 1);
};

class EeCoreCop0Register_TagLo : public SizedWordRegister
{
public:
	static constexpr Bitfield L      = Bitfield(3, 1);
	static constexpr Bitfield R      = Bitfield(4, 1);
	static constexpr Bitfield V      = Bitfield(5, 1);
	static constexpr Bitfield D      = Bitfield(6, 1);
	static constexpr Bitfield PTAGLO = Bitfield(12, 31);
};

class EeCoreCop0Register_TagHi : public SizedWordRegister
{
public:
	static constexpr Bitfield L      = Bitfield(3, 1);
	static constexpr Bitfield R      = Bitfield(4, 1);
	static constexpr Bitfield V      = Bitfield(5, 1);
	static constexpr Bitfield D      = Bitfield(6, 1);
	static constexpr Bitfield PTAGHI = Bitfield(12, 31);
};
