#pragma once

#include "Common/Types/MIPS/MIPSInstruction_t.h"
#include "Common/Tables/EECoreInstructionTable.h"

/*
Extends the MIPS instruction type with additional fields available specific to the EECore.
*/
struct EECoreInstruction_t : public MIPSInstruction_t
{
	/*
	Construct the instruction with the raw value.
	Performs a lookup and stores the instruction info for use.
	*/
	EECoreInstruction_t(const u32 value) : 
		MIPSInstruction_t(value) 
	{ 
		mInstructionInfo = EECoreInstructionTable::getInstructionInfo(this); 
	}

	/*
	Gets the various COP2/VU instruction fields. Prefixed with getV*.
	- I    @ bits 0.
	- BC   @ bits 0-1.
	- Dest @ bits 21-24.
	- CO   @ bits 25.
	*/
	u8 getVI() const
	{
		return static_cast<u8>(mValue & 0x1);
	}
	u8 getVBC() const
	{
		return static_cast<u8>(mValue & 0x3);
	}
	u8 getVDest() const
	{
		return (static_cast<u8>(mValue >> 21) & 0xF);
	}
	u8 getVCO() const
	{
		return (static_cast<u8>(mValue >> 25) & 0x1);
	}

	/*
	Returns the constant EECore instruction information.
	*/
	const EECoreInstructionTable::EECoreInstructionInfo_t * getInstructionInfo()
	{
		return mInstructionInfo;
	}

private:
	/*
	Constant instruction information.
	*/
	const EECoreInstructionTable::EECoreInstructionInfo_t * mInstructionInfo;
};