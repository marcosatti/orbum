#pragma once

#include "Common/Constants.hpp"
#include "Common/Types/Primitive.hpp"

#include "Resources/Ee/Core/EeCoreTlbEntry.hpp"

/// Implements the TLB found in the EE Core, similar to a standard MIPS TLB spec.
/// See the EE Core Users Manual, chapter 5.
class EeCoreTlb
{
public:
    EeCoreTlb();

	/// TLB write count, used by the emulator for various tasks
	/// ie: cache coherency checks. Incremented whenever a TLB
	/// entry is written (set_tlb_entry_at).
	size_t write_count;

	/// Performs an iterative lookup on the TLB for the given VPN 
    /// contained in the virtual address. A return value of -1 
    /// indicates an entry was not found. Any functions that call
    /// this may throw a TLB refill exception if n entry was not 
    /// found (this function doesn't do this automatically). The 
    /// process is based on EE Core Users Manual page 120.
	int find_tlb_entry_index(const uptr vaddress);

	/// Gets the TLB entry at the specified index - use 
    /// find_tlb_entry_index() to make sure it exists first.
	const EeCoreTlbEntry & tlb_entry_at(const int index) const;

	/// Copies the TLB entry info to the specified index.
	void set_tlb_entry_at(const EeCoreTlbEntry & entry, const int index);

	/// Gets an index to a new TLB entry position.
	/// This is used whenever a MMU exception error is raised.
	/// See for example EE Users Manual page 101.
	/// TODO: currently not working properly, throws error.
	int generate_new_tlb_index();

private:
	/// TLB entries. See EE Core Users Manual page 120.
	/// In total there are 48 entries.
	EeCoreTlbEntry tlb_entries[Constants::EE::EECore::MMU::NUMBER_TLB_ENTRIES];

    /// Checks whether the given virtual address matches the TLB entry by index.
    bool is_match(const uptr vaddress, const int index) const;
};

