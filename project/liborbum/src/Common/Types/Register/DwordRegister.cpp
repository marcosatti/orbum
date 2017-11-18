#include "Common/Types/Register/DwordRegister.hpp"

udword DwordRegister::extract_field(const Bitfield field)
{
	return field.extract_from(read_udword());
}

void DwordRegister::insert_field(const Bitfield field, const udword value)
{
	write_udword(field.insert_into(read_udword(), value));
}

ubyte DwordRegister::byte_bus_read_ubyte(const BusContext context, const usize offset)
{
	return read_ubyte(offset);
}

void DwordRegister::byte_bus_write_ubyte(const BusContext context, const usize offset, const ubyte value)
{
	write_ubyte(offset, value);
}

uhword DwordRegister::byte_bus_read_uhword(const BusContext context, const usize offset)
{
	return read_uhword(offset / NUMBER_BYTES_IN_HWORD);
}

void DwordRegister::byte_bus_write_uhword(const BusContext context, const usize offset, const uhword value)
{
	write_uhword(offset / NUMBER_BYTES_IN_HWORD, value);
}

uword DwordRegister::byte_bus_read_uword(const BusContext context, const usize offset)
{
	return read_uword(offset / NUMBER_BYTES_IN_WORD);
}

void DwordRegister::byte_bus_write_uword(const BusContext context, const usize offset, const uword value)
{
	write_uword(offset / NUMBER_BYTES_IN_WORD, value);
}

udword DwordRegister::byte_bus_read_udword(const BusContext context, const usize offset)
{
	return read_udword();
}

void DwordRegister::byte_bus_write_udword(const BusContext context, const usize offset, const udword value)
{
	write_udword(value);
}

void DwordRegister::offset(const sdword value)
{
	write_udword(read_udword() + value);
}
