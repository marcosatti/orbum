#include "Common/Types/Register/MapperHwordWordRegister.hpp"
#include "Common/Types/Register/HwordRegister.hpp"

void MapperHwordWordRegister::initialise()
{
	hword_register->initialise();
}

ubyte MapperHwordWordRegister::read_ubyte(const size_t offset)
{
	throw std::runtime_error("Only Word R/W wrapper calls to HwordRegister are allowed.");
}

void MapperHwordWordRegister::write_ubyte(const size_t offset, const ubyte value)
{
	throw std::runtime_error("Only Word R/W wrapper calls to HwordRegister are allowed.");
}

uhword MapperHwordWordRegister::read_uhword(const size_t offset)
{
	throw std::runtime_error("Only Word R/W wrapper calls to HwordRegister are allowed.");
}

void MapperHwordWordRegister::write_uhword(const size_t offset, const uhword value)
{
	throw std::runtime_error("Only Word R/W wrapper calls to HwordRegister are allowed.");
}

uword MapperHwordWordRegister::read_uword()
{
	return static_cast<uword>(hword_register->read_uhword());
}

void MapperHwordWordRegister::write_uword(const uword value)
{
	hword_register->write_uhword(static_cast<uhword>(value));
}
