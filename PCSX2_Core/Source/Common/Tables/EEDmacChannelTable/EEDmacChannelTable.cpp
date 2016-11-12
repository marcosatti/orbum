#include "stdafx.h"

#include "Common/Tables/EEDmacChannelTable/EEDmacChannelTable.h"

const EEDmacChannelTable::ChannelProperties_t* EEDmacChannelTable::getChannelInfo(u32 index)
{
	return &ChannelProperties[index];
}

const u8& EEDmacChannelTable::getSTSChannelIndex(const u8 & STS)
{
	return STS_MAP[STS];
}

const u8& EEDmacChannelTable::getSTDChannelIndex(const u8 & STD)
{
	return STD_MAP[STD];
}
