#pragma once

#include "Common/Global/Globals.h"

/*
An IOP DMAtag type, as explained by wisi and SP193's IOP DMA docs.
Although a DMAtag is 128-bit long, only the lower 2 x 32-bits are used (referred to as 64-bits in the map data below).
*/
struct IOPDMAtag_t
{
	/*
	DMAtag values.
	All functions below extract information from these.
	mValue0 is for bits 0-31.
	mValue1 is for bits 32-63.
	*/
	u32 mValue0;
	u32 mValue1;

	/*
	Get functions for the DMAtag field values.
	Bitfield map (relevant only):
	- Bits 0-23 (length 24): "ADDR" (data memory address).
	- Bits 30 (length 1): "IRQ" (tag interrupt flag).
	- Bits 31 (length 1): "ERT" (tag end transfer flag).
	- Bits 32-55 (length 24): "Length" (transfer amount).
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

};


