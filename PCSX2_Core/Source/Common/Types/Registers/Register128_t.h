#pragma once

#include <string>

#include "Common/Global/Globals.h"

/*
Register type and size definitions.
Register8, Register16, Register32, Register64 and Register128 define the base register sizes used thoughout the emulator.

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
*/
class Register128_t
{
public:
	// Initialise union with 0 value.
	explicit Register128_t();
	explicit Register128_t(const char * mnemonic);

	virtual ~Register128_t();

	union
	{
		u128 UQ;
		u64  UD[Constants::NUMBER_DWORDS_IN_QWORD];
		u32  UW[Constants::NUMBER_WORDS_IN_QWORD];
		u16  UH[Constants::NUMBER_HWORDS_IN_QWORD];
		u8   UB[Constants::NUMBER_BYTES_IN_QWORD];
	};

	// Functions to access the register value - you should use these functions instead of accessing them directly, as subclassed registers can contain additional check code (for specialised registers).
	virtual u8 readByte(u32 arrayIndex);
	virtual void writeByte(u32 arrayIndex, u8 value);
	virtual u16 readHword(u32 arrayIndex);
	virtual void writeHword(u32 arrayIndex, u16 value);
	virtual u32 readWord(u32 arrayIndex);
	virtual void writeWord(u32 arrayIndex, u32 value);
	virtual u64 readDword(u32 arrayIndex);
	virtual void writeDword(u32 arrayIndex, u64 value);
	virtual u128 readQword();
	virtual void writeQword(u128 value);

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