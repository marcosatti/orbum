#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/ByteMMU/MapperRegister128ByteMMU_t.h"

MapperRegister128ByteMMU_t::MapperRegister128ByteMMU_t(const u32 physicalAddress, const std::shared_ptr<Register128_t> & register128) :
	MapperBaseObjectByteMMU_t(physicalAddress),
	mRegister128(register128)
{
}

size_t MapperRegister128ByteMMU_t::getSize()
{
	return Constants::NUMBER_BYTES_IN_QWORD;
}

u8 MapperRegister128ByteMMU_t::readByte(const Context_t context, const size_t storageIndex)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MapperRegister128ByteMMU_t with unaligned index. Not allowed.");
	return mRegister128->readByte(context, storageIndex / 1);
}

void MapperRegister128ByteMMU_t::writeByte(const Context_t context, const size_t storageIndex, const u8 value)
{
	if (storageIndex % 1 != 0)
		throw std::runtime_error("Tried to access MapperRegister128ByteMMU_t with unaligned index. Not allowed.");
	mRegister128->writeByte(context, storageIndex / 1, value);
}

u16 MapperRegister128ByteMMU_t::readHword(const Context_t context, const size_t storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MapperRegister128ByteMMU_t with unaligned index. Not allowed.");
	return mRegister128->readHword(context, storageIndex / Constants::NUMBER_BYTES_IN_HWORD);
}

void MapperRegister128ByteMMU_t::writeHword(const Context_t context, const size_t storageIndex, const u16 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access MapperRegister128ByteMMU_t with unaligned index. Not allowed.");
	mRegister128->writeHword(context, storageIndex / Constants::NUMBER_BYTES_IN_HWORD, value);
}

u32 MapperRegister128ByteMMU_t::readWord(const Context_t context, const size_t storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MapperRegister128ByteMMU_t with unaligned index. Not allowed.");
	return mRegister128->readWord(context, storageIndex / Constants::NUMBER_BYTES_IN_WORD);
}

void MapperRegister128ByteMMU_t::writeWord(const Context_t context, const size_t storageIndex, const u32 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access MapperRegister128ByteMMU_t with unaligned index. Not allowed.");
	mRegister128->writeWord(context, storageIndex / Constants::NUMBER_BYTES_IN_WORD, value);
}

u64 MapperRegister128ByteMMU_t::readDword(const Context_t context, const size_t storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_DWORD != 0)
		throw std::runtime_error("Tried to access MapperRegister128ByteMMU_t with unaligned index. Not allowed.");
	return mRegister128->readDword(context, storageIndex / Constants::NUMBER_BYTES_IN_DWORD);
}

void MapperRegister128ByteMMU_t::writeDword(const Context_t context, const size_t storageIndex, const u64 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_DWORD != 0)
		throw std::runtime_error("Tried to access MapperRegister128ByteMMU_t with unaligned index. Not allowed.");
	mRegister128->writeDword(context, storageIndex / Constants::NUMBER_BYTES_IN_DWORD, value);
}

u128 MapperRegister128ByteMMU_t::readQword(const Context_t context, const size_t storageIndex)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_QWORD != 0)
		throw std::runtime_error("Tried to access MapperRegister128ByteMMU_t with unaligned index. Not allowed.");
	return mRegister128->readQword(context);
}

void MapperRegister128ByteMMU_t::writeQword(const Context_t context, const size_t storageIndex, const u128 value)
{
	if (storageIndex % Constants::NUMBER_BYTES_IN_QWORD != 0)
		throw std::runtime_error("Tried to access MapperRegister128ByteMMU_t with unaligned index. Not allowed.");
	mRegister128->writeQword(context, value);
}
