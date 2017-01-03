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

u8 MappedRegister16_t::readByte(const Context_t& context, u32 storageIndex)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MappedRegister16_t with unaligned index. Not allowed.");
	return mRegister16->readByte(context, storageIndex / 1);
}

void MappedRegister16_t::writeByte(const Context_t& context, u32 storageIndex, u8 value)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MappedRegister16_t with unaligned index. Not allowed.");
	mRegister16->writeByte(context, storageIndex / 1, value);
}

u16 MappedRegister16_t::readHword(const Context_t& context, u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister16_t with unaligned index. Not allowed.");
	return mRegister16->readHword(context);
}

void MappedRegister16_t::writeHword(const Context_t& context, u32 storageIndex, u16 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister16_t with unaligned index. Not allowed.");
	mRegister16->writeHword(context, value);
}

u32 MappedRegister16_t::readWord(const Context_t& context, u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedRegister16_t with larger than allowed size. Not allowed.");
}

void MappedRegister16_t::writeWord(const Context_t& context, u32 storageIndex, u32 value)
{
	throw std::runtime_error("Tried to access MappedRegister16_t with larger than allowed size. Not allowed.");
}

u64 MappedRegister16_t::readDword(const Context_t& context, u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedRegister16_t with larger than allowed size. Not allowed.");
}

void MappedRegister16_t::writeDword(const Context_t& context, u32 storageIndex, u64 value)
{
	throw std::runtime_error("Tried to access MappedRegister16_t with larger than allowed size. Not allowed.");
}

u128 MappedRegister16_t::readQword(const Context_t& context, u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedRegister16_t with larger than allowed size. Not allowed.");
}

void MappedRegister16_t::writeQword(const Context_t& context, u32 storageIndex, u128 value)
{
	throw std::runtime_error("Tried to access MappedRegister16_t with larger than allowed size. Not allowed.");
}
