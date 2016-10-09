#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/Util/EECoreMMUUtil/EECoreMMUUtil.h"

u32 EECoreMMUUtil::getVirtualAddressHI19(u32 PS2VirtualAddress)
{
	return (PS2VirtualAddress & 0xFFFFE000) >> 19;
}
