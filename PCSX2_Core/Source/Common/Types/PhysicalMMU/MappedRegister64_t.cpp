#include "stdafx.h"

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/PhysicalMMU/MappedRegister64_t.h"

MappedRegister64_t::MappedRegister64_t(const u32& physicalAddress, const std::shared_ptr<Register64_t> & register64) :
	PhysicalMapped(physicalAddress),
	mRegister64(register64)
{
}

MappedRegister64_t::~MappedRegister64_t()
{
}

size_t MappedRegister64_t::getSize()
{
	return Constants::NUMBER_BYTES_IN_DWORD;
}

const char* MappedRegister64_t::getMnemonic() const
{
	return mRegister64->getMnemonic();
}

u8 MappedRegister64_t::readByte(u32 storageIndex)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MappedRegister64_t with unaligned index. Not allowed.");
	return mRegister64->readByte(storageIndex / 1);
}

void MappedRegister64_t::writeByte(u32 storageIndex, u8 value)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MappedRegister64_t with unaligned index. Not allowed.");
	mRegister64->writeByte(storageIndex / 1, value);
}

u16 MappedRegister64_t::readHword(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister64_t with unaligned index. Not allowed.");
	return mRegister64->readHword(storageIndex / Constants::NUMBER_BYTES_IN_HWORD);
}

void MappedRegister64_t::writeHword(u32 storageIndex, u16 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister64_t with unaligned index. Not allowed.");
	mRegister64->writeHword(storageIndex / Constants::NUMBER_BYTES_IN_HWORD, value);
}

u32 MappedRegister64_t::readWord(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedRegister64_t with unaligned index. Not allowed.");
	return mRegister64->readWord(storageIndex / Constants::NUMBER_BYTES_IN_WORD);
}

void MappedRegister64_t::writeWord(u32 storageIndex, u32 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedRegister64_t with unaligned index. Not allowed.");
	mRegister64->writeWord(storageIndex / Constants::NUMBER_BYTES_IN_WORD, value);
}

u64 MappedRegister64_t::readDword(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_DWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister64_t with unaligned index. Not allowed.");
	return mRegister64->readDword();
}

void MappedRegister64_t::writeDword(u32 storageIndex, u64 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_DWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister64_t with unaligned index. Not allowed.");
	mRegister64->writeDword(value);
}

u128 MappedRegister64_t::readQword(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedRegister64_t with larger than allowed size. Not allowed.");
}

void MappedRegister64_t::writeQword(u32 storageIndex, u128 value)
{
	throw std::runtime_error("Tried to access MappedRegister64_t with larger than allowed size. Not allowed.");
}
