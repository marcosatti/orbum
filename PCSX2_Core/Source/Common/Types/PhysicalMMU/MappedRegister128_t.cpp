#include "stdafx.h"

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/PhysicalMMU/MappedRegister128_t.h"

MappedRegister128_t::MappedRegister128_t(const u32& physicalAddress, const std::shared_ptr<Register128_t> & register128) :
	PhysicalMapped(physicalAddress),
	mRegister128(register128)
{
}

MappedRegister128_t::~MappedRegister128_t()
{
}

size_t MappedRegister128_t::getSize()
{
	return Constants::NUMBER_BYTES_IN_QWORD;
}

const char* MappedRegister128_t::getMnemonic() const
{
	return mRegister128->getMnemonic();
}

u8 MappedRegister128_t::readByte(u32 storageIndex)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MappedRegister128_t with unaligned index. Not allowed.");
	return mRegister128->readByte(storageIndex / 1);
}

void MappedRegister128_t::writeByte(u32 storageIndex, u8 value)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MappedRegister128_t with unaligned index. Not allowed.");
	mRegister128->writeByte(storageIndex / 1, value);
}

u16 MappedRegister128_t::readHword(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister128_t with unaligned index. Not allowed.");
	return mRegister128->readHword(storageIndex / Constants::NUMBER_BYTES_IN_HWORD);
}

void MappedRegister128_t::writeHword(u32 storageIndex, u16 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister128_t with unaligned index. Not allowed.");
	mRegister128->writeHword(storageIndex / Constants::NUMBER_BYTES_IN_HWORD, value);
}

u32 MappedRegister128_t::readWord(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedRegister128_t with unaligned index. Not allowed.");
	return mRegister128->readWord(storageIndex / Constants::NUMBER_BYTES_IN_WORD);
}

void MappedRegister128_t::writeWord(u32 storageIndex, u32 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedRegister128_t with unaligned index. Not allowed.");
	mRegister128->writeWord(storageIndex / Constants::NUMBER_BYTES_IN_WORD, value);
}

u64 MappedRegister128_t::readDword(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_DWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister128_t with unaligned index. Not allowed.");
	return mRegister128->readDword(storageIndex / Constants::NUMBER_BYTES_IN_DWORD);
}

void MappedRegister128_t::writeDword(u32 storageIndex, u64 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_DWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister128_t with unaligned index. Not allowed.");
	mRegister128->writeDword(storageIndex / Constants::NUMBER_BYTES_IN_DWORD, value);
}

u128 MappedRegister128_t::readQword(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_QWORD != 0)
		throw std::runtime_error("Tried to access MappedFPRegister128_t with unaligned index. Not allowed.");
	return mRegister128->readQword();
}

void MappedRegister128_t::writeQword(u32 storageIndex, u128 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_QWORD != 0)
		throw std::runtime_error("Tried to access MappedFPRegister128_t with unaligned index. Not allowed.");
	mRegister128->writeQword(value);
}
