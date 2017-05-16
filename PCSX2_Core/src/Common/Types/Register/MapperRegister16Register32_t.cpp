#include "Common/Types/Register/MapperRegister16Register32_t.h"
#include "Common/Types/Register/Register16_t.h"

MapperRegister16Register32_t::MapperRegister16Register32_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const std::shared_ptr<Register16_t>& register16) :
	Register32_t(mnemonic, debugReads, debugWrites),
	mRegister16(register16)
{
}

u8 MapperRegister16Register32_t::readByte(const System_t context, const size_t arrayIndex)
{
	throw std::runtime_error("Only Word R/W wrapper calls to Register16_t are allowed.");
}

void MapperRegister16Register32_t::writeByte(const System_t context, const size_t arrayIndex, const u8 value)
{
	throw std::runtime_error("Only Word R/W wrapper calls to Register16_t are allowed.");
}

u16 MapperRegister16Register32_t::readHword(const System_t context, const size_t arrayIndex)
{
	throw std::runtime_error("Only Word R/W wrapper calls to Register16_t are allowed.");
}

void MapperRegister16Register32_t::writeHword(const System_t context, const size_t arrayIndex, const u16 value)
{
	throw std::runtime_error("Only Word R/W wrapper calls to Register16_t are allowed.");
}

u32 MapperRegister16Register32_t::readWord(const System_t context)
{
	return static_cast<u32>(mRegister16->readHword(context));
}

void MapperRegister16Register32_t::writeWord(const System_t context, const u32 value)
{
	mRegister16->writeHword(context, static_cast<u16>(value));
}

void MapperRegister16Register32_t::initialise()
{
	mRegister16->initialise();
}
