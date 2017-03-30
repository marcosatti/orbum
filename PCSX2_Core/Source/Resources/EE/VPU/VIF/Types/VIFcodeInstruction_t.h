#pragma once

#include "Common/Global/Globals.h"
#include "Common/Tables/VIFcodeInstructionTable.h"

/*
A VIFcode type, as explained on page 87 of the EE Users Manual.
Although a VIF transfer packet is 128-bit long, the VIFcode part is 32-bit.
*/
struct VIFcodeInstruction_t
{
	/*
	Construct the instruction with the raw value.
	Performs a lookup and stores the code info for use.
	*/
	VIFcodeInstruction_t(const u32 value) : 
		mValue(value)
	{
		mInstructionInfo = VIFcodeTable::getInfo(this);
	}

	/*
	Returns the instruction value.
	*/
	u32 getValue() const
	{
		return mValue;
	}

	/*
	Get functions for the VIFcode field values.
	Bitfield map (relevant only):
	- Bits 0-15 (length 16): "IMMEDIATE" (Immediate value, meaning varies accross the CMD field).
	- Bits 16-23 (length 8): "NUM" (Amount of data to be written to the VU memory).
	- Bits 24-31 (length 8): "CMD" (Operation of the VIF to perform).
	*/
	u16 getIMMEDIATE() const
	{
		return static_cast<u16>(mValue & 0xFFFF);
	}
	u8 getNUM() const
	{
		return static_cast<u8>((mValue >> 16) & 0xFF);
	}
	u8 getCMD() const
	{
		return static_cast<u8>((mValue >> 24) & 0xFF);
	}

	/*
	Returns the constant VIFcode instruction information.
	*/
	const VIFcodeTable::VIFcodeInstructionInfo_t * getInstructionInfo()
	{
		return mInstructionInfo;
	}

private:
	/*
	Raw instruction value.
	All functions above extract information from this.
	*/
	u32 mValue;

	/*
	Constant instruction information.
	*/
	const VIFcodeTable::VIFcodeInstructionInfo_t * mInstructionInfo;
};
