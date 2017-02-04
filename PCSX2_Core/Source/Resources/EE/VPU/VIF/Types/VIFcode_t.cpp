#include "stdafx.h"

#include "Resources/EE/VPU/VIF/Types/VIFcode_t.h"


VIFcode_t::VIFcode_t() :
	mCodeValue(0)
{
}

VIFcode_t::VIFcode_t(const u32 & VIFcodeValue) :
	mCodeValue(VIFcodeValue)
{
}

void VIFcode_t::setValue(const u32 & VIFcodeValue)
{
	mCodeValue = VIFcodeValue;
}

u16 VIFcode_t::getIMMEDIATE() const
{
	return static_cast<u16>(mCodeValue & 0xFFFF);
}

u8 VIFcode_t::getNUM() const
{
	return static_cast<u8>((mCodeValue >> 16) & 0xFF);
}

u8 VIFcode_t::getCMD() const
{
	return static_cast<u8>((mCodeValue >> 24) & 0xFF);
}
