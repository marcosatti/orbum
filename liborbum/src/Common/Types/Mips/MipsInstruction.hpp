#pragma once

#include "Common/Types/Bitfield.hpp"
#include "Common/Types/Primitive.hpp"

/// A MIPS instruction type which is used to read specific values from it.
/// An instruction follows the MIPS 32-bit instruction format, see here:
/// https://en.wikibooks.org/wiki/MIPS_Assembly/Instruction_Formats.
/// Functions are provided to extract fields from it.
struct MipsInstruction
{
    static constexpr Bitfield OPCODE = Bitfield(26, 6);
    static constexpr Bitfield RS = Bitfield(21, 5);
    static constexpr Bitfield RT = Bitfield(16, 5);
    static constexpr Bitfield RD = Bitfield(11, 5);
    static constexpr Bitfield SHAMT = Bitfield(6, 5);
    static constexpr Bitfield FUNCT = Bitfield(0, 6);
    static constexpr Bitfield IMM = Bitfield(0, 16);
    static constexpr Bitfield ADDR = Bitfield(0, 26);

    MipsInstruction(const uword value) :
        value(value)
    {
    }

    /// Field extraction functions.
    /// See documentation above for the actual bits.
    int opcode() const
    {
        return static_cast<int>(OPCODE.extract_from(value));
    }

    int rs() const
    {
        return static_cast<int>(RS.extract_from(value));
    }

    int rt() const
    {
        return static_cast<int>(RT.extract_from(value));
    }

    int rd() const
    {
        return static_cast<int>(RD.extract_from(value));
    }

    int shamt() const
    {
        return static_cast<int>(SHAMT.extract_from(value));
    }

    int funct() const
    {
        return static_cast<int>(FUNCT.extract_from(value));
    }

    uhword u_imm() const
    {
        return static_cast<uhword>(IMM.extract_from(value));
    }

    shword s_imm() const
    {
        return static_cast<shword>(u_imm());
    }

    uptr addr() const
    {
        return static_cast<uptr>(ADDR.extract_from(value));
    }

    /// Raw instruction value.
    /// All functions above extract information from this.
    const uword value;
};
