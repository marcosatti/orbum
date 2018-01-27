#include <stdexcept>

#include "Resources/Ee/Core/EeCoreTlb.hpp"

int EeCoreTlb::find_tlb_entry_index(const uptr vaddress) const
{
	// Since the VPN can be a number of sizes, we start with the largest page 
	// size of 16 MiB or the most significant 8 bits (which means smallest VPN 
	// number) and search for that. If a match is found, then we get the proper
	// page size from the TLB entry and check to see if the VA is within the 
	// page. If not we continue searching. Note that the TLB entries' VPN are
	// stored as VPN / 2 (aka VPN2), so we need to search by using the same. 
	// This is done as each VPN represents 2 physical pages (named 'even' and 
	// 'odd'). Therefore the LSB of the VPN is ommitted and only 19 bits are
	// used (at most). So for 16 MiB pages, we need to search using the last 7
	// bits.
	uword search_vpn2_msb = (vaddress >> 25); // End up with 7 bits.

	for (int i = 0; i < Constants::EE::EECore::MMU::NUMBER_TLB_ENTRIES; i++)
	{
		const auto& entry = tlb_entries[i];

		// The MSB 7 bits (for 16 MiB comparison) in a tlb entry are at bits 12-18.
		uword vpn2_msb = (entry.vpn2 & Constants::EE::EECore::MMU::MASK_VPN2_FIELD_16MB) >> 12;

		if (search_vpn2_msb == vpn2_msb)
		{
			// A potential match was found. 

			// Check for the scratchpad RAM mapping first. In this case, 
			// MASK will be 0 (indicating page size of 4KB), but the SPRAM 
			// occupies 16KB of continuous space (4 x 4KB pages).
			if (entry.s)
			{
				// If it is the scratchpad entry, the VPN is 20 bits long, with 
				// the LSB 2 bits indicating which 4KB page it is of the 16KB 
				// (0 -> 3). Ie: we need to check the upper 18 bits (bits 31-14)
				// against the upper 18 bits of the TLB VPN2.
				uword search_spr_vpn2 = (vaddress >> 14);
				uword spr_vpn2 = (entry.vpn2 >> 1);
				if (search_spr_vpn2 == spr_vpn2)
				{
					return i;
				}
			}

			// Not a SPR entry - need to now check if the VPN is 
			// actually correct by using the TLB entry mask. It is up to the 
			// callee to check for the ASID and G bits.
			uword vpn2 = (vaddress & entry.mask.tlb_mask) >> 13;
			if (vpn2 == entry.vpn2)
			{
				// A match was found. It is undefined behaviour for there to be
				// 2 entries (MIPS specifications).
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
