#include "stdafx.h"

#include "Common/Tables/EEDmacChannelTable/EEDmacChannelTable.h"

const EEDmacChannelTable::ChannelProperties_t* EEDmacChannelTable::getChannelInfo(const u32 & index)
{
	return &ChannelProperties[index];
}

int EEDmacChannelTable::getSTSChannelIndex(const int STS)
{
	return STS_MAP[STS];
}

int EEDmacChannelTable::getSTDChannelIndex(const int STD)
{
	return STD_MAP[STD];
}
