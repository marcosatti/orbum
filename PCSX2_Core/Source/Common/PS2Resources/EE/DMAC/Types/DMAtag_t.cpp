#include "stdafx.h"

#include "Common/PS2Resources/EE/DMAC/Types/DMAtag_t.h"

DMAtag_t::DMAtag_t(u64 value) :
	QWC(value & 0xFFFF),
	PCE((value >> 26) & 0x3),
	ID((value >> 28) & 0x7),
	IRQ((value >> 31) & 0x1),
	ADDR((value >> 32) & 0x7FFFFFFF),
	SPR((value >> 63) & 0x1)
{
}
