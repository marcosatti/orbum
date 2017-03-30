#include "stdafx.h"

#include "Common/Tables/VIFcodeInstructionTable.h"

#include "Resources/EE/VPU/VIF/Types/VIFcodeInstruction_t.h"

const VIFcodeTable::VIFcodeInstructionInfo_t * VIFcodeTable::getInfo(const VIFcodeInstruction_t * vifCode)
{
	u8 CMD = vifCode->getCMD();

	// Test for the unpack table (bits 5 & 6 set). We don't need an elaborate lookup function, a simple if suffices for the VIFcode instructions.
	if ((CMD & 0x60) == 0x60)
		return &VIFCODE_UNPACK_TABLE[(CMD >> 1) & 0xF];

	// Else we are in the base table.
	return &VIFCODE_BASE_TABLE[CMD & 0x7F];
}