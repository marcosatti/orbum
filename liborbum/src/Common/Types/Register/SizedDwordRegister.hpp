#pragma once

#include <stdexcept>

#include <cereal/cereal.hpp>

#include "Common/Types/Primitive.hpp"
#include "Common/Types/Register/DwordRegister.hpp"

/// Sized Dword register.
class SizedDwordRegister : public DwordRegister
{
public:
    SizedDwordRegister(const udword initial_value = 0, const bool read_only = false) :
        d(initial_value),
        initial_value(initial_value),
        read_only(read_only)
    {
    }

    /// Initialise register.
    void initialize() override
    {
        d = initial_value;
    }

    /// Read/write functions to access the register.
    ubyte read_ubyte(const size_t offset) override
    {
#if defined(BUILD_DEBUG)
        if (offset >= NUMBER_BYTES_IN_DWORD)
            throw std::runtime_error("Tried to access SizedDwordRegister with an invalid offset.");
#endif

        return b[offset];
    }

    void write_ubyte(const size_t offset, const ubyte value) override
    {
#if defined(BUILD_DEBUG)
        if (offset >= NUMBER_BYTES_IN_DWORD)
            throw std::runtime_error("Tried to access SizedDwordRegister with an invalid offset.");
#endif

        if (!read_only)
            b[offset] = value;
    }

    uhword read_uhword(const size_t offset) override
    {
#if defined(BUILD_DEBUG)
        if (offset >= NUMBER_HWORDS_IN_DWORD)
            throw std::runtime_error("Tried to access SizedDwordRegister with an invalid offset.");
#endif

        return h[offset];
    }

    void write_uhword(const size_t offset, const uhword value) override
    {
#if defined(BUILD_DEBUG)
        if (offset >= NUMBER_HWORDS_IN_DWORD)
            throw std::runtime_error("Tried to access SizedDwordRegister with an invalid offset.");
#endif

        if (!read_only)
            h[offset] = value;
    }

    uword read_uword(const size_t offset) override
    {
#if defined(BUILD_DEBUG)
        if (offset >= NUMBER_WORDS_IN_DWORD)
            throw std::runtime_error("Tried to access SizedDwordRegister with an invalid offset.");
#endif

        return w[offset];
    }

    void write_uword(const size_t offset, const uword value) override
    {
#if defined(BUILD_DEBUG)
        if (offset >= NUMBER_WORDS_IN_DWORD)
            throw std::runtime_error("Tried to access SizedDwordRegister with an invalid offset.");
#endif

        if (!read_only)
            w[offset] = value;
    }

    udword read_udword() override
    {
        return d;
    }

    void write_udword(const udword value) override
    {
        if (!read_only)
            d = value;
    }

private:
    /// Primitive (sized) storage for register.
    union {
        ubyte b[NUMBER_BYTES_IN_DWORD];
        uhword h[NUMBER_HWORDS_IN_DWORD];
        uword w[NUMBER_WORDS_IN_DWORD];
        udword d;
    };

    /// Initial value.
    udword initial_value;

    /// Read-only flag.
    /// Writes are silently discarded if turned on.
    bool read_only;

public:
    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            CEREAL_NVP(d)
        );
    }
};
