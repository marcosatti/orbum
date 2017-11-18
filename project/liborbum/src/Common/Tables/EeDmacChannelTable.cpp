#include "Common/Tables/EEDmacChannelTable.h"

#include "Resources/EE/DMAC/Types/EEDmacChannels_t.h"

constexpr EEDmacChannelTable::EEDmacChannelInfo_t EEDmacChannelTable::EEDMAC_CHANNEL_TABLE[Constants::EE::DMAC::NUMBER_DMAC_CHANNELS];
constexpr int EEDmacChannelTable::STS_MAP[4];
constexpr int EEDmacChannelTable::STD_MAP[4];

const EEDmacChannelTable::EEDmacChannelInfo_t * EEDmacChannelTable::getInfo(const EEDmacChannel_t * channel)
{
	return &EEDMAC_CHANNEL_TABLE[channel->channel_id()];
}

const char* EEDmacChannelTable::getMnemonic(const int channelIdx)
{
	return EEDMAC_CHANNEL_TABLE[channelIdx].mMnemonic;
}

int EEDmacChannelTable::getSTSChannelIndex(const int STS)
{
	return STS_MAP[STS];
}

int EEDmacChannelTable::getSTDChannelIndex(const int STD)
{
	return STD_MAP[STD];
}