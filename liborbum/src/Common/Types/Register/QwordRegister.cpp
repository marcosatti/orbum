#include "Common/Types/Register/QwordRegister.hpp"

ubyte QwordRegister::byte_bus_read_ubyte(const BusContext context, const usize offset)
{
	return read_ubyte(offset);
}

void QwordRegister::byte_bus_write_ubyte(const BusContext context, const usize offset, const ubyte value)
{
	write_ubyte(offset, value);
}

uhword QwordRegister::byte_bus_read_uhword(const BusContext context, const usize offset)
{
	return read_uhword(offset / NUMBER_BYTES_IN_HWORD);
}

void QwordRegister::byte_bus_write_uhword(const BusContext context, const usize offset, const uhword value)
{
	write_uhword(offset / NUMBER_BYTES_IN_HWORD, value);
}

uword QwordRegister::byte_bus_read_uword(const BusContext context, const usize offset)
{
	return read_uword(offset / NUMBER_BYTES_IN_WORD);
}

void QwordRegister::byte_bus_write_uword(const BusContext context, const usize offset, const uword value)
{
	write_uword(offset / NUMBER_BYTES_IN_WORD, value);
}

udword QwordRegister::byte_bus_read_udword(const BusContext context, const usize offset)
{
	return read_udword(offset / NUMBER_BYTES_IN_DWORD);
}

void QwordRegister::byte_bus_write_udword(const BusContext context, const usize offset, const udword value)
{
	write_udword(offset / NUMBER_BYTES_IN_DWORD, value);
}

uqword QwordRegister::byte_bus_read_uqword(const BusContext context, const usize offset)
{
	return read_uqword();
}

void QwordRegister::byte_bus_write_uqword(const BusContext context, const usize offset, const uqword value)
{
	write_uqword(value);
}

f32 QwordRegister::read_float(const size_t offset)
{
	return static_cast<f32>(read_uword(offset));
}

void QwordRegister::write_float(const size_t offset, const f32 value)
{
	write_uword(offset, static_cast<uword>(value));
}

usize QwordRegister::byte_bus_map_size() const
{
	return static_cast<usize>(NUMBER_BYTES_IN_QWORD);
}
