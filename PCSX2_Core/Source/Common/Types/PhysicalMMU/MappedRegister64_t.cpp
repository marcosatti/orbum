#include "stdafx.h"

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/PhysicalMMU/MappedRegister64_t.h"

MappedRegister64_t::MappedRegister64_t(const u32& physicalAddress, const std::shared_ptr<Register64_t> & register64) :
	PhysicalMapped_t(physicalAddress),
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

u8 MappedRegister64_t::readByte(const Context_t& context, size_t storageIndex)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MappedRegister64_t with unaligned index. Not allowed.");
	return mRegister64->readByte(context, storageIndex / 1);
}

void MappedRegister64_t::writeByte(const Context_t& context, size_t storageIndex, u8 value)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MappedRegister64_t with unaligned index. Not allowed.");
	mRegister64->writeByte(context, storageIndex / 1, value);
}

u16 MappedRegister64_t::readHword(const Context_t& context, size_t storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister64_t with unaligned index. Not allowed.");
	return mRegister64->readHword(context, storageIndex / Constants::NUMBER_BYTES_IN_HWORD);
}

void MappedRegister64_t::writeHword(const Context_t& context, size_t storageIndex, u16 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister64_t with unaligned index. Not allowed.");
	mRegister64->writeHword(context, storageIndex / Constants::NUMBER_BYTES_IN_HWORD, value);
}

u32 MappedRegister64_t::readWord(const Context_t& context, size_t storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedRegister64_t with unaligned index. Not allowed.");
	return mRegister64->readWord(context, storageIndex / Constants::NUMBER_BYTES_IN_WORD);
}

void MappedRegister64_t::writeWord(const Context_t& context, size_t storageIndex, u32 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedRegister64_t with unaligned index. Not allowed.");
	mRegister64->writeWord(context, storageIndex / Constants::NUMBER_BYTES_IN_WORD, value);
}

u64 MappedRegister64_t::readDword(const Context_t& context, size_t storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_DWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister64_t with unaligned index. Not allowed.");
	return mRegister64->readDword(context);
}

void MappedRegister64_t::writeDword(const Context_t& context, size_t storageIndex, u64 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_DWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister64_t with unaligned index. Not allowed.");
	mRegister64->writeDword(context, value);
}

u128 MappedRegister64_t::readQword(const Context_t& context, size_t storageIndex)
{
	throw std::runtime_error("Tried to access MappedRegister64_t with larger than allowed size. Not allowed.");
}

void MappedRegister64_t::writeQword(const Context_t& context, size_t storageIndex, u128 value)
{
	throw std::runtime_error("Tried to access MappedRegister64_t with larger than allowed size. Not allowed.");
}
