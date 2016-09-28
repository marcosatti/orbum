#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/Types/MappedMemory/MappedMemory32_t.h"


MappedMemory32_t::MappedMemory32_t(const char *const mnemonic, const u32 & PS2PhysicalAddress) :
	MappedMemory_t(Constants::NUMBER_BYTES_IN_WORD, mnemonic, PS2PhysicalAddress)
{
}

MappedMemory32_t::~MappedMemory32_t()
{
}

u8 MappedMemory32_t::readByteU(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedMemory32_t with a size other than Word. Not allowed.");
}

void MappedMemory32_t::writeByteU(u32 storageIndex, u8 value)
{
	throw std::runtime_error("Tried to access MappedMemory32_t with a size other than Word. Not allowed.");
}

s8 MappedMemory32_t::readByteS(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedMemory32_t with a size other than Word. Not allowed.");
}

void MappedMemory32_t::writeByteS(u32 storageIndex, s8 value)
{
	throw std::runtime_error("Tried to access MappedMemory32_t with a size other than Word. Not allowed.");
}

u16 MappedMemory32_t::readHwordU(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedMemory32_t with a size other than Word. Not allowed.");
}

void MappedMemory32_t::writeHwordU(u32 storageIndex, u16 value)
{
	throw std::runtime_error("Tried to access MappedMemory32_t with a size other than Word. Not allowed.");
}

s16 MappedMemory32_t::readHwordS(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedMemory32_t with a size other than Word. Not allowed.");
}

void MappedMemory32_t::writeHwordS(u32 storageIndex, s16 value)
{
	throw std::runtime_error("Tried to access MappedMemory32_t with a size other than Word. Not allowed.");
}

u32 MappedMemory32_t::readWordU(u32 storageIndex)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedMemory32_t unaligned (storageIndex != 0). Not allowed.");
	return MappedMemory_t::readWordU(storageIndex);
}

void MappedMemory32_t::writeWordU(u32 storageIndex, u32 value)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedMemory32_t unaligned (storageIndex != 0). Not allowed.");
	MappedMemory_t::writeWordU(storageIndex, value);
}

s32 MappedMemory32_t::readWordS(u32 storageIndex)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedMemory32_t unaligned (storageIndex != 0). Not allowed.");
	return MappedMemory_t::readWordS(storageIndex);
}

void MappedMemory32_t::writeWordS(u32 storageIndex, s32 value)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedMemory32_t unaligned (storageIndex != 0). Not allowed.");
	MappedMemory_t::writeWordS(storageIndex, value);
}

u64 MappedMemory32_t::readDwordU(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedMemory32_t with a size other than Word. Not allowed.");
}

void MappedMemory32_t::writeDwordU(u32 storageIndex, u64 value)
{
	throw std::runtime_error("Tried to access MappedMemory32_t with a size other than Word. Not allowed.");
}

s64 MappedMemory32_t::readDwordS(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedMemory32_t with a size other than Word. Not allowed.");
}

void MappedMemory32_t::writeDwordS(u32 storageIndex, s64 value)
{
	throw std::runtime_error("Tried to access MappedMemory32_t with a size other than Word. Not allowed.");
}