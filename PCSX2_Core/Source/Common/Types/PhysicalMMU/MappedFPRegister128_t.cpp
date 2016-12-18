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

u8 MappedFPRegister128_t::readByteU(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedFPRegister128_t with smaller than allowed size. Not allowed.");
}

void MappedFPRegister128_t::writeByteU(u32 storageIndex, u8 value)
{
	throw std::runtime_error("Tried to access MappedFPRegister128_t with smaller than allowed size. Not allowed.");
}

s8 MappedFPRegister128_t::readByteS(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedFPRegister128_t with smaller than allowed size. Not allowed.");
}

void MappedFPRegister128_t::writeByteS(u32 storageIndex, s8 value)
{
	throw std::runtime_error("Tried to access MappedFPRegister128_t with smaller than allowed size. Not allowed.");
}

u16 MappedFPRegister128_t::readHwordU(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedFPRegister128_t with smaller than allowed size. Not allowed.");
}

void MappedFPRegister128_t::writeHwordU(u32 storageIndex, u16 value)
{
	throw std::runtime_error("Tried to access MappedFPRegister128_t with smaller than allowed size. Not allowed.");
}

s16 MappedFPRegister128_t::readHwordS(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedFPRegister128_t with smaller than allowed size. Not allowed.");
}

void MappedFPRegister128_t::writeHwordS(u32 storageIndex, s16 value)
{
	throw std::runtime_error("Tried to access MappedFPRegister128_t with smaller than allowed size. Not allowed.");
}

u32 MappedFPRegister128_t::readWordU(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedFPRegister128_t with unaligned index. Not allowed.");
	return mFPRegister128->readWordU(0);
}

void MappedFPRegister128_t::writeWordU(u32 storageIndex, u32 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedFPRegister128_t with unaligned index. Not allowed.");
	mFPRegister128->writeWordU(0, value);
}

s32 MappedFPRegister128_t::readWordS(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedFPRegister128_t with unaligned index. Not allowed.");
	return mFPRegister128->readWordS(0);
}

void MappedFPRegister128_t::writeWordS(u32 storageIndex, s32 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedFPRegister128_t with unaligned index. Not allowed.");
	mFPRegister128->writeWordS(0, value);
}

u64 MappedFPRegister128_t::readDwordU(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_DWORD != 0)
		throw std::runtime_error("Tried to access MappedFPRegister128_t with unaligned index. Not allowed.");
	return mFPRegister128->readDwordU(storageIndex / Constants::NUMBER_BYTES_IN_DWORD);
}

void MappedFPRegister128_t::writeDwordU(u32 storageIndex, u64 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_DWORD != 0)
		throw std::runtime_error("Tried to access MappedFPRegister128_t with unaligned index. Not allowed.");
	mFPRegister128->writeDwordU(storageIndex / Constants::NUMBER_BYTES_IN_DWORD, value);
}

s64 MappedFPRegister128_t::readDwordS(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_DWORD != 0)
		throw std::runtime_error("Tried to access MappedFPRegister128_t with unaligned index. Not allowed.");
	return mFPRegister128->readDwordS(storageIndex / Constants::NUMBER_BYTES_IN_DWORD);
}

void MappedFPRegister128_t::writeDwordS(u32 storageIndex, s64 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_DWORD != 0)
		throw std::runtime_error("Tried to access MappedFPRegister128_t with unaligned index. Not allowed.");
	mFPRegister128->writeDwordS(storageIndex / Constants::NUMBER_BYTES_IN_DWORD, value);
}

u128 MappedFPRegister128_t::readQwordU(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_QWORD != 0)
		throw std::runtime_error("Tried to access MappedFPRegister128_t with unaligned index. Not allowed.");
	return mFPRegister128->readQwordU();
}

void MappedFPRegister128_t::writeQwordU(u32 storageIndex, u128 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_QWORD != 0)
		throw std::runtime_error("Tried to access MappedFPRegister128_t with unaligned index. Not allowed.");
	mFPRegister128->writeQwordU(value);
}
