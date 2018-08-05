#pragma once

#include <cstddef>

#include "Common/Types/Bitfield.hpp"
#include "Common/Types/Bus/ByteBusMappable.hpp"
#include "Common/Types/Primitive.hpp"

/// Word register.
class WordRegister : public ByteBusMappable
{
public:
    /// Initialise register.
    virtual void initialise() = 0;

    /// Read/write functions to access the register, with subclassed functionality.
    virtual ubyte read_ubyte(const size_t offset) = 0;
    virtual void write_ubyte(const size_t offset, const ubyte value) = 0;
    virtual uhword read_uhword(const size_t offset) = 0;
    virtual void write_uhword(const size_t offset, const uhword value) = 0;
    virtual uword read_uword() = 0;
    virtual void write_uword(const uword value) = 0;

    /// Read/write floats - wrappers around read/write uword.
    f32 read_float()
    {
        uword raw = read_uword();
        return *reinterpret_cast<f32*>(&raw);
    }

    void write_float(const f32 value)
    {
        f32 raw = value;
        write_uword(*reinterpret_cast<uword*>(&raw));
    }

    /// Bitfield extraction/insertion.
    uword extract_field(const Bitfield field)
    {
        return field.extract_from(read_uword());
    }

    void insert_field(const Bitfield field, const uword value)
    {
        write_uword(field.insert_into(read_uword(), value));
    }

    /// Offsets the register by the specified (signed) value.
    void offset(const sword value)
    {
        write_uword(read_uword() + value);
    }

    /// ByteBusMappable overrides.
    usize byte_bus_map_size() const override
    {
        return static_cast<usize>(NUMBER_BYTES_IN_WORD);
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
        return read_uword();
    }

    void byte_bus_write_uword(const BusContext context, const usize offset, const uword value) override
    {
        write_uword(value);
    }
};
