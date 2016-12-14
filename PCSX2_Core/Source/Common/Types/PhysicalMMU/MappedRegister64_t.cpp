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

u8 MappedRegister64_t::readByteU(u32 storageIndex)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MappedRegister64_t with unaligned index. Not allowed.");
	return mRegister64->readByteU(storageIndex / 1);
}

void MappedRegister64_t::writeByteU(u32 storageIndex, u8 value)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MappedRegister64_t with unaligned index. Not allowed.");
	mRegister64->writeByteU(storageIndex / 1, value);
}

s8 MappedRegister64_t::readByteS(u32 storageIndex)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MappedRegister64_t with unaligned index. Not allowed.");
	return mRegister64->readByteS(storageIndex / 1);
}

void MappedRegister64_t::writeByteS(u32 storageIndex, s8 value)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MappedRegister64_t with unaligned index. Not allowed.");
	mRegister64->writeByteS(storageIndex / 1, value);
}

u16 MappedRegister64_t::readHwordU(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister64_t with unaligned index. Not allowed.");
	return mRegister64->readHwordU(storageIndex / Constants::NUMBER_BYTES_IN_HWORD);
}

void MappedRegister64_t::writeHwordU(u32 storageIndex, u16 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister64_t with unaligned index. Not allowed.");
	mRegister64->writeHwordU(storageIndex / Constants::NUMBER_BYTES_IN_HWORD, value);
}

s16 MappedRegister64_t::readHwordS(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister64_t with unaligned index. Not allowed.");
	return mRegister64->readHwordS(storageIndex / Constants::NUMBER_BYTES_IN_HWORD);
}

void MappedRegister64_t::writeHwordS(u32 storageIndex, s16 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister64_t with unaligned index. Not allowed.");
	mRegister64->writeHwordU(storageIndex / Constants::NUMBER_BYTES_IN_HWORD, value);
}

u32 MappedRegister64_t::readWordU(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedRegister64_t with unaligned index. Not allowed.");
	return mRegister64->readWordU(storageIndex / Constants::NUMBER_BYTES_IN_WORD);
}

void MappedRegister64_t::writeWordU(u32 storageIndex, u32 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedRegister64_t with unaligned index. Not allowed.");
	mRegister64->writeWordU(storageIndex / Constants::NUMBER_BYTES_IN_WORD, value);
}

s32 MappedRegister64_t::readWordS(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedRegister64_t with unaligned index. Not allowed.");
	return mRegister64->readWordS(storageIndex / Constants::NUMBER_BYTES_IN_WORD);
}

void MappedRegister64_t::writeWordS(u32 storageIndex, s32 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedRegister64_t with unaligned index. Not allowed.");
	mRegister64->writeWordS(storageIndex / Constants::NUMBER_BYTES_IN_WORD, value);
}

u64 MappedRegister64_t::readDwordU(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_DWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister64_t with unaligned index. Not allowed.");
	return mRegister64->readDwordU();
}

void MappedRegister64_t::writeDwordU(u32 storageIndex, u64 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_DWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister64_t with unaligned index. Not allowed.");
	mRegister64->writeDwordU(value);
}

s64 MappedRegister64_t::readDwordS(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_DWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister64_t with unaligned index. Not allowed.");
	return mRegister64->readDwordS();
}

void MappedRegister64_t::writeDwordS(u32 storageIndex, s64 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_DWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister64_t with unaligned index. Not allowed.");
	mRegister64->writeDwordS(value);
}