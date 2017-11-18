#include "Common/Types/Register/ByteRegister.hpp"

ubyte ByteRegister::extract_field(const Bitfield field)
{
	return field.extract_from(read_ubyte());
}

void ByteRegister::insert_field(const Bitfield field, const ubyte value)
{
	write_ubyte(field.insert_into(read_ubyte(), value));
}

ubyte ByteRegister::byte_bus_read_ubyte(const BusContext context, const usize offset)
{
	return read_ubyte();
}

void ByteRegister::byte_bus_write_ubyte(const BusContext context, const usize offset, const ubyte value)
{
	write_ubyte(value);
}

void ByteRegister::offset(const sbyte value)
{
	write_ubyte(read_ubyte() + value);
}
