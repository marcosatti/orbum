#pragma once

#include <cstddef>

#include "Common/Types/Primitive.hpp"
#include "Common/Types/Bus/ByteBusMappable.hpp"
#include "Common/Types/Bitfield.hpp"

/// Dword register.
class DwordRegister : public ByteBusMappable
{
public:
	/// Initialise register.
	virtual void initialise() = 0;

	/// Read/write functions to access the register, with subclassed functionality. 
    virtual ubyte read_ubyte(const size_t offset) = 0;
	virtual void write_ubyte(const size_t offset, const ubyte value) = 0;
	virtual uhword read_uhword(const size_t offset) = 0;
	virtual void write_uhword(const size_t offset, const uhword value) = 0;
	virtual uword read_uword(const size_t offset) = 0;
	virtual void write_uword(const size_t offset, const uword value) = 0;
	virtual udword read_udword() = 0;
	virtual void write_udword(const udword value) = 0;
	
	/// Bitfield extraction/insertion.
	udword extract_field(const Bitfield field)
	{
		return field.extract_from(read_udword());
	}

	void insert_field(const Bitfield field, const udword value)
	{
		write_udword(field.insert_into(read_udword(), value));
	}

	/// Offsets the register by the specified (signed) value.
	void offset(const sdword value)
	{
		write_udword(read_udword() + value);
	}

	/// ByteBusMappable overrides.
	usize byte_bus_map_size() const override
	{
		return static_cast<usize>(NUMBER_BYTES_IN_DWORD);
	}

	ubyte byte_bus_read_ubyte(const BusContext context, const usize offset) override
	{
		return read_ubyte(offset);
	}

	void byte_bus_write_ubyte(const BusContext context, const usize offset, const ubyte value) override
	{
		write_ubyte(offset, value);
	}

	uhword byte_bus_read_uhword(const BusContext context, const usize offset) override
	{
		return read_uhword(offset / NUMBER_BYTES_IN_HWORD);
	}

	void byte_bus_write_uhword(const BusContext context, const usize offset, const uhword value) override
	{
		write_uhword(offset / NUMBER_BYTES_IN_HWORD, value);
	}

	uword byte_bus_read_uword(const BusContext context, const usize offset) override
	{
		return read_uword(offset / NUMBER_BYTES_IN_WORD);
	}

	void byte_bus_write_uword(const BusContext context, const usize offset, const uword value) override
	{
		write_uword(offset / NUMBER_BYTES_IN_WORD, value);
	}

	udword byte_bus_read_udword(const BusContext context, const usize offset) override
	{
		return read_udword();
	}

	void byte_bus_write_udword(const BusContext context, const usize offset, const udword value) override
	{
		write_udword(value);
	}
};
