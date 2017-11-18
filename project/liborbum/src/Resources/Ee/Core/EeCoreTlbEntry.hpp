#pragma once

/// EE Core TLB entry, similar to a MIPS TLB entry.
/// A TLB entry is heavily related to the COP0 registers
/// Entry{Hi, Lo0, Lo1}, PageMask and others.
/// See EE Core Users Manual page 120 - 123 about the TLB.
/// For the internal struct array below, index 0 corresponds to the Even
/// infomation, and index 1 correponds to the Odd information.
struct EeCoreTlbEntry
{
	uword mask;
	uword vpn2;
	uword g;
	uword asid;
	uword s;

	struct
	{
		uword pfn;
		uword c;
		uword d;
		uword v;
	} physical_info[2]; // Index 0 = Even, index 1 = Odd.
};