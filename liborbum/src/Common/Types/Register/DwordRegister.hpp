#pragma once

#include <cstddef>

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
	udword extract_field(const Bitfield field);
	void insert_field(const Bitfield field, const udword value);

	/// Offsets the register by the specified (signed) value.
	void offset(const sdword value);
	
	/// ByteBusMappable overrides.
	usize byte_bus_map_size() const override;
	ubyte byte_bus_read_ubyte(const BusContext context, const usize offset) override;
	void byte_bus_write_ubyte(const BusContext context, const usize offset, const ubyte value) override;
	uhword byte_bus_read_uhword(const BusContext context, const usize offset) override;
	void byte_bus_write_uhword(const BusContext context, const usize offset, const uhword value) override;
	uword byte_bus_read_uword(const BusContext context, const usize offset) override;
	void byte_bus_write_uword(const BusContext context, const usize offset, const uword value) override;
	udword byte_bus_read_udword(const BusContext context, const usize offset) override;
	void byte_bus_write_udword(const BusContext context, const usize offset, const udword value) override;
};