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
	EECoreInstruction_t(const u32 value);

	/*
	Gets the various COP2/VU instruction fields. Prefixed with getV*.
	- I    @ bits 0.
	- BC   @ bits 0-1.
	- Dest @ bits 21-24.
	- CO   @ bits 25.
	*/
	u8 getVI() const;
	u8 getVBC() const;
	u8 getVDest() const;
	u8 getVCO() const;

	/*
	Returns the constant EECore instruction information.
	*/
	const EECoreInstructionTable::EECoreInstructionInfo_t * getInfo() const;

private:
	/*
	Constant instruction information.
	*/
	const EECoreInstructionTable::EECoreInstructionInfo_t * mInfo;
};