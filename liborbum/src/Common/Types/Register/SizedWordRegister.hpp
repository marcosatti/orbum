#pragma once

#include <stdexcept>

#include "Common/Types/Primitive.hpp"
#include "Common/Types/Register/WordRegister.hpp"

/// Sized Word register.
class SizedWordRegister : public WordRegister
{
public:
    SizedWordRegister(const uword initial_value = 0, const bool read_only = false) :
        w(initial_value),
        initial_value(initial_value),
        read_only(read_only)
    {
    }

    /// Initialise register.
    void initialise() override
    {
        w = initial_value;
    }

    /// Read/write functions to access the register.
    ubyte read_ubyte(const size_t offset) override
    {
#if defined(BUILD_DEBUG)
        if (offset >= NUMBER_BYTES_IN_WORD)
            throw std::runtime_error("Tried to access SizedWordRegister with an invalid offset.");
#endif

        return b[offset];
    }

    void write_ubyte(const size_t offset, const ubyte value) override
    {
#if defined(BUILD_DEBUG)
        if (offset >= NUMBER_BYTES_IN_WORD)
            throw std::runtime_error("Tried to access SizedWordRegister with an invalid offset.");
#endif

        if (!read_only)
            b[offset] = value;
    }

    uhword read_uhword(const size_t offset) override
    {
#if defined(BUILD_DEBUG)
        if (offset >= NUMBER_HWORDS_IN_WORD)
            throw std::runtime_error("Tried to access SizedWordRegister with an invalid offset.");
#endif

        return h[offset];
    }

    void write_uhword(const size_t offset, const uhword value) override
    {
#if defined(BUILD_DEBUG)
        if (offset >= NUMBER_HWORDS_IN_WORD)
            throw std::runtime_error("Tried to access SizedWordRegister with an invalid offset.");
#endif

        if (!read_only)
            h[offset] = value;
    }

    uword read_uword() override
    {
        return w;
    }

    void write_uword(const uword value) override
    {
        if (!read_only)
            w = value;
    }

    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            CEREAL_NVP(w)
        );
    }

private:
    /// Primitive (sized) storage for register.
    union {
        ubyte b[NUMBER_BYTES_IN_WORD];
        uhword h[NUMBER_HWORDS_IN_WORD];
        uword w;
    };

    /// Initial value.
    uword initial_value;

    /// Read-only flag.
    /// Writes are silently discarded if turned on.
    bool read_only;
};
