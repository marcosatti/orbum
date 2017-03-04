#include "stdafx.h"

#include "Resources/IOP/DMAC/Types/IOPDMAtag_t.h"

IOPDMAtag_t::IOPDMAtag_t() :
	mTagValue0(0),
	mTagValue1(0)
{
}

void IOPDMAtag_t::setValue(const u32& DMAtagValue0, const u32& DMAtagValue1)
{
	mTagValue0 = DMAtagValue0;
	mTagValue1 = DMAtagValue1;
}

u32 IOPDMAtag_t::getADDR() const
{
	return static_cast<u32>(mTagValue0 & 0x00FFFFFF);
}

u8 IOPDMAtag_t::getIRQ() const
{
	return static_cast<u8>((mTagValue0 >> 30) & 0x1);
}

u8 IOPDMAtag_t::getERT() const
{
	return static_cast<u8>((mTagValue0 >> 31) & 0x1);
}

u32 IOPDMAtag_t::getLength() const
{
	return static_cast<u32>(mTagValue1 & 0x00FFFFFF);
}