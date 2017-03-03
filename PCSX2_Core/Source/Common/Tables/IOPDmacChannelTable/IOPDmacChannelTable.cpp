#include "stdafx.h"

#include "Common/Tables/IOPDmacChannelTable/IOPDmacChannelTable.h"

const IOPDmacChannelTable::ChannelProperties_t* IOPDmacChannelTable::getChannelInfo(const int channelIndex)
{
	return &ChannelProperties[channelIndex];
}