#include "Common/Types/Memory/ByteMemory.hpp"

void ByteMemory::read(const size_t offset, ubyte * buffer, const size_t length)
{
	for (size_t i = 0; i < length; i++)
		buffer[i] = read_ubyte(offset + i);
}

void ByteMemory::write(const size_t offset, const ubyte * buffer, const size_t length)
{
	for (size_t i = 0; i < length; i++)
		write_ubyte(offset + i, buffer[i]);
}

ubyte ByteMemory::byte_bus_read_ubyte(const BusContext context, const usize offset)
{
	return read_ubyte(offset);
}

void ByteMemory::byte_bus_write_ubyte(const BusContext context, const usize offset, const ubyte value)
{
	write_ubyte(offset, value);
}

uhword ByteMemory::byte_bus_read_uhword(const BusContext context, const usize offset)
{
	return read_uhword(offset);
}

void ByteMemory::byte_bus_write_uhword(const BusContext context, const usize offset, const uhword value)
{
	write_uhword(offset, value);
}

uword ByteMemory::byte_bus_read_uword(const BusContext context, const usize offset)
{
	return read_uword(offset);
}

void ByteMemory::byte_bus_write_uword(const BusContext context, const usize offset, const uword value)
{
	write_uword(offset, value);
}

udword ByteMemory::byte_bus_read_udword(const BusContext context, const usize offset)
{
	return read_udword(offset);
}

void ByteMemory::byte_bus_write_udword(const BusContext context, const usize offset, const udword value)
{
	write_udword(offset, value);
}

uqword ByteMemory::byte_bus_read_uqword(const BusContext context, const usize offset)
{
	return read_uqword(offset);
}

void ByteMemory::byte_bus_write_uqword(const BusContext context, const usize offset, const uqword value)
{
	write_uqword(offset, value);
}
