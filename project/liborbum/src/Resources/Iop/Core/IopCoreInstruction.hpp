#pragma once

#include "Common/Types/Mips/MipsInstruction.hpp"

#include "Resources/Iop/Core/IopCoreInstructionTable.hpp"

/// Extends the MIPS instruction type with additional fields available specific to the IOPCore.
struct IopCoreInstruction : public MipsInstruction
{
	/// Construct the instruction with the raw value.
	/// Performs a lookup and stores the instruction info for use.
	IopCoreInstruction(const uword value);

	/// Returns the constant IOPCore instruction information.
	const IOPCoreInstructionTable::IOPCoreInstructionInfo_t * get_info() const;

private:
	/// Constant instruction information.
	const IOPCoreInstructionTable::IOPCoreInstructionInfo_t * info;
};