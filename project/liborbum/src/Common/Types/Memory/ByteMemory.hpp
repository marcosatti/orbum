#pragma once

#include <cstddef>

#include "Common/Types/Primitive.hpp"
#include "Common/Types/Bus/BusContext.hpp"
#include "Common/Types/Bus/ByteBusMappable.hpp"

/*
Byte-addressed memory interface.
*/
class ByteMemory : public ByteBusMappable
{
public:
	/*
	Initialise memory.
	*/
	virtual void initialise() = 0;

	/*
	Read or write a value of a given type, to the specified byte index (offset).
	*/
	virtual ubyte read_ubyte(const size_t offset) = 0;
	virtual void write_ubyte(const size_t offset, const ubyte value) = 0;
	virtual uhword read_uhword(const size_t offset) = 0;
	virtual void write_uhword(const size_t offset, const uhword value) = 0;
	virtual uword read_uword(const size_t offset) = 0;
	virtual void write_uword(const size_t offset, const uword value) = 0;
	virtual udword read_udword(const size_t offset) = 0;
	virtual void write_udword(const size_t offset, const udword value) = 0;
	virtual uqword read_uqword(const size_t offset) = 0;
	virtual void write_uqword(const size_t offset, const uqword value) = 0;

	/*
	Reads bytes to the buffer given.
	This is a wrapper around the read_ubyte function, and should not be treated as a separate interface (not made virtual).
	*/
	void read(const size_t offset, ubyte * buffer, const size_t length);

	/*
	Writes bytes from the buffer given.
	This is a wrapper around the write_ubyte function, and should not be treated as a separate interface (not made virtual).
	*/
	void write(const size_t offset, const ubyte * buffer, const size_t length);

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

