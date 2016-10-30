#include "stdafx.h"

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/PS2Resources/Types/PhysicalMMU/MappedRegister32_t.h"

MappedRegister32_t::MappedRegister32_t(const char* const mnemonic, const u32& PS2PhysicalAddress, const std::shared_ptr<Register32_t> & register32) :
	mPS2PhysicalAddress(PS2PhysicalAddress),
	mMnemonic(mnemonic),
	mRegister32(register32)
{
}

MappedRegister32_t::~MappedRegister32_t()
{
}

const u32& MappedRegister32_t::getMappedPhysicalAddress() const
{
	return mPS2PhysicalAddress;
}

size_t MappedRegister32_t::getMappedSize()
{
	return Constants::NUMBER_BYTES_IN_WORD;
}

const char* MappedRegister32_t::getMnemonic() const
{
	return mMnemonic.c_str();
}

u8 MappedRegister32_t::readByteU(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedRegister32_t with a size other than Word. Not allowed.");
}

void MappedRegister32_t::writeByteU(u32 storageIndex, u8 value)
{
	throw std::runtime_error("Tried to access MappedRegister32_t with a size other than Word. Not allowed.");
}

s8 MappedRegister32_t::readByteS(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedRegister32_t with a size other than Word. Not allowed.");
}

void MappedRegister32_t::writeByteS(u32 storageIndex, s8 value)
{
	throw std::runtime_error("Tried to access MappedRegister32_t with a size other than Word. Not allowed.");
}

u16 MappedRegister32_t::readHwordU(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedRegister32_t with a size other than Word. Not allowed.");
}

void MappedRegister32_t::writeHwordU(u32 storageIndex, u16 value)
{
	throw std::runtime_error("Tried to access MappedRegister32_t with a size other than Word. Not allowed.");
}

s16 MappedRegister32_t::readHwordS(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedRegister32_t with a size other than Word. Not allowed.");
}

void MappedRegister32_t::writeHwordS(u32 storageIndex, s16 value)
{
	throw std::runtime_error("Tried to access MappedRegister32_t with a size other than Word. Not allowed.");
}

u32 MappedRegister32_t::readWordU(u32 storageIndex)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedRegister32_t unaligned (storageIndex != 0). Not allowed.");
	return mRegister32->readWordU();
}

void MappedRegister32_t::writeWordU(u32 storageIndex, u32 value)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedRegister32_t unaligned (storageIndex != 0). Not allowed.");
	mRegister32->writeWordU(value);
}

s32 MappedRegister32_t::readWordS(u32 storageIndex)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedRegister32_t unaligned (storageIndex != 0). Not allowed.");
	return mRegister32->readWordS();
}

void MappedRegister32_t::writeWordS(u32 storageIndex, s32 value)
{
	if (storageIndex != 0)
		throw std::runtime_error("Tried to access MappedRegister32_t unaligned (storageIndex != 0). Not allowed.");
	mRegister32->writeWordS(value);
}

u64 MappedRegister32_t::readDwordU(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedRegister32_t with a size other than Word. Not allowed.");
}

void MappedRegister32_t::writeDwordU(u32 storageIndex, u64 value)
{
	throw std::runtime_error("Tried to access MappedRegister32_t with a size other than Word. Not allowed.");
}

s64 MappedRegister32_t::readDwordS(u32 storageIndex)
{
	throw std::runtime_error("Tried to access MappedRegister32_t with a size other than Word. Not allowed.");
}

void MappedRegister32_t::writeDwordS(u32 storageIndex, s64 value)
{
	throw std::runtime_error("Tried to access MappedRegister32_t with a size other than Word. Not allowed.");
}