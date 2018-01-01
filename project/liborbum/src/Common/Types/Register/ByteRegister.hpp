#pragma once

#include <cstddef>

#include "Common/Types/Bus/ByteBusMappable.hpp"
#include "Common/Types/Bitfield.hpp"

/// Byte register.
class ByteRegister : public ByteBusMappable
{
public:
	/// Initialise register.
	virtual void initialise() = 0;

	/// Read/write functions to access the register, with subclassed functionality. 
	virtual ubyte read_ubyte() = 0;
	virtual void write_ubyte(const ubyte value) = 0;

	/// Bitfield extraction/insertion.
	ubyte extract_field(const Bitfield field);
	void insert_field(const Bitfield field, const ubyte value);

	/// Offsets the register by the specified (signed) value.
	void offset(const sbyte value);
	
	/// ByteBusMappable overrides.
	usize byte_bus_map_size() const override;
	ubyte byte_bus_read_ubyte(const BusContext context, const usize offset) override;
	void byte_bus_write_ubyte(const BusContext context, const usize offset, const ubyte value) override;
};
