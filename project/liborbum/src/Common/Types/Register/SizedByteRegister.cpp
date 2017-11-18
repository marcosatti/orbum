#include "Common/Types/Register/SizedByteRegister.hpp"

SizedByteRegister::SizedByteRegister(const ubyte initial_value, const bool read_only) :
	initial_value(initial_value),
	read_only(read_only)
{
}

void SizedByteRegister::initialise()
{
	b = initial_value;
}

ubyte SizedByteRegister::read_ubyte()
{
	return b;
}

void SizedByteRegister::write_ubyte(const ubyte value)
{
	if (!read_only)
		b = value;
}

usize SizedByteRegister::byte_bus_map_size() const
{
	return static_cast<usize>(1);
}