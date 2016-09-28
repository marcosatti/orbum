#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/Types/MappedMemory/BitfieldMMemory32_t.h"
#include <Common/Util/MathUtil/MathUtil.h>


BitfieldMMemory32_t::BitfieldMMemory32_t(const char *const mnemonic, const u32 & PS2PhysicalAddress) :
	MappedMemory32_t(mnemonic, PS2PhysicalAddress),
	BitfieldMap32_t(true)
{
}

BitfieldMMemory32_t::~BitfieldMMemory32_t()
{
}

u32 BitfieldMMemory32_t::getBitRange32(u8 startPosition, u8 bitLength)
{
	const u32 rawValue = MappedMemory32_t::readWordU(0);
	return MathUtil::extractMaskedValue32(rawValue, startPosition, bitLength);
}

void BitfieldMMemory32_t::setBitRange32(u8 startPosition, u8 bitLength, u32 value)
{
	const u32 rawValue = MappedMemory32_t::readWordU(0);
	const u32 insertedvalue = MathUtil::insertMaskedValue32(rawValue, value, startPosition, bitLength);
	MappedMemory32_t::writeWordU(0, insertedvalue);
}

void BitfieldMMemory32_t::writeWordU(u32 storageIndex, u32 value)
{
	MappedMemory32_t::writeWordU(storageIndex, value);
	BitfieldMap32_t::syncMapFromMemory();
}

void BitfieldMMemory32_t::writeWordS(u32 storageIndex, s32 value)
{
	writeWordU(storageIndex, static_cast<u32>(value));
}
