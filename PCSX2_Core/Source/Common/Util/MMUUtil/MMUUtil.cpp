#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/Util/MMUUtil/MMUUtil.h"

u32 MMUUtil::getVirtualAddressHI19(u32 PS2VirtualAddress)
{
	return (PS2VirtualAddress & 0xFFFFE000) >> 19;
}
