#include <stdexcept>

#include "Resources/Ee/Core/EeCoreTlb.hpp"

int EeCoreTlb::find_tlb_entry_index(const uptr vaddress) const
{
	// Since the VPN can be a number of sizes, we start with the largest page size of 16MB or the most significant 8 bits (which means smallest VPN number) and search for that.
	// If a match is found, then we get the proper page size from the TLB entry and check to see if the VA is within the page. If not we continue searching.
	// Note that the TLB entries' VPN are stored as VPN / 2 (aka VPN2), so we need to search by using the same. This is done as each VPN represents 2 physical pages (named 'even' and 'odd').
	//  Therefore the LSB of the VPN is ommitted and only 19 bits are used at most. I am not 100% sure on the details on this, however. If the above is true, then we need to search using the
	//  last 7 bits.
	uword searchVPN2 = (vaddress >> 25); // End up with 7 bits.
	for (int i = 0; i < Constants::EE::EECore::MMU::NUMBER_TLB_ENTRIES; i++)
	{
		// Even though in a real tlb entry the VPN2 field uses bits 77-95 (length 19), we have stored it in a separate uword type (ie: from bits 0-18).
		// For the MSB 7 bits (for a page size of 16MB), we need to mask out bits 12-18 (length 7), in order to make a comparison.
		const EeCoreTlbEntry & tlbEntry = tlb_entries[i];
		uword tlbMaskedVPN2 = (tlbEntry.vpn2 & Constants::EE::EECore::MMU::MASK_VPN2_FIELD_16MB) >> 12;
		if (searchVPN2 == tlbMaskedVPN2)
		{
			// A potential match was found. Need to now check if the VPN is actually correct by using the TLB entry mask. It is up to the callee to check for the ASID and G bits.
			uword realTlbMask = (~tlbEntry.mask) << 13;
			uword realVPN2 = (vaddress & realTlbMask) >> 13;
			if (realVPN2 == tlbEntry.vpn2)
				return i; // A match was found. I will assume that there will never be 2 entries with the same VPN.
			
			// Need to also check for the scratchpad RAM mapping. In this case, MASK will be 0 (indicating page size of 4KB), but the SPRAM occupies 16KB of continuous space (4 x 4KB pages).
			if (tlbEntry.s)
			{
				// If it is the scratchpad entry, the VPN is 20 bits long, with the LSB 2 bits indicating which 4KB page it is of the 16KB (0 -> 3).
				// Ie: we need to check the upper 18 bits (bits 31-14) against the upper 18 bits of the tlb VPN2 (which is always of length 19 bits).
				uword sprRealVPN2 = (vaddress >> 14);
				uword sprTLBVPN2 = (tlbEntry.vpn2 >> 1);
				if (sprRealVPN2 == sprTLBVPN2)
					return i;
			}
		}
	}

	// No match was found, return -1 for the caller to deal with.
	return -1;
}

const EeCoreTlbEntry & EeCoreTlb::tlb_entry_at(int index) const
{
	return tlb_entries[index];
}

int EeCoreTlb::generate_new_tlb_index()
{
	throw std::runtime_error("New TLB index not implemented.");

// #if defined(BUILD_DEBUG)
// 	log(Debug, "Warning: generate_new_tlb_index() called, but not properly implemented.");
// #endif 

// 	for (auto i = 0; i < Constants::EE::EECore::MMU::NUMBER_TLB_ENTRIES; i++)
// 	{
// 		auto tlbEntry = tlb_entries[i];
// 		if (tlbEntry.mVPN2 == 0)
// 			return i;
// 	}

// 	// No empty spot was found, so return the first index.
// 	// TODO: Create a better algorithm for determining which index to use. See old PCSX2?
// 	return 0;
}

void EeCoreTlb::set_tlb_entry_at(const EeCoreTlbEntry& entry, const int index)
{
	tlb_entries[index] = entry;
}
