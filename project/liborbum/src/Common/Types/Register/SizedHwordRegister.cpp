#include "Common/Types/Register/SizedHwordRegister.hpp"

SizedHwordRegister::SizedHwordRegister(const uhword initial_value, const bool read_only) :
	initial_value(initial_value),
	read_only(read_only)
{
}

void SizedHwordRegister::initialise()
{
	h = initial_value;
}

ubyte SizedHwordRegister::read_ubyte(const size_t offset)
{
#if defined(BUILD_DEBUG)
	if (offset >= NUMBER_BYTES_IN_HWORD)
		throw std::runtime_error("Tried to access SizedHwordRegister with an invalid offset.");
#endif

	return b[offset];
}

void SizedHwordRegister::write_ubyte(const size_t offset, const ubyte value)
{
#if defined(BUILD_DEBUG)
	if (offset >= NUMBER_BYTES_IN_HWORD)
		throw std::runtime_error("Tried to access SizedHwordRegister with an invalid offset.");
#endif

	if (!read_only)
		b[offset] = value;
}

uhword SizedHwordRegister::read_uhword()
{
	return h;
}

void SizedHwordRegister::write_uhword(const uhword value)
{
	if (!read_only)
		h = value;
}

usize SizedHwordRegister::byte_bus_map_size() const
{
	return static_cast<usize>(NUMBER_BYTES_IN_HWORD);
}