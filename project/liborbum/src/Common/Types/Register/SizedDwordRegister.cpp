#include "Common/Types/Register/SizedDwordRegister.hpp"

SizedDwordRegister::SizedDwordRegister(const udword initial_value, const bool read_only) :
	initial_value(initial_value),
	read_only(read_only)
{
}

void SizedDwordRegister::initialise()
{
	d = initial_value;
}

ubyte SizedDwordRegister::read_ubyte(const size_t offset)
{
#if defined(BUILD_DEBUG)
	if (offset >= NUMBER_BYTES_IN_DWORD)
		throw std::runtime_error("Tried to access SizedDwordRegister with an invalid offset.");
#endif

	return b[offset];
}

void SizedDwordRegister::write_ubyte(const size_t offset, const ubyte value)
{
#if defined(BUILD_DEBUG)
	if (offset >= NUMBER_BYTES_IN_DWORD)
		throw std::runtime_error("Tried to access SizedDwordRegister with an invalid offset.");
#endif

	if (!read_only)
		b[offset] = value;
}

uhword SizedDwordRegister::read_uhword(const size_t offset)
{
#if defined(BUILD_DEBUG)
	if (offset >= NUMBER_HWORDS_IN_DWORD)
		throw std::runtime_error("Tried to access SizedDwordRegister with an invalid offset.");
#endif

	return h[offset];
}

void SizedDwordRegister::write_uhword(const size_t offset, const uhword value)
{
#if defined(BUILD_DEBUG)
	if (offset >= NUMBER_HWORDS_IN_DWORD)
		throw std::runtime_error("Tried to access SizedDwordRegister with an invalid offset.");
#endif

	if (!read_only)
		h[offset] = value;
}

uword SizedDwordRegister::read_uword(const size_t offset)
{
#if defined(BUILD_DEBUG)
	if (offset >= NUMBER_WORDS_IN_DWORD)
		throw std::runtime_error("Tried to access SizedDwordRegister with an invalid offset.");
#endif

	return w[offset];
}

void SizedDwordRegister::write_uword(const size_t offset, const uword value)
{
#if defined(BUILD_DEBUG)
	if (offset >= NUMBER_WORDS_IN_DWORD)
		throw std::runtime_error("Tried to access SizedDwordRegister with an invalid offset.");
#endif

	if (!read_only)
		w[offset] = value;
}

udword SizedDwordRegister::read_udword()
{
	return d;
}

void SizedDwordRegister::write_udword(const udword value)
{
	if (!read_only)
		d = value;
}

usize SizedDwordRegister::byte_bus_map_size() const
{
	return static_cast<usize>(NUMBER_BYTES_IN_DWORD);
}