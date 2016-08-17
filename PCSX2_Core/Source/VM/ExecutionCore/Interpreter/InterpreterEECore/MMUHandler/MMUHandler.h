#pragma once

#include "Common/Global/Globals.h"

#include "Common/Interfaces/VMExecutionCoreComponent.h"
#include "Common/PS2 Constants/PS2Constants.h"

class VMMain;

/*
MMUHandler implements the PS2 virtual address -> PS2 physical address mappings (through a TLB).
*/
class MMUHandler : public VMExecutionCoreComponent
{
public:
	MMUHandler(const VMMain *const vmMain);

	/*
	Convenience functions for reading or writing to a PS2 virtual address. Performs the VA translation into the client memory address, and then operates on the value.
	This is the main access point that any PS2 reads or writes will come through.
	TODO: Add in address error exceptions. These will occur when an unaligned access is tried.
	*/
	u8 readByteU(u32 PS2VirtualAddress) const;
	void writeByteU(u32 PS2VirtualAddress, u8 value) const;
	s8 readByteS(u32 PS2VirtualAddress) const;
	void writeByteS(u32 PS2VirtualAddress, s8 value) const;
	u16 readHwordU(u32 PS2VirtualAddress) const;
	void writeHwordU(u32 PS2VirtualAddress, u16 value) const;
	s16 readHwordS(u32 PS2VirtualAddress) const;
	void writeHwordS(u32 PS2VirtualAddress, s16 value) const;
	u32 readWordU(u32 PS2VirtualAddress) const;
	void writeWordU(u32 PS2VirtualAddress, u32 value) const;
	s32 readWordS(u32 PS2VirtualAddress) const;
	void writeWordS(u32 PS2VirtualAddress, s32 value) const;
	u64 readDwordU(u32 PS2VirtualAddress) const;
	void writeDwordU(u32 PS2VirtualAddress, u64 value) const;
	s64 readDwordS(u32 PS2VirtualAddress) const;
	void writeDwordS(u32 PS2VirtualAddress, s64 value) const;

	/*
	Stage 1 of a physical address lookup. See diagram on EE Core Users Manual page 122.
	Stage 1 tests the PS2VirtualAddress against the context of the CPU, to see if the address if valid. If running in kernel mode, and a kseg0 or kseg1 address is supplied,
	 the function returns the physical address immediately.
	Access type information is needed in order to throw the correct exception if an error occurs (eventually it is handled by one of the PS2 bios exception handler vectors).
	TODO: Implement an Address Error exception. See for example the instruction LDL on page 72 of the EE Core Instruction manual.
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

