#include "Common/Types/Register/HwordRegister.hpp"

uhword HwordRegister::extract_field(const Bitfield field)
{
	return field.extract_from(read_uhword());
}

void HwordRegister::insert_field(const Bitfield field, const uhword value)
{
	write_uhword(field.insert_into(read_uhword(), value));
}

ubyte HwordRegister::byte_bus_read_ubyte(const BusContext context, const usize offset)
{
	return read_ubyte(offset);
}

void HwordRegister::byte_bus_write_ubyte(const BusContext context, const usize offset, const ubyte value)
{
	write_ubyte(offset, value);
}

uhword HwordRegister::byte_bus_read_uhword(const BusContext context, const usize offset)
{
	return read_uhword();
}

void HwordRegister::byte_bus_write_uhword(const BusContext context, const usize offset, const uhword value)
{
	write_uhword(value);
}

void HwordRegister::offset(const shword value)
{
	write_uhword(read_uhword() + value);
}
