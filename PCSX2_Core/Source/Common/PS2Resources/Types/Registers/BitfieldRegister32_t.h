#pragma once

#include "Common/PS2Resources/Types/Registers/Register32_t.h"
#include "Common/PS2Resources/Types/BitfieldMap32/BitfieldMap32_t.h"

/*
A 32-bit bitfield register, accessed mostly in the same way as a normal register.

Sync'ing with the bitfield map is provided though the get/setRegisterValue() functions, from which you can extract bitfields easily.
It is not automatically done as registers need to be accessed often and manipulated for a while before interfacing with other hardware.
*/
class BitfieldRegister32_t : public Register32_t, public BitfieldMap32_t
{
public:
	explicit BitfieldRegister32_t();

	/*
	Gets the combined bitfield value from the individual fields. Also syncs Register32_t.UW to reflect the same value.
	*/
	virtual u32 getRegisterValue();

	/*
	Sets the Register32_t.UW register value to reflect the parsed value, and updates all of the registered fields to reflect the bitfield values from Register32_t.UW.
	*/
	virtual void setRegisterValue(const u32 & value);

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
};

