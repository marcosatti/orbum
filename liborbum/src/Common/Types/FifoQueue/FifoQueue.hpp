#pragma once

#include <cstddef>

#include "Common/Types/Bus/BusContext.hpp"
#include "Common/Types/Bus/ByteBusMappable.hpp"
#include "Common/Types/Primitive.hpp"

/// FIFO queue.
/// Minimum sized type that can be transfered is a byte.
class FifoQueue : public ByteBusMappable
{
public:
    /// Initialise FIFO queue.
    virtual void initialise() = 0;

    /// Reads byte(s) from the FIFO queue (pop).
    virtual ubyte read_ubyte() = 0;

    /// Writes push bytes(s) to the end of the FIFO queue.
    virtual void write_ubyte(const ubyte data) = 0;

    /// Reads bytes to the buffer given.
    /// This is a wrapper around the read_ubyte function, and should not be treated as a separate interface (not made virtual).
    void read(ubyte* buffer, const size_t length)
    {
        for (size_t i = 0; i < length; i++)
            buffer[i] = read_ubyte();
    }

    /// Writes bytes from the buffer given.
    /// This is a wrapper around the write_ubyte function, and should not be treated as a separate interface (not made virtual).
    void write(const ubyte* buffer, const size_t length)
    {
        for (size_t i = 0; i < length; i++)
            write_ubyte(buffer[i]);
    }

    /// Checks if the queue has at least n_bytes available for reading.
    virtual bool has_read_available(const size_t n_bytes) const = 0;

    /// Checks if the queue has at least n_bytes available for writing.
    virtual bool has_write_available(const size_t n_bytes) const = 0;

    /// Check if queue is full/empty (wrappers around above functions).
    bool is_empty() const
    {
        return !has_read_available(1);
    }

    bool is_full() const
    {
        return !has_write_available(1);
    }

    /// ByteBusMappable overrides.
    /// For the FifoQueue object, the map size is always one byte.
    /// The offset is not used in reading or writing to the queue.
    /// For a larger mapping, map the queue multiple times.
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

    uhword byte_bus_read_uhword(const BusContext context, const usize offset) override
    {
        uhword value;
        read(reinterpret_cast<ubyte*>(&value), NUMBER_BYTES_IN_HWORD);
        return value;
    }

    void byte_bus_write_uhword(const BusContext context, const usize offset, const uhword value) override
    {
        write(reinterpret_cast<const ubyte*>(&value), NUMBER_BYTES_IN_HWORD);
    }

    uword byte_bus_read_uword(const BusContext context, const usize offset) override
    {
        uword value;
        read(reinterpret_cast<ubyte*>(&value), NUMBER_BYTES_IN_WORD);
        return value;
    }

    void byte_bus_write_uword(const BusContext context, const usize offset, const uword value) override
    {
        write(reinterpret_cast<const ubyte*>(&value), NUMBER_BYTES_IN_WORD);
    }

    udword byte_bus_read_udword(const BusContext context, const usize offset) override
    {
        udword value;
        read(reinterpret_cast<ubyte*>(&value), NUMBER_BYTES_IN_DWORD);
        return value;
    }

    void byte_bus_write_udword(const BusContext context, const usize offset, const udword value) override
    {
        write(reinterpret_cast<const ubyte*>(&value), NUMBER_BYTES_IN_DWORD);
    }

    uqword byte_bus_read_uqword(const BusContext context, const usize offset) override
    {
        uqword value;
        read(reinterpret_cast<ubyte*>(&value), NUMBER_BYTES_IN_QWORD);
        return value;
    }

    void byte_bus_write_uqword(const BusContext context, const usize offset, const uqword value) override
    {
        write(reinterpret_cast<const ubyte*>(&value), NUMBER_BYTES_IN_QWORD);
    }
};
