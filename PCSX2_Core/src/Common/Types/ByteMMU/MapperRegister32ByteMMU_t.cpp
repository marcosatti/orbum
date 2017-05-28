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

u8 MapperRegister32ByteMMU_t::readByte(const Context_t context, const size_t storageIndex)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MapperRegister32ByteMMU_t with unaligned index. Not allowed.");
	return mRegister32->readByte(context, storageIndex / 1);
}

void MapperRegister32ByteMMU_t::writeByte(const Context_t context, const size_t storageIndex, const u8 value)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MapperRegister32ByteMMU_t with unaligned index. Not allowed.");
	mRegister32->writeByte(context, storageIndex / 1, value);
}

u16 MapperRegister32ByteMMU_t::readHword(const Context_t context, const size_t storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MapperRegister32ByteMMU_t with unaligned index. Not allowed.");
	return mRegister32->readHword(context, storageIndex / Constants::NUMBER_BYTES_IN_HWORD);
}

void MapperRegister32ByteMMU_t::writeHword(const Context_t context, const size_t storageIndex, const u16 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MapperRegister32ByteMMU_t with unaligned index. Not allowed.");
	mRegister32->writeHword(context, storageIndex / Constants::NUMBER_BYTES_IN_HWORD, value);
}

u32 MapperRegister32ByteMMU_t::readWord(const Context_t context, const size_t storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MapperRegister32ByteMMU_t with unaligned index. Not allowed.");
	return mRegister32->readWord(context);
}

void MapperRegister32ByteMMU_t::writeWord(const Context_t context, const size_t storageIndex, const u32 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MapperRegister32ByteMMU_t with unaligned index. Not allowed.");
	mRegister32->writeWord(context, value);
}

u64 MapperRegister32ByteMMU_t::readDword(const Context_t context, const size_t storageIndex)
{
	throw std::runtime_error("Tried to access MapperRegister32ByteMMU_t with larger than allowed size. Not allowed.");
}

void MapperRegister32ByteMMU_t::writeDword(const Context_t context, const size_t storageIndex, const u64 value)
{
	throw std::runtime_error("Tried to access MapperRegister32ByteMMU_t with larger than allowed size. Not allowed.");
}

u128 MapperRegister32ByteMMU_t::readQword(const Context_t context, const size_t storageIndex)
{
	throw std::runtime_error("Tried to access MapperRegister32ByteMMU_t with larger than allowed size. Not allowed.");
}

void MapperRegister32ByteMMU_t::writeQword(const Context_t context, const size_t storageIndex, const u128 value)
{
	throw std::runtime_error("Tried to access MapperRegister32ByteMMU_t with larger than allowed size. Not allowed.");
}
