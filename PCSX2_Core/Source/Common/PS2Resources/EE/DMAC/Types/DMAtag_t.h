#pragma once

#include "Common/Global/Globals.h"

/*
A struct containing info as required by a DMAtag, as explained on page 58 of the EE Users Manual.
A constructor is supplied which can take in a u64 value, and produce a compatible DMAtag.

Although a DMAtag is 128-bit long, only the lower 64-bits are used.

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
	explicit DMAtag_t(u64 value);

	u16 QWC;
	u8 PCE;
	u8 ID;
	u8 IRQ;
	u32 ADDR;
	u8 SPR;
};


