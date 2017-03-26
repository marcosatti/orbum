#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/Types/MIPSInstruction/MIPSInstruction_t.h"

u8 MIPSInstruction_t::getOpcode() const
{
	return static_cast<u8>((mValue >> 26) & 0x3F);
}

u8 MIPSInstruction_t::getRRs() const
{
	return static_cast<u8>((mValue >> 21) & 0x1F);
}

u8 MIPSInstruction_t::getRRt() const
{
	return static_cast<u8>((mValue >> 16) & 0x1F);
}

u8 MIPSInstruction_t::getRRd() const
{
	return static_cast<u8>((mValue >> 11) & 0x1F);
}

u8 MIPSInstruction_t::getRShamt() const
{
	return static_cast<u8>((mValue >> 6) & 0x1F);
}

u8 MIPSInstruction_t::getRFunct() const
{
	return static_cast<u8>((mValue) & 0x3F);
}

u32 MIPSInstruction_t::getJRegionAddress() const
{
	return (mValue & 0x03ffffff);
}

u8 MIPSInstruction_t::getIRs() const
{
	return static_cast<u8>((mValue >> 21) & 0x1F);
}

u8 MIPSInstruction_t::getIRt() const
{
	return static_cast<u8>((mValue >> 16) & 0x1F);
}

u16 MIPSInstruction_t::getIImmU() const
{
	return static_cast<u16>(mValue & 0xFFFF);
}

s16 MIPSInstruction_t::getIImmS() const
{
	return (static_cast<s16>(mValue) & 0xFFFF);
}

u8 MIPSInstruction_t::getIImmSignBit() const
{
	return static_cast<u8>((mValue >> 15) & 0x1);
}

u16 MIPSInstruction_t::getITrapCode() const
{
	return static_cast<u16>((getIImmU() >> 6) & 0x3FF);
}