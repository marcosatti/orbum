#include "Common/Types/FifoQueue/FifoQueue.hpp"

bool FifoQueue::read(ubyte* buffer, const size_t length)
{
	if (read_available() < length)
		return false;

	for (size_t i = 0; i < length; i++)
	{
		if (!read_ubyte(buffer[i]))
			throw std::runtime_error("FifoQueue::read() failed while in loop. Please debug.");
	}

	return true;
}

bool FifoQueue::write(const ubyte* buffer, const size_t length)
{
	if (write_available() < length)
		return false;

	for (size_t i = 0; i < length; i++)
	{
		if (!write_ubyte(buffer[i]))
			throw std::runtime_error("FifoQueue::read() failed while in loop. Please debug.");
	}

	return true;
}

ubyte FifoQueue::byte_bus_read_ubyte(const BusContext context, const usize offset)
{
	ubyte value;
	read_ubyte(value);
	return value;
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
