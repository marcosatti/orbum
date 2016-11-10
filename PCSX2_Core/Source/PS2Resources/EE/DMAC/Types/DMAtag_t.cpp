#include "stdafx.h"

#include "PS2Resources/EE/DMAC/Types/DMAtag_t.h"

DMAtag_t::DMAtag_t()
{
}

DMAtag_t::DMAtag_t(const u128 & dataUnit) :
	mDMADataUnit(dataUnit)
{
}

const u128& DMAtag_t::getDataUnit() const
{
	return mDMADataUnit;
}

void DMAtag_t::setDataUnit(const u128& dataUnit)
{
	mDMADataUnit = dataUnit;
}

u16 DMAtag_t::getQWC() const
{
	return static_cast<u16>(mDMADataUnit.lo & 0xFFFF);
}

u8 DMAtag_t::getPCE() const
{
	return static_cast<u8>((mDMADataUnit.lo >> 26) & 0x3);
}

u8 DMAtag_t::getID() const
{
	return static_cast<u8>((mDMADataUnit.lo >> 28) & 0x7);
}

u8 DMAtag_t::getIRQ() const
{
	return static_cast<u8>((mDMADataUnit.lo >> 31) & 0x1);
}

u32 DMAtag_t::getADDR() const
{
	return static_cast<u32>((mDMADataUnit.lo >> 32) & 0x7FFFFFFF);
}

u8 DMAtag_t::getSPR() const
{
	return static_cast<u8>((mDMADataUnit.lo >> 63) & 0x1);
}
