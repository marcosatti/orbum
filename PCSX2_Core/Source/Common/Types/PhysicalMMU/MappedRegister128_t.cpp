#include "stdafx.h"

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/PhysicalMMU/MappedRegister128_t.h"

MappedRegister128_t::MappedRegister128_t(const u32& physicalAddress, const std::shared_ptr<Register128_t> & register128) :
	PhysicalMapped_t(physicalAddress),
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

u8 MappedRegister128_t::readByte(const Context& context, size_t storageIndex)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MappedRegister128_t with unaligned index. Not allowed.");
	return mRegister128->readByte(context, storageIndex / 1);
}

void MappedRegister128_t::writeByte(const Context& context, size_t storageIndex, u8 value)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MappedRegister128_t with unaligned index. Not allowed.");
	mRegister128->writeByte(context, storageIndex / 1, value);
}

u16 MappedRegister128_t::readHword(const Context& context, size_t storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister128_t with unaligned index. Not allowed.");
	return mRegister128->readHword(context, storageIndex / Constants::NUMBER_BYTES_IN_HWORD);
}

void MappedRegister128_t::writeHword(const Context& context, size_t storageIndex, u16 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister128_t with unaligned index. Not allowed.");
	mRegister128->writeHword(context, storageIndex / Constants::NUMBER_BYTES_IN_HWORD, value);
}

u32 MappedRegister128_t::readWord(const Context& context, size_t storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedRegister128_t with unaligned index. Not allowed.");
	return mRegister128->readWord(context, storageIndex / Constants::NUMBER_BYTES_IN_WORD);
}

void MappedRegister128_t::writeWord(const Context& context, size_t storageIndex, u32 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedRegister128_t with unaligned index. Not allowed.");
	mRegister128->writeWord(context, storageIndex / Constants::NUMBER_BYTES_IN_WORD, value);
}

u64 MappedRegister128_t::readDword(const Context& context, size_t storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_DWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister128_t with unaligned index. Not allowed.");
	return mRegister128->readDword(context, storageIndex / Constants::NUMBER_BYTES_IN_DWORD);
}

void MappedRegister128_t::writeDword(const Context& context, size_t storageIndex, u64 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_DWORD != 0)
		throw std::runtime_error("Tried to access MappedRegister128_t with unaligned index. Not allowed.");
	mRegister128->writeDword(context, storageIndex / Constants::NUMBER_BYTES_IN_DWORD, value);
}

u128 MappedRegister128_t::readQword(const Context& context, size_t storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_QWORD != 0)
		throw std::runtime_error("Tried to access MappedFPRegister128_t with unaligned index. Not allowed.");
	return mRegister128->readQword(context);
}

void MappedRegister128_t::writeQword(const Context& context, size_t storageIndex, u128 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_QWORD != 0)
		throw std::runtime_error("Tried to access MappedFPRegister128_t with unaligned index. Not allowed.");
	mRegister128->writeQword(context, value);
}
