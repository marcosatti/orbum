#include "stdafx.h"

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/ByteMMU/MapperRegister8ByteMMU_t.h"

MapperRegister8ByteMMU_t::MapperRegister8ByteMMU_t(const u32 physicalAddress, const std::shared_ptr<Register8_t> & register8) :
	MapperBaseObjectByteMMU_t(physicalAddress),
	mRegister8(register8)
{
}

size_t MapperRegister8ByteMMU_t::getSize()
{
	return 1; // One byte.
}

u8 MapperRegister8ByteMMU_t::readByte(const System_t context, const size_t storageIndex)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MapperRegister8ByteMMU_t with unaligned index. Not allowed.");
	return mRegister8->readByte(context);
}

void MapperRegister8ByteMMU_t::writeByte(const System_t context, const size_t storageIndex, const u8 value)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MapperRegister8ByteMMU_t with unaligned index. Not allowed.");
	mRegister8->writeByte(context, value);
}

u16 MapperRegister8ByteMMU_t::readHword(const System_t context, const size_t storageIndex)
{
	throw std::runtime_error("Tried to access MapperRegister8ByteMMU_t with larger than allowed size. Not allowed.");
}

void MapperRegister8ByteMMU_t::writeHword(const System_t context, const size_t storageIndex, const u16 value)
{
	throw std::runtime_error("Tried to access MapperRegister8ByteMMU_t with larger than allowed size. Not allowed.");
}

u32 MapperRegister8ByteMMU_t::readWord(const System_t context, const size_t storageIndex)
{
	throw std::runtime_error("Tried to access MapperRegister8ByteMMU_t with larger than allowed size. Not allowed.");
}

void MapperRegister8ByteMMU_t::writeWord(const System_t context, const size_t storageIndex, const u32 value)
{
	throw std::runtime_error("Tried to access MapperRegister8ByteMMU_t with larger than allowed size. Not allowed.");
}

u64 MapperRegister8ByteMMU_t::readDword(const System_t context, const size_t storageIndex)
{
	throw std::runtime_error("Tried to access MapperRegister8ByteMMU_t with larger than allowed size. Not allowed.");
}

void MapperRegister8ByteMMU_t::writeDword(const System_t context, const size_t storageIndex, const u64 value)
{
	throw std::runtime_error("Tried to access MapperRegister8ByteMMU_t with larger than allowed size. Not allowed.");
}

u128 MapperRegister8ByteMMU_t::readQword(const System_t context, const size_t storageIndex)
{
	throw std::runtime_error("Tried to access MapperRegister8ByteMMU_t with larger than allowed size. Not allowed.");
}

void MapperRegister8ByteMMU_t::writeQword(const System_t context, const size_t storageIndex, const u128 value)
{
	throw std::runtime_error("Tried to access MapperRegister8ByteMMU_t with larger than allowed size. Not allowed.");
}
