#include "stdafx.h"

#include "Common/Tables/EEDmacChannelTable.h"

#include "Resources/EE/DMAC/Types/EEDmacChannels_t.h"

const EEDmacChannelTable::EEDmacChannelInfo_t * EEDmacChannelTable::getInfo(const EEDmacChannel_t * channel)
{
	return &EEDMAC_CHANNEL_TABLE[channel->getChannelID()];
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