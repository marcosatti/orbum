#pragma once

#include <cstddef>

#include "Common/Types/Bus/ByteBusMappable.hpp"
#include "Common/Types/Primitive.hpp"

/// Qword register.
class QwordRegister : public ByteBusMappable
{
public:
    /// Initialise register.
    virtual void initialize() = 0;

    /// Read/write functions to access the register, with subclassed functionality.
    virtual ubyte read_ubyte(const size_t offset) = 0;
    virtual void write_ubyte(const size_t offset, const ubyte value) = 0;
    virtual uhword read_uhword(const size_t offset) = 0;
    virtual void write_uhword(const size_t offset, const uhword value) = 0;
    virtual uword read_uword(const size_t offset) = 0;
    virtual void write_uword(const size_t offset, const uword value) = 0;
    virtual udword read_udword(const size_t offset) = 0;
    virtual void write_udword(const size_t offset, const udword value) = 0;
    virtual uqword read_uqword() = 0;
    virtual void write_uqword(const uqword value) = 0;

    /// Read/write floats - wrappers around read/write uword.
    f32 read_float(const size_t offset)
    {
        const uword raw = read_uword(offset);
        return *reinterpret_cast<const f32*>(&raw);
    }

    void write_float(const size_t offset, const f32 value)
    {
        write_uword(offset, *reinterpret_cast<const uword*>(&value));
    }

    /// ByteBusMappable overrides.
    usize byte_bus_map_size() const override
    {
        return static_cast<usize>(NUMBER_BYTES_IN_QWORD);
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
        return read_udword(offset / NUMBER_BYTES_IN_DWORD);
    }

    void byte_bus_write_udword(const BusContext context, const usize offset, const udword value) override
    {
        write_udword(offset / NUMBER_BYTES_IN_DWORD, value);
    }

    uqword byte_bus_read_uqword(const BusContext context, const usize offset) override
    {
        return read_uqword();
    }

    void byte_bus_write_uqword(const BusContext context, const usize offset, const uqword value) override
    {
        write_uqword(value);
    }
};
