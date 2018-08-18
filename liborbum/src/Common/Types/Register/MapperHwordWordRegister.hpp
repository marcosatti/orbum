#pragma once

#include <stdexcept>

#include "Common/Types/Primitive.hpp"
#include "Common/Types/Register/HwordRegister.hpp"
#include "Common/Types/Register/WordRegister.hpp"

/// Maps a hword register to word register by zero-filling or truncating.
class MapperHwordWordRegister : public WordRegister
{
public:
    /// Initialise register (initialize underlying register).
    void initialize() override
    {
        hword_register->initialize();
    }

    ubyte read_ubyte(const size_t offset) override
    {
        throw std::runtime_error("Only Word R/W wrapper calls to HwordRegister are allowed.");
    }

    void write_ubyte(const size_t offset, const ubyte value) override
    {
        throw std::runtime_error("Only Word R/W wrapper calls to HwordRegister are allowed.");
    }

    uhword read_uhword(const size_t offset) override
    {
        throw std::runtime_error("Only Word R/W wrapper calls to HwordRegister are allowed.");
    }

    void write_uhword(const size_t offset, const uhword value) override
    {
        throw std::runtime_error("Only Word R/W wrapper calls to HwordRegister are allowed.");
    }

    uword read_uword() override
    {
        return static_cast<uword>(hword_register->read_uhword());
    }

    void write_uword(const uword value) override
    {
        hword_register->write_uhword(static_cast<uhword>(value));
    }

    /// Reference to mapped hword register.
    HwordRegister* hword_register;
};
