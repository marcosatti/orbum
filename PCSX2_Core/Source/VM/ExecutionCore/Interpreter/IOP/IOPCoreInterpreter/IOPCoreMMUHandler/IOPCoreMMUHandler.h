#pragma once

#include "Common/Global/Globals.h"
#include "Common/Interfaces/VMExecutionCoreComponent.h"

#include "PS2Resources/IOP/IOPCore/Types/IOPCoreException_t.h"

class VMMain;

/*
TODO: Requires more work - all code implemented is based of PCSX2's code, which looked like it was the minimum to get it working. Lots of things are left unimplemented and will throw exception, such as a TLB lookup.
IOPCoreMMUHandler implements the IOP Core virtual address -> IOP Core physical address mappings.
This should only be used by the IOP Core (instructions).
Any request performed must be followed by a check for any errors. If an error occured, then the offending instruction must raise the exception.

As there is no TLB implemented on the IOP, all addresses should fall into one of the unmapped regions, such as kseg0 / 1.
According to PCSX2, there is also unmapped regions for accessing the main memory, as well as the BIOS.
See the stage 1 lookup function (it is assumed that this applies to kernel mode only).

If the COP0.Status.IsC bit is switched on, no writes to the main memory (if the VA is within this region) will be performed and it will silently fail, which is how PCSX2 has implemented it.
*/
class IOPCoreMMUHandler : public VMExecutionCoreComponent
{
public:
	explicit IOPCoreMMUHandler(VMMain * vmMain);

	/*
	Public functions for reading or writing to a IOP Core virtual address. Performs the VA translation into the host memory address, and then operates on the value.
	On error, reads will return 0, writes will not happen, and the COP0 MMU context is set automatically.
	The calls to the underlying storage are always done with an IOP context parsed as the parameter.
	TODO: Add in address error exceptions. These will occur when an unaligned access is tried. See for example the instruction LDL on page 72 of the IOP Core Instruction manual.
	*/
	u8 readByte(u32 PS2VirtualAddress);
	void writeByte(u32 PS2VirtualAddress, u8 value);
	u16 readHword(u32 PS2VirtualAddress);
	void writeHword(u32 PS2VirtualAddress, u16 value);
	u32 readWord(u32 PS2VirtualAddress);
	void writeWord(u32 PS2VirtualAddress, u32 value);

	/*
	Exception handling functionality. Because this is used within the IOP Core instructions, there needs to be a way for the exception to propogate.
	An exception could be generated when reading or writing from/to a PS2 memory location.
	A call should be made to hasExceptionOccurred() whenever the MMU is accessed. 
	If that returns true, get the resulting exception through getExceptionInfo(), and queue it.
	*/
	bool hasExceptionOccurred() const;
	const IOPCoreException_t & getException();

private:
	/*
	Exception handling state variables - see above.
	mHasExceptionOccured is set whenever an exception in the MMU occurs, with exception type of mExType.
	*/
	bool mHasExceptionOccurred;
	IOPCoreException_t mException;
	
	/*
	Physical Address lookup state variables - used by the stage functions below to perform a lookup.
	*/
	enum AccessType { READ, WRITE } mAccessType;
	u32	mPS2VirtualAddress;
	u32	mPS2PhysicalAddress;
	u8 mIndexEvenOdd;
	bool mHasISCFailed;
	
	/*
	Returns the physical address from the given virtual address, by using the 4 stage lookup functions below.
	Access type information is needed in order to throw the correct exception if an error occurs (eventually it is handled by one of the PS2 bios exception handler vectors).
	*/
	u32 getPS2PhysicalAddress(u32 PS2VirtualAddress, AccessType accessType);

	/*
	Stage 1 of a physical address lookup. Based of PCSX2 code.
	Stage 1 tests the PS2VirtualAddress against the context of the CPU, to see if the address if valid.
	If running in kernel mode, and a kseg0 or kseg1 address is supplied, the function returns the physical address immediately.
	*/
	void getPS2PhysicalAddress_Stage1();

	/*
	Stage 2 of a physical address lookup. 
	Throws exception as TLB lookup is not implemented (in normal operation this will never be called).
	*/
	void getPS2PhysicalAddress_Stage2();
};

