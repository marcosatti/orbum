#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/Types/StorageObject/StorageObject128_t.h"


StorageObject128_t::StorageObject128_t(const char *const mnemonic, const u32 & PS2PhysicalAddress) :
	StorageObject_t(Constants::NUMBER_BYTES_IN_QWORD, mnemonic, PS2PhysicalAddress)
{
}

StorageObject128_t::~StorageObject128_t()
{
}

u8 StorageObject128_t::readByteU(u32 storageIndex)
{
	throw std::runtime_error("Tried to access StorageObject128_t with a size other than Dword. Not allowed.");
}

void StorageObject128_t::writeByteU(u32 storageIndex, u8 value)
{
	throw std::runtime_error("Tried to access StorageObject128_t with a size other than Dword. Not allowed.");
}

s8 StorageObject128_t::readByteS(u32 storageIndex)
{
	throw std::runtime_error("Tried to access StorageObject128_t with a size other than Dword. Not allowed.");
}

void StorageObject128_t::writeByteS(u32 storageIndex, s8 value)
{
	throw std::runtime_error("Tried to access StorageObject128_t with a size other than Dword. Not allowed.");
}

u16 StorageObject128_t::readHwordU(u32 storageIndex)
{
	throw std::runtime_error("Tried to access StorageObject128_t with a size other than Dword. Not allowed.");
}

void StorageObject128_t::writeHwordU(u32 storageIndex, u16 value)
{
	throw std::runtime_error("Tried to access StorageObject128_t with a size other than Dword. Not allowed.");
}

s16 StorageObject128_t::readHwordS(u32 storageIndex)
{
	throw std::runtime_error("Tried to access StorageObject128_t with a size other than Dword. Not allowed.");
}

void StorageObject128_t::writeHwordS(u32 storageIndex, s16 value)
{
	throw std::runtime_error("Tried to access StorageObject128_t with a size other than Dword. Not allowed.");
}

u32 StorageObject128_t::readWordU(u32 storageIndex)
{
	throw std::runtime_error("Tried to access StorageObject128_t with a size other than Dword. Not allowed.");
}

void StorageObject128_t::writeWordU(u32 storageIndex, u32 value)
{
	throw std::runtime_error("Tried to access StorageObject128_t with a size other than Dword. Not allowed.");
}

s32 StorageObject128_t::readWordS(u32 storageIndex)
{
	throw std::runtime_error("Tried to access StorageObject128_t with a size other than Dword. Not allowed.");
}

void StorageObject128_t::writeWordS(u32 storageIndex, s32 value)
{
	throw std::runtime_error("Tried to access StorageObject128_t with a size other than Dword. Not allowed.");
}

u64 StorageObject128_t::readDwordU(u32 storageIndex)
{
	if (storageIndex != 0 || storageIndex != 8)
		throw std::runtime_error("Tried to access StorageObject128_t unaligned (storageIndex != [0 or 8]). Not allowed.");
	return StorageObject_t::readDwordU(storageIndex);
}

void StorageObject128_t::writeDwordU(u32 storageIndex, u64 value)
{
	if (storageIndex != 0 || storageIndex != 8)
		throw std::runtime_error("Tried to access StorageObject128_t unaligned (storageIndex != [0 or 8]). Not allowed.");
	StorageObject_t::writeDwordU(storageIndex, value);
}

s64 StorageObject128_t::readDwordS(u32 storageIndex)
{
	if (storageIndex != 0 || storageIndex != 8)
		throw std::runtime_error("Tried to access StorageObject128_t unaligned (storageIndex != [0 or 8]). Not allowed.");
	return StorageObject_t::readDwordS(storageIndex);
}

void StorageObject128_t::writeDwordS(u32 storageIndex, s64 value)
{
	if (storageIndex != 0 || storageIndex != 8)
		throw std::runtime_error("Tried to access StorageObject128_t unaligned (storageIndex != [0 or 8]). Not allowed.");
	StorageObject_t::writeDwordS(storageIndex, value);
}
