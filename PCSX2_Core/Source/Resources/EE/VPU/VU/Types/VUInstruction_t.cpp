#include "stdafx.h"

#include <stdexcept>

#include "Resources/EE/VPU/VU/Types/VUInstruction_t.h"

VUInstruction_t::VUInstruction_t(const u32 & vuCodeValue) :
	mInstructionValue(vuCodeValue)
{
}

void VUInstruction_t::setValue(const u32& vuCodeValue)
{
	mInstructionValue = vuCodeValue;
}

u8 VUInstruction_t::getMSB7() const
{
	return static_cast<u8>((mInstructionValue >> 25) & 0x7F);
}

u8 VUInstruction_t::getDest() const
{
	return static_cast<u8>((mInstructionValue >> 21) & 0xF);
}

u8 VUInstruction_t::getFt() const
{
	return static_cast<u8>((mInstructionValue >> 16) & 0x1F);
}

u8 VUInstruction_t::getFs() const
{
	return static_cast<u8>((mInstructionValue >> 11) & 0x1F);
}

u8 VUInstruction_t::getFd() const
{
	return static_cast<u8>((mInstructionValue >> 6) & 0x1F);
}

u8 VUInstruction_t::getOpcode() const
{
	return static_cast<u8>((mInstructionValue) & 0x3F);
}

u8 VUInstruction_t::getBc() const
{
	return static_cast<u8>((mInstructionValue) & 0x3);
}

u8 VUInstruction_t::getFtf() const
{
	return static_cast<u8>((mInstructionValue >> 23) & 0x3);
}

u8 VUInstruction_t::getFsf() const
{
	return static_cast<u8>((mInstructionValue >> 21) & 0x3);
}

u16 VUInstruction_t::getImm11() const
{
	return static_cast<u8>((mInstructionValue) & 0x7FF);
}

u32 VUInstruction_t::getImm24() const
{
	return static_cast<u8>((mInstructionValue) & 0xFFFFFF);
}

bool VUInstruction_t::testDestField(const u8& fieldIndex) const
{
#if defined(BUILD_DEBUG)
	if (fieldIndex >= 4)
		throw std::runtime_error("Dest field index not valid");
#endif
	return ((mInstructionValue >> (24 - fieldIndex)) & 0x1);
}

bool VUInstruction_t::testDestX() const
{
	return ((mInstructionValue >> 24) & 0x1);
}

bool VUInstruction_t::testDestY() const
{
	return ((mInstructionValue >> 23) & 0x1);
}

bool VUInstruction_t::testDestZ() const
{
	return ((mInstructionValue >> 22) & 0x1);
}

bool VUInstruction_t::testDestW() const
{
	return ((mInstructionValue >> 21) & 0x1);
}
