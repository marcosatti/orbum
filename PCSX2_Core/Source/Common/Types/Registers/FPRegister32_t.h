#pragma once

#include <string>

#include "Common/Global/Globals.h"

/*
FPRegister32_t is an additional register type defined within the PS2's floating point unit (FPU) system, which are used for operating on floating point numbers.
All FPR's are 32-bit (single precision) according to the documentation, and the floating point value is defined by the 'F' union field below.

See EE Core Users Manual, chapter 8, especially page 157 which define the aritmetic registers.

Code is based of the Register32_t implementation.
Some additional functions are exposed for manipulating the floating point fields (sign, exponent and fraction), which is done by manipulating the u32 UW in the union defined.

The FPU and the floating point values in general are NOT FULLY IEEE-754 compliant (mostly, but not fully).
In particular, the FPU does not support (in comparison to IEEE-754):
 - Denormalised numbers.
 - Plus and minus infinity.
 - 'NaN' (not a number) representation.
*/
class FPRegister32_t
{
public:

	explicit FPRegister32_t();
	explicit FPRegister32_t(const char * mnemonic);

	virtual ~FPRegister32_t()
	{
	}

	union
	{
		u32 UW;
		s32 SW;
		f32 F;
	};

	/*
	Functions to access the register value - you should use these functions instead of accessing them directly.
	NOTE: IT IS UP TO THE USER TO MAKE SURE THE FLOAT VALUE WRITTEN IS COMPATIBLE WITH THE PS2! Use the FPUUtil static class functions to help with conversion.
	*/
	virtual u32 readWordU();
	virtual void writeWordU(u32 value);	
	virtual s32 readWordS();
	virtual void writeWordS(s32 value);
	virtual f32 readFloat();
	virtual void writeFloat(f32 value);

	/*
	Gets the mnemonic of this register. Used for debug/logging.
	*/
	const char * getMnemonic() const;

private:
	/*
	The mnemonic.
	*/
	const std::string mMnemonic;
};

