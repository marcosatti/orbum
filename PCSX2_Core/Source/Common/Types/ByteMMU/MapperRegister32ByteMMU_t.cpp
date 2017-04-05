#include "stdafx.h"

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/ByteMMU/MapperRegister32ByteMMU_t.h"

MapperRegister32ByteMMU_t::MapperRegister32ByteMMU_t(const u32 physicalAddress, const std::shared_ptr<Register32_t> & register32) :
	MapperBaseObjectByteMMU_t(physicalAddress),
	mRegister32(register32)
{
}

size_t MapperRegister32ByteMMU_t::getSize()
{
	return Constants::NUMBER_BYTES_IN_WORD;
}

const char* MapperRegister32ByteMMU_t::getMnemonic() const
{
	return mRegister32->getMnemonic();
}

u8 MapperRegister32ByteMMU_t::readByte(const System_t context, size_t storageIndex)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MapperRegister32ByteMMU_t with unaligned index. Not allowed.");
	return mRegister32->readByte(context, storageIndex / 1);
}

void MapperRegister32ByteMMU_t::writeByte(const System_t context, size_t storageIndex, u8 value)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MapperRegister32ByteMMU_t with unaligned index. Not allowed.");
	mRegister32->writeByte(context, storageIndex / 1, value);
}

u16 MapperRegister32ByteMMU_t::readHword(const System_t context, size_t storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MapperRegister32ByteMMU_t with unaligned index. Not allowed.");
	return mRegister32->readHword(context, storageIndex / Constants::NUMBER_BYTES_IN_HWORD);
}

void MapperRegister32ByteMMU_t::writeHword(const System_t context, size_t storageIndex, u16 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MapperRegister32ByteMMU_t with unaligned index. Not allowed.");
	mRegister32->writeHword(context, storageIndex / Constants::NUMBER_BYTES_IN_HWORD, value);
}

u32 MapperRegister32ByteMMU_t::readWord(const System_t context, size_t storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MapperRegister32ByteMMU_t with unaligned index. Not allowed.");
	return mRegister32->readWord(context);
}

void MapperRegister32ByteMMU_t::writeWord(const System_t context, size_t storageIndex, u32 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MapperRegister32ByteMMU_t with unaligned index. Not allowed.");
	mRegister32->writeWord(context, value);
}

u64 MapperRegister32ByteMMU_t::readDword(const System_t context, size_t storageIndex)
{
	throw std::runtime_error("Tried to access MapperRegister32ByteMMU_t with larger than allowed size. Not allowed.");
}

void MapperRegister32ByteMMU_t::writeDword(const System_t context, size_t storageIndex, u64 value)
{
	throw std::runtime_error("Tried to access MapperRegister32ByteMMU_t with larger than allowed size. Not allowed.");
}

u128 MapperRegister32ByteMMU_t::readQword(const System_t context, size_t storageIndex)
{
	throw std::runtime_error("Tried to access MapperRegister32ByteMMU_t with larger than allowed size. Not allowed.");
}

void MapperRegister32ByteMMU_t::writeQword(const System_t context, size_t storageIndex, u128 value)
{
	throw std::runtime_error("Tried to access MapperRegister32ByteMMU_t with larger than allowed size. Not allowed.");
}
