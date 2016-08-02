#pragma once

#include "Common/Global/Globals.h"

#include "VM/Component Interfaces/VMPS2Component.h"
#include "Common/PS2 Constants/PS2Constants.h"

class VMMain;

/*
PS2MMUHandler implements the PS2 virtual address -> PS2 physical address mappings (through a TLB)
*/
class PS2MMUHandler : public VMPS2Component
{
public:
	
	PS2MMUHandler(const VMMain *const vmMain);

	/*
	Stage 1 of a physical address lookup. See diagram on EE Core Users Manual page 122.
	Stage 1 tests the PS2VirtualAddress against the context of the CPU, to see if the address if valid. If running in kernel mode, and a kseg0 or kseg1 address is supplied,
	 the function returns the physical address immediately.
	Access type information is needed in order to throw the correct exception if an error occurs (eventually it is handled by one of the PS2 bios exception handler vectors).
	*/
	enum AccessType {READ, WRITE};
	u32 getPS2PhysicalAddress(const u32 & PS2VirtualAddress, const AccessType & accessType) const; // Convenience function for Stage 1 (looks nicer).
	u32 getPS2PhysicalAddress_Stage1(const u32 & PS2VirtualAddress, const AccessType & accessType) const;

private:
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
	Constants needed to figure out VPN2's etc.
	*/
	static constexpr u32 MASK_VPN2_FIELD = 0x0007F000;

	/*
	TLB entries. See EE Core Users Manual page 120.
	In total there are 48 entries.
	*/
	TLBEntryInformation mTLBEntries[PS2Constants::EE::EECore::MMU::SIZE_TLB_ENTRIES];

	/*
	Stage 2 of a physical address lookup. See diagram on EE Core Users Manual page 122.
	Performs the VPN lookup and tests the ASID & G bit.
	*/
	u32 getPS2PhysicalAddress_Stage2(const u32 & PS2VirtualAddress, const AccessType & accessType) const;

	/*
	Stage 3 of a physical address lookup. See diagram on EE Core Users Manual page 122.
	Tests the valid and dirty flags. Also determines if the VPN in PS2VirtualAddress is for the Odd or Even PFN (by testing the LSB). Calls either the Stage4 Odd or Even functions based on this.
	*/
	u32 getPS2PhysicalAddress_Stage3(const u32 & PS2VirtualAddress, const AccessType & accessType, const TLBEntryInformation & tlbEntry) const;

	/*
	Stage 4 of a physical address lookup. See diagram on EE Core Users Manual page 122.
	Split up into Odd or Even functions, based on the LSB of the VPN from PS2VirtualAddress.
	Returns the PS2 Physical Address, based on which memory is accessed (scratchpad, cache or main memory).
	*/
	u32 getPS2PhysicalAddress_Stage4Odd(const u32 & PS2VirtualAddress, const AccessType & accessType, const TLBEntryInformation & tlbEntry) const;
	u32 getPS2PhysicalAddress_Stage4Even(const u32 & PS2VirtualAddress, const AccessType & accessType, const TLBEntryInformation & tlbEntry) const;

	/*
	Performs an iterative lookup on the TLB for the given VPN contained in the PS2VirtualAddress.
	A return value of -1 indicates an entry was not found. Any functions that call this may throw a TLB refill exception if an entry was not found (this function doesn't do this automatically).
	*/
	s32 getTLBIndex(u32 PS2VirtualAddress) const; // -1 indicates not found.
};

