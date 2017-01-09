#pragma once

#include "Common/Types/Registers/Register32_t.h"
#include "Common/Types/BitfieldMap32/BitfieldMap32_t.h"

/*
A 32-bit bitfield register, accessed mostly in the same way as a normal register.

Sync'ing with the bitfield map is provided automatically with the write{Byte,Hword,Word} functions, from which you can extract bitfields easily (using getFieldValue()).
Setting bitfields using setFieldValue() will also automatically sync.
*/
class BitfieldRegister32_t : public Register32_t, public BitfieldMap32_t
{
public:
	explicit BitfieldRegister32_t();
	explicit BitfieldRegister32_t(const char * mnemonic);

#if defined(BUILD_DEBUG)
	explicit BitfieldRegister32_t(const char * mnemonic, bool debug); // Turn on/off debugging functionality.
	bool mDebug;

	/*
	Debug logs all bitfield mnemonics with values.
	*/
	void logDebugAllFields();

	u8 readByte(const Context_t& context, u32 arrayIndex) override;
	u16 readHword(const Context_t& context, u32 arrayIndex) override;
	u32 readWord(const Context_t& context) override;
#endif

	virtual ~BitfieldRegister32_t();

	/*
	Function to get a value (bit array) with a specified length at startPos in the word storage object.
	This function is primarily used for getting a bitmask field in a word storage object.
	*/
	u32 getBitRange32(u8 startPosition, u8 bitLength) override;

	/*
	Function to insert a value (bit array) with a specified length at startPos in the word storage object.
	This will overwrite the bits currently set at the startPos to (startPos + length).
	This function is primarily used for setting bit masks in a register.
	Note: If there are more bits set in value than bitLength allows for, the extra bits will not be written.
	*/
	void setBitRange32(u8 startPosition, u8 bitLength, u32 value) override;

	/*
	Override write functions to sync with the bitfield map.
	*/
	void writeByte(const Context_t& context, u32 arrayIndex, u8 value) override;
	void writeHword(const Context_t& context, u32 arrayIndex, u16 value) override;
	void writeWord(const Context_t & context, u32 value) override;

	/*
	Initalise register (set back to default value).
	*/
	void initalise() override;
};

