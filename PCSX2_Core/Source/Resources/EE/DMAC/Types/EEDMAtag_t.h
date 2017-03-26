#pragma once

#include "Common/Global/Globals.h"

/*
An EE DMAtag type, as explained on page 58 of the EE Users Manual.
Although a DMAtag is 128-bit long, only the lower 2 x 32-bits are used (referred to as 64-bits in the map data below).
*/
struct EEDMAtag_t
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
	- Bits 0-15 (length 16): "QWC" (Quadword count).
	- Bits 26-27 (length 2): "PCE" (Priority control enable).
	- Bits 28-30 (length 3): "ID" (Tag ID, used as a DMAC instruction).
	- Bits 31 (length 1): "IRQ" (Interrupt request, to the EE Core on IRQ1).
	- Bits 32-62 (length 31): "ADDR" (Address of packet or next tag instruction, due to qword alignment, lower 4 bits are 0's).
	- Bits 63 (length 1): "SPR" (Memory or scratchpad ram (SPR) selection).
	*/
	u16 getQWC() const;
	u8 getPCE() const;
	u8 getID() const;
	u8 getIRQ() const;
	u32 getADDR() const;
	u8 getSPR() const;

#if defined(BUILD_DEBUG)
	/*
	Log debug each of the fields above.
	*/
	void logDebugAllFields() const;
#endif
};


