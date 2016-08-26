#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/PS2 Constants/PS2Constants.h"
#include "Common/PS2 Resources/PS2Resources_t.h"
#include "Common/PS2 Resources/EE/EECore/R5900/Types/R5900ResourcesSubobject.h"
#include "Common/PS2 Resources/EE/EECore/MMU/MMU_t.h"

MMU_t::MMU_t(const PS2Resources_t* const PS2Resources) : R5900ResourcesSubobject(PS2Resources) 
{
}

s32 MMU_t::findTLBIndex(u32 PS2VirtualAddress) const
{
	// Since the VPN can be a number of sizes, we start with the largest page size of 16MB or the most significant 8 bits (which means smallest VPN number) and search for that.
	// If a match is found, then we get the proper page size from the TLB entry and check to see if the VA is within the page. If not we continue searching.
	// Note that the TLB entries' VPN are stored as VPN / 2 (aka VPN2), so we need to search by using the same. This is done as each VPN represents 2 physical pages (named 'even' and 'odd').
	//  Therefore the LSB of the VPN is ommitted and only 19 bits are used at most. I am not 100% sure on the details on this, however. If the above is true, then we need to search using the
	//  last 7 bits.
	u32 searchVPN2 = (PS2VirtualAddress >> 25); // End up with 7 bits. Normally this would be ((value >> 24) / 2) but dividing by 2 is exactly the same as shifting it right by 1 (ie: >> 25).
	for (auto i = 0; i < PS2Constants::EE::EECore::MMU::NUMBER_TLB_ENTRIES; i++)
	{
		// Even though in a real tlb entry the VPN2 field uses bits 77-95 (length 19), we have stored it in a separate u32 type (ie: from bits 0-18), so we need to mask out bits 12-18 (length 7).
		auto tlbEntry = mTLBEntries[i];
		u32 tlbMaskedVPN2 = tlbEntry.mVPN2 & PS2Constants::EE::EECore::MMU::MASK_VPN2_FIELD;
		if (searchVPN2 == tlbMaskedVPN2)
		{
			// A potential match was found. Need to now check if the VPN is actually correct by using the TLB entry mask.
			u32 realVPN2 = (PS2VirtualAddress & ~tlbEntry.mMask) / 2;
			if (realVPN2 == tlbEntry.mVPN2)
			{
				// A match was found. I will assume that there will never be 2 entries with the same VPN.
				return i;
			}
		}
	}

	// No match was found, return -1 for the caller to deal with.
	return -1;
}

const MMU_t::TLBEntryInfo& MMU_t::getTLBEntry(s32 index) const
{
	return mTLBEntries[index];
}

s32 MMU_t::getNewTLBIndex()
{
	for (auto i = 0; i < PS2Constants::EE::EECore::MMU::NUMBER_TLB_ENTRIES; i++)
	{
		auto tlbEntry = mTLBEntries[i];
		if (tlbEntry.mVPN2 == 0)
			return i;
	}

	// No empty spot was found, so return the first index.
	return 0;
}

void MMU_t::setTLBEntry(const TLBEntryInfo& entry, const s32& index)
{
	mTLBEntries[index] = entry;
}
