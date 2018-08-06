#pragma once

#include <cstddef>

#include "Common/Types/Bitfield.hpp"
#include "Common/Types/Bus/ByteBusMappable.hpp"
#include "Common/Types/Primitive.hpp"

/// Byte register.
class ByteRegister : public ByteBusMappable
{
public:
    /// Initialise register.
    virtual void initialize() = 0;

    /// Read/write functions to access the register, with subclassed functionality.
    virtual ubyte read_ubyte() = 0;
    virtual void write_ubyte(const ubyte value) = 0;

    /// Bitfield extraction/insertion.
    ubyte extract_field(const Bitfield field)
    {
        return field.extract_from(read_ubyte());
    }

    void insert_field(const Bitfield field, const ubyte value)
    {
        write_ubyte(field.insert_into(read_ubyte(), value));
    }

    /// Offsets the register by the specified (signed) value.
    void offset(const sbyte value)
    {
        write_ubyte(read_ubyte() + value);
    }

    /// ByteBusMappable overrides.
    usize byte_bus_map_size() const override
    {
        return static_cast<usize>(1);
    }

    ubyte byte_bus_read_ubyte(const BusContext context, const usize offset) override
    {
        return read_ubyte();
    }

    void byte_bus_write_ubyte(const BusContext context, const usize offset, const ubyte value) override
    {
        write_ubyte(value);
    }
};
