#include "stdafx.h"

#include "Common/PS2Resources/EE/DMAC/Types/DMAtag_t.h"

DMAtag_t::DMAtag_t(u64 lower, u64 upper) :
	QWC(lower & 0xFFFF),
	PCE((lower >> 26) & 0x3),
	ID((lower >> 28) & 0x7),
	IRQ((lower >> 31) & 0x1),
	ADDR((lower >> 32) & 0x7FFFFFFF),
	SPR((lower >> 63) & 0x1),
	mDataUnit(lower, upper)
{
}

DMAtag_t::DMAtag_t(const DMADataUnit_t & dataUnit) :
	QWC(dataUnit.mDataUnit[0] & 0xFFFF),
	PCE((dataUnit.mDataUnit[0] >> 26) & 0x3),
	ID((dataUnit.mDataUnit[0] >> 28) & 0x7),
	IRQ((dataUnit.mDataUnit[0] >> 31) & 0x1),
	ADDR((dataUnit.mDataUnit[0] >> 32) & 0x7FFFFFFF),
	SPR((dataUnit.mDataUnit[0] >> 63) & 0x1),
	mDataUnit(dataUnit)
{
}

const DMADataUnit_t & DMAtag_t::getDMADataUnit() const
{
	return mDataUnit;
}
