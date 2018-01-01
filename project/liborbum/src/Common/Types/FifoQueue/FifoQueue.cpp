#include "Common/Types/FifoQueue/FifoQueue.hpp"

void FifoQueue::read(ubyte* buffer, const size_t length)
{
	for (size_t i = 0; i < length; i++)
		buffer[i] = read_ubyte();
}

void FifoQueue::write(const ubyte* buffer, const size_t length)
{
	for (size_t i = 0; i < length; i++)
		write_ubyte(buffer[i]);
}

ubyte FifoQueue::byte_bus_read_ubyte(const BusContext context, const usize offset)
{
	return read_ubyte();
}

void FifoQueue::byte_bus_write_ubyte(const BusContext context, const usize offset, const ubyte value)
{
	write_ubyte(value);
}

uhword FifoQueue::byte_bus_read_uhword(const BusContext context, const usize offset)
{
	uhword value;
	read(reinterpret_cast<ubyte*>(&value), NUMBER_BYTES_IN_HWORD);
	return value;
}

void FifoQueue::byte_bus_write_uhword(const BusContext context, const usize offset, const uhword value)
{
	write(reinterpret_cast<const ubyte*>(&value), NUMBER_BYTES_IN_HWORD);
}

uword FifoQueue::byte_bus_read_uword(const BusContext context, const usize offset)
{
	uword value;
	read(reinterpret_cast<ubyte*>(&value), NUMBER_BYTES_IN_WORD);
	return value;
}

void FifoQueue::byte_bus_write_uword(const BusContext context, const usize offset, const uword value)
{
	write(reinterpret_cast<const ubyte*>(&value), NUMBER_BYTES_IN_WORD);
}

udword FifoQueue::byte_bus_read_udword(const BusContext context, const usize offset)
{
	udword value;
	read(reinterpret_cast<ubyte*>(&value), NUMBER_BYTES_IN_DWORD);
	return value;
}

void FifoQueue::byte_bus_write_udword(const BusContext context, const usize offset, const udword value)
{
	write(reinterpret_cast<const ubyte*>(&value), NUMBER_BYTES_IN_DWORD);
}

uqword FifoQueue::byte_bus_read_uqword(const BusContext context, const usize offset)
{
	uqword value;
	read(reinterpret_cast<ubyte*>(&value), NUMBER_BYTES_IN_QWORD);
	return value;
}

void FifoQueue::byte_bus_write_uqword(const BusContext context, const usize offset, const uqword value)
{
	write(reinterpret_cast<const ubyte*>(&value), NUMBER_BYTES_IN_QWORD);
}

bool FifoQueue::is_empty() const
{
	return !has_read_available(1);
}

bool FifoQueue::is_full() const
{
	return !has_write_available(1);
}

usize FifoQueue::byte_bus_map_size() const
{
	return static_cast<usize>(1);
}