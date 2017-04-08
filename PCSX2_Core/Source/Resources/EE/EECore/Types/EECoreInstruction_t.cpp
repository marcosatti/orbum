#include "stdafx.h"

#include "Resources/EE/EECore/Types/EECoreInstruction_t.h"

EECoreInstruction_t::EECoreInstruction_t(const u32 value) :
	MIPSInstruction_t(value)
{
	mInfo = EECoreInstructionTable::getInfo(this);
}

u8 EECoreInstruction_t::getVI() const
{
	return static_cast<u8>(mValue & 0x1);
}

u8 EECoreInstruction_t::getVBC() const
{
	return static_cast<u8>(mValue & 0x3);
}

u8 EECoreInstruction_t::getVDest() const
{
	return (static_cast<u8>(mValue >> 21) & 0xF);
}

u8 EECoreInstruction_t::getVCO() const
{
	return (static_cast<u8>(mValue >> 25) & 0x1);
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EECoreInstruction_t::getInfo() const
{
	return mInfo;
}
