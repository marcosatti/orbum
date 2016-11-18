#include "stdafx.h"

#include "Common/Types/Registers/Wrapper16Register32_t.h"
#include "Common/Types/Registers/Register16_t.h"

Wrapper16Register32_t::Wrapper16Register32_t(const std::shared_ptr<Register16_t>& register16) :
	mRegister16(register16)
{
}

Wrapper16Register32_t::Wrapper16Register32_t(const char* mnemonic, const std::shared_ptr<Register16_t>& register16) :
	Register32_t(mnemonic),
	mRegister16(register16)
{
}

Wrapper16Register32_t::~Wrapper16Register32_t()
{
}

u8 Wrapper16Register32_t::readByteU(u32 arrayIndex)
{
	throw std::runtime_error("Only Word R/W wrapper calls to Register16_t are allowed.");
}

void Wrapper16Register32_t::writeByteU(u32 arrayIndex, u8 value)
{
	throw std::runtime_error("Only Word R/W wrapper calls to Register16_t are allowed.");
}

s8 Wrapper16Register32_t::readByteS(u32 arrayIndex)
{
	throw std::runtime_error("Only Word R/W wrapper calls to Register16_t are allowed.");
}

void Wrapper16Register32_t::writeByteS(u32 arrayIndex, s8 value)
{
	throw std::runtime_error("Only Word R/W wrapper calls to Register16_t are allowed.");
}

u16 Wrapper16Register32_t::readHwordU(u32 arrayIndex)
{
	throw std::runtime_error("Only Word R/W wrapper calls to Register16_t are allowed.");
}

void Wrapper16Register32_t::writeHwordU(u32 arrayIndex, u16 value)
{
	throw std::runtime_error("Only Word R/W wrapper calls to Register16_t are allowed.");
}

s16 Wrapper16Register32_t::readHwordS(u32 arrayIndex)
{
	throw std::runtime_error("Only Word R/W wrapper calls to Register16_t are allowed.");
}

void Wrapper16Register32_t::writeHwordS(u32 arrayIndex, s16 value)
{
	throw std::runtime_error("Only Word R/W wrapper calls to Register16_t are allowed.");
}

u32 Wrapper16Register32_t::readWordU()
{
	return static_cast<u32>(mRegister16->readHwordU());
}

void Wrapper16Register32_t::writeWordU(u32 value)
{
	mRegister16->writeHwordU(static_cast<u16>(value));
}

s32 Wrapper16Register32_t::readWordS()
{
	// Additional processing - must keep upper 16-bits all zeros, which does not allow sign-extension.
	return static_cast<s32>(static_cast<u32>(mRegister16->readHwordS()));
}

void Wrapper16Register32_t::writeWordS(s32 value)
{
	mRegister16->writeHwordS(static_cast<s16>(value));
}
