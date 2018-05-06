#pragma once

#include "Common/Types/Primitive.hpp"
#include "Common/Types/Mips/MipsInstructionInfo.hpp"
#include "Common/Types/Mips/MipsInstruction.hpp"

/// Extends the MIPS instruction type with additional fields available specific to the EECore.
struct EeCoreInstruction : public MipsInstruction
{
    static constexpr Bitfield I = Bitfield(0, 1);
    static constexpr Bitfield BC = Bitfield(0, 2);
    static constexpr Bitfield DEST = Bitfield(21, 4);
    static constexpr Bitfield CO = Bitfield(25, 1);

    EeCoreInstruction(const uword value);

    /// Field extraction functions.
    /// See documentation above for the actual bits.
    ubyte i() const
    {
        return static_cast<ubyte>(I.extract_from(value));
    }

    ubyte bc() const
    {
        return static_cast<ubyte>(BC.extract_from(value));
    }

    ubyte dest() const
    {
        return static_cast<ubyte>(DEST.extract_from(value));
    }

    ubyte co() const
    {
        return static_cast<ubyte>(CO.extract_from(value));
    }

    /// CPI instruction constants.
    static constexpr int CPI_R5900_DEFAULT = 9;
    static constexpr int CPI_R5900_BRANCH = 11;
    static constexpr int CPI_R5900_MULTIPLY = 16;
    static constexpr int CPI_R5900_DIVIDE = 112;
    static constexpr int CPI_R5900_STORE = 14;
    static constexpr int CPI_R5900_LOAD = 14;
    static constexpr int CPI_MMI_DEFAULT = 14;
    static constexpr int CPI_COP_DEFAULT = 11;
    static constexpr int CPI_COP_BRANCH_DELAY = 10;
    static constexpr int CPI_COP_BRANCH_DELAY_LIKELY = 10;

    /// Performs a lookup if required and returns the instruction details.
    const MipsInstructionInfo * get_info()
    {
        if (!info)
            info = lookup();
        return info;
    }

private:
	/// Instruction information (from performing lookup).
	MipsInstructionInfo * info;

	/// Determines what instruction this is by performing a lookup.
	MipsInstructionInfo * lookup() const;
};