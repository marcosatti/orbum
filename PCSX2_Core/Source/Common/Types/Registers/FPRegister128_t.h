#pragma once

#include <string>

#include "Common/Global/Globals.h"
#include "Common/Types/Context_t.h"

/*
FPRegister128_t is a register type used for VU floating point operations. It is made up of 4 x 32-bit single precision floats, and not intented to be a 128-bit 'float' type.
All FPR's are 32-bit (single precision) according to the documentation, and the floating point array is defined by the 'F' union field below.

See the VU Users Manual page 16 onwards.

Some additional functions are exposed for manipulating the floating point fields (sign, exponent and fraction), which is done by manipulating the u32 UW in the union defined.

The FPU and the floating point values in general are NOT FULLY IEEE-754 compliant (mostly, but not fully).
In particular, the FPU does not support (in comparison to IEEE-754):
 - Denormalised numbers.
 - Plus and minus infinity.
 - 'NaN' (not a number) representation.

When looking through the VU manual etc, the fields / vector components x, y, z, w correspond to F[0], F[1], F[2], F[3] respectively.
*/
class FPRegister128_t
{
public:
	// Initialise union with 0 value.
	explicit FPRegister128_t();
	explicit FPRegister128_t(const char * mnemonic);

	virtual ~FPRegister128_t();

	/*
	Read/write functions to access the register, with subclassed functionality. 
	TODO: can get small speedup by separating the VM context into own direct function ( readTypeRaw() / writeTypeRaw() ) if needed.
	NOTE: IT IS UP TO THE USER TO MAKE SURE THE FLOAT VALUE WRITTEN IS COMPATIBLE WITH THE PS2! Use the FPUUtil static class functions to help with conversion.
	*/
	virtual u32 readWord(const Context_t context, size_t arrayIndex);
	virtual void writeWord(const Context_t context, size_t arrayIndex, u32 value);
	virtual u64 readDword(const Context_t context, size_t arrayIndex);
	virtual void writeDword(const Context_t context, size_t arrayIndex, u64 value);
	virtual u128 readQword(const Context_t context);
	virtual void writeQword(const Context_t context, u128 value);
	virtual f32 readFloat(const Context_t context, size_t arrayIndex);
	virtual void writeFloat(const Context_t context, size_t arrayIndex, f32 value);

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
		u128 UQ;
		u64  UD[Constants::NUMBER_DWORDS_IN_QWORD];
		u32  UW[Constants::NUMBER_WORDS_IN_QWORD];
		f32  F[Constants::NUMBER_WORDS_IN_QWORD];
	};

private:
	/*
	The mnemonic.
	*/
	const std::string mMnemonic;
};

