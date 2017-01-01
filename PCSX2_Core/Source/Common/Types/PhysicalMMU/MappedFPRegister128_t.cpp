#include "stdafx.h"

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/PhysicalMMU/MappedFPRegister128_t.h"

MappedFPRegister128_t::MappedFPRegister128_t(const u32& physicalAddress, const std::shared_ptr<FPRegister128_t> & fpRegister128) :
	PhysicalMapped(physicalAddress),
	mFPRegister128(fpRegister128)
{
}

MappedFPRegister128_t::~MappedFPRegister128_t()
{
}

size_t MappedFPRegister128_t::getSize()
{
	return Constants::NUMBER_BYTES_IN_QWORD;
}

const char* MappedFPRegister128_t::getMnemonic() const
{
	return mFPRegister128->getMnemonic();
}

u8 MappedFPRegister128_t::readByte(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedFPRegister128_t with smaller than allowed size. Not allowed.");
}

void MappedFPRegister128_t::writeByte(u32 storageIndex, u8 value)
{
	throw std::runtime_error("Tried to access MappedFPRegister128_t with smaller than allowed size. Not allowed.");
}

u16 MappedFPRegister128_t::readHword(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedFPRegister128_t with smaller than allowed size. Not allowed.");
}

void MappedFPRegister128_t::writeHword(u32 storageIndex, u16 value)
{
	throw std::runtime_error("Tried to access MappedFPRegister128_t with smaller than allowed size. Not allowed.");
}

u32 MappedFPRegister128_t::readWord(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedFPRegister128_t with unaligned index. Not allowed.");
	return mFPRegister128->readWord(0);
}

void MappedFPRegister128_t::writeWord(u32 storageIndex, u32 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedFPRegister128_t with unaligned index. Not allowed.");
	mFPRegister128->writeWord(0, value);
}

u64 MappedFPRegister128_t::readDword(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_DWORD != 0)
		throw std::runtime_error("Tried to access MappedFPRegister128_t with unaligned index. Not allowed.");
	return mFPRegister128->readDword(storageIndex / Constants::NUMBER_BYTES_IN_DWORD);
}

void MappedFPRegister128_t::writeDword(u32 storageIndex, u64 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_DWORD != 0)
		throw std::runtime_error("Tried to access MappedFPRegister128_t with unaligned index. Not allowed.");
	mFPRegister128->writeDword(storageIndex / Constants::NUMBER_BYTES_IN_DWORD, value);
}

u128 MappedFPRegister128_t::readQword(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_QWORD != 0)
		throw std::runtime_error("Tried to access MappedFPRegister128_t with unaligned index. Not allowed.");
	return mFPRegister128->readQword();
}

void MappedFPRegister128_t::writeQword(u32 storageIndex, u128 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_QWORD != 0)
		throw std::runtime_error("Tried to access MappedFPRegister128_t with unaligned index. Not allowed.");
	mFPRegister128->writeQword(value);
}
