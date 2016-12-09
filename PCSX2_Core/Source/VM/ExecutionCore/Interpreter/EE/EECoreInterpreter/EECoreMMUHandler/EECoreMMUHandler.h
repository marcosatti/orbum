#pragma once

#include "Common/Global/Globals.h"

#include "Common/Interfaces/VMExecutionCoreComponent.h"
#include "PS2Resources/EE/EECore/Types/EECoreException_t.h"

/*
MMUHandler implements the PS2 virtual address -> PS2 physical address mappings (through a TLB), and interfaces with the Physical MMU (which is responsible for 
 converting a PS2 physical address -> host memory address).
It handles any requests from reading or writing from a virtual address.

Any request performed must be followed by a check for any errors (similar to how Linux ERRNO handling works). This is because the PS2's MMU may generate an exception,
 and the instruction must perform differently when an error is raised (it can not automatically enter the exception queue for this reason).
*/

class VMMain;
struct EECoreTLBEntryInfo_t;

class EECoreMMUHandler : public VMExecutionCoreComponent
{
public:
	explicit EECoreMMUHandler(VMMain * vmMain);

	/*
	Public functions for reading or writing to a PS2 virtual address. Performs the VA translation into the host memory address, and then operates on the value.
	This is the main access point that any PS2 reads or writes will come through. On error, read functions will return 0, and write functions will not perform the operation.
	To see what error it is, use getErrorInfo() defined below.
	TODO: Add in address error exceptions. These will occur when an unaligned access is tried. See for example the instruction LDL on page 72 of the EE Core Instruction manual.
	TODO: Produce the proper exception info, such as the TLB index or OS page table address. Not properly done at the moment.
	*/
	u8 readByteU(u32 PS2VirtualAddress);
	void writeByteU(u32 PS2VirtualAddress, u8 value);
	s8 readByteS(u32 PS2VirtualAddress);
	void writeByteS(u32 PS2VirtualAddress, s8 value);
	u16 readHwordU(u32 PS2VirtualAddress);
	void writeHwordU(u32 PS2VirtualAddress, u16 value);
	s16 readHwordS(u32 PS2VirtualAddress);
	void writeHwordS(u32 PS2VirtualAddress, s16 value);
	u32 readWordU(u32 PS2VirtualAddress);
	void writeWordU(u32 PS2VirtualAddress, u32 value);
	s32 readWordS(u32 PS2VirtualAddress);
	void writeWordS(u32 PS2VirtualAddress, s32 value);
	u64 readDwordU(u32 PS2VirtualAddress);
	void writeDwordU(u32 PS2VirtualAddress, u64 value);
	s64 readDwordS(u32 PS2VirtualAddress);
	void writeDwordS(u32 PS2VirtualAddress, s64 value);

	/*
	Exception handling functionality. Because this is used within the EE Core instruction implementations, there needs to be a way for the exception to
	 be thrown (queued) within the instruction body.
	An exception could be generated when reading or writing from/to a PS2 memory location.
	A call should be made to hasExceptionOccurred() whenever the MMU is accessed. If that returns true, get the resulting EECoreException_t through getExceptionInfo(),
	 from which you can queue it from. When the call to getExceptionInfo() is made, it will reset the exception state.
	NOTE 1: getExceptionInfo() may contain data left over from a previous translation, but the exception generated will always have valid data attached to it.
	NOTE 2: On error, no writes or reads will occur - see the description in the read/write functions above on what happens in this case.
	TODO: Check for race condition between using the MMU and checking for error (could produce different error by the time it is called). Need a mutex?
	*/
	bool hasExceptionOccurred() const;
	const EECoreException_t & getExceptionInfo();

private:
	/*
	Exception handling state variables - see hasExceptionOccurred() above.
	mHasExceptionOccured is set whenever an exception in the MMU occurs, with exception type of mExType.
	*/
	bool mHasExceptionOccurred;
	EECoreException_t mExceptionInfo;

	/*
	Physical Address lookup state variables - used by the 4 stage functions below to perform a lookup.
	*/
	enum AccessType { READ, WRITE } mAccessType;
	const EECoreTLBEntryInfo_t *mTLBEntryInfo;
	u32	mPS2VirtualAddress;
	u32	mPS2PhysicalAddress;
	u8 mIndexEvenOdd;

	/*
	Returns the physical address from the given virtual address, by using the 4 stage lookup functions below.
	Access type information is needed in order to throw the correct exception if an error occurs (eventually it is handled by one of the PS2 bios exception handler vectors).
	*/
	u32 getPS2PhysicalAddress(u32 PS2VirtualAddress, AccessType accessType);

	/*
	Stage 1 of a physical address lookup. See diagram on EE Core Users Manual page 122.
	Stage 1 tests the PS2VirtualAddress against the context of the CPU, to see if the address if valid. 
	If running in kernel mode, and a kseg0 or kseg1 address is supplied, the function returns the physical address immediately.
	*/
	void getPS2PhysicalAddress_Stage1();

	/*
	Stage 2 of a physical address lookup. See diagram on EE Core Users Manual page 122.
	Performs the VPN lookup and tests the ASID & G bit.
	Will set mTLBEntryInfo when a match is made for future stages.
	*/
	void getPS2PhysicalAddress_Stage2();
	

	/*
	Stage 3 of a physical address lookup. See diagram on EE Core Users Manual page 122.
	Tests the valid and dirty flags. Also determines if the VPN in PS2VirtualAddress is for the Odd or Even PFN (by testing the MSB of the VPN). 
	*/
	void getPS2PhysicalAddress_Stage3();

	/*
	Stage 4 of a physical address lookup. See diagram on EE Core Users Manual page 122.
	Returns the PS2 Physical Address, based on which memory is accessed (scratchpad, cache or main memory).
	*/
	void getPS2PhysicalAddress_Stage4();
};

