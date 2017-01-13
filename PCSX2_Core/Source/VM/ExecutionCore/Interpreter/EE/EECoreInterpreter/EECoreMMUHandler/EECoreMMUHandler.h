#pragma once

#include "Common/Global/Globals.h"
#include "Common/Interfaces/VMExecutionCoreComponent.h"

#include "PS2Resources/EE/EECore/Types/EECoreException_t.h"

class VMMain;
struct EECoreTLBEntryInfo_t;

/*
EECoreMMUHandler implements the EE Core virtual address -> EE Core physical address mappings.
This should only be used by the EE Core (instructions).
Any request performed must be followed by a check for any errors. If an error occured, then the offending instruction must raise the exception.
*/
class EECoreMMUHandler : public VMExecutionCoreComponent
{
public:
	explicit EECoreMMUHandler(VMMain * vmMain);

	/*
	Public functions for reading or writing to a EE Core virtual address. Performs the VA translation into the host memory address, and then operates on the value.
	On error, reads will return 0, writes will not happen, and the COP0 MMU context is set automatically.
	The calls to the underlying storage are always done with an EE context parsed as the parameter.
	TODO: Add in address error exceptions. These will occur when an unaligned access is tried. See for example the instruction LDL on page 72 of the EE Core Instruction manual.
	*/
	u8 readByte(u32 PS2VirtualAddress);
	void writeByte(u32 PS2VirtualAddress, u8 value);
	u16 readHword(u32 PS2VirtualAddress);
	void writeHword(u32 PS2VirtualAddress, u16 value);
	u32 readWord(u32 PS2VirtualAddress);
	void writeWord(u32 PS2VirtualAddress, u32 value);
	u64 readDword(u32 PS2VirtualAddress);
	void writeDword(u32 PS2VirtualAddress, u64 value);
	u128 readQword(u32 PS2VirtualAddress);
	void writeQword(u32 PS2VirtualAddress, u128 value);

	/*
	Exception handling functionality. Because this is used within the EE Core instructions, there needs to be a way for the exception to propogate.
	An exception could be generated when reading or writing from/to a PS2 memory location.
	A call should be made to hasExceptionOccurred() whenever the MMU is accessed. 
	If that returns true, get the resulting exception through getExceptionInfo(), and queue it.
	*/
	bool hasExceptionOccurred() const;
	const EECoreException_t & getException();

private:
	/*
	Exception handling state variables - see hasExceptionOccurred() above.
	*/
	bool mHasExceptionOccurred;
	EECoreException_t mException;

	/*
	Physical Address lookup state variables - used by the stage functions below to perform a lookup.
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

