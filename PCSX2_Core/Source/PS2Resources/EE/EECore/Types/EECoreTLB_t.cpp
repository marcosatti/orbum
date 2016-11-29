#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "PS2Constants/PS2Constants.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreTLB_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreTLBEntryInfo_t.h"

EECoreTLB_t::EECoreTLB_t(const PS2Resources_t* const PS2Resources) : 
	PS2ResourcesSubobject(PS2Resources),
	mTLBEntries{ 0 }
{
}

s32 EECoreTLB_t::findTLBIndex(u32 PS2VirtualAddress) const
{
	// Since the VPN can be a number of sizes, we start with the largest page size of 16MB or the most significant 8 bits (which means smallest VPN number) and search for that.
	// If a match is found, then we get the proper page size from the TLB entry and check to see if the VA is within the page. If not we continue searching.
	// Note that the TLB entries' VPN are stored as VPN / 2 (aka VPN2), so we need to search by using the same. This is done as each VPN represents 2 physical pages (named 'even' and 'odd').
	//  Therefore the LSB of the VPN is ommitted and only 19 bits are used at most. I am not 100% sure on the details on this, however. If the above is true, then we need to search using the
	//  last 7 bits.
	u32 searchVPN2 = (PS2VirtualAddress >> 25); // End up with 7 bits.
	for (auto i = 0; i < PS2Constants::EE::EECore::MMU::NUMBER_TLB_ENTRIES; i++)
	{
		// Even though in a real tlb entry the VPN2 field uses bits 77-95 (length 19), we have stored it in a separate u32 type (ie: from bits 0-18).
		// For the MSB 7 bits (for a page size of 16MB), we need to mask out bits 12-18 (length 7), in order to make a comparison.
		const EECoreTLBEntryInfo_t & tlbEntry = mTLBEntries[i];
		u32 tlbMaskedVPN2 = (tlbEntry.mVPN2 & PS2Constants::EE::EECore::MMU::MASK_VPN2_FIELD_16MB) >> 12;
		if (searchVPN2 == tlbMaskedVPN2)
		{
			// A potential match was found. Need to now check if the VPN is actually correct by using the TLB entry mask. It is up to the callee to check for the ASID and G bits.
			u32 realTlbMask = (~tlbEntry.mMask) << 13;
			u32 realVPN2 = (PS2VirtualAddress & realTlbMask) >> 13;
			if (realVPN2 == tlbEntry.mVPN2)
				return i; // A match was found. I will assume that there will never be 2 entries with the same VPN.
			
			// Need to also check for the scratchpad RAM mapping. In this case, MASK will be 0 (indicating page size of 4KB), but the SPRAM occupies 16KB of continuous space (4 x 4KB pages).
			if (tlbEntry.mS)
			{
				// If it is the scratchpad entry, the VPN is 20 bits long, with the LSB 2 bits indicating which 4KB page it is of the 16KB (0 -> 3).
				// Ie: we need to check the upper 18 bits (bits 31-14) against the upper 18 bits of the tlb VPN2 (which is always of length 19 bits).
				u32 sprRealVPN2 = (PS2VirtualAddress >> 14);
				u32 sprTLBVPN2 = (tlbEntry.mVPN2 >> 1);
				if (sprRealVPN2 == sprTLBVPN2)
					return i;
			}
		}
	}

	// No match was found, return -1 for the caller to deal with.
	return -1;
}

const EECoreTLBEntryInfo_t & EECoreTLB_t::getTLBEntry(s32 index) const
{
	return mTLBEntries[index];
}

s32 EECoreTLB_t::getNewTLBIndex()
{
	for (auto i = 0; i < PS2Constants::EE::EECore::MMU::NUMBER_TLB_ENTRIES; i++)
	{
		auto tlbEntry = mTLBEntries[i];
		if (tlbEntry.mVPN2 == 0)
			return i;
	}

	// No empty spot was found, so return the first index.
	// TODO: Create a better algorithm for determining which index to use. See old PCSX2.
	return 0;
}

void EECoreTLB_t::setTLBEntry(const EECoreTLBEntryInfo_t& entry, const s32& index)
{
	mTLBEntries[index] = entry;
}
