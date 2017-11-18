#pragma once

#include "Common/Types/Mips/MipsInstruction.hpp"
#include "Resources/Ee/Core/EeCoreInstructionTable.hpp"

/// Extends the MIPS instruction type with additional fields available specific to the EECore.
struct EeCoreInstruction : public MipsInstruction
{
	static constexpr Bitfield I    = Bitfield(0, 1);
	static constexpr Bitfield BC   = Bitfield(0, 2);
	static constexpr Bitfield DEST = Bitfield(21, 4);
	static constexpr Bitfield CO   = Bitfield(25, 0);

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

	/// Returns the constant EECore instruction information.
	const EECoreInstructionTable::EECoreInstructionInfo_t * getInfo() const;

private:
	/// Constant instruction information.
	const EECoreInstructionTable::EECoreInstructionInfo_t * mInfo;
};