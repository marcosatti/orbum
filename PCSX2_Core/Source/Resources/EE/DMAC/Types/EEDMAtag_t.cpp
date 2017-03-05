#include "stdafx.h"

#include "Resources/EE/DMAC/Types/EEDMAtag_t.h"

EEDMAtag_t::EEDMAtag_t() :
	mTagValue(0)
{
}

const u64& EEDMAtag_t::getValue() const
{
	return mTagValue;
}

void EEDMAtag_t::setValue(const u64& DMAtagValue)
{
	mTagValue = DMAtagValue;
}

u16 EEDMAtag_t::getQWC() const
{
	return static_cast<u16>(mTagValue & 0xFFFF);
}

u8 EEDMAtag_t::getPCE() const
{
	return static_cast<u8>((mTagValue >> 26) & 0x3);
}

u8 EEDMAtag_t::getID() const
{
	return static_cast<u8>((mTagValue >> 28) & 0x7);
}

u8 EEDMAtag_t::getIRQ() const
{
	return static_cast<u8>((mTagValue >> 31) & 0x1);
}

u32 EEDMAtag_t::getADDR() const
{
	return static_cast<u32>((mTagValue >> 32) & 0x7FFFFFFF);
}

u8 EEDMAtag_t::getSPR() const
{
	return static_cast<u8>((mTagValue >> 63) & 0x1);
}

void EEDMAtag_t::logDebugAllFields() const
{
	log(Debug, "EE DMA tag info: QWC = 0x%X, PCE = 0x%X, ID = 0x%X, IRQ = 0x%X, ADDR = 0x%X, SPR = 0x%X.", getQWC(), getPCE(), getID(), getIRQ(), getADDR(), getSPR());
}
