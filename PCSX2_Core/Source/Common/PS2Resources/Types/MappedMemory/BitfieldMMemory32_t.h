#pragma once

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/Types/MappedMemory/MappedMemory32_t.h"
#include "Common/PS2Resources/Types/BitfieldMap32/BitfieldMap32_t.h"

/*
BitfieldMMemory32_t provides read or write access to the underlying 32-bit memory allocated, in terms of bitfields.
This is similar to BitfieldRegister32_t.
It is set to auto sync with the bitfield map every time a field is written to (since they are not heavily related to performance).
*/
class BitfieldMMemory32_t : public MappedMemory32_t, public BitfieldMap32_t
{
public:
	explicit BitfieldMMemory32_t(const char *const mnemonic, const u32 & PS2PhysicalAddress);
	virtual ~BitfieldMMemory32_t();

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
	Override writeWord[U/S] to sync with the bitfield map. WriteWordS calls the unsigned version.
	WriteWordU() can be overriden by sub classes to provide pre processing on the value.
	*/
	void writeWordU(u32 storageIndex, u32 value) override;
	void writeWordS(u32 storageIndex, s32 value) override;

};

