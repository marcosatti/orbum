#include "Common/Types/Register/WordRegister.hpp"

uword WordRegister::extract_field(const Bitfield field)
{
	return field.extract_from(read_uword());
}

void WordRegister::insert_field(const Bitfield field, const uword value)
{
	write_uword(field.insert_into(read_uword(), value));
}

ubyte WordRegister::byte_bus_read_ubyte(const BusContext context, const usize offset)
{
	return read_ubyte(offset);
}

void WordRegister::byte_bus_write_ubyte(const BusContext context, const usize offset, const ubyte value)
{
	write_ubyte(offset, value);
}

uhword WordRegister::byte_bus_read_uhword(const BusContext context, const usize offset)
{
	return read_uhword(offset / NUMBER_BYTES_IN_HWORD);
}

void WordRegister::byte_bus_write_uhword(const BusContext context, const usize offset, const uhword value)
{
	write_uhword(offset / NUMBER_BYTES_IN_HWORD, value);
}

uword WordRegister::byte_bus_read_uword(const BusContext context, const usize offset)
{
	return read_uword();
}

void WordRegister::byte_bus_write_uword(const BusContext context, const usize offset, const uword value)
{
	write_uword(value);
}

void WordRegister::offset(const sword value)
{
	write_uword(read_uword() + value);
}

f32 WordRegister::read_float()
{
	return static_cast<f32>(read_uword());
}

void WordRegister::write_float(const f32 value)
{
	write_uword(static_cast<uword>(value));
}

usize WordRegister::byte_bus_map_size() const
{
	return static_cast<usize>(NUMBER_BYTES_IN_WORD);
}
