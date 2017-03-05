#pragma once

#include "Common/Global/Globals.h"

/*
A class containing info as required by a DMAtag, as explained by wisi and SP193's IOP DMA docs.

Designed so it can be reused (use setValue() and then the get functions to extract the field values).

Although a DMAtag is 128-bit long, only the lower 2 x 32-bits are used (referred to as 64-bits in the map data below).

Bitfield map (relevant only):
- Bits 0-23 (length 24): "ADDR" (data memory address).
- Bits 30 (length 1): "IRQ" (tag interrupt flag).
- Bits 31 (length 1): "ERT" (tag end transfer flag).
- Bits 32-55 (length 24): "Length" (transfer amount).
*/
class IOPDMAtag_t
{
public:
	IOPDMAtag_t();
	/*
	Set the tag value.
	DMAtagValue0 should be the first word (LSB) of the tag, DMAtagValue1 should be the next word of the tag.
	*/
	void setValue(const u32 & DMAtagValue0, const u32 & DMAtagValue1);

	/*
	Get functions for the DMAtag field values.
	*/
	u32 getADDR() const;
	u8 getIRQ() const;
	u8 getERT() const;
	u32 getLength() const;

#if defined(BUILD_DEBUG)
	/*
	Log debug each of the fields above.
	*/
	void logDebugAllFields() const;
#endif

private:
	/*
	Holder for the tag value.
	*/
	u32 mTagValue0;
	u32 mTagValue1;
};


