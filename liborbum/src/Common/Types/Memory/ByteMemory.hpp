#pragma once

#include <cstddef>

#include "Common/Types/Bus/BusContext.hpp"
#include "Common/Types/Bus/ByteBusMappable.hpp"
#include "Common/Types/Primitive.hpp"

/// Byte-addressed memory interface.
class ByteMemory : public ByteBusMappable
{
public:
    /// Initialise memory.
    virtual void initialise() = 0;

    /// Read or write a value of a given type, to the specified byte index (offset).
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

    /// Reads bytes to the buffer given.
    /// This is a wrapper around the read_ubyte function, and should not be treated as a separate interface (not made virtual).
    void read(const size_t offset, ubyte* buffer, const size_t length)
    {
        for (size_t i = 0; i < length; i++)
            buffer[i] = read_ubyte(offset + i);
    }

    /// Writes bytes from the buffer given.
    /// This is a wrapper around the write_ubyte function, and should not be treated as a separate interface (not made virtual).
    void write(const size_t offset, const ubyte* buffer, const size_t length)
    {
        for (size_t i = 0; i < length; i++)
            write_ubyte(offset + i, buffer[i]);
    }

    /// ByteBusMappable overrides.
    ubyte byte_bus_read_ubyte(const BusContext context, const usize offset)
    {
        return read_ubyte(offset);
    }

    void byte_bus_write_ubyte(const BusContext context, const usize offset, const ubyte value)
    {
        write_ubyte(offset, value);
    }

    uhword byte_bus_read_uhword(const BusContext context, const usize offset)
    {
        return read_uhword(offset);
    }

    void byte_bus_write_uhword(const BusContext context, const usize offset, const uhword value)
    {
        write_uhword(offset, value);
    }

    uword byte_bus_read_uword(const BusContext context, const usize offset)
    {
        return read_uword(offset);
    }

    void byte_bus_write_uword(const BusContext context, const usize offset, const uword value)
    {
        write_uword(offset, value);
    }

    udword byte_bus_read_udword(const BusContext context, const usize offset)
    {
        return read_udword(offset);
    }

    void byte_bus_write_udword(const BusContext context, const usize offset, const udword value)
    {
        write_udword(offset, value);
    }

    uqword byte_bus_read_uqword(const BusContext context, const usize offset)
    {
        return read_uqword(offset);
    }

    void byte_bus_write_uqword(const BusContext context, const usize offset, const uqword value)
    {
        write_uqword(offset, value);
    }
};
