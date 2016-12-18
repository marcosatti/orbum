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

u8 MappedRegister128_t::readByteU(u32 storageIndex)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MappedRegister128_t with unaligned index. Not allowed.");
	return mRegister128->readByteU(storageIndex / 1);
}

void MappedRegister128_t::writeByteU(u32 storageIndex, u8 value)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MappedRegister128_t with unaligned index. Not allowed.");
	mRegister128->writeByteU(storageIndex / 1, value);
}

s8 MappedRegister128_t::readByteS(u32 storageIndex)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MappedRegister128_t with unaligned index. Not allowed.");
	return mRegister128->readByteS(storageIndex / 1);
}

void MappedRegister128_t::writeByteS(u32 storageIndex, s8 value)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MappedRegister128_t with unaligned index. Not allowed.");
	mRegister128->writeByteS(storageIndex / 1, value);
}

u16 MappedRegister128_t::readHwordU(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister128_t with unaligned index. Not allowed.");
	return mRegister128->readHwordU(storageIndex / Constants::NUMBER_BYTES_IN_HWORD);
}

void MappedRegister128_t::writeHwordU(u32 storageIndex, u16 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister128_t with unaligned index. Not allowed.");
	mRegister128->writeHwordU(storageIndex / Constants::NUMBER_BYTES_IN_HWORD, value);
}

s16 MappedRegister128_t::readHwordS(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister128_t with unaligned index. Not allowed.");
	return mRegister128->readHwordS(storageIndex / Constants::NUMBER_BYTES_IN_HWORD);
}

void MappedRegister128_t::writeHwordS(u32 storageIndex, s16 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister128_t with unaligned index. Not allowed.");
	mRegister128->writeHwordU(storageIndex / Constants::NUMBER_BYTES_IN_HWORD, value);
}

u32 MappedRegister128_t::readWordU(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedRegister128_t with unaligned index. Not allowed.");
	return mRegister128->readWordU(storageIndex / Constants::NUMBER_BYTES_IN_WORD);
}

void MappedRegister128_t::writeWordU(u32 storageIndex, u32 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedRegister128_t with unaligned index. Not allowed.");
	mRegister128->writeWordU(storageIndex / Constants::NUMBER_BYTES_IN_WORD, value);
}

s32 MappedRegister128_t::readWordS(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedRegister128_t with unaligned index. Not allowed.");
	return mRegister128->readWordS(storageIndex / Constants::NUMBER_BYTES_IN_WORD);
}

void MappedRegister128_t::writeWordS(u32 storageIndex, s32 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedRegister128_t with unaligned index. Not allowed.");
	mRegister128->writeWordS(storageIndex / Constants::NUMBER_BYTES_IN_WORD, value);
}

u64 MappedRegister128_t::readDwordU(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_DWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister128_t with unaligned index. Not allowed.");
	return mRegister128->readDwordU(storageIndex / Constants::NUMBER_BYTES_IN_DWORD);
}

void MappedRegister128_t::writeDwordU(u32 storageIndex, u64 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_DWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister128_t with unaligned index. Not allowed.");
	mRegister128->writeDwordU(storageIndex / Constants::NUMBER_BYTES_IN_DWORD, value);
}

s64 MappedRegister128_t::readDwordS(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_DWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister128_t with unaligned index. Not allowed.");
	return mRegister128->readDwordS(storageIndex / Constants::NUMBER_BYTES_IN_DWORD);
}

void MappedRegister128_t::writeDwordS(u32 storageIndex, s64 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_DWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister128_t with unaligned index. Not allowed.");
	mRegister128->writeDwordS(storageIndex / Constants::NUMBER_BYTES_IN_DWORD, value);
}

u128 MappedRegister128_t::readQwordU(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_QWORD != 0)
		throw std::runtime_error("Tried to access MappedFPRegister128_t with unaligned index. Not allowed.");
	return mRegister128->readQwordU();
}

void MappedRegister128_t::writeQwordU(u32 storageIndex, u128 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_QWORD != 0)
		throw std::runtime_error("Tried to access MappedFPRegister128_t with unaligned index. Not allowed.");
	mRegister128->writeQwordU(value);
}
