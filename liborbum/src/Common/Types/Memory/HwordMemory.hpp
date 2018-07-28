#pragma once

#include <cstddef>

#include "Common/Types/Primitive.hpp"

/// Hword-addressed memory interface.
class HwordMemory
{
public:
    /// Initialise memory.
    virtual void initialise() = 0;

    /// Read or write a value of a given type, to the specified hword index (offset).
    virtual uhword read_uhword(const size_t offset) = 0;
    virtual void write_uhword(const size_t offset, const uhword value) = 0;
    virtual uword read_uword(const size_t offset) = 0;
    virtual void write_uword(const size_t offset, const uword value) = 0;
    virtual udword read_udword(const size_t offset) = 0;
    virtual void write_udword(const size_t offset, const udword value) = 0;
    virtual uqword read_uqword(const size_t offset) = 0;
    virtual void write_uqword(const size_t offset, const uqword value) = 0;

    /// Reads hwords to the buffer given.
    /// This is a wrapper around the read_uhword function, and should not be treated as a separate interface (not made virtual).
    void read(const size_t offset, uhword* buffer, const size_t length)
    {
        for (size_t i = 0; i < length; i++)
            buffer[i] = read_uhword(offset + i);
    }

    /// Writes hwords from the buffer given.
    /// This is a wrapper around the write_uhword function, and should not be treated as a separate interface (not made virtual).
    void write(const size_t offset, const uhword* buffer, const size_t length)
    {
        for (size_t i = 0; i < length; i++)
            write_uhword(offset + i, buffer[i]);
    }
};
