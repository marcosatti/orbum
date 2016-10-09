#include "stdafx.h"

#include "Common/Tables/EEDmacTable/EEDmacTable.h"

const EEDmacTable::ChannelProperties_t* EEDmacTable::getChannelInfo(u32 index)
{
	return &ChannelProperties[index];
}
