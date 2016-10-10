#include "stdafx.h"

#include "Common/Tables/EEDmacTable/EEDmacTable.h"

const EEDmacTable::ChannelProperties_t* EEDmacTable::getChannelInfo(u32 index)
{
	return &ChannelProperties[index];
}

const u8& EEDmacTable::getSTSChannelIndex(const u8 & STS)
{
	return STS_MAP[STS];
}

const u8& EEDmacTable::getSTDChannelIndex(const u8 & STD)
{
	return STD_MAP[STD];
}
