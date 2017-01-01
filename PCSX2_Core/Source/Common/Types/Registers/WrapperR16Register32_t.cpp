#include "stdafx.h"

#include "Common/Types/Registers/WrapperR16Register32_t.h"
#include "Common/Types/Registers/Register16_t.h"

WrapperR16Register32_t::WrapperR16Register32_t(const std::shared_ptr<Register16_t>& register16) :
	mRegister16(register16)
{
}

WrapperR16Register32_t::WrapperR16Register32_t(const char* mnemonic, const std::shared_ptr<Register16_t>& register16) :
	Register32_t(mnemonic),
	mRegister16(register16)
{
}

WrapperR16Register32_t::~WrapperR16Register32_t()
{
}

u8 WrapperR16Register32_t::readByte(u32 arrayIndex)
{
	throw std::runtime_error("Only Word R/W wrapper calls to Register16_t are allowed.");
}

void WrapperR16Register32_t::writeByte(u32 arrayIndex, u8 value)
{
	throw std::runtime_error("Only Word R/W wrapper calls to Register16_t are allowed.");
}

u16 WrapperR16Register32_t::readHword(u32 arrayIndex)
{
	throw std::runtime_error("Only Word R/W wrapper calls to Register16_t are allowed.");
}

void WrapperR16Register32_t::writeHword(u32 arrayIndex, u16 value)
{
	throw std::runtime_error("Only Word R/W wrapper calls to Register16_t are allowed.");
}

u32 WrapperR16Register32_t::readWord()
{
	return static_cast<u32>(mRegister16->readHword());
}

void WrapperR16Register32_t::writeWord(u32 value)
{
	mRegister16->writeHword(static_cast<u16>(value));
}