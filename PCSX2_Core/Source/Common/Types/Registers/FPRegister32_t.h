#pragma once

#include <string>

#include "Common/Global/Globals.h"
#include "Common/Types/Context_t.h"

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

	virtual ~FPRegister32_t();

	/*
	Read/write functions to access the register, with subclassed functionality. 
	TODO: can get small speedup by separating the VM context into own direct function ( readTypeRaw() / writeTypeRaw() ) if needed.
	NOTE: IT IS UP TO THE USER TO MAKE SURE THE FLOAT VALUE WRITTEN IS COMPATIBLE WITH THE PS2! Use the FPUUtil static class functions to help with conversion.
	*/
	virtual u32 readWord(const Context_t context);
	virtual void writeWord(const Context_t context, u32 value);
	virtual f32 readFloat(const Context_t context);
	virtual void writeFloat(const Context_t context, f32 value);

	/*
	Gets the mnemonic of this register. Used for debug/logging.
	*/
	const char * getMnemonic() const;

	/*
	Initalise register (set back to default value).
	*/
	virtual void initalise();

protected:
	/*
	Underlying storage for register.
	*/
	union
	{
		u32 UW;
		f32 F;
	};

private:
	/*
	The mnemonic.
	*/
	const std::string mMnemonic;
};

