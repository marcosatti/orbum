#include <stdexcept>
#include <utility>

#include "Resources/Ee/Core/EeCoreTlb.hpp"

EeCoreTlb::EeCoreTlb()
{
}

int EeCoreTlb::find_tlb_entry_index(const uptr vaddress)
{
    // A bit of profile guided optimisation here - try searching the most
    // commonly used areas of the TLB first (follows BIOS mapping).

    // SPR occupies TLB entry 0.
    if (is_match(vaddress, 0))
        return 0;

    // Userspace occupies TLB entries 13 -> 30.
    for (int i = 13; i <= 30; i++)
        if (is_match(vaddress, i))
            return i;

    // Kernel occupies TLB entries 1 -> 12.
    for (int i = 1; i <= 12; i++)
        if (is_match(vaddress, i))
            return i;

    // Extended occupies TLB entries 31 -> 38.
	for (int i = 31; i < 38; i++)
        if (is_match(vaddress, i))
            return i;

    // Others at 38 -> 47.
    for (int i = 38; i < 47; i++)
        if (is_match(vaddress, i))
            return i;

	// No match was found, return -1 for the caller to deal with.
	return -1;
}

const EeCoreTlbEntry & EeCoreTlb::tlb_entry_at(const int index) const
{
	return tlb_entries[index];
}

int EeCoreTlb::generate_new_tlb_index()
{
	throw std::runtime_error("New TLB index not implemented.");
}

bool EeCoreTlb::is_match(const uptr vaddress, const int index) const
{
    const auto& entry = tlb_entries[index];

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
            return true;
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
        return true;
    }

    return false;
}

void EeCoreTlb::set_tlb_entry_at(const EeCoreTlbEntry& entry, const int index)
{
	tlb_entries[index] = entry;
}
