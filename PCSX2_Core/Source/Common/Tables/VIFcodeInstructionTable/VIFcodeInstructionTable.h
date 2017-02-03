#pragma once

#include "Common/Global/Globals.h"

class VIFcode_t;

/*
A struct to hold information about a VIFcode instruction.
Contains the unique implementation index, the interrupt (i) bit status, and for the UNPACK commands, the m bit.

This is used similar to the EECoreInstructionTable lookup. It does not have an associated spreadsheet table as there is only a small number of instructions.
*/
struct VIFcodeInstructionInfo_Base_t
{
	VIFcodeInstructionInfo_Base_t(const char * mnemonic, const u32 implementationIndex);

	const char * mMnemonic;
	const u32 mImplementationIndex;
};
struct VIFcodeInstructionInfo_t
{
	VIFcodeInstructionInfo_t(const VIFcodeInstructionInfo_Base_t* baseInfo, const bool interruptBitStatus, const bool unpackMBitStatus);

	const VIFcodeInstructionInfo_Base_t	* mBaseInfo;
	const bool mInterruptBitStatus;
	const bool mUnpackMBitStatus;
};

/*
Static class used as the VIFcode instruction information lookup.
See EE Users Manual page 87.
*/
class VIFcodeInstructionTable
{
public:
	/*
	Returns VIFcodeInstructionInfo_t which contains the unique instruction info, the interrupt bit status, and for the UNPACK commands, the m bit.
	*/
	static VIFcodeInstructionInfo_t getInstructionInfo(const VIFcode_t & vifCode);

	/*
	The base table information and the UNPACK table information.
	For the base table, it encompases the first 7-bits worth (128 instructions).
	For the UNPACK table, it only encompases bits 1-4 ("mvnv") which amounts to 16 instructions.
	The lookup function tests for bits 5-6 which determines if the base or UNPACK table is used.
	*/
	static const VIFcodeInstructionInfo_Base_t VIFCODE_BASE_TABLE[128];
	static const VIFcodeInstructionInfo_Base_t VIFCODE_UNPACK_TABLE[16];
};