#pragma once

#include "Common/Types/Mips/MipsInstruction.hpp"
#include "Resources/Ee/Vpu/VifcodeInstructionTable.hpp"

/// A VIFcode type, as explained on page 87 of the EE Users Manual.
/// Although a VIF transfer packet is 128-bit long, the VIFcode part is 32-bit.
struct VifcodeInstruction : public MipsInstruction
{
	static constexpr Bitfield IMMEDIATE = Bitfield(0, 16);
	static constexpr Bitfield NUM       = Bitfield(16, 8);
	static constexpr Bitfield CMD       = Bitfield(24, 8);

	VifcodeInstruction(const uword value);

	/// Field extraction functions.
	/// See documentation above for the actual bits.
	uhword getIMMEDIATE() const
	{
		return static_cast<uhword>(IMMEDIATE.extract_from(value));
	}

	ubyte getNUM() const
	{
		return static_cast<ubyte>(NUM.extract_from(value));
	}

	ubyte getCMD() const
	{
		return static_cast<ubyte>(CMD.extract_from(value));
	}

	/*
	Returns the constant VIFcode instruction information.
	*/
	const VIFcodeTable::VIFcodeInstructionInfo_t * get_instruction_info() const;

private:
	/*
	Constant instruction information.
	*/
	const VIFcodeTable::VIFcodeInstructionInfo_t * mInstructionInfo;
};
