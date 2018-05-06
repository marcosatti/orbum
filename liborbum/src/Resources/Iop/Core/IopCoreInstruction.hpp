#pragma once

#include "Common/Types/Primitive.hpp"
#include "Common/Types/Mips/MipsInstructionInfo.hpp"
#include "Common/Types/Mips/MipsInstruction.hpp"

/// Extends the MIPS instruction type with additional fields available specific to the IOPCore.
struct IopCoreInstruction : public MipsInstruction
{
	/// Construct the instruction with the raw value.
	/// Performs a lookup and stores the instruction info for use.
	IopCoreInstruction(const uword value);

	/// CPI instruction constants.
	static constexpr int CPI_R3000_DEFAULT = 9;
	static constexpr int CPI_R3000_BRANCH = 11;
	static constexpr int CPI_R3000_MULTIPLY = 16;
	static constexpr int CPI_R3000_DIVIDE = 112;
	static constexpr int CPI_R3000_STORE = 14;
	static constexpr int CPI_R3000_LOAD = 14;
	static constexpr int CPI_COP_DEFAULT = 11;
	static constexpr int CPI_COP_BRANCH_DELAY = 20;

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