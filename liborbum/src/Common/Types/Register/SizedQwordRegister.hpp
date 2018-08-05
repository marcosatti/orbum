#pragma once

#include <stdexcept>

#include "Common/Types/Primitive.hpp"
#include "Common/Types/Register/QwordRegister.hpp"

/// Sized Qword register.
class SizedQwordRegister : public QwordRegister
{
public:
    SizedQwordRegister(const uqword initial_value = 0, const bool read_only = false) :
        q(initial_value),
        initial_value(initial_value),
        read_only(read_only)
    {
    }

    /// Initialise register.
    void initialise() override
    {
        q = initial_value;
    }

    /// Read/write functions to access the register.
    ubyte read_ubyte(const size_t offset) override
    {
#if defined(BUILD_DEBUG)
        if (offset >= NUMBER_BYTES_IN_QWORD)
            throw std::runtime_error("Tried to access SizedQwordRegister with an invalid offset.");
#endif

        return b[offset];
    }

    void write_ubyte(const size_t offset, const ubyte value) override
    {
#if defined(BUILD_DEBUG)
        if (offset >= NUMBER_BYTES_IN_QWORD)
            throw std::runtime_error("Tried to access SizedQwordRegister with an invalid offset.");
#endif

        if (!read_only)
            b[offset] = value;
    }

    uhword read_uhword(const size_t offset) override
    {
#if defined(BUILD_DEBUG)
        if (offset >= NUMBER_HWORDS_IN_QWORD)
            throw std::runtime_error("Tried to access SizedQwordRegister with an invalid offset.");
#endif

        return h[offset];
    }

    void write_uhword(const size_t offset, const uhword value) override
    {
#if defined(BUILD_DEBUG)
        if (offset >= NUMBER_HWORDS_IN_QWORD)
            throw std::runtime_error("Tried to access SizedQwordRegister with an invalid offset.");
#endif

        if (!read_only)
            h[offset] = value;
    }

    uword read_uword(const size_t offset) override
    {
#if defined(BUILD_DEBUG)
        if (offset >= NUMBER_WORDS_IN_QWORD)
            throw std::runtime_error("Tried to access SizedQwordRegister with an invalid offset.");
#endif

        return w[offset];
    }

    void write_uword(const size_t offset, const uword value) override
    {
#if defined(BUILD_DEBUG)
        if (offset >= NUMBER_WORDS_IN_QWORD)
            throw std::runtime_error("Tried to access SizedQwordRegister with an invalid offset.");
#endif

        if (!read_only)
            w[offset] = value;
    }

    udword read_udword(const size_t offset) override
    {
#if defined(BUILD_DEBUG)
        if (offset >= NUMBER_WORDS_IN_QWORD)
            throw std::runtime_error("Tried to access SizedQwordRegister with an invalid offset.");
#endif

        return d[offset];
    }

    void write_udword(const size_t offset, const udword value) override
    {
#if defined(BUILD_DEBUG)
        if (offset >= NUMBER_WORDS_IN_QWORD)
            throw std::runtime_error("Tried to access SizedQwordRegister with an invalid offset.");
#endif

        if (!read_only)
            d[offset] = value;
    }

    uqword read_uqword() override
    {
        return q;
    }

    void write_uqword(const uqword value) override
    {
        if (!read_only)
            q = value;
    }

    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            CEREAL_NVP(q)
        );
    }

private:
    /// Primitive (sized) storage for register.
    union {
        ubyte b[NUMBER_BYTES_IN_QWORD];
        uhword h[NUMBER_HWORDS_IN_QWORD];
        uword w[NUMBER_WORDS_IN_QWORD];
        udword d[NUMBER_DWORDS_IN_QWORD];
        uqword q;
    };

    /// Initial value.
    uqword initial_value;

    /// Read-only flag.
    /// Writes are silently discarded if turned on.
    bool read_only;
};
