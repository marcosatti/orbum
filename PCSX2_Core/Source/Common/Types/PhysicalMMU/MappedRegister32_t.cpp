#include "stdafx.h"

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/PhysicalMMU/MappedRegister32_t.h"

MappedRegister32_t::MappedRegister32_t(const u32& physicalAddress, const std::shared_ptr<Register32_t> & register32) :
	PhysicalMapped(physicalAddress),
	mRegister32(register32)
{
}

MappedRegister32_t::~MappedRegister32_t()
{
}

size_t MappedRegister32_t::getSize()
{
	return Constants::NUMBER_BYTES_IN_WORD;
}

const char* MappedRegister32_t::getMnemonic() const
{
	return mRegister32->getMnemonic();
}

u8 MappedRegister32_t::readByteU(u32 storageIndex)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MappedRegister32_t with unaligned index. Not allowed.");
	return mRegister32->readByteU(storageIndex / 1);
}

void MappedRegister32_t::writeByteU(u32 storageIndex, u8 value)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MappedRegister32_t with unaligned index. Not allowed.");
	mRegister32->writeByteU(storageIndex / 1, value);
}

s8 MappedRegister32_t::readByteS(u32 storageIndex)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MappedRegister32_t with unaligned index. Not allowed.");
	return mRegister32->readByteS(storageIndex / 1);
}

void MappedRegister32_t::writeByteS(u32 storageIndex, s8 value)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MappedRegister32_t with unaligned index. Not allowed.");
	mRegister32->writeByteS(storageIndex / 1, value);
}

u16 MappedRegister32_t::readHwordU(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister32_t with unaligned index. Not allowed.");
	return mRegister32->readHwordU(storageIndex / Constants::NUMBER_BYTES_IN_HWORD);
}

void MappedRegister32_t::writeHwordU(u32 storageIndex, u16 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister32_t with unaligned index. Not allowed.");
	mRegister32->writeHwordU(storageIndex / Constants::NUMBER_BYTES_IN_HWORD, value);
}

s16 MappedRegister32_t::readHwordS(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister32_t with unaligned index. Not allowed.");
	return mRegister32->readHwordS(storageIndex / Constants::NUMBER_BYTES_IN_HWORD);
}

void MappedRegister32_t::writeHwordS(u32 storageIndex, s16 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister32_t with unaligned index. Not allowed.");
	mRegister32->writeHwordU(storageIndex / Constants::NUMBER_BYTES_IN_HWORD, value);
}

u32 MappedRegister32_t::readWordU(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedRegister32_t with unaligned index. Not allowed.");
	return mRegister32->readWordU();
}

void MappedRegister32_t::writeWordU(u32 storageIndex, u32 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedRegister32_t with unaligned index. Not allowed.");
	mRegister32->writeWordU(value);
}

s32 MappedRegister32_t::readWordS(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedRegister32_t with unaligned index. Not allowed.");
	return mRegister32->readWordS();
}

void MappedRegister32_t::writeWordS(u32 storageIndex, s32 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedRegister32_t with unaligned index. Not allowed.");
	mRegister32->writeWordS(value);
}
u64 MappedRegister32_t::readDwordU(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedRegister32_t with larger than allowed size. Not allowed.");
}

void MappedRegister32_t::writeDwordU(u32 storageIndex, u64 value)
{
	throw std::runtime_error("Tried to access MappedRegister32_t with larger than allowed size. Not allowed.");
}

s64 MappedRegister32_t::readDwordS(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedRegister32_t with larger than allowed size. Not allowed.");
}

void MappedRegister32_t::writeDwordS(u32 storageIndex, s64 value)
{
	throw std::runtime_error("Tried to access MappedRegister32_t with larger than allowed size. Not allowed.");
}