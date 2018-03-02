#pragma once

#include <cstddef>

#include "Common/Types/Bus/ByteBusMappable.hpp"
#include "Common/Types/Bitfield.hpp"

/// Hword register.
class HwordRegister : public ByteBusMappable
{
public:
	/// Initialise register.
	virtual void initialise() = 0;

	/// Read/write functions to access the register, with subclassed functionality. 
    virtual ubyte read_ubyte(const size_t offset) = 0;
	virtual void write_ubyte(const size_t offset, const ubyte value) = 0;
	virtual uhword read_uhword() = 0;
	virtual void write_uhword(const uhword value) = 0;

	/// Bitfield extraction/insertion.
	uhword extract_field(const Bitfield field);
	void insert_field(const Bitfield field, const uhword value);

	/// Offsets the register by the specified (signed) value.
	void offset(const shword value);
	
	/// ByteBusMappable overrides.
	usize byte_bus_map_size() const override;
	ubyte byte_bus_read_ubyte(const BusContext context, const usize offset) override;
	void byte_bus_write_ubyte(const BusContext context, const usize offset, const ubyte value) override;
	uhword byte_bus_read_uhword(const BusContext context, const usize offset) override;
	void byte_bus_write_uhword(const BusContext context, const usize offset, const uhword value) override;
};