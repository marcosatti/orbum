#include "stdafx.h"

#include "Common/Types/Register/MapperRegister16Register32_t.h"
#include "Common/Types/Register/Register16_t.h"

MapperRegister16Register32_t::MapperRegister16Register32_t(const std::shared_ptr<Register16_t>& register16) :
	mRegister16(register16)
{
}

MapperRegister16Register32_t::MapperRegister16Register32_t(const char* mnemonic, const std::shared_ptr<Register16_t>& register16) :
	Register32_t(mnemonic),
	mRegister16(register16)
{
}

u8 MapperRegister16Register32_t::readByte(const System_t context, size_t arrayIndex)
{
	throw std::runtime_error("Only Word R/W wrapper calls to Register16_t are allowed.");
}

void MapperRegister16Register32_t::writeByte(const System_t context, size_t arrayIndex, u8 value)
{
	throw std::runtime_error("Only Word R/W wrapper calls to Register16_t are allowed.");
}

u16 MapperRegister16Register32_t::readHword(const System_t context, size_t arrayIndex)
{
	throw std::runtime_error("Only Word R/W wrapper calls to Register16_t are allowed.");
}

void MapperRegister16Register32_t::writeHword(const System_t context, size_t arrayIndex, u16 value)
{
	throw std::runtime_error("Only Word R/W wrapper calls to Register16_t are allowed.");
}

u32 MapperRegister16Register32_t::readWord(const System_t context)
{
	return static_cast<u32>(mRegister16->readHword(context));
}

void MapperRegister16Register32_t::writeWord(const System_t context, u32 value)
{
	mRegister16->writeHword(context, static_cast<u16>(value));
}

void MapperRegister16Register32_t::initalise()
{
	mRegister16->initalise();
}
