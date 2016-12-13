#include "stdafx.h"

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/PhysicalMMU/MappedRegister16_t.h"

MappedRegister16_t::MappedRegister16_t(const u32& physicalAddress, const std::shared_ptr<Register16_t> & register16) :
	PhysicalMapped(physicalAddress),
	mRegister16(register16)
{
}

MappedRegister16_t::~MappedRegister16_t()
{
}

size_t MappedRegister16_t::getSize()
{
	return Constants::NUMBER_BYTES_IN_HWORD;
}

const char* MappedRegister16_t::getMnemonic() const
{
	return mRegister16->getMnemonic();
}

u8 MappedRegister16_t::readByteU(u32 storageIndex)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedRegister16_t with unaligned index. Not allowed.");
	return mRegister16->readByteU(0);
}

void MappedRegister16_t::writeByteU(u32 storageIndex, u8 value)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedRegister16_t with unaligned index. Not allowed.");
	mRegister16->writeByteU(0, value);
}

s8 MappedRegister16_t::readByteS(u32 storageIndex)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedRegister16_t with unaligned index. Not allowed.");
	return mRegister16->readByteS(0);
}

void MappedRegister16_t::writeByteS(u32 storageIndex, s8 value)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedRegister16_t with unaligned index. Not allowed.");
	mRegister16->writeByteS(0, value);
}

u16 MappedRegister16_t::readHwordU(u32 storageIndex)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedRegister16_t with unaligned index. Not allowed.");
	return mRegister16->readHwordU();
}

void MappedRegister16_t::writeHwordU(u32 storageIndex, u16 value)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedRegister16_t with unaligned index. Not allowed.");
	mRegister16->writeHwordU(value);
}

s16 MappedRegister16_t::readHwordS(u32 storageIndex)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedRegister16_t with unaligned index. Not allowed.");
	return mRegister16->readHwordS();
}

void MappedRegister16_t::writeHwordS(u32 storageIndex, s16 value)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedRegister16_t with unaligned index. Not allowed.");
	mRegister16->writeHwordU(value);
}

u32 MappedRegister16_t::readWordU(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedRegister16_t with larger than allowed size. Not allowed.");
}

void MappedRegister16_t::writeWordU(u32 storageIndex, u32 value)
{
	throw std::runtime_error("Tried to access MappedRegister16_t with larger than allowed size. Not allowed.");
}

s32 MappedRegister16_t::readWordS(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedRegister16_t with larger than allowed size. Not allowed.");
}

void MappedRegister16_t::writeWordS(u32 storageIndex, s32 value)
{
	throw std::runtime_error("Tried to access MappedRegister16_t with larger than allowed size. Not allowed.");
}
u64 MappedRegister16_t::readDwordU(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedRegister16_t with larger than allowed size. Not allowed.");
}

void MappedRegister16_t::writeDwordU(u32 storageIndex, u64 value)
{
	throw std::runtime_error("Tried to access MappedRegister16_t with larger than allowed size. Not allowed.");
}

s64 MappedRegister16_t::readDwordS(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedRegister16_t with larger than allowed size. Not allowed.");
}

void MappedRegister16_t::writeDwordS(u32 storageIndex, s64 value)
{
	throw std::runtime_error("Tried to access MappedRegister16_t with larger than allowed size. Not allowed.");
}