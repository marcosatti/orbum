#include "Common/Tables/IOPDmacChannelTable.h"

#include "Resources/Iop/Dmac/IopDmacChannels.hpp"

constexpr IOPDmacChannelTable::IOPDmacChannelInfo_t IOPDmacChannelTable::IOPDMAC_CHANNEL_TABLE[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS];

const IOPDmacChannelTable::IOPDmacChannelInfo_t * IOPDmacChannelTable::getInfo(const IopDmacChannel * channel)
{
	return &IOPDMAC_CHANNEL_TABLE[channel->channel_id()];
}

const char* IOPDmacChannelTable::getMnemonic(const int channelIdx)
{
	return IOPDMAC_CHANNEL_TABLE[channelIdx].mMnemonic;
}
