#include "stdafx.h"

#include "Resources/EE/VPU/VIF/Types/VIFcodeInstruction_t.h"

VIFcodeInstruction_t::VIFcodeInstruction_t(const u32 value) :
	mValue(value)
{
	mInstructionInfo = VIFcodeTable::getInfo(this);
}

u32 VIFcodeInstruction_t::getValue() const
{
	return mValue;
}

u16 VIFcodeInstruction_t::getIMMEDIATE() const
{
	return static_cast<u16>(mValue & 0xFFFF);
}

u8 VIFcodeInstruction_t::getNUM() const
{
	return static_cast<u8>((mValue >> 16) & 0xFF);
}

u8 VIFcodeInstruction_t::getCMD() const
{
	return static_cast<u8>((mValue >> 24) & 0xFF);
}

const VIFcodeTable::VIFcodeInstructionInfo_t * VIFcodeInstruction_t::getInstructionInfo() const
{
	return mInstructionInfo;
}
