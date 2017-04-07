#include "stdafx.h"

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/ByteMMU/MapperRegister64ByteMMU_t.h"

MapperRegister64ByteMMU_t::MapperRegister64ByteMMU_t(const u32 physicalAddress, const std::shared_ptr<Register64_t> & register64) :
	MapperBaseObjectByteMMU_t(physicalAddress),
	mRegister64(register64)
{
}

size_t MapperRegister64ByteMMU_t::getSize()
{
	return Constants::NUMBER_BYTES_IN_DWORD;
}

u8 MapperRegister64ByteMMU_t::readByte(const System_t context, size_t storageIndex)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MapperRegister64ByteMMU_t with unaligned index. Not allowed.");
	return mRegister64->readByte(context, storageIndex / 1);
}

void MapperRegister64ByteMMU_t::writeByte(const System_t context, size_t storageIndex, u8 value)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MapperRegister64ByteMMU_t with unaligned index. Not allowed.");
	mRegister64->writeByte(context, storageIndex / 1, value);
}

u16 MapperRegister64ByteMMU_t::readHword(const System_t context, size_t storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MapperRegister64ByteMMU_t with unaligned index. Not allowed.");
	return mRegister64->readHword(context, storageIndex / Constants::NUMBER_BYTES_IN_HWORD);
}

void MapperRegister64ByteMMU_t::writeHword(const System_t context, size_t storageIndex, u16 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MapperRegister64ByteMMU_t with unaligned index. Not allowed.");
	mRegister64->writeHword(context, storageIndex / Constants::NUMBER_BYTES_IN_HWORD, value);
}

u32 MapperRegister64ByteMMU_t::readWord(const System_t context, size_t storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MapperRegister64ByteMMU_t with unaligned index. Not allowed.");
	return mRegister64->readWord(context, storageIndex / Constants::NUMBER_BYTES_IN_WORD);
}

void MapperRegister64ByteMMU_t::writeWord(const System_t context, size_t storageIndex, u32 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MapperRegister64ByteMMU_t with unaligned index. Not allowed.");
	mRegister64->writeWord(context, storageIndex / Constants::NUMBER_BYTES_IN_WORD, value);
}

u64 MapperRegister64ByteMMU_t::readDword(const System_t context, size_t storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_DWORD != 0)
		throw std::runtime_error("Tried to access MapperRegister64ByteMMU_t with unaligned index. Not allowed.");
	return mRegister64->readDword(context);
}

void MapperRegister64ByteMMU_t::writeDword(const System_t context, size_t storageIndex, u64 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_DWORD != 0)
		throw std::runtime_error("Tried to access MapperRegister64ByteMMU_t with unaligned index. Not allowed.");
	mRegister64->writeDword(context, value);
}

u128 MapperRegister64ByteMMU_t::readQword(const System_t context, size_t storageIndex)
{
	throw std::runtime_error("Tried to access MapperRegister64ByteMMU_t with larger than allowed size. Not allowed.");
}

void MapperRegister64ByteMMU_t::writeQword(const System_t context, size_t storageIndex, u128 value)
{
	throw std::runtime_error("Tried to access MapperRegister64ByteMMU_t with larger than allowed size. Not allowed.");
}
