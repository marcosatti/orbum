#pragma once

#include <cstddef>

#include "Common/Types/Primitive.hpp"
#include "Common/Types/Bus/BusContext.hpp"
#include "Common/Types/Bus/ByteBusMappable.hpp"

/*
FIFO queue.
Minimum sized type that can be transfered is a byte.
*/
class FifoQueue : public ByteBusMappable
{
public:
	/*
	Initialise FIFO queue (set to empty).
	*/
	virtual void initialise() = 0;

	/*
	Reads byte(s) from the FIFO queue (pop).
	Returns true on a successful read.
	*/
	virtual bool read_ubyte(ubyte & data) = 0;

	/*
	Writes push bytes(s) to the end of the FIFO queue.
	Returns true on a successful writes.
	*/
	virtual bool write_ubyte(const ubyte data) = 0;
	
	/*
	Reads bytes to the buffer given.
	This is a wrapper around the read_ubyte function, and should not be treated as a separate interface (not made virtual).
	Before reading from the queue, first checks that there are 'length' elements available. 
	Returns true if this check passed and bytes were read into 'buffer', false otherwise.
	*/
	bool read(ubyte * buffer, const size_t length);

	/*
	Writes bytes from the buffer given.
	This is a wrapper around the write_ubyte function, and should not be treated as a separate interface (not made virtual).
	Before writing to the queue, first checks that there are 'length' spaces available. 
	Returns true if this check passed and bytes were written from 'buffer', false otherwise.
	*/
	bool write(const ubyte * buffer, const size_t length);

	/*
	Returns the number of bytes remaining in the queue available for reading.
	Use only from a consumer thread.
	*/
	virtual size_t read_available() const = 0;

	/*
	Returns the number of bytes free in the queue available for writing.
	Use only from a producer thread.
	*/
	virtual size_t write_available() const = 0;

	/*
	ByteBusMappable overrides.
	*/
	ubyte byte_bus_read_ubyte(const BusContext context, const usize offset) override;
	void byte_bus_write_ubyte(const BusContext context, const usize offset, const ubyte value) override;
	uhword byte_bus_read_uhword(const BusContext context, const usize offset) override;
	void byte_bus_write_uhword(const BusContext context, const usize offset, const uhword value) override;
	uword byte_bus_read_uword(const BusContext context, const usize offset) override;
	void byte_bus_write_uword(const BusContext context, const usize offset, const uword value) override;
	udword byte_bus_read_udword(const BusContext context, const usize offset) override;
	void byte_bus_write_udword(const BusContext context, const usize offset, const udword value) override;
	uqword byte_bus_read_uqword(const BusContext context, const usize offset) override;
	void byte_bus_write_uqword(const BusContext context, const usize offset, const uqword value) override;
};

