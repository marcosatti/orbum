#include "stdafx.h"

#include "PS2Resources/EE/EECore/Types/EECoreInstruction_t.h"

u8 EECoreInstruction_t::getVI() const
{
	return static_cast<u8>(mInstructionValue & 0x1);
}

u8 EECoreInstruction_t::getVBC() const
{
	return static_cast<u8>(mInstructionValue & 0x3);
}

u8 EECoreInstruction_t::getVDest() const
{
	return (static_cast<u8>(mInstructionValue >> 21) & 0xF);
}

u8 EECoreInstruction_t::getVCO() const
{
	return (static_cast<u8>(mInstructionValue >> 25) & 0x1);
}
