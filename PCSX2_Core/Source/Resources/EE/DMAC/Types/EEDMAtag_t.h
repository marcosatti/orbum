#pragma once

#include "Common/Global/Globals.h"

/*
An EE DMAtag type, as explained on page 58 of the EE Users Manual.
Although a DMAtag is 128-bit long, only the lower 2 x 32-bits are used (referred to as 64-bits in the map data below).
*/
struct EEDMAtag_t
{
	/*
	Construct the tag with the raw values.
	- tag0 is for bits 0-31.
	- tag1 is for bits 32-63.
	*/
	EEDMAtag_t(const u32 tag0, const u32 tag1) :
		mTag0(tag0),
		mTag1(tag1)
	{
	}

	/*
	Returns the tag values.
	*/
	u32 getTag0() const
	{
		return mTag0;
	}
	u32 getTag1() const
	{
		return mTag1;
	}

	/*
	Get functions for the DMAtag field values.
	Bitfield map (relevant only):
	- Bits 0-15 (length 16): "QWC" (Quadword count).
	- Bits 16-32 (length 16): "TAG" Various tag info (needed for the CHCR register).
	- Bits 26-27 (length 2): "PCE" (Priority control enable).
	- Bits 28-30 (length 3): "ID" (Tag ID, used as a DMAC instruction).
	- Bits 31 (length 1): "IRQ" (Interrupt request, to the EE Core on IRQ1).
	- Bits 32-62 (length 31): "ADDR" (Address of packet or next tag instruction, due to qword alignment, lower 4 bits are 0's).
	- Bits 63 (length 1): "SPR" (Memory or scratchpad ram (SPR) selection).
	*/
	u16 getQWC() const
	{
		return static_cast<u16>(mTag0 & 0xFFFF);
	}

	u16 getTAG() const
	{
		return static_cast<u16>((mTag0 >> 16) & 0xFFFF);
	}
	
	u8 getPCE() const
	{
		return static_cast<u8>((mTag0 >> 26) & 0x3);
	}

	u8 getID() const
	{
		return static_cast<u8>((mTag0 >> 28) & 0x7);
	}

	u8 getIRQ() const
	{
		return static_cast<u8>((mTag0 >> 31) & 0x1);
	}

	u32 getADDR() const
	{
		return static_cast<u32>(mTag1 & 0x7FFFFFFF);
	}

	u8 getSPR() const
	{
		return static_cast<u8>((mTag1 >> 31) & 0x1);
	}

	void logDebugAllFields() const
	{
#if defined(BUILD_DEBUG)
		log(Debug, "EE DMA tag info: QWC = 0x%X, PCE = 0x%X, ID = 0x%X, IRQ = 0x%X, ADDR = 0x%X, SPR = 0x%X.", getQWC(), getPCE(), getID(), getIRQ(), getADDR(), getSPR());
#endif
	}

private:
	/*
	DMAtag values.
	All functions above extract information from these.
	mTag0 is for bits 0-31.
	mTag1 is for bits 32-63.
	*/
	u32 mTag0;
	u32 mTag1;
};