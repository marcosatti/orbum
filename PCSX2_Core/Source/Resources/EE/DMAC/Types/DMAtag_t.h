#pragma once

#include "Common/Global/Globals.h"

/*
A class containing info as required by a DMAtag, as explained on page 58 of the EE Users Manual.

Designed so it can be reused (use setValue() and then the get functions to extract the field values).

Although a DMAtag is 128-bit long, only the lower 64-bits are used (for the tag).

Bitfield map (relevant only):
- Bits 0-15 (length 16): "QWC" (Quadword count).
- Bits 26-27 (length 2): "PCE" (Priority control enable).
- Bits 28-30 (length 3): "ID" (Tag ID, used as a DMAC instruction).
- Bits 31 (length 1): "IRQ" (Interrupt request, to the EE Core on IRQ1).
- Bits 32-62 (length 31): "ADDR" (Address of packet or next tag instruction, due to qword alignment, lower 4 bits are 0's).
- Bits 63 (length 1): "SPR" (Memory or scratchpad ram (SPR) selection).
*/
class DMAtag_t
{
public:
	/*
	Initalise a DMAtag object optionally with the tag value.
	*/
	DMAtag_t();
	DMAtag_t(const u64 & DMAtagValue);

	/*
	Holder for the tag value.
	*/
	u64 mTagValue;

	/*
	Set the tag value.
	*/
	void setValue(const u64 & DMAtagValue);

	/*
	Get functions for the DMAtag field values.
	*/
	u16 getQWC() const;
	u8 getPCE() const;
	u8 getID() const;
	u8 getIRQ() const;
	u32 getADDR() const;
	u8 getSPR() const;

};


