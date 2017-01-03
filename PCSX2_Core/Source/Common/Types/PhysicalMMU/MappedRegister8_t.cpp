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

u8 MappedRegister8_t::readByte(const Context_t& context, u32 storageIndex)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MappedRegister8_t with unaligned index. Not allowed.");
	return mRegister8->readByte(context);
}

void MappedRegister8_t::writeByte(const Context_t& context, u32 storageIndex, u8 value)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MappedRegister8_t with unaligned index. Not allowed.");
	mRegister8->writeByte(context, value);
}

u16 MappedRegister8_t::readHword(const Context_t& context, u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedRegister8_t with larger than allowed size. Not allowed.");
}

void MappedRegister8_t::writeHword(const Context_t& context, u32 storageIndex, u16 value)
{
	throw std::runtime_error("Tried to access MappedRegister8_t with larger than allowed size. Not allowed.");
}

u32 MappedRegister8_t::readWord(const Context_t& context, u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedRegister8_t with larger than allowed size. Not allowed.");
}

void MappedRegister8_t::writeWord(const Context_t& context, u32 storageIndex, u32 value)
{
	throw std::runtime_error("Tried to access MappedRegister8_t with larger than allowed size. Not allowed.");
}

u64 MappedRegister8_t::readDword(const Context_t& context, u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedRegister8_t with larger than allowed size. Not allowed.");
}

void MappedRegister8_t::writeDword(const Context_t& context, u32 storageIndex, u64 value)
{
	throw std::runtime_error("Tried to access MappedRegister8_t with larger than allowed size. Not allowed.");
}

u128 MappedRegister8_t::readQword(const Context_t& context, u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedRegister8_t with larger than allowed size. Not allowed.");
}

void MappedRegister8_t::writeQword(const Context_t& context, u32 storageIndex, u128 value)
{
	throw std::runtime_error("Tried to access MappedRegister8_t with larger than allowed size. Not allowed.");
}
