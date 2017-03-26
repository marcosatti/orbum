#include "stdafx.h"

#include "Resources/EE/VPU/VIF/Types/VIFcode_t.h"

u16 VIFcode_t::getIMMEDIATE() const
{
	return static_cast<u16>(mValue & 0xFFFF);
}

u8 VIFcode_t::getNUM() const
{
	return static_cast<u8>((mValue >> 16) & 0xFF);
}

u8 VIFcode_t::getCMD() const
{
	return static_cast<u8>((mValue >> 24) & 0xFF);
}
