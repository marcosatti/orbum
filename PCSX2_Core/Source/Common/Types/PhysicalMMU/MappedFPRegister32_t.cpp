#include "stdafx.h"

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/PhysicalMMU/MappedFPRegister32_t.h"

MappedFPRegister32_t::MappedFPRegister32_t(const u32& physicalAddress, const std::shared_ptr<FPRegister32_t> & fpRegister32) :
	PhysicalMapped(physicalAddress),
	mFPRegister32(fpRegister32)
{
}

MappedFPRegister32_t::~MappedFPRegister32_t()
{
}

size_t MappedFPRegister32_t::getSize()
{
	return Constants::NUMBER_BYTES_IN_QWORD;
}

const char* MappedFPRegister32_t::getMnemonic() const
{
	return mFPRegister32->getMnemonic();
}

u8 MappedFPRegister32_t::readByteU(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedFPRegister32_t with smaller than allowed size. Not allowed.");
}

void MappedFPRegister32_t::writeByteU(u32 storageIndex, u8 value)
{
	throw std::runtime_error("Tried to access MappedFPRegister32_t with smaller than allowed size. Not allowed.");
}

s8 MappedFPRegister32_t::readByteS(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedFPRegister32_t with smaller than allowed size. Not allowed.");
}

void MappedFPRegister32_t::writeByteS(u32 storageIndex, s8 value)
{
	throw std::runtime_error("Tried to access MappedFPRegister32_t with smaller than allowed size. Not allowed.");
}

u16 MappedFPRegister32_t::readHwordU(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedFPRegister32_t with smaller than allowed size. Not allowed.");
}

void MappedFPRegister32_t::writeHwordU(u32 storageIndex, u16 value)
{
	throw std::runtime_error("Tried to access MappedFPRegister32_t with smaller than allowed size. Not allowed.");
}

s16 MappedFPRegister32_t::readHwordS(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedFPRegister32_t with smaller than allowed size. Not allowed.");
}

void MappedFPRegister32_t::writeHwordS(u32 storageIndex, s16 value)
{
	throw std::runtime_error("Tried to access MappedFPRegister32_t with smaller than allowed size. Not allowed.");
}

u32 MappedFPRegister32_t::readWordU(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedFPRegister32_t with unaligned index. Not allowed.");
	return mFPRegister32->readWordU();
}

void MappedFPRegister32_t::writeWordU(u32 storageIndex, u32 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedFPRegister32_t with unaligned index. Not allowed.");
	mFPRegister32->writeWordU(value);
}

s32 MappedFPRegister32_t::readWordS(u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedFPRegister32_t with unaligned index. Not allowed.");
	return mFPRegister32->readWordS();
}

void MappedFPRegister32_t::writeWordS(u32 storageIndex, s32 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedFPRegister32_t with unaligned index. Not allowed.");
	mFPRegister32->writeWordS(value);
}

u64 MappedFPRegister32_t::readDwordU(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedFPRegister32_t with larger than allowed size. Not allowed.");
}

void MappedFPRegister32_t::writeDwordU(u32 storageIndex, u64 value)
{
	throw std::runtime_error("Tried to access MappedFPRegister32_t with larger than allowed size. Not allowed.");
}

s64 MappedFPRegister32_t::readDwordS(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedFPRegister32_t with larger than allowed size. Not allowed.");
}

void MappedFPRegister32_t::writeDwordS(u32 storageIndex, s64 value)
{
	throw std::runtime_error("Tried to access MappedFPRegister32_t with larger than allowed size. Not allowed.");
}