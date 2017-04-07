#pragma once

#include <string>

#include "Common/Global/Globals.h"
#include "Common/Types/System_t.h"
#include "Common/Types/DebugBaseObject_t.h"

/*
Register type and size definitions.
Register8, Register16, Register32, Register64 and Register128 define the base register sizes used thoughout the emulator.
Upon initalisation, set to 0.

These registers are implemented (at core) as a union of the unsigned sums (to the register size) of these types.
However, they should be accessed by the read/write functions instead to account for overriden functionality.

TODO: Check byte order / endianess - it is assumed within the emulator that, for example in a 128-bit register:
Register128_t.UW[0] = bits 0-31.    Least significant bits
Register128_t.UW[1] = bits 32-63.              |
Register128_t.UW[2] = bits 64-95.              ↓
Register128_t.UW[3] = bits 96-127.  Most significant bits

The primary difference between a Register type and Memory type is that registers are accessed by the size index, not by the byte index.
For example, a writeWordU(0, value) will write to the first 0-31 bits, while writeWord(1, value) will write to bits 32-63.
See the Memory type for the counter-example.

Register32 and Register128 also include support for floats (f32's), however these are not checked for the correct format.
Floating point values within the PS2 in general are NOT FULLY IEEE-754 compliant (mostly, but not fully).
In particular, the floats do not support:
- Denormalised numbers.
- Plus and minus infinity.
- 'NaN' (not a number) representation.
Use the FPUUtil static class functions to help with conversion.
*/
class Register128_t : public DebugBaseObject_t
{
public:
	explicit Register128_t(const char * mnemonic, bool debugReads, bool debugWrites); 
	virtual ~Register128_t() = default;

	/*
	Read/write functions to access the register, with subclassed functionality.
	TODO: can get small speedup by separating the VM context into own direct function ( readTypeRaw() / writeTypeRaw() ) if needed.
	*/
	virtual u8 readByte(const System_t context, size_t arrayIndex);
	virtual void writeByte(const System_t context, size_t arrayIndex, u8 value);
	virtual u16 readHword(const System_t context, size_t arrayIndex);
	virtual void writeHword(const System_t context, size_t arrayIndex, u16 value);
	virtual u32 readWord(const System_t context, size_t arrayIndex);
	virtual void writeWord(const System_t context, size_t arrayIndex, u32 value);
	virtual u64 readDword(const System_t context, size_t arrayIndex);
	virtual void writeDword(const System_t context, size_t arrayIndex, u64 value);
	virtual u128 readQword(const System_t context);
	virtual void writeQword(const System_t context, u128 value);
	virtual f32 readFloat(const System_t context, size_t arrayIndex);
	virtual void writeFloat(const System_t context, size_t arrayIndex, f32 value);

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
		u16  UH[Constants::NUMBER_HWORDS_IN_QWORD];
		u8   UB[Constants::NUMBER_BYTES_IN_QWORD];
		f32  F[Constants::NUMBER_WORDS_IN_QWORD];
	};
};