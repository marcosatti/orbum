#include "Common/Types/Register/SizedWordRegister.hpp"

SizedWordRegister::SizedWordRegister(const uword initial_value, const bool read_only) :
	initial_value(initial_value),
	read_only(read_only)
{
}

void SizedWordRegister::initialise()
{
	w = initial_value;
}

ubyte SizedWordRegister::read_ubyte(const size_t offset)
{
#if defined(BUILD_DEBUG)
	if (offset >= NUMBER_BYTES_IN_WORD)
		throw std::runtime_error("Tried to access SizedWordRegister with an invalid offset.");
#endif

	return b[offset];
}

void SizedWordRegister::write_ubyte(const size_t offset, const ubyte value)
{
#if defined(BUILD_DEBUG)
	if (offset >= NUMBER_BYTES_IN_WORD)
		throw std::runtime_error("Tried to access SizedWordRegister with an invalid offset.");
#endif

	if (!read_only)
		b[offset] = value;
}

uhword SizedWordRegister::read_uhword(const size_t offset)
{
#if defined(BUILD_DEBUG)
	if (offset >= NUMBER_HWORDS_IN_WORD)
		throw std::runtime_error("Tried to access SizedWordRegister with an invalid offset.");
#endif

	return h[offset];
}

void SizedWordRegister::write_uhword(const size_t offset, const uhword value)
{
#if defined(BUILD_DEBUG)
	if (offset >= NUMBER_HWORDS_IN_WORD)
		throw std::runtime_error("Tried to access SizedWordRegister with an invalid offset.");
#endif

	if (!read_only)
		h[offset] = value;
}

uword SizedWordRegister::read_uword()
{
	return w;
}

void SizedWordRegister::write_uword(const uword value)
{
	if (!read_only)
		w = value;
}

usize SizedWordRegister::byte_bus_map_size() const
{
	return static_cast<usize>(NUMBER_BYTES_IN_WORD);
}