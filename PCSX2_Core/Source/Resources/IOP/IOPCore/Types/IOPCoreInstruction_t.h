#pragma once

#include "Common/Types/MIPS/MIPSInstruction_t.h"
#include "Common/Tables/IOPCoreInstructionTable.h"

/*
Extends the MIPS instruction type with additional fields available specific to the IOPCore.
*/
struct IOPCoreInstruction_t : public MIPSInstruction_t
{
	/*
	Construct the instruction with the raw value.
	Performs a lookup and stores the instruction info for use.
	*/
	IOPCoreInstruction_t(const u32 value);

	/*
	Returns the constant IOPCore instruction information.
	*/
	const IOPCoreInstructionTable::IOPCoreInstructionInfo_t * getInfo() const;

private:
	/*
	Constant instruction information.
	*/
	const IOPCoreInstructionTable::IOPCoreInstructionInfo_t * mInfo;
};