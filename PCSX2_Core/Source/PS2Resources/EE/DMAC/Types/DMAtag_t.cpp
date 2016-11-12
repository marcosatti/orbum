#include "stdafx.h"

#include "PS2Resources/EE/DMAC/Types/DMAtag_t.h"

DMAtag_t::DMAtag_t() :
	mTagValue(0)
{
}

DMAtag_t::DMAtag_t(const u64 & DMAtagValue) :
	mTagValue(DMAtagValue)
{
}

void DMAtag_t::setValue(const u64& DMAtagValue)
{
	mTagValue = DMAtagValue;
}

u16 DMAtag_t::getQWC() const
{
	return static_cast<u16>(mTagValue & 0xFFFF);
}

u8 DMAtag_t::getPCE() const
{
	return static_cast<u8>((mTagValue >> 26) & 0x3);
}

u8 DMAtag_t::getID() const
{
	return static_cast<u8>((mTagValue >> 28) & 0x7);
}

u8 DMAtag_t::getIRQ() const
{
	return static_cast<u8>((mTagValue >> 31) & 0x1);
}

u32 DMAtag_t::getADDR() const
{
	return static_cast<u32>((mTagValue >> 32) & 0x7FFFFFFF);
}

u8 DMAtag_t::getSPR() const
{
	return static_cast<u8>((mTagValue >> 63) & 0x1);
}
