#include "stdafx.h"

#include "Common/Tables/VIFcodeInstructionTable/VIFcodeInstructionTable.h"

#include "Resources/EE/VPU/VIF/Types/VIFcode_t.h"

VIFcodeInstructionInfo_Base_t::VIFcodeInstructionInfo_Base_t(const char * mnemonic, const u32 implementationIndex) :
	mMnemonic(mnemonic),
	mImplementationIndex(implementationIndex)
{
}

VIFcodeInstructionInfo_t::VIFcodeInstructionInfo_t(const VIFcodeInstructionInfo_Base_t* baseInfo, const bool interruptBitStatus, const bool unpackMBitStatus) :
	mBaseInfo(baseInfo), 
	mInterruptBitStatus(interruptBitStatus),
	mUnpackMBitStatus(unpackMBitStatus)
{
}

VIFcodeInstructionInfo_t VIFcodeInstructionTable::getInstructionInfo(const VIFcode_t& vifCode)
{
	u8 CMD = vifCode.getCMD();
	bool IBit = (CMD & 0x80) > 0; // Test bit 7.
	bool MBit = (CMD & 0x10) > 0; // Test bit 4.

	// Test for the unpack table (bits 5 & 6 set)
	if ((CMD & 0x60) == 0x60)
		return { &VIFCODE_UNPACK_TABLE[(CMD >> 1) & 0xF], IBit, MBit };

	// Else we are in the base table.
	return { &VIFCODE_BASE_TABLE[CMD & 0x7F], IBit, MBit };
}

const VIFcodeInstructionInfo_Base_t VIFcodeInstructionTable::VIFCODE_BASE_TABLE[128] =
{
	{ "NOP", 1 },
	{ "STCYCL", 2 },
	{ "OFFSET", 3 },
	{ "BASE", 4 },
	{ "ITOP", 5 },
	{ "STMOD", 6 },
	{ "MSKPATH3", 7 },
	{ "MARK", 8 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "FLUSHE", 9 },
	{ "FLUSH", 10 },
	{ "undefined", 0 },
	{ "FLUSHA", 11 },
	{ "MSCAL", 12 },
	{ "MSCALF", 13 },
	{ "undefined", 0 },
	{ "MSCNT", 14 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "STMASK", 15 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "STROW", 16 },
	{ "STCOL", 17 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "MPG", 18 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "DIRECT", 19 },
	{ "DIRECTHL", 20 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "undefined", 0 },
	{ "INVALID/UNPACK (FIX ME!)", 0 },
	{ "INVALID/UNPACK (FIX ME!)", 0 },
	{ "INVALID/UNPACK (FIX ME!)", 0 },
	{ "INVALID/UNPACK (FIX ME!)", 0 },
	{ "INVALID/UNPACK (FIX ME!)", 0 },
	{ "INVALID/UNPACK (FIX ME!)", 0 },
	{ "INVALID/UNPACK (FIX ME!)", 0 },
	{ "INVALID/UNPACK (FIX ME!)", 0 },
	{ "INVALID/UNPACK (FIX ME!)", 0 },
	{ "INVALID/UNPACK (FIX ME!)", 0 },
	{ "INVALID/UNPACK (FIX ME!)", 0 },
	{ "INVALID/UNPACK (FIX ME!)", 0 },
	{ "INVALID/UNPACK (FIX ME!)", 0 },
	{ "INVALID/UNPACK (FIX ME!)", 0 },
	{ "INVALID/UNPACK (FIX ME!)", 0 },
	{ "INVALID/UNPACK (FIX ME!)", 0 },
	{ "INVALID/UNPACK (FIX ME!)", 0 },
	{ "INVALID/UNPACK (FIX ME!)", 0 },
	{ "INVALID/UNPACK (FIX ME!)", 0 },
	{ "INVALID/UNPACK (FIX ME!)", 0 },
	{ "INVALID/UNPACK (FIX ME!)", 0 },
	{ "INVALID/UNPACK (FIX ME!)", 0 },
	{ "INVALID/UNPACK (FIX ME!)", 0 },
	{ "INVALID/UNPACK (FIX ME!)", 0 },
	{ "INVALID/UNPACK (FIX ME!)", 0 },
	{ "INVALID/UNPACK (FIX ME!)", 0 },
	{ "INVALID/UNPACK (FIX ME!)", 0 },
	{ "INVALID/UNPACK (FIX ME!)", 0 },
	{ "INVALID/UNPACK (FIX ME!)", 0 },
	{ "INVALID/UNPACK (FIX ME!)", 0 },
	{ "INVALID/UNPACK (FIX ME!)", 0 },
	{ "INVALID/UNPACK (FIX ME!)", 0 }
};

const VIFcodeInstructionInfo_Base_t VIFcodeInstructionTable::VIFCODE_UNPACK_TABLE[16] =
{
	{ "UNPACK_S_32", 21 },
	{ "UNPACK_S_16", 22 },
	{ "UNPACK_S_8", 23 },
	{ "undefined", 0 },
	{ "UNPACK_V2_32", 24 },
	{ "UNPACK_V2_16", 25 },
	{ "UNPACK_V2_8", 26 },
	{ "undefined", 0 },
	{ "UNPACK_V3_32", 27 },
	{ "UNPACK_V3_16", 28 },
	{ "UNPACK_V3_8", 29 },
	{ "undefined", 0 },
	{ "UNPACK_V4_32", 30 },
	{ "UNPACK_V4_16", 31 },
	{ "UNPACK_V4_8", 32 },
	{ "UNPACK_V4_5", 33 }
};