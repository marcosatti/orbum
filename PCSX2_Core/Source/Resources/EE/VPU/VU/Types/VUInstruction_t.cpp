#include "stdafx.h"

#include "Resources/EE/VPU/VU/Types/VUInstruction_t.h"

VUInstruction_t::VUInstruction_t(const u32 value) :
	mValue(value)
{
	// mInfo = VUInstructionTable::getInfo(this);
}

u8 VUInstruction_t::getMSB7() const
{
	return static_cast<u8>((mValue >> 25) & 0x7F);
}

u8 VUInstruction_t::getDest() const
{
	return static_cast<u8>((mValue >> 21) & 0xF);
}

u8 VUInstruction_t::getFt() const
{
	return static_cast<u8>((mValue >> 16) & 0x1F);
}

u8 VUInstruction_t::getFs() const
{
	return static_cast<u8>((mValue >> 11) & 0x1F);
}

u8 VUInstruction_t::getFd() const
{
	return static_cast<u8>((mValue >> 6) & 0x1F);
}

u8 VUInstruction_t::getOpcode() const
{
	return static_cast<u8>((mValue) & 0x3F);
}

u8 VUInstruction_t::getBc() const
{
	return static_cast<u8>((mValue) & 0x3);
}

u8 VUInstruction_t::getFtf() const
{
	return static_cast<u8>((mValue >> 23) & 0x3);
}

u8 VUInstruction_t::getFsf() const
{
	return static_cast<u8>((mValue >> 21) & 0x3);
}

u16 VUInstruction_t::getImm11() const
{
	return static_cast<u8>((mValue) & 0x7FF);
}

u32 VUInstruction_t::getImm24() const
{
	return static_cast<u8>((mValue) & 0xFFFFFF);
}

bool VUInstruction_t::testDestField(const int index) const
{
#if defined(BUILD_DEBUG)
	if (index >= 4)
		throw std::runtime_error("VUInstruction_t testDestField index not valid");
#endif
	return ((mValue >> (24 - index)) & 0x1);
}

bool VUInstruction_t::testDestX() const
{
	return ((mValue >> 24) & 0x1);
}

bool VUInstruction_t::testDestY() const
{
	return ((mValue >> 23) & 0x1);
}

bool VUInstruction_t::testDestZ() const
{
	return ((mValue >> 22) & 0x1);
}

bool VUInstruction_t::testDestW() const
{
	return ((mValue >> 21) & 0x1);
}

/*
const VUInstructionTable::VUInstructionInfo_t * VUInstruction_t::getInfo() const
{
return mInfo;
}
*/