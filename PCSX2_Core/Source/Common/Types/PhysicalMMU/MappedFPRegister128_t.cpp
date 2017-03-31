#include "stdafx.h"

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/PhysicalMMU/MappedFPRegister128_t.h"

MappedFPRegister128_t::MappedFPRegister128_t(const u32 physicalAddress, const std::shared_ptr<FPRegister128_t> & fpRegister128) :
	PhysicalMapped_t(physicalAddress),
	mFPRegister128(fpRegister128)
{
}

size_t MappedFPRegister128_t::getSize()
{
	return Constants::NUMBER_BYTES_IN_QWORD;
}

const char* MappedFPRegister128_t::getMnemonic() const
{
	return mFPRegister128->getMnemonic();
}

u8 MappedFPRegister128_t::readByte(const Context_t context, size_t storageIndex)
{
	throw std::runtime_error("Tried to access MappedFPRegister128_t with smaller than allowed size. Not allowed.");
}

void MappedFPRegister128_t::writeByte(const Context_t context, size_t storageIndex, u8 value)
{
	throw std::runtime_error("Tried to access MappedFPRegister128_t with smaller than allowed size. Not allowed.");
}

u16 MappedFPRegister128_t::readHword(const Context_t context, size_t storageIndex)
{
	throw std::runtime_error("Tried to access MappedFPRegister128_t with smaller than allowed size. Not allowed.");
}

void MappedFPRegister128_t::writeHword(const Context_t context, size_t storageIndex, u16 value)
{
	throw std::runtime_error("Tried to access MappedFPRegister128_t with smaller than allowed size. Not allowed.");
}

u32 MappedFPRegister128_t::readWord(const Context_t context, size_t storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedFPRegister128_t with unaligned index. Not allowed.");
	return mFPRegister128->readWord(context, storageIndex / Constants::NUMBER_BYTES_IN_WORD);
}

void MappedFPRegister128_t::writeWord(const Context_t context, size_t storageIndex, u32 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MappedFPRegister128_t with unaligned index. Not allowed.");
	mFPRegister128->writeWord(context, storageIndex / Constants::NUMBER_BYTES_IN_WORD, value);
}

u64 MappedFPRegister128_t::readDword(const Context_t context, size_t storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_DWORD != 0)
		throw std::runtime_error("Tried to access MappedFPRegister128_t with unaligned index. Not allowed.");
	return mFPRegister128->readDword(context, storageIndex / Constants::NUMBER_BYTES_IN_DWORD);
}

void MappedFPRegister128_t::writeDword(const Context_t context, size_t storageIndex, u64 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_DWORD != 0)
		throw std::runtime_error("Tried to access MappedFPRegister128_t with unaligned index. Not allowed.");
	mFPRegister128->writeDword(context, storageIndex / Constants::NUMBER_BYTES_IN_DWORD, value);
}

u128 MappedFPRegister128_t::readQword(const Context_t context, size_t storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_QWORD != 0)
		throw std::runtime_error("Tried to access MappedFPRegister128_t with unaligned index. Not allowed.");
	return mFPRegister128->readQword(context);
}

void MappedFPRegister128_t::writeQword(const Context_t context, size_t storageIndex, u128 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_QWORD != 0)
		throw std::runtime_error("Tried to access MappedFPRegister128_t with unaligned index. Not allowed.");
	mFPRegister128->writeQword(context, value);
}
