#pragma once

#include "Common/Global/Globals.h"

#include "Common/Interfaces/VMExecutionCoreComponent.h"
#include "Common/PS2 Resources/EE/EECore/R5900/MMU/MMU_t.h"

class VMMain;

using TLBEntryInformation = MMU_t::TLBEntryInformation;

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
};

