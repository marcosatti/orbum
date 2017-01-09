#include "stdafx.h"

#include "Common/Tables/IOPDmacChannelTable/IOPDmacChannelTable.h"

const IOPDmacChannelTable::ChannelProperties_t* IOPDmacChannelTable::getChannelInfo(u32 index)
{
	return &ChannelProperties[index];
}