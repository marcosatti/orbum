#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/Types/StorageObject/StorageObject32_t.h"


StorageObject32_t::StorageObject32_t(const char *const mnemonic, const u32 & PS2PhysicalAddress) :
	StorageObject_t(Constants::NUMBER_BYTES_IN_WORD, mnemonic, PS2PhysicalAddress)
{
}

StorageObject32_t::~StorageObject32_t()
{
}

u8 StorageObject32_t::readByteU(u32 storageIndex)
{
	throw std::runtime_error("Tried to access StorageObject32_t with a size other than Word. Not allowed.");
}

void StorageObject32_t::writeByteU(u32 storageIndex, u8 value)
{
	throw std::runtime_error("Tried to access StorageObject32_t with a size other than Word. Not allowed.");
}

s8 StorageObject32_t::readByteS(u32 storageIndex)
{
	throw std::runtime_error("Tried to access StorageObject32_t with a size other than Word. Not allowed.");
}

void StorageObject32_t::writeByteS(u32 storageIndex, s8 value)
{
	throw std::runtime_error("Tried to access StorageObject32_t with a size other than Word. Not allowed.");
}

u16 StorageObject32_t::readHwordU(u32 storageIndex)
{
	throw std::runtime_error("Tried to access StorageObject32_t with a size other than Word. Not allowed.");
}

void StorageObject32_t::writeHwordU(u32 storageIndex, u16 value)
{
	throw std::runtime_error("Tried to access StorageObject32_t with a size other than Word. Not allowed.");
}

s16 StorageObject32_t::readHwordS(u32 storageIndex)
{
	throw std::runtime_error("Tried to access StorageObject32_t with a size other than Word. Not allowed.");
}

void StorageObject32_t::writeHwordS(u32 storageIndex, s16 value)
{
	throw std::runtime_error("Tried to access StorageObject32_t with a size other than Word. Not allowed.");
}

u32 StorageObject32_t::readWordU(u32 storageIndex)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access StorageObject32_t unaligned (storageIndex != 0). Not allowed.");
	return StorageObject_t::readWordU(storageIndex);
}

void StorageObject32_t::writeWordU(u32 storageIndex, u32 value)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access StorageObject32_t unaligned (storageIndex != 0). Not allowed.");
	StorageObject_t::writeWordU(storageIndex, value);
}

s32 StorageObject32_t::readWordS(u32 storageIndex)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access StorageObject32_t unaligned (storageIndex != 0). Not allowed.");
	return StorageObject_t::readWordS(storageIndex);
}

void StorageObject32_t::writeWordS(u32 storageIndex, s32 value)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access StorageObject32_t unaligned (storageIndex != 0). Not allowed.");
	StorageObject_t::writeWordS(storageIndex, value);
}

u64 StorageObject32_t::readDwordU(u32 storageIndex)
{
	throw std::runtime_error("Tried to access StorageObject32_t with a size other than Word. Not allowed.");
}

void StorageObject32_t::writeDwordU(u32 storageIndex, u64 value)
{
	throw std::runtime_error("Tried to access StorageObject32_t with a size other than Word. Not allowed.");
}

s64 StorageObject32_t::readDwordS(u32 storageIndex)
{
	throw std::runtime_error("Tried to access StorageObject32_t with a size other than Word. Not allowed.");
}

void StorageObject32_t::writeDwordS(u32 storageIndex, s64 value)
{
	throw std::runtime_error("Tried to access StorageObject32_t with a size other than Word. Not allowed.");
}

u32 StorageObject32_t::getBitRange32(u8 startPosition, u8 bitLength)
{
	u32 endPos = startPosition + bitLength;
	u32 maskTemp1 = (static_cast<u32>(~0x0) << startPosition);
	u32 maskTemp2 = static_cast<u32>(~0x0);

	// This workaround is needed due to how x86 shifts - it only allows for 0 -> 31 in the shl/shr instruction. Therefore if we want to mask the end bit, maskTemp2 will not be shifted as endPos = 32.
	// I have not accounted for if startPosition >= 32 as it is assumed that the user wouldn't try it.
	if (endPos >= 32) maskTemp2 = 0;
	else maskTemp2 = (maskTemp2 << endPos);

	u32 mask = (maskTemp1 ^ maskTemp2);
	u32 value = (StorageObject_t::readWordU(0) & mask) >> startPosition;
	return value;
}

void StorageObject32_t::setBitRange32(u8 startPosition, u8 bitLength, u32 value)
{
	u32 endPos = startPosition + bitLength;
	u32 maskTemp1 = (static_cast<u32>(~0x0) << startPosition);
	u32 maskTemp2 = static_cast<u32>(~0x0);

	// This workaround is needed due to how x86 shifts - it only allows for 0 -> 31 in the shl/shr instruction. Therefore if we want to mask the end bit, maskTemp2 will not be shifted as endPos = 32.
	// I have not accounted for if startPosition >= 32 as it is assumed that the user wouldn't try it.
	if (endPos >= 32) maskTemp2 = 0;
	else maskTemp2 = (maskTemp2 << endPos);

	u32 mask = (maskTemp1 ^ maskTemp2);
	u32 maskNot = (~mask);
	StorageObject_t::writeWordU(0, (StorageObject_t::readWordU(0) & maskNot));
	value = ((value << startPosition) & mask);
	StorageObject_t::writeWordU(0, (value | StorageObject_t::readWordU(0)));
}
