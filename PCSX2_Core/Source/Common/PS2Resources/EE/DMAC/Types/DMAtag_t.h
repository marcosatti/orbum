#pragma once

#include "Common/Global/Globals.h"
#include "Common/PS2Resources/EE/DMAC/Types/DMADataUnit_t.h"

/*
A struct containing info as required by a DMAtag, as explained on page 58 of the EE Users Manual.

Although a DMAtag is 128-bit long, only the lower 64-bits are used (for the tag). It is compatible with DMADataUnit_t.
It takes in two u64 values as the upper 64-bits may be used in a tag transfer.

Bitfield map (relevant only):
- Bits 0-15 (length 16): "QWC" (Quadword count).
- Bits 26-27 (length 2): "PCE" (Priority control enable).
- Bits 28-30 (length 3): "ID" (Tag ID, used as a DMAC instruction).
- Bits 31 (length 1): "IRQ" (Interrupt request, to the EE Core on IRQ1).
- Bits 32-62 (length 31): "ADDR" (Address of packet or next tag instruction, due to qword alignment, lower 4 bits are 0's).
- Bits 63 (length 1): "SPR" (Memory or scratchpad ram (SPR) selection).
*/

struct DMAtag_t
{
	explicit DMAtag_t(u64 lower, u64 upper);
	explicit DMAtag_t(const DMADataUnit_t & dataUnit);

	const u16 QWC;
	const u8 PCE;
	const u8 ID;
	const u8 IRQ;
	const u32 ADDR;
	const u8 SPR;

	const DMADataUnit_t mDataUnit;
	DMADataUnit_t getDMADataUnit() const;
};


