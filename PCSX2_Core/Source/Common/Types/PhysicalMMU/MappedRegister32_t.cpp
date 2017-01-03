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

u8 MappedRegister32_t::readByte(const Context_t& context, u32 storageIndex)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MappedRegister32_t with unaligned index. Not allowed.");
	return mRegister32->readByte(context, storageIndex / 1);
}

void MappedRegister32_t::writeByte(const Context_t& context, u32 storageIndex, u8 value)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MappedRegister32_t with unaligned index. Not allowed.");
	mRegister32->writeByte(context, storageIndex / 1, value);
}

u16 MappedRegister32_t::readHword(const Context_t& context, u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister32_t with unaligned index. Not allowed.");
	return mRegister32->readHword(context, storageIndex / Constants::NUMBER_BYTES_IN_HWORD);
}

void MappedRegister32_t::writeHword(const Context_t& context, u32 storageIndex, u16 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister32_t with unaligned index. Not allowed.");
	mRegister32->writeHword(context, storageIndex / Constants::NUMBER_BYTES_IN_HWORD, value);
}

u32 MappedRegister32_t::readWord(const Context_t& context, u32 storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedRegister32_t with unaligned index. Not allowed.");
	return mRegister32->readWord(context);
}

void MappedRegister32_t::writeWord(const Context_t& context, u32 storageIndex, u32 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedRegister32_t with unaligned index. Not allowed.");
	mRegister32->writeWord(context, value);
}

u64 MappedRegister32_t::readDword(const Context_t& context, u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedRegister32_t with larger than allowed size. Not allowed.");
}

void MappedRegister32_t::writeDword(const Context_t& context, u32 storageIndex, u64 value)
{
	throw std::runtime_error("Tried to access MappedRegister32_t with larger than allowed size. Not allowed.");
}

u128 MappedRegister32_t::readQword(const Context_t& context, u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedRegister32_t with larger than allowed size. Not allowed.");
}

void MappedRegister32_t::writeQword(const Context_t& context, u32 storageIndex, u128 value)
{
	throw std::runtime_error("Tried to access MappedRegister32_t with larger than allowed size. Not allowed.");
}
