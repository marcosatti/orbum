#pragma once

#include "Common/Global/Globals.h"

/*
A class containing info as required by a VIFcode, as explained on page 87 of the EE Users Manual.

Designed so it can be reused (use setValue() and then the get functions to extract the field values).

Although a VIF transfer packet is 128-bit long, the VIFcode part is 32-bit.

Bitfield map (relevant only):
- Bits 0-15 (length 16): "IMMEDIATE" (Immediate value, meaning varies accross the CMD field).
- Bits 16-23 (length 8): "NUM" (Amount of data to be written to the VU memory).
- Bits 24-31 (length 8): "CMD" (Operation of the VIF to perform).
*/
class VIFcode_t
{
public:
	/*
	Initalise a VIFcode object optionally with the code value.
	*/
	VIFcode_t();
	VIFcode_t(const u32 & VIFcodeValue);

	/*
	Holder for the code value.
	*/
	u32 mCodeValue;

	/*
	Set the code value.
	*/
	void setValue(const u32 & VIFcodeValue);

	/*
	Get functions for the VIFcode field values.
	*/
	u16 getIMMEDIATE() const;
	u8 getNUM() const;
	u8 getCMD() const;
};
