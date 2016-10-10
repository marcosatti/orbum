#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/Types/MappedMemory/MappedMemory128_t.h"


MappedMemory128_t::MappedMemory128_t(const char *const mnemonic, const u32 & PS2PhysicalAddress) :
	MappedMemory_t(Constants::NUMBER_BYTES_IN_QWORD, mnemonic, PS2PhysicalAddress)
{
}

MappedMemory128_t::~MappedMemory128_t()
{
}

u8 MappedMemory128_t::readByteU(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedMemory128_t with a size other than Dword. Not allowed.");
}

void MappedMemory128_t::writeByteU(u32 storageIndex, u8 value)
{
	throw std::runtime_error("Tried to access MappedMemory128_t with a size other than Dword. Not allowed.");
}

s8 MappedMemory128_t::readByteS(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedMemory128_t with a size other than Dword. Not allowed.");
}

void MappedMemory128_t::writeByteS(u32 storageIndex, s8 value)
{
	throw std::runtime_error("Tried to access MappedMemory128_t with a size other than Dword. Not allowed.");
}

u16 MappedMemory128_t::readHwordU(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedMemory128_t with a size other than Dword. Not allowed.");
}

void MappedMemory128_t::writeHwordU(u32 storageIndex, u16 value)
{
	throw std::runtime_error("Tried to access MappedMemory128_t with a size other than Dword. Not allowed.");
}

s16 MappedMemory128_t::readHwordS(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedMemory128_t with a size other than Dword. Not allowed.");
}

void MappedMemory128_t::writeHwordS(u32 storageIndex, s16 value)
{
	throw std::runtime_error("Tried to access MappedMemory128_t with a size other than Dword. Not allowed.");
}

u32 MappedMemory128_t::readWordU(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedMemory128_t with a size other than Dword. Not allowed.");
}

void MappedMemory128_t::writeWordU(u32 storageIndex, u32 value)
{
	throw std::runtime_error("Tried to access MappedMemory128_t with a size other than Dword. Not allowed.");
}

s32 MappedMemory128_t::readWordS(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedMemory128_t with a size other than Dword. Not allowed.");
}

void MappedMemory128_t::writeWordS(u32 storageIndex, s32 value)
{
	throw std::runtime_error("Tried to access MappedMemory128_t with a size other than Dword. Not allowed.");
}

u64 MappedMemory128_t::readDwordU(u32 storageIndex)
{
	if (storageIndex != 0 && storageIndex != 8)
		throw std::runtime_error("Tried to access MappedMemory128_t unaligned (storageIndex != [0 or 8]). Not allowed.");
	return MappedMemory_t::readDwordU(storageIndex);
}

void MappedMemory128_t::writeDwordU(u32 storageIndex, u64 value)
{
	if (storageIndex != 0 && storageIndex != 8)
		throw std::runtime_error("Tried to access MappedMemory128_t unaligned (storageIndex != [0 or 8]). Not allowed.");
	MappedMemory_t::writeDwordU(storageIndex, value);
}

s64 MappedMemory128_t::readDwordS(u32 storageIndex)
{
	if (storageIndex != 0 && storageIndex != 8)
		throw std::runtime_error("Tried to access MappedMemory128_t unaligned (storageIndex != [0 or 8]). Not allowed.");
	return MappedMemory_t::readDwordS(storageIndex);
}

void MappedMemory128_t::writeDwordS(u32 storageIndex, s64 value)
{
	if (storageIndex != 0 && storageIndex != 8)
		throw std::runtime_error("Tried to access MappedMemory128_t unaligned (storageIndex != [0 or 8]). Not allowed.");
	MappedMemory_t::writeDwordS(storageIndex, value);
}
