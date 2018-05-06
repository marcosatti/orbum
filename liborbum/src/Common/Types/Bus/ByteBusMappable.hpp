#pragma once

#include <stdexcept>

#include "Common/Types/Primitive.hpp"
#include "Common/Types/Bus/BusContext.hpp"

/// Able to be mapped onto a byte bus. See ByteBus for more details.
struct ByteBusMappable
{
	/// Total byte bus map size in bytes.
	virtual usize byte_bus_map_size() const = 0;

	/// Read/write to this object with the byte-addressed offset.
	/// Needs to be overriden by sub-types - by default it will throw a runtime error.
	/// These functions should never called directly, only though a ByteBus.
	virtual ubyte byte_bus_read_ubyte(const BusContext context, const usize offset)
	{
		throw std::runtime_error("ByteBusMappable method not implemented for this type. Please fix!");
	}

	virtual void byte_bus_write_ubyte(const BusContext context, const usize offset, const ubyte value)
	{
		throw std::runtime_error("ByteBusMappable method not implemented for this type. Please fix!");
	}

	virtual uhword byte_bus_read_uhword(const BusContext context, const usize offset)
	{
		throw std::runtime_error("ByteBusMappable method not implemented for this type. Please fix!");
	}

	virtual void byte_bus_write_uhword(const BusContext context, const usize offset, const uhword value)
	{
		throw std::runtime_error("ByteBusMappable method not implemented for this type. Please fix!");
	}

	virtual uword byte_bus_read_uword(const BusContext context, const usize offset)
	{
		throw std::runtime_error("ByteBusMappable method not implemented for this type. Please fix!");
	}

	virtual void byte_bus_write_uword(const BusContext context, const usize offset, const uword value)
	{
		throw std::runtime_error("ByteBusMappable method not implemented for this type. Please fix!");
	}

	virtual udword byte_bus_read_udword(const BusContext context, const usize offset)
	{
		throw std::runtime_error("ByteBusMappable method not implemented for this type. Please fix!");
	}

	virtual void byte_bus_write_udword(const BusContext context, const usize offset, const udword value)
	{
		throw std::runtime_error("ByteBusMappable method not implemented for this type. Please fix!");
	}

	virtual uqword byte_bus_read_uqword(const BusContext context, const usize offset)
	{
		throw std::runtime_error("ByteBusMappable method not implemented for this type. Please fix!");
	}

	virtual void byte_bus_write_uqword(const BusContext context, const usize offset, const uqword value)
	{
		throw std::runtime_error("ByteBusMappable method not implemented for this type. Please fix!");
	}
};