#pragma once

#include "Common/Types/Register/ByteRegister.hpp"

/// Sized Byte register.
class SizedByteRegister : public ByteRegister
{
public:
    SizedByteRegister(const ubyte initial_value = 0, const bool read_only = false) :
        b(initial_value),
        initial_value(initial_value),
        read_only(read_only)
    {
    }

    /// Initialise register.
    void initialize() override
    {
        b = initial_value;
    }

    /// Read/write functions to access the register.
    ubyte read_ubyte() override
    {
        return b;
    }

    void write_ubyte(const ubyte value) override
    {
        if (!read_only)
            b = value;
    }

private:
    /// Primitive (sized) storage for register.
    union {
        ubyte b;
    };

    /// Initial value.
    ubyte initial_value;

    /// Read-only flag.
    /// Writes are silently discarded if turned on.
    bool read_only;

public:
    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            CEREAL_NVP(b)
        );
    }
};
