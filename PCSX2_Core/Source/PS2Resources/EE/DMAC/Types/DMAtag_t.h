#pragma once

#include "Common/Global/Globals.h"

/*
A class containing info as required by a DMAtag, as explained on page 58 of the EE Users Manual.

Designed so it can be reused (use setDMAtagValue() to extract the field values).

Although a DMAtag is 128-bit long, only the lower 64-bits are used (for the tag). It is compatible with DMADataUnit_t.
It takes in two u64 values as the upper 64-bits may be used in a tag transfer.

Bitfield map (relevant only):
- Bits 0-15 (length 16): "mQWC" (Quadword count).
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
	Initalise a DMAtag object optionally with the data unit parsed.
	*/
	DMAtag_t();
	DMAtag_t(const u128 & dataUnit);

	/*
	Holder for the data unit.
	*/
	u128 mDMADataUnit;

	/*
	Get/Set the data unit value. Allows an object to be reused so memory allocations are not wasted.
	*/
	const u128 & getDataUnit() const;
	void setDataUnit(const u128 & dataUnit);

	/*
	Get functions for the DMA tag field values.
	*/
	u16 getQWC() const;
	u8 getPCE() const;
	u8 getID() const;
	u8 getIRQ() const;
	u32 getADDR() const;
	u8 getSPR() const;

};


