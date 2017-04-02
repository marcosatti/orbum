#pragma once

#include <memory>

#include "Common/Types/Registers/BitfieldRegister32_t.h"

/*
IOPCore_COP0_Registers_t.h implements the IOP Core specific COP0 control registers. This is used primarily by IOPCoreCOP0_t.h.
Each register will have documentation attached to it, and is prefixed with IOPCore_COP0Register.
Note: where register fields have a constant 0, this is already done due to the base classes initalisation code.

It is recommended that you read the documentation of the BitfieldRegister32_t class, which documents how to access bitfields.
All of the fields available within each register are defined within the Fields struct located inside.
ie: to access a field in a register object from outside this file, you would use:
- RegisterIndex.setFieldValue(RegisterIndex::Fields::Index, u32 value) or
- u32 value = RegisterIndex.getFieldValue(RegisterIndex::Fields::Index)
All of the available field functions are listed in the BitfieldRegister32_t class.

The actual fields are defined at runtime within the IOPCore_COP0_Registers_t.cpp file.

See here where you can find more information: http://hitmen.c02.at/files/docs/psx/psx.pdf (thanks to Joshua Walker).
*/

/*
The Context register of the IOP.
TODO: Finish documentation.
*/
class IOPCoreCOP0Register_System_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr int BadVPN2 = 0;
		static constexpr int PTEBase = 1;

	};

	explicit IOPCoreCOP0Register_System_t();
};

/*
The Status register of the IOP.
TODO: Finish documentation.
*/
class IOPCoreCOP0Register_Status_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr int IEc = 0;
		static constexpr int KUc = 1;
		static constexpr int IEp = 2;
		static constexpr int KUp = 3;
		static constexpr int IEo = 4;
		static constexpr int KUo = 5;
		static constexpr int IM = 6;
		static constexpr int IsC = 7;
		static constexpr int SwC = 8;
		static constexpr int PZ = 9;
		static constexpr int CM = 10;
		static constexpr int PE = 11;
		static constexpr int TS = 12;
		static constexpr int BEV = 13;
		static constexpr int RE = 14;
		static constexpr int CU = 15;
	};

	explicit IOPCoreCOP0Register_Status_t();

	/*
	Pushes/Pops the IE & KU bits (used in exception handling) to an older or earlier level (similar to a stack).
	In the bitfield names for those bits,
	"c" refers to the current status.
	"p" refers to the previous status.
	"o" refers to the oldest status.

	When pushing, clears the expunged bits to 0 (poping contains old values).
	*/
	void pushExceptionStack(const System_t context);
	void popExceptionStack(const System_t context);

	/*
	Returns if all exceptions are currently masked ( = NOT ENABLED).
	TODO: Implement, currently returns false always. Need to check ??? bits? The EE core says to check something...
	*/
	bool isExceptionsMasked(const System_t context) const;

	/*
	Returns if all interrupts are currently masked ( = NOT ENABLED).
	Does so by checking the master IEc bit.
	*/
	bool isInterruptsMasked(const System_t context) const;

	/*
	Returns if a given IRQ line (corresponding to IM bit) is masked ( = NOT ENABLED).
	Does so by checking the IM[irq] bit.
	*/
	bool isIRQMasked(const System_t context, const int irq) const;
};

/*
The Couse register of the IOP.
TODO: Finish documentation.
*/
class IOPCoreCOP0Register_Cause_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr int ExcCode = 0;
		static constexpr int IP = 1;
		static constexpr int CE = 2;
		static constexpr int BD = 3;
	};

	explicit IOPCoreCOP0Register_Cause_t();

	/*
	Clears the Cause.IP bits (from bits 8 -> 15).
	*/
	void clearIP(const System_t context);

	/*
	Sets the given IP[irq] bit given.
	The other IP bits are left unchanged (uses OR).
	*/
	void setIRQLine(const System_t context, const int irq);

	/*
	Clears the given IP[irq] bit given.
	The other IP bits are left unchanged (uses ~AND).
	*/
	void clearIRQLine(const System_t context, const int irq);
};

/*
The PRId register of the IOP - some different initial values to the other PRId (EE Core) implementation.
(Same structure.)
TODO: Finish documentation.
*/
class IOPCoreCOP0Register_PRId_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr int Rev = 0;
		static constexpr int Imp = 1;
	};

	explicit IOPCoreCOP0Register_PRId_t();
};