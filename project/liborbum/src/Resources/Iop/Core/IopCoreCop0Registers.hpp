#pragma once

#include "Common/Types/Register/SizedWordRegister.hpp"

/// IOP Core COP0 registers.
/// See here where you can find more information: http://hitmen.c02.at/files/docs/psx/psx.pdf (thanks to Joshua Walker).

/// Context register of the IOP COP0.
class IopCoreCop0Register_Context : public SizedWordRegister
{
public:
	static constexpr Bitfield BADVPN2 = Bitfield(2, 19);
	static constexpr Bitfield PTEBASE = Bitfield(21, 11);
};

/// Status register of the IOP COP0.
class IopCoreCop0Register_Status : public SizedWordRegister
{
public:
	static constexpr Bitfield IEC = Bitfield(0, 1);
	static constexpr Bitfield KUC = Bitfield(1, 1);
	static constexpr Bitfield IEP = Bitfield(2, 1);
	static constexpr Bitfield KUP = Bitfield(3, 1);
	static constexpr Bitfield IEO = Bitfield(4, 1);
	static constexpr Bitfield KUO = Bitfield(5, 1);
	static constexpr Bitfield IM = Bitfield(8, 8);
	static constexpr Bitfield ISC = Bitfield(16, 1);
	static constexpr Bitfield SWC = Bitfield(17, 1);
	static constexpr Bitfield PZ = Bitfield(18, 1);
	static constexpr Bitfield CM = Bitfield(19, 1);
	static constexpr Bitfield PE = Bitfield(20, 1);
	static constexpr Bitfield TS = Bitfield(21, 1);
	static constexpr Bitfield BEV = Bitfield(22, 1);
	static constexpr Bitfield RE = Bitfield(25, 1);
	static constexpr Bitfield CU = Bitfield(28, 4);

	/*
	Pushes/Pops the IE & KU bits (used in exception handling) to an older or earlier level (similar to a stack).
	In the bitfield names for those bits,
	"c" refers to the current status.
	"p" refers to the previous status.
	"o" refers to the oldest status.

	When pushing, clears the expunged bits to 0 (poping contains old values).
	*/
	void push_exception_stack();
	void pop_exception_stack();

	/*
	Returns if all exceptions are currently masked ( = NOT ENABLED).
	TODO: Implement, currently returns false always. Need to check ??? bits? The EE core says to check something...
	*/
	bool is_exceptions_masked();

	/*
	Returns if all interrupts are currently masked ( = NOT ENABLED).
	Does so by checking the master IEc bit.
	*/
	bool is_interrupts_masked();

	/*
	Returns if a given IRQ line (corresponding to IM bit) is masked ( = NOT ENABLED).
	Does so by checking the IM[irq] bit.
	*/
	bool is_irq_masked(const int irq);
};

/// Cause register of the IOP COP0.
class IopCoreCop0Register_Cause : public SizedWordRegister
{
public:
	static constexpr Bitfield EXCCODE = Bitfield(2, 5);
	static constexpr Bitfield IP = Bitfield(8, 8);
	static constexpr Bitfield CE = Bitfield(28, 2);
	static constexpr Bitfield BD = Bitfield(31, 1);

	/*
	Clears the Cause.IP bits (from bits 8 -> 15).
	*/
	void clear_ip();

	/*
	Sets the given IP[irq] bit given.
	The other IP bits are left unchanged (uses OR).
	*/
	void set_irq_line(const int irq);

	/*
	Clears the given IP[irq] bit given.
	The other IP bits are left unchanged (uses ~AND).
	*/
	void clear_irq_line(const int irq);
};

/// The PRId register of the IOP COP0.
/// Some different initial values to EE Core implementation, same structure.
class IopCoreCop0Register_Prid : public SizedWordRegister
{
public:
	static constexpr Bitfield REV = Bitfield(0, 8);
	static constexpr Bitfield IMP = Bitfield(8, 8);

	static constexpr uword INITIAL_VALUE = 0x1F;

	IopCoreCop0Register_Prid();
};