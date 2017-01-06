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
class IOPCoreCOP0Register_Context_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 BadVPN2 = 0;
		static constexpr u8 PTEBase = 1;

	};

	explicit IOPCoreCOP0Register_Context_t();
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
		static constexpr u8 IEc = 0;
		static constexpr u8 KUc = 1;
		static constexpr u8 IEp = 2;
		static constexpr u8 KUp = 3;
		static constexpr u8 IEo = 4;
		static constexpr u8 KUo = 5;
		static constexpr u8 IM = 6;
		static constexpr u8 IsC = 7;
		static constexpr u8 SwC = 8;
		static constexpr u8 PZ = 9;
		static constexpr u8 CM = 10;
		static constexpr u8 PE = 11;
		static constexpr u8 TS = 12;
		static constexpr u8 BEV = 13;
		static constexpr u8 RE = 14;
		static constexpr u8 CU = 15;
	};

	explicit IOPCoreCOP0Register_Status_t();

	/*
	Pushes/Pops the IE & KU bits (used in exception handling) to an older or earlier level.
	In the bitfield names for those bits,
	"c" refers to the current status.
	"p" refers to the previous status.
	"o" refers to the oldest status.
	*/
	void pushExStack();
	void popExStack();

	/*
	Returns if all exceptions are currently masked ( = NOT ENABLED).
	TODO: Implement, currently returns false always. Need to check ??? bits? The EE core says to check something...
	*/
	bool isExceptionsMasked() const;

	/*
	Returns if all interrupts are currently masked ( = NOT ENABLED).
	Does so by checking the master IEc bit.
	*/
	bool isInterruptsMasked() const;

	/*
	Returns if a given IRQ line (corresponding to IM bit) is masked ( = NOT ENABLED).
	Does so by checking the IM[irq] bit.
	*/
	bool isIRQMasked(u8 irq) const;
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
		static constexpr u8 ExcCode = 0;
		static constexpr u8 IP = 1;
		static constexpr u8 CE = 2;
		static constexpr u8 BD = 3;
	};

	explicit IOPCoreCOP0Register_Cause_t();

	/*
	Clears the Cause.IP bits (from bits 8 -> 15).
	*/
	void clearIP();

	/*
	Sets the given IP[irq] bit given.
	The other IP bits are left unchanged (uses OR). Use the clearIP() function if you need to reset them all.
	*/
	void setIRQPending(u8 irq);
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
		static constexpr u8 Rev = 0;
		static constexpr u8 Imp = 1;
	};

	explicit IOPCoreCOP0Register_PRId_t();
};