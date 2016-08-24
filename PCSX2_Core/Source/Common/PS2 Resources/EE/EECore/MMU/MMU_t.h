#pragma once

#include "Common/Global/Globals.h"

#include "Common/PS2 Resources/EE/EECore/R5900/Types/R5900ResourcesSubobject.h"
#include "Common/PS2 Constants/PS2Constants.h"

class MMU_t : public R5900ResourcesSubobject
{
public:
	explicit MMU_t(const PS2Resources_t* const PS2Resources);

	/*
	TLB entry information. Used as the backbone of storing information in the TLB.
	A TLB entry is heavily related to the COP0 registers Entry{Hi, Lo0, Lo1} and PageMask.
	See EE Core Users Manual page 120 - 123 about the TLB.
	*/
	struct TLBEntryInformation
	{
		u32 mMask;
		u32 mVPN2;
		u32 mG;
		u32 mASID;
		u32 mS;
		u32 mPFNOdd;
		u32 mCOdd;
		u32 mDOdd;
		u32 mVOdd;
		u32 mPFNEven;
		u32 mCEven;
		u32 mDEven;
		u32 mVEven;
	};

	/*
	Performs an iterative lookup on the TLB for the given VPN contained in the PS2VirtualAddress.
	A return value of -1 indicates an entry was not found. Any functions that call this may throw a TLB refill exception if an entry was not found (this function doesn't do this automatically).
	*/
	s32 findTLBIndex(u32 PS2VirtualAddress) const; // -1 indicates not found.

	/*
	Gets the TLB entry at the specified index - use findTLBIndex() to make sure it exists first.
	*/
	const TLBEntryInformation & getTLBEntry(s32 index) const;

	/*
	Sets the TLB entry at the specified index.
	*/
	void setTLBEntry(const TLBEntryInformation & entry, const s32 & index);

private:
	/*
	TLB entries. See EE Core Users Manual page 120.
	In total there are 48 entries.
	*/
	TLBEntryInformation mTLBEntries[PS2Constants::EE::EECore::MMU::NUMBER_TLB_ENTRIES];
};

