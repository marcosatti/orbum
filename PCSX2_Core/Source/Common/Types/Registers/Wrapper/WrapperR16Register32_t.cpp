#include "stdafx.h"

#include "Common/Types/Registers/Wrapper/WrapperR16Register32_t.h"
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

u8 WrapperR16Register32_t::readByte(const Context_t context, size_t arrayIndex)
{
	throw std::runtime_error("Only Word R/W wrapper calls to Register16_t are allowed.");
}

void WrapperR16Register32_t::writeByte(const Context_t context, size_t arrayIndex, u8 value)
{
	throw std::runtime_error("Only Word R/W wrapper calls to Register16_t are allowed.");
}

u16 WrapperR16Register32_t::readHword(const Context_t context, size_t arrayIndex)
{
	throw std::runtime_error("Only Word R/W wrapper calls to Register16_t are allowed.");
}

void WrapperR16Register32_t::writeHword(const Context_t context, size_t arrayIndex, u16 value)
{
	throw std::runtime_error("Only Word R/W wrapper calls to Register16_t are allowed.");
}

u32 WrapperR16Register32_t::readWord(const Context_t context)
{
	return static_cast<u32>(mRegister16->readHword(context));
}

void WrapperR16Register32_t::writeWord(const Context_t context, u32 value)
{
	mRegister16->writeHword(context, static_cast<u16>(value));
}

void WrapperR16Register32_t::initalise()
{
	mRegister16->initalise();
}
