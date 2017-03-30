#pragma once

#include "Common/Global/Globals.h"

/*
An IOP DMAtag type, as explained by wisi and SP193's IOP DMA docs.
Although a DMAtag is 128-bit long, only the lower 2 x 32-bits are used (referred to as 64-bits in the map data below).
*/
struct IOPDMAtag_t
{
	/*
	Construct the tag with the raw values.
	- tag0 is for bits 0-31.
	- tag1 is for bits 32-63.
	*/
	IOPDMAtag_t(const u32 tag0, const u32 tag1) :
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
	- Bits 0-23 (length 24): "ADDR" (data memory address).
	- Bits 30 (length 1): "IRQ" (tag interrupt flag).
	- Bits 31 (length 1): "ERT" (tag end transfer flag).
	- Bits 32-55 (length 24): "Length" (transfer amount).
	*/
	u32 getADDR() const
	{
		return static_cast<u32>(mTag0 & 0x00FFFFFF);
	}

	u8 getIRQ() const
	{
		return static_cast<u8>((mTag0 >> 30) & 0x1);
	}

	u8 getERT() const
	{
		return static_cast<u8>((mTag0 >> 31) & 0x1);
	}

	u32 getLength() const
	{
		return static_cast<u32>(mTag1 & 0x00FFFFFF);
	}

#if defined(BUILD_DEBUG)
	void logDebugAllFields() const
	{
		log(Debug, "IOP DMA tag info: Length = 0x%X, IRQ = 0x%X, ERT = 0x%x, ADDR = 0x%X.", getLength(), getIRQ(), getERT(), getADDR());
	}
#endif

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


