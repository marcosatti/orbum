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
