#include "stdafx.h"

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/PhysicalMMU/MappedRegister8_t.h"

MappedRegister8_t::MappedRegister8_t(const u32& physicalAddress, const std::shared_ptr<Register8_t> & register8) :
	PhysicalMapped(physicalAddress),
	mRegister8(register8)
{
}

MappedRegister8_t::~MappedRegister8_t()
{
}

size_t MappedRegister8_t::getSize()
{
	return 1; // One byte.
}

const char* MappedRegister8_t::getMnemonic() const
{
	return mRegister8->getMnemonic();
}

u8 MappedRegister8_t::readByteU(u32 storageIndex)
{
	// Technically should not happen as due to the way its mapped storageIndex will always be 0.
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedRegister8_t with unaligned index. Not allowed.");
	return mRegister8->readByteU();
}

void MappedRegister8_t::writeByteU(u32 storageIndex, u8 value)
{
	// Technically should not happen as due to the way its mapped storageIndex will always be 0.
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedRegister8_t with unaligned index. Not allowed.");
	mRegister8->writeByteU(value);
}

s8 MappedRegister8_t::readByteS(u32 storageIndex)
{
	// Technically should not happen as due to the way its mapped storageIndex will always be 0.
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedRegister8_t with unaligned index. Not allowed.");
	return mRegister8->readByteS();
}

void MappedRegister8_t::writeByteS(u32 storageIndex, s8 value)
{
	// Technically should not happen as due to the way its mapped storageIndex will always be 0.
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedRegister8_t with unaligned index. Not allowed."); 
	mRegister8->writeByteS(value);
}

u16 MappedRegister8_t::readHwordU(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedRegister8_t with larger than allowed size. Not allowed.");
}

void MappedRegister8_t::writeHwordU(u32 storageIndex, u16 value)
{
	throw std::runtime_error("Tried to access MappedRegister8_t with larger than allowed size. Not allowed.");
}

s16 MappedRegister8_t::readHwordS(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedRegister8_t with larger than allowed size. Not allowed.");
}

void MappedRegister8_t::writeHwordS(u32 storageIndex, s16 value)
{
	throw std::runtime_error("Tried to access MappedRegister8_t with larger than allowed size. Not allowed.");
}

u32 MappedRegister8_t::readWordU(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedRegister8_t with larger than allowed size. Not allowed.");
}

void MappedRegister8_t::writeWordU(u32 storageIndex, u32 value)
{
	throw std::runtime_error("Tried to access MappedRegister8_t with larger than allowed size. Not allowed.");
}

s32 MappedRegister8_t::readWordS(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedRegister8_t with larger than allowed size. Not allowed.");
}

void MappedRegister8_t::writeWordS(u32 storageIndex, s32 value)
{
	throw std::runtime_error("Tried to access MappedRegister8_t with larger than allowed size. Not allowed.");
}
u64 MappedRegister8_t::readDwordU(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedRegister8_t with larger than allowed size. Not allowed.");
}

void MappedRegister8_t::writeDwordU(u32 storageIndex, u64 value)
{
	throw std::runtime_error("Tried to access MappedRegister8_t with larger than allowed size. Not allowed.");
}

s64 MappedRegister8_t::readDwordS(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedRegister8_t with larger than allowed size. Not allowed.");
}

void MappedRegister8_t::writeDwordS(u32 storageIndex, s64 value)
{
	throw std::runtime_error("Tried to access MappedRegister8_t with larger than allowed size. Not allowed.");
}