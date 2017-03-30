#include "stdafx.h"

#include "Common/Tables/IOPDmacChannelTable.h"

#include "Resources/IOP/DMAC/Types/IOPDmacChannels_t.h"

const IOPDmacChannelTable::IOPDmacChannelInfo_t * IOPDmacChannelTable::getInfo(const IOPDmacChannel_t * channel)
{
	return &IOPDMAC_CHANNEL_TABLE[channel->getChannelID()];
}