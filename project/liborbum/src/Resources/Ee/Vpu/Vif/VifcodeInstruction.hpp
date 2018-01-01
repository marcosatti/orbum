#pragma once

#include "Common/Types/Primitive.hpp"
#include "Common/Types/Mips/MipsInstructionInfo.hpp"
#include "Common/Types/Mips/MipsInstruction.hpp"

/// A VIFcode type, as explained on page 87 of the EE Users Manual.
/// Although a VIF transfer packet is 128-bit long, the VIFcode part is 32-bit.
struct VifcodeInstruction : public MipsInstruction
{
	static constexpr Bitfield IMM      = Bitfield(0, 16);
	static constexpr Bitfield NUM      = Bitfield(16, 8);
	static constexpr Bitfield CMD      = Bitfield(24, 8);
	static constexpr Bitfield CMDHI    = Bitfield(29, 2);
	static constexpr Bitfield CMDLO    = Bitfield(24, 5);

	VifcodeInstruction(const uword value);

	/// Field extraction functions.
	/// See documentation above for the actual bits.
	uhword imm() const
	{
		return static_cast<uhword>(IMM.extract_from(value));
	}

	ubyte num() const
	{
		return static_cast<ubyte>(NUM.extract_from(value));
	}

	ubyte cmd() const
	{
		return static_cast<ubyte>(CMD.extract_from(value));
	}

	ubyte cmdlo() const
	{
		return static_cast<ubyte>(CMDLO.extract_from(value));
	}

	ubyte cmdhi() const
	{
		return static_cast<ubyte>(CMDHI.extract_from(value));
	}

	/// Performs a lookup if required and returns the instruction details.
	MipsInstructionInfo * get_info();

private:
	/// Instruction information (from performing lookup).
	MipsInstructionInfo * info;

	/// Determines what instruction this is by performing a lookup.
	MipsInstructionInfo * lookup() const;
};
