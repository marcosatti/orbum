#include "stdafx.h"

#include "Resources/IOP/DMAC/Types/IOPDMAtag_t.h"

u32 IOPDMAtag_t::getADDR() const
{
	return static_cast<u32>(mValue0 & 0x00FFFFFF);
}

u8 IOPDMAtag_t::getIRQ() const
{
	return static_cast<u8>((mValue0 >> 30) & 0x1);
}

u8 IOPDMAtag_t::getERT() const
{
	return static_cast<u8>((mValue0 >> 31) & 0x1);
}

u32 IOPDMAtag_t::getLength() const
{
	return static_cast<u32>(mValue1 & 0x00FFFFFF);
}

void IOPDMAtag_t::logDebugAllFields() const
{
	log(Debug, "IOP DMA tag info: Length = 0x%X, IRQ = 0x%X, ERT = 0x%x, ADDR = 0x%X.", getLength(), getIRQ(), getERT(), getADDR());
}
