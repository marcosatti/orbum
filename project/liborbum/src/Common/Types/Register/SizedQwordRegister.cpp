#include "Common/Types/Register/SizedQwordRegister.hpp"

SizedQwordRegister::SizedQwordRegister(const uqword initial_value, const bool read_only) :
	initial_value(initial_value),
	read_only(read_only)
{
}

void SizedQwordRegister::initialise()
{
	q = initial_value;
}

ubyte SizedQwordRegister::read_ubyte(const size_t offset)
{
#if defined(BUILD_DEBUG)
	if (offset >= NUMBER_BYTES_IN_QWORD)
		throw std::runtime_error("Tried to access SizedQwordRegister with an invalid offset.");
#endif

	return b[offset];
}

void SizedQwordRegister::write_ubyte(const size_t offset, const ubyte value)
{
#if defined(BUILD_DEBUG)
	if (offset >= NUMBER_BYTES_IN_QWORD)
		throw std::runtime_error("Tried to access SizedQwordRegister with an invalid offset.");
#endif

	if (!read_only)
		b[offset] = value;
}

uhword SizedQwordRegister::read_uhword(const size_t offset)
{
#if defined(BUILD_DEBUG)
	if (offset >= NUMBER_HWORDS_IN_QWORD)
		throw std::runtime_error("Tried to access SizedQwordRegister with an invalid offset.");
#endif

	return h[offset];
}

void SizedQwordRegister::write_uhword(const size_t offset, const uhword value)
{
#if defined(BUILD_DEBUG)
	if (offset >= NUMBER_HWORDS_IN_QWORD)
		throw std::runtime_error("Tried to access SizedQwordRegister with an invalid offset.");
#endif

	if (!read_only)
		h[offset] = value;
}

uword SizedQwordRegister::read_uword(const size_t offset)
{
#if defined(BUILD_DEBUG)
	if (offset >= NUMBER_WORDS_IN_QWORD)
		throw std::runtime_error("Tried to access SizedQwordRegister with an invalid offset.");
#endif

	return w[offset];
}

void SizedQwordRegister::write_uword(const size_t offset, const uword value)
{
#if defined(BUILD_DEBUG)
	if (offset >= NUMBER_WORDS_IN_QWORD)
		throw std::runtime_error("Tried to access SizedQwordRegister with an invalid offset.");
#endif

	if (!read_only)
		w[offset] = value;
}

udword SizedQwordRegister::read_udword(const size_t offset)
{
#if defined(BUILD_DEBUG)
	if (offset >= NUMBER_WORDS_IN_QWORD)
		throw std::runtime_error("Tried to access SizedQwordRegister with an invalid offset.");
#endif

	return d[offset];
}

void SizedQwordRegister::write_udword(const size_t offset, const udword value)
{
#if defined(BUILD_DEBUG)
	if (offset >= NUMBER_WORDS_IN_QWORD)
		throw std::runtime_error("Tried to access SizedQwordRegister with an invalid offset.");
#endif

	if (!read_only)
		d[offset] = value;
}

uqword SizedQwordRegister::read_uqword()
{
	return q;
}

void SizedQwordRegister::write_uqword(const uqword value)
{
	if (!read_only)
		q = value;
}

usize SizedQwordRegister::byte_bus_map_size() const
{
	return static_cast<usize>(NUMBER_BYTES_IN_QWORD);
}